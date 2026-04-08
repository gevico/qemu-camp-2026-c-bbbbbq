#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    QueueNode *node = malloc(sizeof(*node));
    node->tree_node = tree_node;
    node->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
}

TreeNode* dequeue(Queue *q) {
    if (is_empty(q)) {
        return NULL;
    }

    QueueNode *node = q->front;
    TreeNode *tree_node = node->tree_node;
    q->front = node->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(node);
    return tree_node;
}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    if (size <= 0 || level_order[0] == INT_MIN) {
        return NULL;
    }

    TreeNode *root = malloc(sizeof(*root));
    root->val = level_order[0];
    root->left = NULL;
    root->right = NULL;

    Queue *q = create_queue();
    enqueue(q, root);

    int idx = 1;
    while (idx < size && !is_empty(q)) {
        TreeNode *parent = dequeue(q);

        if (idx < size && level_order[idx] != INT_MIN) {
            parent->left = malloc(sizeof(*parent->left));
            parent->left->val = level_order[idx];
            parent->left->left = NULL;
            parent->left->right = NULL;
            enqueue(q, parent->left);
        }
        idx++;

        if (idx < size && level_order[idx] != INT_MIN) {
            parent->right = malloc(sizeof(*parent->right));
            parent->right->val = level_order[idx];
            parent->right->left = NULL;
            parent->right->right = NULL;
            enqueue(q, parent->right);
        }
        idx++;
    }

    free_queue(q);
    return root;
}

void preorder_traversal(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void preorder_traversal_iterative(TreeNode *root) {
    TreeNode *stack[256];
    int top = 0;

    if (root == NULL) {
        return;
    }

    stack[top++] = root;
    while (top > 0) {
        TreeNode *node = stack[--top];
        printf("%d ", node->val);

        if (node->right != NULL) {
            stack[top++] = node->right;
        }
        if (node->left != NULL) {
            stack[top++] = node->left;
        }
    }
}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
