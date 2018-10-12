#include <stdio.h>
#include <math.h>
#include <string.h>

char str[255];

char chr[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int val[26] = {1,3,3,2,1,4,2,4,1,8,5,2,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
int i;

int get_score(char* str) {
    int total = 0;
    int i = 0;
    while (*(str)) {
        total += val[*(str) - 97];
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
    for (i = str_length; i >= 0; --i) {
        if (str[i] == '.') {
            str[i] = '\0';
            break;
        }
    }
    return i;
}

int main() {
    int score;
    size_t str_length;
    scanf("%s", str);
    remove_tld(str);
    str_length = strlen(str);
    printf("You entered %s\n", str);
    score = get_score(str);
    printf("The score is %d\n", score);
    printf("The per-letter score is %d\n", score/(int) str_length); 
    printf("The per-letter score is %f\n", score/(float) str_length); 
    printf("%d	%f\n", score, score/(float) str_length);
    return 0;
}
