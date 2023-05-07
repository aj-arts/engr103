#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

int main(){
    Point p1;
    p1 = {1, 2};
    printf("%d\n", p1.x);
    printf("%d\n", p1.y);
    return 0;
}