#include <stdio.h>
#include <string.h>

void reverseString(char str[]) {
    int len = strlen(str);
    printf("Reversed String: ");
    for (int i = len - 1; i >= 0; i--)
        printf("%c", str[i]);
    printf("\n");
}

void processString(char str[], void (*func)(char[])) {
    printf("\nOriginal String: %s\n", str);
    func(str);
}

int main() {
    char text[100];
    printf("Enter a string: ");
    gets(text);

    processString(text, reverseString);

    return 0;
}
