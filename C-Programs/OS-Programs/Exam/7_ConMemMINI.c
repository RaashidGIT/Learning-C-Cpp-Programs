#include <stdio.h>     

int num = 0;           
int len[10];            
int str[10];           
char fid[10];           
char a[20];             

void directory() {
    printf("\nFile\tStart\tLength\n");
    for (int i = 0; i < num; i++)
        printf("%-4c\t%3d\t%6d\n", fid[i], str[i], len[i]);  
}

void display() {
    printf("\nDisk Space:\n");

    for (int i = 0; i < 20; i++)
        printf("%4d", i); 
    printf("\n");

    for (int i = 0; i < 20; i++)
        printf("%4c", a[i]); 

    printf("\n");
}

int main() {
    char id;       
    int st;        
    int nb;         
    int ch;        

    for (int i = 0; i < 20; i++)
        a[i] = '.';

    printf("Disk space before allocation:\n");
    display();

    do {
        printf("\nEnter file name (1 character): ");
        scanf(" %c", &id);  

        printf("Enter the start block: ");
        scanf("%d", &st);

        printf("Enter number of blocks: ");
        scanf("%d", &nb);

        if (st < 0 || st + nb > 20) {
            printf("Requirement exceeds range.\n");
            continue;   
        }

        int flag = 1;  
        for (int i = st; i < st + nb; i++) {
            if (a[i] != '.') {   
                flag = 0;
                break;
            }
        }

        if (!flag) {
            printf("Contiguous allocation not possible.\n");
            continue; 
        }

        fid[num] = id;   
        len[num] = nb;      
        str[num] = st;    

        for (int i = st; i < st + nb; i++)
            a[i] = id;

        printf("Allocation done.\n");
        num++;

        printf("Any more allocation? (1. Yes, 2. No): ");
        scanf("%d", &ch);

    } while (ch == 1); 

    printf("\nContiguous Allocation:\n");
    directory();

    printf("\nDisk space after allocation:\n");
    display();

    return 0;  
}
