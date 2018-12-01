#include <stdio.h>
#include <math.h>
#include <string.h>

char line[255];
size_t n = 255;
int length;
int score;
int dots;
int val[26] = {1,3,3,2,1,4,2,4,1,8,5,2,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

/* 
well this is ugly
hard-coded
and off by one (there is nothing at index 38 I think)
*/
float entropy[40][40] = {
{0.2, 1.0, 1.0, 1.0, 0.6, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.6, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
{1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 1.0, 1.0, 0.9, 0.9, 0.9, 0.9, 0.9, 1.0, 0.9, 0.8, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
{1.0, 1.0, 0.7, 0.8, 0.9, 0.9, 1.0, 0.9, 1.0, 0.9, 0.9, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.7},
{1.0, 1.0, 0.8, 0.9, 0.8, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.7},
{1.0, 1.0, 0.7, 0.9, 0.9, 0.9, 0.7, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.7},
{1.0, 1.0, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.8, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.6},
{1.0, 1.0, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 1.0, 0.9, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.6},
{1.0, 1.0, 0.8, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.6},
{1.0, 1.0, 0.8, 0.9, 0.9, 0.9, 0.9, 0.8, 0.8, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.6},
{1.0, 1.0, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.8, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
{1.0, 1.0, 0.8, 0.9, 1.0, 1.0, 1.0, 0.9, 0.9, 1.0, 0.7, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
{1.0, 1.0, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.9, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.6},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 0.9, 1.0, 1.0, 0.9, 1.0, 0.9, 1.0, 1.0, 0.8, 0.9, 0.7, 1.0, 0.9, 1.0, 0.8, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.7, 1.0, 1.0, 1.0, 0.7, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 0.9, 1.0, 1.0, 0.8, 1.0, 1.0, 0.8, 0.9, 1.0, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 0.9, 0.9, 1.0, 1.0, 0.9, 1.0, 0.9, 0.2, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 0.6, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 0.9, 0.9, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 0.9, 0.8, 1.0, 1.0, 1.0, 0.7, 0.8, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 0.8, 0.9, 1.0, 1.0, 0.7, 1.0, 1.0, 0.9, 1.0, 1.0, 0.7, 1.0, 1.0, 0.8, 1.0, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 0.9, 1.0, 0.8, 1.0, 1.0, 0.9, 0.9, 1.0, 1.0, 0.9, 1.0, 0.9, 0.8, 1.0, 1.0, 0.8, 0.9, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.7, 1.0, 1.0, 1.0, 0.6, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 0.7, 1.0, 1.0, 1.0, 1.0, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 0.8, 0.9, 0.9, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 0.9, 0.9, 0.6, 0.9, 1.0, 1.0, 0.9, 0.9, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 0.6, 1.0, 1.0, 0.9, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 0.9, 1.0, 0.7, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 0.9, 1.0, 1.0, 0.9, 1.0, 1.0, 0.9, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 0.9, 0.7, 1.0, 1.0, 1.0, 0.7, 1.0, 1.0, 0.9, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 0.9, 0.9, 0.9, 0.8, 1.0, 0.9, 1.0, 0.9, 1.0, 1.0, 1.0, 0.9, 1.0, 0.9, 0.9, 1.0, 1.0, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 0.9, 0.9, 0.7, 0.9, 0.8, 1.0, 0.9, 1.0, 1.0, 0.9, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 0.9, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 0.4, 0.8, 1.0, 1.0, 1.0, 0.8, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 0.9, 0.9, 1.0, 1.0, 0.8, 1.0, 1.0, 0.8, 0.9, 1.0, 0.8, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 0.4, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 0.8, 1.0, 0.8, 1.0, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 0.9, 0.9, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 0.9, 1.0, 0.8, 1.0, 1.0, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 0.9, 1.0, 1.0, 0.9, 0.7, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.6},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 0.9, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 0.9, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 0.8},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 0.9, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 0.9, 1.0, 0.9, 0.9, 0.9, 0.8, 1.0, 0.9, 1.0, 0.8, 0.8, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 0.6, 1.0, 1.0, 1.0, 1.0, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.8},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.7, 1.0, 1.0, 1.0, 0.7, 1.0, 1.0, 0.9, 0.8, 1.0, 1.0, 1.0, 1.0, 0.9, 0.8, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 0.9, 1.0, 0.9, 1.0, 1.0, 1.0, 0.8, 1.0, 1.0, 1.0, 1.0, 0.8, 1.0, 0.9, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 0.9, 0.9, 1.0, 1.0, 0.6},
{1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 0.9, 0.9, 0.9, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 0.9, 0.9, 0.9, 0.9, 1.0, 1.0, 0.8, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.6},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.7, 1.0, 0.9, 1.0, 0.8, 1.0, 1.0, 0.9, 0.8, 1.0, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 0.9, 1.0, 0.9, 1.0, 1.0, 1.0, 0.9, 0.9, 1.0, 0.8},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.2, 0.9, 1.0, 1.0, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 0.9, 0.9, 1.0, 1.0, 0.9, 1.0, 1.0, 0.9, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0}
};

/* ^,-,0...9,a...z,. */
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

int is_letter(c) {
    return (c >= 'a' && c<= 'z');
}

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

float get_entropy_score(int current, int previous) {
    int current_index;
    int previous_index;

    current_index = get_pos(current);
    previous_index = get_pos(previous);

    if (current_index >= 0 && current_index < 40 && previous_index >= 0 && previous_index < 40) {
        return entropy[previous_index][current_index];
    }
    return 1.0;
}

int main(int argc, char *argv[]) {
    int c;
    int i;
    int p = '^';
    int alpha_counts[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    printf("DOMAIN\tSCORE\tLENGTH\tSPL\tENTROPY\tEPL\tJ\tQ\tX\tZ\n");

    length = 0;
    score = 0;
    float entropy_score = 0.0;
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
            printf("\t%i\t%i\t%.1f\t%.1f\t%.3f\t%i\t%i\t%i\t%i", score, length, div_ints(score, length - dots), entropy_score, entropy_score/length, alpha_counts['j'-'a'], alpha_counts['q'-'a'], alpha_counts['x'-'a'], alpha_counts['z'-'a']);
            p = '^';
            length = 0;
            score = 0;
            entropy_score = 0;
            dots = 0;
            for (i = 0; i <= 'z' - 'a'; i++) {
                alpha_counts[i] = 0;
            }
        }

        /* otherwise, continue processing string */
        else {
            length++;
            score += get_score(c);
            entropy_score += get_entropy_score(p,c);
            dots += get_dots(c);
            if (is_letter(c)) {
                alpha_counts[c - 'a']++;
            }
            p = c;
        }
        printf("%c", c);
        c = getchar();
    }

}
