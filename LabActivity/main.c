#include <stdio.h>
#define BUFFER_SIZE 256
#define CASE_DIFFERENCE 32 /* Add this number to a char to make it lowercase, subtract it to make it uppercase */

char PrintMenu(char *text);
int FixCapitalization(char *text);
int GetNumOfNonWSCharacters(char *text);
int GetNumOfWords(char *text);
int ShortenSpaces(char *text);
int ReplaceExclamation(char *text);

int main(){

    char buffer[BUFFER_SIZE];

    printf("Enter a sample text:\n");
    fgets(buffer, BUFFER_SIZE - 1, stdin);
    printf("You entered: %s", buffer);

    switch (PrintMenu("fixme")) {
        case 'c':
            printf("Number of non-whitespace characters: %d\n", GetNumOfNonWSCharacters(buffer));
            break;
        case 'w':
            printf("Number of words: %d\n", GetNumOfWords(buffer));
            break;
        case 'f':
            FixCapitalization(buffer);
            printf("Edited text: %s", buffer);
            break;
        case 'r':
            ReplaceExclamation(buffer);
            printf("Edited text: %s", buffer);
            break;
        case 's':
            ShortenSpaces(buffer);
            printf("Edited text: %s", buffer);
            break;
    }
}

char PrintMenu(char *text) {

    int c;

    printf("MENU\n");
    printf("c - Number of non-whitespace characters\n");
    printf("w - Number of words\n");
    printf("f - Fix capitalization\n");
    printf("r - Replace all !'s\n");
    printf("s - Shorten spaces\n");
    printf("q - Quit\n");

    while (c != 'q') {
        printf("Enter an option:\n");
        c = getchar();
        getchar();

        switch (c) {
        case 'c':
        case 'w':
        case 'f':
        case 'r':
        case 's':
            return c;
        default:
            printf("Error: Please select a valid option from the menu above.\n");
        }
    }
}

int GetNumOfNonWSCharacters(char *text) {
    int count = 0;
    char c;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        c = text[i];
        if (c == '\0') {
            return count;
        } else if (c != '\t' && c != '\n'  && c != ' ') {
            count++;
        }
    }
    return -1;
}

int GetNumOfWords(char *text) {
    int count = 0;
    char c;
    int previous_whitespace = 1;
    int current_whitespace;

    for (int i = 0; i < BUFFER_SIZE; i++) {
        c = text[i];
        current_whitespace = (c == '\t' || c == '\n' || c == ' ');
        if (c == '\0') {
            return count;
        }
        else if (current_whitespace && !previous_whitespace) {
            //A transition from whitespace to text (word ended)
            previous_whitespace = 1;
            count++;
        }
        else if (!current_whitespace && previous_whitespace) {
            //A transition from text to whitespace (word began)
            previous_whitespace = 0;
        }
    }

    return count;
}

int FixCapitalization(char *text) {
    //ACSII LOWERCASE RANGE = 97 to 122 inclusive
    //ACSII UPPERCASE RANGE = 65 to 90 inclusive
    char c;
    int previous_punctuation = 1;

    for (int i = 0; i < BUFFER_SIZE; i++) {
        c = text[i];

        if (c == '\0') {
            return 1;
        } else if (previous_punctuation && c <= 122 && c >= 97) {
            //c is a lowercase that should be uppercase
            text[i] = c - 32;
        } else if (!previous_punctuation && c >= 65 && c <= 90) {
            //c is an uppercase letter that should be lowercase. This ignores the idea of proper nouns such as names, etc
            // 33 = !
            // 63 = ?
            // 46 = .
            text[i] = c + 32;
        }

        if (c != ' ' && c != '\n' && c != '\t') {
            //FINDING WHITESPACE DOES NOT CHANGE THE STAUS OF PREVIOUS_PUNCTUATION
            previous_punctuation = (c == 33 || c == 63 || c == 46);
        }
        
    }

}

int ReplaceExclamation(char *text) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (text[i] == '\0') {
            return 1;
        } else if (text[i] == '!') {
            text[i] = '.';
        }
    }
}

int ShortenSpaces(char *text) {
    int previous_space = 0;
    int j = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (text[i] == '\0') {
            text[j] = '\0';
            return 1;
        } else if (previous_space && text[i] == ' ') {
            //DO NOTHING
        } else {
            text[j] = text[i];
            j++;
        }
        previous_space = (text[i] == ' ');
    }
}