/*

This code allows you to store and display information about multiple students using a struct in C.

getchar() is often used after scanf() to consume the newline character (\n) that remains in the input buffer when you enter data. 
This is especially relevant when you switch between reading numbers and strings in C.

*/


#include <stdio.h>
#include <string.h>

struct student {
    char name[50], address[100], place[50];
    int pin;
} s[10];

int main() {
    int n, i;
    printf("Enter number of students: ");
    scanf("%d", &n);
    getchar();  // Consume the newline character left after reading the integer

    // Loop to input details of each student
    for (i = 0; i < n; i++) {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Enter name: ");
        // Read name, including spaces, and consume the newline character
        fgets(s[i].name, sizeof(s[i].name), stdin);
        s[i].name[strcspn(s[i].name, "\n")] = '\0'; // Remove trailing newline

        printf("Enter address: ");
        // Read address, including spaces, and consume the newline character
        fgets(s[i].address, sizeof(s[i].address), stdin);
        s[i].address[strcspn(s[i].address, "\n")] = '\0'; // Remove trailing newline

        printf("Enter place: ");
        // Read place, including spaces, and consume the newline character
        fgets(s[i].place, sizeof(s[i].place), stdin);
        s[i].place[strcspn(s[i].place, "\n")] = '\0'; // Remove trailing newline

        printf("Enter pin: ");
        scanf("%d", &s[i].pin);
        getchar();  // Consume the newline character left after reading the integer
    }

    // Output the student details
    printf("\nDisplaying student information:\n");
    for (i = 0; i < n; i++) {
        printf("\nName: %s\nAddress: %s\nPlace: %s\nPin: %d\n",
               s[i].name, s[i].address, s[i].place, s[i].pin);
    }

    return 0;
}

/*

OUTPUT
------------------------------------------------------------------------
Enter number of students: 2

Enter details of student 1
Enter name: John Doe
Enter address: 123 Main St
Enter place: Springfield
Enter pin: 12345

Enter details of student 2
Enter name: Jane Smith
Enter address: 456 Oak Ave
Enter place: Rivertown
Enter pin: 67890


Displaying student information:

Name: John Doe
Address: 123 Main St
Place: Springfield
Pin: 12345

Name: Jane Smith
Address: 456 Oak Ave
Place: Rivertown
Pin: 67890

*/
