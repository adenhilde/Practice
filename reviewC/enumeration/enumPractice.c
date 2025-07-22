// enumPractice.c
// Aden Hilderbrand
// 11/22/24

#include <stdio.h>

enum Year {
    FRESHMAN,
    SOPHOMORE,
    JUNIOR,
    SENIOR
};

int main(){
    int i, num_students, sum_students;

    for (i=FRESHMAN;i<=SENIOR;i++){
        printf("How many students are in year %d: ", i + 1);
        scanf("%d", &num_students);
        sum_students += num_students;
        
    }
    
    printf("Total num of students: %d\n", sum_students);

    return 0;
}
