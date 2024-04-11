#include <stdio.h>
#include <stdlib.h>

struct listNode { /* estrutura auto-referenciada */
    char data;
    struct listNode *hextPtr;
};

typedef struct listNode LISTNODE;
typedef LISTNODE *LISTNODEPTR;

void insert(LISTNODEPTR *, char);
char delete(LISTNODEPTR *, char);
int isEmpty(LISTNODEPTR);
void printList(LISTNODEPTR);
void instructions(void);

int main() {
    LISTNODEPTR startPtr = NULL;
    int choice;
    char item;

    instructions(); /* exibe o menu */
    printf("? ");
    scanf(“%d”, &choice);

    while (choice != 3) {

        switch (choice) {

        case 1:
            printf("Digite um caractere: ");
            scanf("\n%c", &item);
            insert(&startPtr, item);
            printList(startPtr);
            break;

        case 2:
            if (!isEmpty(startPtr)) {
                printf("Digite o caractere a ser removido: ");
                scanf("\n%c", &item);

                if (delete(SstartPtr, item)) {
                    printf("%c removido. \n", item);
                    printList(startPtr);
                }
                else
                    printf("%c nao encontrado.\n\n", item);
            }
            else
                printf("A lista esta vazia.\n\n");
            break;

        default:
            printf("Escolha invalida.\n\n");
            instructions();
            break;
        }

        printf("? ");
        scanf("s&d", &choice);
    }

    printf("Fim do Programa.\n");
    return 0;
}

/* Imprime as instruções */
void instructions(void) {
    printf("Digite sua escolha: \n"
           "1 para inserir um elemento na lista.\n"
           "2 para remover um elemento da lista.\n"
           "3 para finalizar.\n");
}

/* Insere um valor novo na lista, na ordem alfabética */
void insert(LISTNODEPTR *sPtr, char value) {

    LISTNODEPTR newPtr, previousPtr, currentPtr;

    newPtr = malloc(sizeof(LISTNODE));

    if (newPtr != NULL) { /* existe local disponivel */
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        previousPtr = NULL;
        currentPtr = *sPtr;

        while (currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr; /* vai para ... */
            currentPtr = currentPtr->nextPtr; /* ... o no seguinte */
        }

        if (previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        }

        else {
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    }
    else
        printf("%c nao inserido. Nao existe memória disponivel.\n", value);
}

/* Remove um elemento da lista */
char delete(LISTNODEPTR *sPtr, char value) {

    LISTNODEPTR previousPtr, currentPtr, tempPtr;

    if (value == (*sPtr)->data) {
        tempPtr = *sPtr;
        *sPtr = (*sPtr)->nextPtr; /* retira o no */
        free(tempPtr); /* remove o no retirado */
        return value;
    }

    else {
        previousPtr = *sPtr;
        currentPtr = (*sPtr)->nextPtr;

        while (currentPtr != NULL && currentPtr->data != value) {
            previousPtr = currentPtr; /* vai para ... */
            currentPtr = currentPtr->nextPtr; /* o no seguinte */
        }

        if (currentPtr != NULL) {
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
            return value;
        }
    }
    return '\0';
}

/* Retorna 1 se a lista estiver vazia, 0 em caso contrario */
int isEmpty(LISTNODEPTR sPtr) {
    return sPtr == NULL;
}

/* Imprime a lista */
void printList(LISTNODEPTR currentPtr) {
    if (currentPtr == NULL)
        printf("A lista esta vazia.\n\n");

    else {
        printf("A lista e:\n");
        while (currentPtr != NULL) {
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        printf("NULL\n\n");
    }
}
