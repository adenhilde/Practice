/* Aden Hilderbrand
 * started 4/10/25
 *
 */

#include <iostream>

using std::cin;
using std::cout;
using std::string;

struct Task{
    int index;
    string title; 
    string details;

};

int main(){
    struct Task task1 = {
        1,
        "Task One",
        "the first task"
    };

    cout << task1.index << ", " << task1.title << ", " << task1.details << "\n";

    return 0;
}
