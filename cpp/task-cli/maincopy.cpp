/* Aden Hilderbrand
 * started 4/10/25
 *
 */

#include <iostream>

struct Task{
    int index;
    char title[20]; 
    char details[20];

};

int main(){
    struct Task task1 = {
        1,
        "Task One",
        "the first task"
    };

    printf("%d, %s, %s\n", task1.index, task1.title, task1.details);

    return 0;
}
