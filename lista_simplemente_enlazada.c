#include <stdio.h>
#include <stdlib.h>

// Definición de nodo para la lista enlazada
struct Node {
    int data;
    struct Node* next;
};

// Función para agregar un nuevo nodo al inicio de la lista
void insertAtBeginning(struct Node** head, int newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = *head;
    *head = newNode;
}

// Función para imprimir los elementos de la lista enlazada
void printLinkedList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;  // Inicializamos la lista enlazada vacía

    // Agregamos algunos elementos a la lista
    insertAtBeginning(&head, 10);
    insertAtBeginning(&head, 20);
    insertAtBeginning(&head, 30);

    printf("Lista simplemente enlazada: ");
    printLinkedList(head);

    // Liberar la memoria de los nodos
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
