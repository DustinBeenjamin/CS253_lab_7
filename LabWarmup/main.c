#include <stdio.h> 
#define MAX_STRING_LENGTH 49

int OutputWithoutWhitespace(char *phrase);
int GetNumOfCharacters(char *phrase);


int main() {


    char phrase[MAX_STRING_LENGTH];
    int length;

    printf("Enter a sentence or a phrase:\n");
    fgets(phrase, MAX_STRING_LENGTH, stdin);

    length = GetNumOfCharacters(phrase);
    printf("You entered: %s", phrase);
    printf("Number of characters: %d\n", length);
    printf("String with no whitespace: ");
    OutputWithoutWhitespace(phrase);

}

int OutputWithoutWhitespace(char *phrase) {
    for (int i = 0; i < MAX_STRING_LENGTH; i++) {
        char c = phrase[i];
        if (c == '\0') {
            printf("\n");
            break;
        }
        else if (c == '\t' || c == ' ' || c == '\n') {
            continue;
        } else {
            printf("%c", phrase[i]);
        }
    }
}

int GetNumOfCharacters(char *phrase) {
    int count = 0;
    for (int i = 0; i < MAX_STRING_LENGTH; i++) {
        if (phrase[i] == '\0') {
            break;
        }
        count++;
    }
    return count;
}
