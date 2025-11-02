#include <stdio.h>      //Soooooo, this one got me good. Took way more time than it should've 

void push(int stack[], int *top, int max_size);
void pop(int stack[], int *top);
void peek(int stack[], int top);
void display(int stack[], int top);


void push(int stack[], int *top, int max_size) 
{
    int element;
    
    if(*top >= max_size - 1) 
    {
        printf("Stack overflow! cannot push element.\n");
        return;
    }
    
    printf("please enter element to push: ");
    scanf("%d", &element);
    
    *top = *top + 1;
    stack[*top] = element;
    
    printf("element %d pushed successfully!\n", element);
}

void pop(int stack[], int *top) 
{
    int element;
    
    if(*top == -1)
    {
        printf("Stack underflow! stack is empty.\n");
        return;
    }
    
    element = stack[*top];
    *top = *top - 1;
    
    printf("element %d popped successfully!\n", element);
}

void peek(int stack[], int top) 
{
    if(top == -1) 
    {
        printf("stack is empty! no element to peek.\n");
        return;
    }
    
    printf("top element: %d\n", stack[top]);
}

void display(int stack[], int top)
{
    int i;
    
    if(top == -1)
    {
        printf("stack is empty!\n");
        return;
    }
    
    printf("\n==== Stack Contents ====\n");
    printf("elements (from top to bottom):\n");
    
    for(i = top; i >= 0; i--) 
    {
        printf("| %d |\n", stack[i]);
    }
    
    printf("\ntotal elements in stack: %d\n", top + 1);
}

int main() 
{
    int stack[100];
    int top = -1;
    int max_size = 100;
    int choice;
    
    while(1) 
    {
        printf("\n===== STACK OPERATIONS =====\n");
        printf("\n1) PUSH - insert an element\n");
        printf("2) POP - remove top element\n");
        printf("3) PEEK - display top element\n");
        printf("4) DISPLAY - show all elements\n");
        printf("5) EXIT - terminate the program\n");
        printf("\nplease enter your choice: ");
        scanf("%d", &choice);
        
        if(choice == 1)
        {
            push(stack, &top, max_size);
        }

        else if(choice == 2) 
        {
            pop(stack, &top);
        }

        else if(choice==3) 
        {
            peek(stack, top);
        }

        else if(choice == 4) 
        {
            display(stack, top);
        }

        else if(choice == 5)
        {
            printf("Exiting software......\n");
            break;
        }

        else 
        {
            printf("Incorrect choice! please try again.\n");
        }
    }
    
    return 0;
}