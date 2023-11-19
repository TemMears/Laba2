#include <stdio.h>
#include <stdlib.h>

typedef struct NodeCBT {
    int value;
    struct NodeCBT* left;
    struct NodeCBT* right;
} NodeCBT;

typedef struct Node_queue {
    NodeCBT* value;
    struct Node_queue* next;
} Node_queue;

void init(Node_queue** head, NodeCBT* data) {
    Node_queue* tmp = (Node_queue*)malloc(sizeof(Node_queue));
    tmp->value = data;
    tmp->next = (*head);
    (*head) = tmp;
}

Node_queue* getLast(Node_queue* head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

void popQueue(Node_queue** head) {
    if (*head == NULL) {
        return;
    }
    Node_queue* prev = *head;
    *head = (*head)->next;
    free(prev);
}

void pushQueue(Node_queue** head, NodeCBT* data) {
    Node_queue* last = getLast(*head);
    Node_queue* tmp = (Node_queue*)malloc(sizeof(Node_queue));
    tmp->value = data;
    tmp->next = NULL;
    if (last == NULL) {
        *head = tmp;
    }
    else {
        last->next = tmp;
    }
}

int getSize(Node_queue* head) {
    int size = 0;
    while (head != NULL) {
        size++;
        head = head->next;
    }
    return size;
}

NodeCBT* getFront(Node_queue* head) { //получить первый элемент в очереди
    if (head == NULL) {
        return NULL;
    }
    return head->value;
}

NodeCBT* createCBT(int data) { //создаём дерево
    NodeCBT* newNode = (NodeCBT*)malloc(sizeof(NodeCBT));
    newNode->value = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

NodeCBT* pushCBT(NodeCBT* Tree, int data) {
    if (Tree == NULL) //если значения нет в корне, то добавляем
        return createCBT(data);
    if (data <= Tree->value)
        Tree->left = pushCBT(Tree->left, data);
    else
        Tree->right = pushCBT(Tree->right, data);
    return Tree;
}

void printTree(struct NodeCBT* root, int level) {
    if (root == NULL) {
        return;
    }
    // Выводим правую ветвь
    printTree(root->right, level + 1);
    // Выводим отступы для текущего уровня
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    // Выводим значение текущего узла
    printf("%d\n", root->value);
    // Выводим левую ветвь
    printTree(root->left, level + 1);
}

void printSnakeTree(struct NodeCBT* root) {
    if (root == NULL) {
        return;
    }
    struct NodeCBT** queue = (struct NodeCBT**)malloc(sizeof(struct NodeCBT*) * 100);
    int front = 0, rear = 0; //перед и конец
    int level = 1;
    queue[rear++] = root;

    while (front < rear) {      //сначала слева направо на одном уровне, затем справа налево на следующем уровне и тд
        if (level % 2 != 0) {
            for (int i = front; i < rear; i++) {
                printf("%d ", queue[i]->value);
            }
        }
        else {
            for (int i = rear - 1; i >= front; i--) {
                printf("%d ", queue[i]->value);
            }
        }
        int size = rear - front;
        for (int i = 0; i < size; i++) {
            struct NodeCBT* current = queue[front++];
            if (current->left != NULL) {
                queue[rear++] = current->left;
            }
            if (current->right != NULL) {
                queue[rear++] = current->right;
            }
        }
        level++;
    }
    free(queue);
    
}

int main() {
    NodeCBT* Tree = NULL;
    Tree = pushCBT(Tree, 4);
    Tree = pushCBT(Tree, 2);
    Tree = pushCBT(Tree, 8);
    Tree = pushCBT(Tree, 1);
    Tree = pushCBT(Tree, 3);
    Tree = pushCBT(Tree, 5);
    Tree = pushCBT(Tree, 9);
    Tree = pushCBT(Tree, 0);
    printf("\n");
    printf("Получаем: ");
    printf("\n");
    printTree(Tree, 0);
    printf("\n");
    printf("Snake tree traversal: ");
    int sizequeue = 0;
    printSnakeTree(Tree);
    printf("\n");
    return 0;
}