/* Code originally from Steve Lorimer
https://stackoverflow.com/questions/801740/c-how-to-draw-a-binary-tree-to-the-console
The code was originally in cpp
*/

#include "../include/minishell.h"

t_tree* createNode(char *data) {
    t_tree* newNode = (t_tree*)malloc(sizeof(t_tree));
    if (newNode != NULL) {
        newNode->list->value = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

int maxDepth(t_tree* n) {
    if (n == NULL)
        return 0;
    int leftDepth = maxDepth(n->left);
    int rightDepth = maxDepth(n->right);
    return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
}

void printTree(t_tree* n) {
    if (n == NULL)
        return;

    int depth = maxDepth(n);

    int lastLevel = 0;
    int offset = (1 << depth) - 1;

    // using a queue for breadth-first traversal
    struct Queue {
        t_tree* node;
        int level;
        struct Queue* next;
    } * front = NULL, * rear = NULL;

    struct Queue* newNode = (struct Queue*)malloc(sizeof(struct Queue));
    newNode->node = n;
    newNode->level = lastLevel;
    newNode->next = NULL;
    front = rear = newNode;

    while (front != NULL) {
        t_tree* current = front->node;
        int currentLevel = front->level;

        if (lastLevel != currentLevel) {
            printf("\n");
            lastLevel = currentLevel;
            offset = (1 << (depth - currentLevel)) - 1;
        }

        if (current != NULL) {
            printf(" %*s%s%*s", offset, " ", current->list->value, offset, " ");
            if (current->left != NULL) {
                struct Queue* leftNode = (struct Queue*)malloc(sizeof(struct Queue));
                leftNode->node = current->left;
                leftNode->level = lastLevel + 1;
                leftNode->next = NULL;
                rear->next = leftNode;
                rear = leftNode;
            }
            if (current->right != NULL) {
                struct Queue* rightNode = (struct Queue*)malloc(sizeof(struct Queue));
                rightNode->node = current->right;
                rightNode->level = lastLevel + 1;
                rightNode->next = NULL;
                rear->next = rightNode;
                rear = rightNode;
            }
        }
        struct Queue* temp = front;
        front = front->next;
        free(temp);
    }
    printf("\n");
}

/* int main() {
    
    t_tree* head = createNode(10);
    head->left = createNode(1);
    head->right = createNode(2);
    head->left->left = createNode(3);
    head->left->right = createNode(4);
    head->right->left = createNode(5);
    head->right->right = createNode(6);

    printTree(head);

    return 0;
} */
