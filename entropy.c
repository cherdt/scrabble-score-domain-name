#include <stdio.h>
#include <math.h>
#include <string.h>

int tab[40][40];
float entropy[40][40];

int get_pos(c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 12;
    }
    else if (c >= '0' && c <= '9') {
        return c - '0' + 2;
    }
    else if (c == '-') {
        return 1;
    }
    else if (c == '.') {
        return 39;
    }
    return 0; 
}

int populate_table(int p, int c) {
    return ++tab[get_pos(p)][get_pos(c)];
}

int populate_entropy_row(int row) {
     int c, i, j;
     float sum, val;

     c = 0;
     for (j = 0; j < 40; j++) {
            c += tab[row][j];
     }
     sum = c;
     for (j = 0; j < 40; j++) {
         val = tab[row][j];
         if (sum > 0.0) {
             entropy[row][j] = 1.0 - (val/sum);
         }
         else {
             entropy[row][j] = 1.0;
         }
     }
     return 0;
}

int print_row(int row) {
    int i;
    printf("{");
    for (i = 0; i < 40; i++) {
        printf("%.1f, ", entropy[row][i]);
    }
    printf("}\n");
    return 0;
}

int main(int argc, char *argv[]) {
    int c;
    int p;
    int i;

    c = getchar();
    p = '^';
    while (c != EOF) {
        /* ignore anything after '#' in a line */
        if (c == '#') {
            while (c != '\n') {
                c = getchar();
            }
            c = getchar();
            continue;
        }
        if (c == '\n') {
            c = getchar();
            continue;
        }
        //printf("%i\n", populate_table(p, c));
        populate_table(p, c);
        p = c;
        c = getchar();
    }

    
    for (i = 0; i < 40; i++) {
        populate_entropy_row(i);
    }

    for (i = 0; i < 40; i++) {
        print_row(i);
    }
}
