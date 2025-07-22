#include <stdio.h>

int main() {
    int num=5;
    int* ptr =&num;
    printf("num= %d &num= %p\n", num, &num); 
    printf("ptr= %p *ptr= %d\n", ptr, *ptr);    
    return 0;
}
