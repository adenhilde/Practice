#include <stdio.h>

typedef struct stack{
    int stk[5];
    int top; //count
}STACK;

void push (STACK* s){
    int num;
    if ((*s).top == (4)){
        printf ("Stack is Full\n");
        return;
    }
    else {
        printf ("Enter the element to be pushed\n");
        scanf ("%d", &num);
        (*s).top = (*s).top + 1;
        (*s).stk[(*s).top] = num;
    }
    return;
}

void pop (STACK* s){
    
    if ((*s).top == -1){
        printf ("Stack is Empty\n");
    }
    else {
        printf ("popped element is = %d", (*s).stk[(*s).top]);
        (*s).top = (*s).top-1;
    }
}

void display (STACK* s){
    int i;
    if ((*s).top == -1){
        printf("Stack is Empty\n");
    } else {
        printf ("\n The status of the stack is \n");
        for (i = (*s).top; i >= 0; i--) {
            printf ("%d\n", (*s).stk[i]);
        }
    }
    printf ("\n");
}

void main (){
    int choice;
    int option = 1;
    STACK s;
    s.top = -1;
 
    printf ("STACK OPERATION\n");
    while (option)
    {
        printf ("------------------------------------\n");
        printf ("      1    -->    PUSH              \n");
        printf ("      2    -->    POP               \n");
        printf ("      3    -->    DISPLAY           \n");
        printf ("      4    -->    EXIT              \n");
        printf ("------------------------------------\n");
        printf ("Enter your choice\n");
        scanf    ("%d", &choice);
        switch (choice){
        case 1:
            push(&s);
            break;
        case 2:
            pop(&s);
            break;
        case 3:
            display(&s);
            break;
        case 4:
            return;
        }
        //fflush (stdin);
        printf ("\nDo you want to continue(Type 0 or 1)?\n");
        scanf    ("%d", &option);
    }
}
