#include <stdio.h>    // Hello again Sire! I have to say, this one was longer and more time comsuming than Q1 :(
#include <string.h>   // Lets see how I did!

char product_code[100][20];
int quantity_in_stock[100];
float price_per_product[100];
int total_products = 4;

char cart_product_code[100][20];
int cart_quantity[100];
int cart_size = 0;
char customer_name[100];
char customer_cnic[20];

void customer_info();
void display_inventory();
void update_inventory();
void add_item_to_cart();
void display_bill();
void display_invoice();


void customer_info() 
{
    printf("please enter customer name: ");
    scanf(" %[^\n]", customer_name);
    printf("please enter CNIC number: ");
    scanf("%s", customer_cnic);
    printf("Customer information saved!\n");
}

void display_inventory() 
{
    int i;
    
    printf("\n==== Current Inventory ====\n");
    printf("Product code | Quantity in stock | Price per product\n");
    
    for(i = 0; i < total_products; i++) 
    {
        printf("%-12s | %-17d | %.2f\n", product_code[i], quantity_in_stock[i], price_per_product[i]);
    }
}

void update_inventory() 
{
    char code[20];
    int qty;
    int found = -1;
    int i;
    
    printf("please enter product code: ");
    scanf("%s", code);
    
    for(i = 0; i < total_products; i++)
    {
        if(strcmp(product_code[i], code) == 0) 
        {
            found = i;
            break;
        }
    }
    
    if(found == -1) 
    {
        printf("product not found!\n");
        return;
    }
    
    printf("please enter the quantity purchased: ");
    scanf("%d", &qty);
    
    if(qty < 0) 
    {
        printf("Incorrect quantity!\n");
        return;
    }
    
    quantity_in_stock[found] = quantity_in_stock[found] + qty;

    printf("Inventory updated! new quantity: %d\n", quantity_in_stock[found]);
}

void add_item_to_cart() 
{
    char code[20];
    int qty;
    int found = -1;
    int cart_index = -1;
    int i;
    
    printf("please enter product code: ");
    scanf("%s", code);
    
    for(i = 0; i < total_products; i++) 
    {
        if(strcmp(product_code[i], code) == 0) 
        {
            found = i;
            break;
        }
    }
    
    if(found == -1)
    {
        printf("product not found!\n");
        return;
    }
    
    printf("please enter desired quantity: ");
    scanf("%d", &qty);
    
    if(qty <= 0) 
    {
        printf("Invalid quantity!\n");
        return;
    }
    
    if(quantity_in_stock[found] < qty) 
    {
        printf("Insufficient stock! only %d available\n", quantity_in_stock[found]);
        return;
    }
    
    for(i = 0; i < cart_size; i++)
    {
        if(strcmp(cart_product_code[i], code) == 0) 
        {
            cart_index = i;
            break;
        }
    }
    
    if(cart_index != -1) 
    {
        cart_quantity[cart_index] = cart_quantity[cart_index] + qty;
    }
    
    else
    {
        strcpy(cart_product_code[cart_size], code);
        cart_quantity[cart_size] = qty;
        cart_size++;
    }
    
    quantity_in_stock[found] = quantity_in_stock[found] - qty;
    printf("Item added to cart!\n");
}

void display_bill() 
{
    float total_bill = 0;
    float item_total;
    char promocode[20];
    int i, j;
    
    if(cart_size == 0) 
    {
        printf("Your Cart is empty!\n");
        return;
    }
    
    printf("\n==== Total Bill ====\n");
    
    for(i = 0; i < cart_size; i++) 
    {
        for(j = 0; j < total_products; j++)
        {
            if(strcmp(cart_product_code[i], product_code[j]) == 0) 
            {
                item_total = cart_quantity[i] * price_per_product[j];
                total_bill = total_bill + item_total;
                break;
            }
        }
    }
    
    printf("Total amount: %.2f\n", total_bill);
    
    printf("Do you have a promocode? (type promocode or 'no'): ");
    scanf("%s", promocode);
    
    if(strcmp(promocode, "EID2025") == 0)
    {
        float discount = total_bill * 0.25;
        float final_amount = total_bill - discount;

        printf("promocode applied! 25%% discount\n");
        printf("Discount: %.2f\n", discount);
        printf("Final amount: %.2f\n", final_amount);
    }

    else 
    {
        printf("No discount applied\n");
        printf("Final amount: %.2f\n", total_bill);
    }
}

void display_invoice() 
{
    float total_bill = 0;
    float item_total;
    float discount;
    float final_amount;
    int i, j;
    
    if(cart_size == 0)
    {
        printf("Your Cart is empty!\n");
        return;
    }
    
    printf("                 INVOICE                    \n");
    printf("============================================\n");
    printf("Customer Name: %s\n", customer_name);
    printf("CNIC: %s\n", customer_cnic);
    printf("--------------------------------------------\n");
    printf("Product | Quantity | Price | Total\n");
    printf("--------------------------------------------\n");
    
    for(i = 0; i < cart_size; i++) 
    {
        for(j = 0; j < total_products; j++) 
        {
            if(strcmp(cart_product_code[i], product_code[j]) == 0)
            {
                item_total = cart_quantity[i] * price_per_product[j];

                printf("%-7s | %-8d | %-5.2f | %.2f\n", 
                       cart_product_code[i], cart_quantity[i], 
                       price_per_product[j], item_total);
                total_bill = total_bill + item_total;
                break;
            }
        }
    }
    
    discount = total_bill * 0.25;
    final_amount = total_bill - discount;
    
    printf("--------------------------------------------\n");
    printf("Subtotal: %.2f\n", total_bill);
    printf("Discount (25%%): %.2f\n", discount);
    printf("FINAL AMOUNT: %.2f\n", final_amount);
}

int main() 
{
    int choice;
    
    strcpy(product_code[0], "001");
    quantity_in_stock[0] = 50;
    price_per_product[0] = 100;
    
    strcpy(product_code[1], "002");
    quantity_in_stock[1] = 10;
    price_per_product[1] = 200;
    
    strcpy(product_code[2], "003");
    quantity_in_stock[2] = 20;
    price_per_product[2] = 300;
    
    strcpy(product_code[3], "004");
    quantity_in_stock[3] = 8;
    price_per_product[3] = 150;
    
    while(1) 
    {
        printf("\n========== Main menu ==========\n");
        printf("\n1) Customer information\n");
        printf("2) Display inventory\n");
        printf("3) Update inventory\n");
        printf("4) Add item to cart\n");
        printf("5) Display total bill\n");
        printf("6) Display invoice\n");
        printf("7) Exit software\n");
        printf("\nplease enter your choice: ");
        scanf("%d", &choice);
        
        if(choice == 1)
        {
            customer_info();
        }

        else if(choice == 2) 
        {
            display_inventory();
        }

        else if(choice==3) 
        {
            update_inventory();
        }

        else if(choice == 4) 
        {
            add_item_to_cart();
        }

        else if(choice == 5) 
        {
            display_bill();
        }

        else if(choice == 6)
        {
            display_invoice();
        }

        else if(choice == 7) 
        {
            printf("Thank you for using our system! Exiting software..............\n");
            break;
        }

        else 
        {
            printf("Invalid choice!\n");
        }
    }
    
    return 0;
}