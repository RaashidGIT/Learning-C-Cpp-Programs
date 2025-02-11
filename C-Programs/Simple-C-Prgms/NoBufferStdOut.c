#include <stdio.h>
int main() {
    setbuf(stdout, NULL); // Disable buffering for stdout
    printf("This text is not buffered and will be immediately displayed.\n");
    printf("This is another line of unbuffered text.\n");
    // ...
    return 0;
}
//In this example, the output from printf calls is not buffered, so each line will be immediately displayed as it is written.