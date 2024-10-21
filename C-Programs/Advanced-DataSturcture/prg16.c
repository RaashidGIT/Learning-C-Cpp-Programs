// Implementation of a Binary Search Tree (BST) with insertion and inorder traversal functionalities.

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node *root = NULL;

struct node *create(struct node *root, int data) {
    struct node *newnode = (struct node *)malloc(sizeof(struct node));
    newnode->data = data;
    if (root == NULL) {
        newnode->left = newnode->right = NULL;
        return newnode;  // Return new node as root
    } else {
        if (root->data < data)
            root->right = create(root->right, data);
        else
            root->left = create(root->left, data);
    }
    return root;
}

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);  // Fixed missing semicolon
        printf("%d\t", root->data);
        inorder(root->right);
    }
}

int main() {  // Changed void main() to int main()
    int ch, data;
    while (1) {
        printf("\n___________BINARY SEARCH TREE MENU__________\n1.Insert\n2.Display\n3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);  // Added & to store input correctly
        switch (ch) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                root = create(root, data);
                break;
            case 2:
                printf("\nThe binary search tree :\n");
                inorder(root);
                printf("\n");
                break;
            case 3:
                exit(0);
            default:
                printf("\nInvalid choice, try again.\n");
        }
    }
    return 0;  // Added return statement for main
}

