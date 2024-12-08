/*

This code allows you to store and display information about multiple students using a struct in C.

getchar() is often used after scanf() to consume the newline character (\n) that remains in the input buffer when you enter data. 
This is especially relevant when you switch between reading numbers and strings in C.

*/


#include <stdio.h>

struct student {
    char name[50], address[100], place[50];
    int pin;
};

int main() {
    int n, i;
    printf("Enter number of students: ");
    scanf("%d", &n);
    getchar(); // Consume newline after scanf

    // Loop to input details of each student
    for(i = 0; i < n; i++) {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Enter name: ");
        scanf("%[^\n]%*c", s[i].name);  // Reads string with spaces

        printf("Enter address: ");
        scanf("%[^\n]%*c", s[i].address);

        printf("Enter place: ");
        scanf("%[^\n]%*c", s[i].place);

        printf("Enter pin: ");
        scanf("%d", &s[i].pin);
    }

    // Output the student details
    printf("\nDisplaying student information:\n");
    for(i = 0; i < n; i++) {
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
