#include <stdio.h>      // Greetings! I assume this is Sir TA the great, good day to you!
#include <string.h>     // Here is my attempt at Q1, i hope you enjoy! :)

int isbns[100][50];
char book_title[100][50];
float book_price[100];
int book_quantity[100];
int book_count = 0;

void book_registration();
void sale_processing();
void low_stock_report();


void book_registration() 
{
    int i, j;
    int duplicate = 0;
    char isbn_input[100];
    int isbn_length;
    
    if(book_count >= 100) 
    {
        printf("Error! Inventory is full!\n");
        return;
    }
    
    printf("Enter ISBN: ");
    scanf("%s", isbn_input);

    isbn_length = strlen(isbn_input);
    
    for(i = 0; i < isbn_length && i < 50; i++) 
    {
        isbns[book_count][i] = isbn_input[i] - '0';
    }
    
    isbns[book_count][isbn_length] = -1;
    
    for(i = 0; i < book_count; i++)
    {
        int same = 1;
        for(j = 0; j < 50; j++) 
        {
            if(isbns[i][j] != isbns[book_count][j]) 
            {
                same = 0;
                break;
            }
            if(isbns[i][j] == -1) 
            {
                break;
            }
        }
        
        if(same == 1) 
        {
            duplicate = 1;
            break;
        }
    }
    
    if(duplicate == 1) 
    {
        printf("Error! This ISBN already exists! Cannot add a duplicate ISBN.\n");
        return;
    }
    
    printf("please enter the book title: ");
    scanf(" %[^\n]", book_title[book_count]);    
    printf("please enter the price: ");
    scanf("%f", &book_price[book_count]);    
    printf("please enter the desired quantity: ");
    scanf("%d", &book_quantity[book_count]);
    
    if(book_quantity[book_count] < 0) 
    {
        printf("Error! the quantity cannot be negative!\n");
        return;
    }
    
    book_count++;
    printf("Book added!\n");
}

void sale_processing() 
{
    char isbn_input[100];
    int search_isbn[50];
    int i, j, found = -1;
    int order_qty;
    float total;
    int isbn_length;
    
    printf("Enter ISBN to search: ");
    scanf("%s", isbn_input);
    isbn_length = strlen(isbn_input);
    
    for(i = 0; i < isbn_length && i < 50; i++) 
    {
        search_isbn[i] = isbn_input[i] - '0';
    }
    
    search_isbn[isbn_length] = -1;
    
    for(i = 0; i < book_count; i++) 
    {
        int match = 1;
        for(j = 0; j < 50; j++)
        {
            if(isbns[i][j] != search_isbn[j]) 
            {
                match = 0;
                break;
            }
            if(isbns[i][j] == -1) 
            {
                break;
            }
        }
        if(match == 1) 
        {
            found = i;
            break;
        }
    }
    
    if(found == -1) 
    {
        printf("Error! Book not found in the inventory!\n");
        return;
    }
    
    printf("please enter quantity to order: ");
    scanf("%d", &order_qty);
    
    if(order_qty <= 0) 
    {
        printf("Error! incorrect quantity!\n");
        return;
    }
    
    if(book_quantity[found] < order_qty) 
    {
        printf("Error! not enough stock! Only %d copies in stock currently.\n", book_quantity[found]);
        return;
    }
    
    book_quantity[found] = book_quantity[found] - order_qty;
    total = order_qty * book_price[found];
    
    printf("\n==== Order summary ====\n");
    printf("Title: %s\n", book_title[found]);
    printf("ISBN: ");
    for(i = 0; i < 50; i++) 
    {
        if(isbns[found][i] == -1) break;
        printf("%d", isbns[found][i]);
    }

    printf("\n");
    printf("quantity ordered: %d\n", order_qty);
    printf("Price per book: %.2f\n", book_price[found]);
    printf("total cost: %.2f\n", total);
    printf("Remaining stock: %d\n", book_quantity[found]);
}

void low_stock_report() 
{
    int i, j;
    int found_low_stock = 0;
    
    printf("\n==== Low inventory stock report ====\n");
    printf("Books with null stock:\n\n");
    
    for(i = 0; i < book_count; i++) 
    {
        if(book_quantity[i] == 0)
        {
            printf("ISBN: ");

            for(j = 0; j < 50; j++) 
            {
                if(isbns[i][j] == -1) break;

                printf("%d", isbns[i][j]);
            }

            printf("\n");
            printf("Title: %s\n", book_title[i]);
            printf("Price: %.2f\n", book_price[i]);
            printf("quantity: %d\n", book_quantity[i]);
            printf("------------------------\n");
            found_low_stock = 1;
        }
    }
    
    if(found_low_stock == 0) 
    {
        printf("All books have sufficient inventory!\n");
    }
}

int main() 
{
    int choice;
    
    while(1) 
    {
        printf("\n==== Welcome to the Inventory System for Liberty books ====\n");
        printf("\n1) Add a new book\n");
        printf("2) Process an order\n");
        printf("3) generate low-stock report\n");
        printf("4) exit software\n");
        printf("\nplease enter your choice: ");
        scanf("%d", &choice);
        
        if(choice == 1) 
        {
            book_registration();
        }

        else if(choice == 2) 
        {
            sale_processing();
        }

        else if(choice == 3)
        {
            low_stock_report();
        }

        else if(choice == 4)
        {
            printf("Exiting software.........\n");
            break;
        }

        else 
        {
            printf("Incorrect option! please try again.\n");
        }
    }
    
    return 0;
}
