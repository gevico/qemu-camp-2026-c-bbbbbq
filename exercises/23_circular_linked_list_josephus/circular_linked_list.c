#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    Node *head = NULL;
    Node *tail = NULL;

    for (int i = 1; i <= n; i++) {
        Node *node = malloc(sizeof(*node));
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        node->id = i;
        node->next = NULL;

        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }

    if (tail != NULL) {
        tail->next = head;
    }

    return head;
}

void free_list(Node* head) {
    if (head == NULL) {
        return;
    }

    Node *current = head->next;
    while (current != NULL && current != head) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    free(head);
}
