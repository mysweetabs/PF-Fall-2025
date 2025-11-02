#include <stdio.h>

int grid[10][10];       //Back at it again Sire! Bitwise is still a lil confusing for me
                        //But nonetheless, lets see how i did! here we go again!

void update_sector_status(int row, int col, int bit, int value);
void query_sector_status(int row, int col);
void run_system_diagnostic();

void update_sector_status(int row, int col, int bit, int value) 
{
    int i;
    
    if(value == 1) 
    {
        grid[row][col] = grid[row][col] | (1 << bit);
    }

    else
    {
        grid[row][col] = grid[row][col] & ~(1 << bit);
    }
    
    printf("Sector [%d][%d] updated!\n", row, col);
    printf("New status value: %d\n", grid[row][col]);
    printf("binary: ");
    
    for(i = 7; i >= 0; i--) 
    {
        if((grid[row][col] >> i) & 1)
        {
            printf("1");
        }

        else 
        {
            printf("0");
        }
    }

    printf("\n");
}

void query_sector_status(int row, int col) 
{
    int status;
    int power_status, overload_warning, maintenance_required;
    int i;
    
    status = grid[row][col];
    
    printf("\n==== Sector Status Report ====\n");
    printf("\nCoordinates: [%d][%d]\n", row, col);
    printf("status value: %d\n", status);
    printf("binary representation: ");
    
    for(i = 7; i >= 0; i--)
    {
        if((status >> i) & 1) 
        {
            printf("1");
        }

        else
        {
            printf("0");
        }
    }

    printf("\n\n");
    
    power_status = status & 1;
    printf("bit 0 - Power Status: ");

    if(power_status == 1) 
    {
        printf("on\n");
    }

    else 
    {
        printf("off\n");
    }
    
    overload_warning = (status >> 1) & 1;
    printf("bit 1 - overload warning: ");

    if(overload_warning == 1)
    {
        printf("Overloaded\n");
    }

    else 
    {
        printf("Normal\n");
    }
    
    maintenance_required = (status >> 2) & 1;
    printf("Bit 2 - maintenance required: ");

    if(maintenance_required == 1) 
    {
        printf("yes\n");
    }

    else
    {
        printf("no\n");
    }
    
}

void run_system_diagnostic() 
{
    int overload_count = 0;
    int maintenance_count = 0;
    int status, overload, maintenance;
    int i, j;
    
    printf("\n==== System Diagnostic ====\n");
    printf("scanning entire grid, please wait\n\n");
    printf("sectors with issues:\n");
    
    for(i = 0; i < 10; i++) 
    {
        for(j = 0; j < 10; j++)
        {
            status = grid[i][j];
            overload = (status >> 1) & 1;
            maintenance = (status >> 2) & 1;
            
            if(overload == 1 || maintenance == 1) 
            {
                printf("Sector [%d][%d]: ", i, j);
                
                if(overload == 1 && maintenance == 1)
                {
                    printf("Overloaded and maintainance required!");
                    overload_count++;
                    maintenance_count++;
                }

                else if(overload == 1) 
                {
                    printf("overloaded");
                    overload_count++;
                }

                else if(maintenance == 1)
                {
                    printf("maintainance required!");
                    maintenance_count++;
                }
                
                printf("\n");
            }
        }
    }
    
    printf("total sectors currently overloaded: %d\n", overload_count);
    printf("total sectors requiring maintenance: %d\n", maintenance_count);
}

int main() 
{
    int choice;
    int row, col, bit, value;
    int i, j;
    
    for(i = 0; i < 10; i++) 
    {
        for(j = 0; j < 10; j++)
        {
            grid[i][j] = 0;
        }
    }
    
    printf("Grid initialized! All sectors set to 0.\n");
    
    while(1) 
    {
        printf("\n===== Operator Interface =====\n");
        printf("\n1. Update sector status\n");
        printf("2. query sector status\n");
        printf("3. Run system diagnostic\n");
        printf("4. Exit\n");
        printf("\nplease enter your choice: ");
        scanf("%d", &choice);
        
        if(choice == 1)
        {
            printf("please enter row coordinate (0-9): ");
            scanf("%d", &row);
            printf("please enter column coordinate (0-9): ");
            scanf("%d", &col);
            
            if(row < 0 || row >= 10 || col < 0 || col >= 10) 
            {
                printf("Invalid coordinates!\n");
                continue;
            }
            
            printf("please enter bit position (0, 1, or 2): ");
            scanf("%d", &bit);
            
            if(bit < 0 || bit > 2)
            {
                printf("invalid bit position!\n");
                continue;
            }
            
            printf("please enter value (0 to clear, 1 to set): ");
            scanf("%d", &value);
            
            if(value != 0 && value != 1) 
            {
                printf("invalid value!\n");
                continue;
            }
            
            update_sector_status(row, col, bit, value);
        }

        else if(choice == 2) 
        {
            printf("please enter row coordinate (0-9): ");
            scanf("%d", &row);
            printf("please enter column coordinate (0-9): ");
            scanf("%d", &col);
            
            if(row < 0 || row >= 10 || col < 0 || col >= 10)
            {
                printf("Invalid coordinates!\n");
                continue;
            }
            
            query_sector_status(row, col);
        }

        else if(choice==3) 
        {
            run_system_diagnostic();
        }

        else if(choice == 4) 
        {
            printf("Exiting system......\n");
            break;
        }

        else
        {
            printf("Incorrect choice!\n");
        }
    }
    
    return 0;
}
