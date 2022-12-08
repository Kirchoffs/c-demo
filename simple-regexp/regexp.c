#include <stdio.h>

int match_from_here(char* regexp, char* text);
int match_star(char c, char* regexp, char* text);

int match(char* regexp, char* text) {
    if (regexp[0] == '^') {
        return match_from_here(regexp + 1, text);
    }

    do {
        if (match_from_here(regexp, text)) {
            return 1;
        }
    } while (*text++ != '\0');

    return 0;
}

int match_from_here(char* regexp, char* text) {
    if (regexp[0] == '\0') {
        return 1;
    }

    if (regexp[1] == '*') {
        return match_star(regexp[0], regexp + 2, text);
    }

    if (regexp[0] == '$' && regexp[1] == '\0') {
        return *text == '\0';
    }

    if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text)) {
        return match_from_here(regexp + 1, text + 1);
    }
    
    return 0;
}

int match_star(char c, char* regexp, char* text) {
    // do {
    //     if (match_from_here(regexp, text)) {
    //         return 1;
    //     }
    // } while (*text != '\0' && (*text++ == c || c == '.'));

    char* tmp = text;
    for (; *tmp != '\0' && (*tmp == c || c == '.'); tmp++);

    do {
        if (match_from_here(regexp, tmp)) {
            return 1;
        }
    } while (tmp-- != text);

    return 0;
}

int main() {
    char* regexp = "a*b";
    char* text = "aaab";
    printf("%d\n", match(regexp, text));
    return 0;
}
