/*

This program is designed to count the number of occurrences of a given substring within a larger string.

"%99[^\n]" reads at most 99 characters from the input stream until it encounters a newline character.

*/


#include <stdio.h>
#include <string.h>

int main() {
    char str[100], sub[100]; // Declare character arrays to store the main string and the substring
    int count = 0;          // Initialize a counter for the number of occurrences

    printf("Enter a string: ");
    scanf("%99[^\n]", str); // Read the main string from the user with input size limit

    printf("Enter a substring: ");
    scanf(" %99[^\n]", sub); // Read the substring, consuming the newline from previous input

    // Iterate through the main string, checking for substring occurrences
    for (int i = 0; i <= strlen(str) - strlen(sub); i++) { 
        if (strncmp(&str[i], sub, strlen(sub)) == 0) { // Compare current substring with the input substring
            count++; // Increment the counter if a match is found
        }
    }

    printf("%s occurs %d times in %s\n", sub, count, str); // Print the result

    return 0;
}

/*

OUTPUT
---------------------------------------------------------
Enter a string: This is a test string
Enter a substring: is

is occurs 2 times in This is a test string

--------------------------------------------------------------------------------
Break down of strncmp(&str[i], sub, strlen(sub)):
--------------------------------------------------------------------------------

strncmp(): This is a standard library function in C that compares two strings.

It takes three arguments:

const char *s1: The first string to compare.
const char *s2: The second string to compare.
size_t n: The maximum number of characters to compare.
strncmp() compares the first n characters of s1 and s2.

It returns:

0: If the first n characters of both strings are equal.
< 0: If s1 is less than s2 lexicographically.
> 0: If s1 is greater than s2 lexicographically.
&str[i]: This expression provides a pointer to the character at index i within the string str.

str is the original string.
str[i] accesses the character at position i in the string.
&str[i] gives the memory address of that character, effectively creating a pointer to the substring starting at that position.
sub: This is the substring we are searching for within the main string str.

strlen(sub): This function calculates the length of the substring sub.

In the context of the code:

strncmp(&str[i], sub, strlen(sub)) == 0

This line checks if the substring starting at index i in the main string str matches the given substring sub for the length of sub. 
If they match, strncmp() returns 0, indicating that the substring is found.

*/
