#include <stdio.h>
#include <math.h>
#include <string.h>

char line[255];
size_t n = 255;
int length;
int score;
int dots;
int val[26] = {1,3,3,2,1,4,2,4,1,8,5,2,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

float div_ints(int n, int m) {
    float f1 = n;
    float f2 = m;
    return f1/f2;
}

int get_dots(int c) {
    if (c == '.') {
        return 1;
    }
    return 0;
}

int get_score(int c) {
    if (c >= 'a' && c <= 'z') {
        return val[c - 'a'];
    }
    if (c != '.') {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int c;

    length = 0;
    score = 0;
    dots = 0;
    c = getchar();
    while (c != EOF) {
        /* ignore lines starting with '#' */
        if (c == '#' && length == 0) {
            while (c != '\n') {
                c = getchar();
            }
            c = getchar();
            continue;
        }

        /* if we're at the end of a line, print summary data */
        if (c == '\n') {
            printf("\t%i\t%i\t%.1f", score, length, div_ints(score, length - dots));
            length = 0;
            score = 0;
            dots = 0;
        }

        /* otherwise, continue processing string */
        else {
            length++;
            score += get_score(c);
            dots += get_dots(c);
        }
        printf("%c", c);
        c = getchar();
    }
}
