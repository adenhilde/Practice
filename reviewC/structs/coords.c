// coords.c
// Joshua Wilkerson
// Aden Hilderbrand

#include <stdio.h>
#include <stdlib.h>

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Rectangle {
    Point corner1;
    Point corner2;

} Rectangle;

int calcPerimeter(Rectangle r){
    int perimeter=0;
    int l,w;
// calculate perimeter
    l = abs(r.corner1.y) + abs(r.corner2.y);
    w = abs(r.corner1.x) + abs(r.corner2.x);
    
    perimeter = (l * 2) + (w * 2);

    return perimeter;
}

int calcAreabyRef(Rectangle* r){
    int area=0;
// calculate area
    int l,w;

    l = abs(r->corner1.y) + abs(r->corner2.y);
    w = abs(r->corner1.x) + abs(r->corner2.x);

    area = l * w;

    return area;
}

int main(){
    Rectangle rect; 
   
    printf("Enter the corner 1 (x and y coords): ");
    scanf("%d %d", &rect.corner1.x, &rect.corner1.y); 
    
    printf("Enter the corner 2 (x and y coords): ");
    scanf("%d %d", &rect.corner2.x, &rect.corner2.y);

    printf("Corners are: (%d, %d), (%d, %d)\n", rect.corner1.x, rect.corner1.y, rect.corner2.x, rect.corner2.y);

    printf("Perimeter is: %d\n", calcPerimeter(rect));    
    printf("Area by ref is: %d\n", calcAreabyRef(&rect));
    return 0;
}
