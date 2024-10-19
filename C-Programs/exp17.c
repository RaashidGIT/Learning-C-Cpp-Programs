#include <stdio.h>
#include <string.h> // Include for string manipulation functions

struct student
{
    char name[50];
    char address[100];
    char place[50];
    int pin;
}s[10];

int main()
{
    int n, i;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    getchar(); // To consume the newline character left by scanf

    for(i = 0; i < n; i++)
    {
        printf("\n");
        printf("Enter details of student %d\n", i + 1);

        printf("Enter name: ");
        fgets(s[i].name, sizeof(s[i].name), stdin);
        // Remove trailing newline character if present
        s[i].name[strcspn(s[i].name, "\n")] = '\0';

        printf("Enter address: ");
        fgets(s[i].address, sizeof(s[i].address), stdin);
        s[i].address[strcspn(s[i].address, "\n")] = '\0';

        printf("Enter place: ");
        fgets(s[i].place, sizeof(s[i].place), stdin);
        s[i].place[strcspn(s[i].place, "\n")] = '\0';

        printf("Enter pin: ");
        scanf("%d", &s[i].pin);
        getchar(); // To consume the newline character left by scanf
    }

    printf("\n-------------------------------\n");
    printf("Displaying information\n");    
    printf("\n-------------------------------\n");
    for(i = 0; i < n; i++)
    {
        printf("Name: %s\n", s[i].name);
        printf("Address: %s\n", s[i].address);
        printf("Place: %s\n", s[i].place);
        printf("Pin: %d\n", s[i].pin);
        printf("\n-------------------------------\n");
    }

    return 0;
}

