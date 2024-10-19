#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *head = NULL;

struct node *create(int num) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = num;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void insert(struct node **nod, int num) {
    if (!*nod) {
        *nod = create(num);
    } else if (num < (*nod)->data) {
        insert(&(*nod)->left, num);
    } else {
        insert(&(*nod)->right, num);
    }
}

void postorder(struct node *nod) {
    if (nod) {
        postorder(nod->left);
        postorder(nod->right);
        printf("%d ", nod->data);
    }
}

void inorder(struct node *nod) {
    if (nod) {
        inorder(nod->left);
        printf("%d ", nod->data);
        inorder(nod->right);
    }
}

void preorder(struct node *nod) {
    if (nod) {
        printf("%d ", nod->data);
        preorder(nod->left);
        preorder(nod->right);
    }
}

int main() {
    int ch, num;
    while (1) {
        printf("Enter choice\n1. Insert\n2. Inorder\n3. Postorder\n4. Preorder\n5. Exit\n: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &num);
                insert(&head, num);
                break;
            case 2:
                printf("Inorder: ");
                inorder(head);
                printf("\n");
                break;
            case 3:
                printf("Postorder: ");
                postorder(head);
                printf("\n");
                break;
            case 4:
                printf("Preorder: ");
                preorder(head);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("\nInvalid choice!\n");
        }
    }
    return 0;
}

