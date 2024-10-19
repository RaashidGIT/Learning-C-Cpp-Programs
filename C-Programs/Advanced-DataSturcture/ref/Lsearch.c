// modified code including error handling

#include <stdio.h>
#include <stdlib.h>  // Required for exception checking
int main()
{
   int array[100], search, c, n, count = 0;
   
   printf("Enter number of elements in array\n");
   if (scanf("%d", &n) != 1) {
      printf("Invalid input. Please enter an integer.\n");
      exit(EXIT_FAILURE);
   }
   
   printf("Enter %d numbers\n", n);
   
   for (c = 0; c < n; c++) {
      if (scanf("%d", &array[c]) != 1) {
         printf("Invalid input. Please enter an integer.\n");
         exit(EXIT_FAILURE);
      }
   }
     
   printf("Enter a number to search\n");
   if (scanf("%d", &search) != 1) {
      printf("Invalid input. Please enter an integer.\n");
      exit(EXIT_FAILURE);
   }
   
   for (c = 0; c < n; c++) {
      if (array[c] == search) {
         printf("%d is present at location %d.\n", search, c+1);
         count++;
      }
   }
   
   if (count == 0)
      printf("%d isn't present in the array.\n", search);
   else
      printf("%d is present %d times in the array.\n", search, count);
     
   return 0;
}

