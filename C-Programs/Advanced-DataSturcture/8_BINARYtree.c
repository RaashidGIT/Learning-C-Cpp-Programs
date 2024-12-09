/*

This C program implements a Binary Search Tree (BST) with three common traversal methods: Inorder, Preorder, and Postorder. 
The users can insert elements and display the tree using these traversal methods through a menu-driven interface.

        40            Inorder: 10 20 30 40 50 60 70
       /  \
     20   60          Preorder: 40 20 10 30 60 50 70
    / \   / \
   10 30 50 70        Postorder: 10 30 20 50 70 60 40


*/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;             // Holds the value of the node
    struct node *left;    // Pointer to the left child
    struct node *right;   // Pointer to the right child
};

struct node *head = NULL;

struct node *create(int num) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = num;
    new_node->left = NULL;    // Initialize left child as NULL
    new_node->right = NULL;   // Initialize right child as NULL
    return new_node;
}

void insert(struct node **nod, int num) { // struct node **nod, the function works with the original pointer, 
                                          // allowing modifications to persist outside the function.
    if (!*nod) {   // If current node is NULL
        *nod = create(num);   // Create a new node
    } else if (num < (*nod)->data) {
        insert(&(*nod)->left, num);  // Insert in the left subtree
    } else {
        insert(&(*nod)->right, num); // Insert in the right subtree
    }
}

void postorder(struct node *nod) {
    if (nod) {
        postorder(nod->left);    // Visit left child
        postorder(nod->right);   // Visit right child
        printf("%d ", nod->data); // Print current node
    }
}

void inorder(struct node *nod) {
    if (nod) {
        inorder(nod->left);      // Visit left child
        printf("%d ", nod->data); // Print current node
        inorder(nod->right);     // Visit right child
    }
}

void preorder(struct node *nod) {
    if (nod) {
        printf("%d ", nod->data); // Print current node
        preorder(nod->left);      // Visit left child
        preorder(nod->right);     // Visit right child
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
                insert(&head, num);   // Call insert function
                break;
            case 2:
                printf("Inorder: ");
                inorder(head);   // Call inorder traversal
                printf("\n");
                break;
            case 3:
                printf("Postorder: ");
                postorder(head);  // Call postorder traversal
                printf("\n");
                break;
            case 4:
                printf("Preorder: ");
                preorder(head);   // Call preorder traversal
                printf("\n");
                break;
            case 5:
                exit(0);   // Exit the program
            default:
                printf("\nInvalid choice!\n");
        }
    }
    return 0;
}

/*

Enter choice
1. Insert
2. Inorder
3. Postorder
4. Preorder
5. Exit
: 1
Enter element to insert: 50

Enter choice
1. Insert
2. Inorder
3. Postorder
4. Preorder
5. Exit
: 1
Enter element to insert: 30

Enter choice
1. Insert
2. Inorder
3. Postorder
4. Preorder
5. Exit
: 1
Enter element to insert: 70

Enter choice
1. Insert
2. Inorder
3. Postorder
4. Preorder
5. Exit
: 2
Inorder: 30 50 70 

Enter choice
1. Insert
2. Inorder
3. Postorder
4. Preorder
5. Exit
: 3
Postorder: 30 70 50 

Enter choice
1. Insert
2. Inorder
3. Postorder
4. Preorder
5. Exit
: 4
Preorder: 50 30 70 

*/
