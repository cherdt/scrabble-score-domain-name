#include <stdio.h>
#include <math.h>
#include <string.h>

char* str;

char chr[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int val[26] = {1,3,3,2,1,4,2,4,1,8,5,2,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
int i;

// Gets the count of a-z characters in the string
// and - an 0-9
int get_length(char* str) {
    int count = 0;
    char** temp = &str;
    while (*(str)) {
        if ((*(str) >= 'a' && *(str) <= 'z') || (*(str) >= '-' && *(str) <= '9')) {
            count++;
        }
        str++;
    }
    str = *temp;
    return count;
}

int get_score(char* str) {
    int total = 0;
    while (*(str)) {
        // lowercase a-z only
        if (*(str) >= 'a' && *(str) <= 'z') {
            total += val[*(str) - 97];
        }
        // 0-9 and hyphens, count as 1?
        if (*(str) >= '-' && *(str) <= '9') {
            total += 1;
        }
        str++;
    }
    return total;
}

// This function loops over the characters of a string backwards
// and chops off characters after (and including) the last period
// by setting the character at the last period to null
int remove_tld(char* str) {
    size_t str_length = strlen(str);
    int i;
    // start 3 from the end, this will skip over country codes
    // like .uk and also catch .com/.net/.org in fewer loops
    for (i = str_length - 4; i >= 0; --i) {
        if (str[i] == '.') {
            str[i] = '\0';
            break;
        }
    }
    return i;
}

int main(int argc, char *argv[]) {
    int score;
    int length;
    char input_str[255];
    size_t str_length;
    if (argc < 2 ) {
        scanf("%s", input_str);
        str = input_str;
    } else {
        str = argv[1];
    }
    remove_tld(str);
    length = get_length(str);
    //printf("String length: %d\n", length);
    //printf("You entered %s\n", str);
    score = get_score(str);
    //printf("The score is %d\n", score);
    //printf("The per-letter score is %d\n", score/(int) length); 
    //printf("The per-letter score is %f\n", score/(float) length); 
    printf("%s\t%d\t%d\t%f\n", str, length, score, score/(float) length);
    return 0;
}
