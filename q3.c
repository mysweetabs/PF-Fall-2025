#include <stdbool.h>   // How did you get 100/100 in oop lol? Structures are annoying for no reason fr 
#include <stdio.h>          
#include <stdlib.h>
#include <string.h>

typedef struct EmployeeStruct
{
    int employee_id;
    char employee_name[50];
    char employee_designation[50];
    double employee_salary;
} Employee;

void display_employee(Employee emp)
{
    printf("Employee ID: %d\t", emp.employee_id);
    printf("Name: %s\t", emp.employee_name);
    printf("Designation: %s\t", emp.employee_designation);
    printf("Salary: %.2lf\n", emp.employee_salary);
}

void display_all_employees(Employee *employee_list, int total_employees)
{
    printf("---- Employees list ----\n");
    printf("EmployeeID \t Name \t Designation \t Salary \n");
    
    for (int i = 0; i < total_employees; i++)
    {
        printf("%d \t %s \t %s \t %.2lf \n",
               employee_list[i].employee_id,
               employee_list[i].employee_name,
               employee_list[i].employee_designation,
               employee_list[i].employee_salary);
    }
}

int insert_employees(Employee **employee_list_ptr, int current_count)
{
    int new_count;
    
    printf("How many employee records do you wish to enter (n): ");
    scanf("%d", &new_count);

    if (new_count <= 0)
        return 0;

    Employee *temp_list = realloc(*employee_list_ptr, (current_count + new_count) * sizeof(Employee));
    
    if (temp_list == NULL)
    {
        printf("Error: Memory reallocation failed!\n");
        return 0;
    }

    *employee_list_ptr = temp_list;

    printf("Enter details for %d new employees.\n", new_count);
    
    for (int i = current_count; i < current_count + new_count; i++)
    {
        printf("[%d] Employee ID: ", i + 1);
        scanf("%d", &(*employee_list_ptr)[i].employee_id);

        printf("[%d] Name: ", i + 1);
        
        while (getchar() != '\n')
            ;
        scanf("%49[^\n]", (*employee_list_ptr)[i].employee_name);

        printf("[%d] Designation: ", i + 1);
        
        while (getchar() != '\n')
            ;
        scanf("%49[^\n]", (*employee_list_ptr)[i].employee_designation);

        printf("[%d] Salary: ", i + 1);
        scanf("%lf", &(*employee_list_ptr)[i].employee_salary);
        printf("\n");
    }

    return new_count;
}

int highest_earning_employee(Employee *employee_list, int total_employees)
{
    int highest_index = 0;
    
    for (int i = 1; i < total_employees; i++)
    {
        if (employee_list[i].employee_salary > employee_list[highest_index].employee_salary)
        {
            highest_index = i;
        }
    }
    return highest_index;
}

int search_employee_by_id(Employee *employee_list, int total_employees)
{
    int search_id;
    
    printf("please enter Employee ID to search: ");
    scanf("%d", &search_id);

    for (int i = 0; i < total_employees; i++)
    {
        if (employee_list[i].employee_id == search_id)
        {
            return i;
        }
    }
    return -1;
}

int search_employee_by_name(Employee *employee_list, int total_employees)
{
    char search_name[50];
    
    printf("please enter Employee Name to search: ");
    
    while (getchar() != '\n')
        ;
    scanf("%49[^\n]", search_name);

    for (int i = 0; i < total_employees; i++)
    {
        if (strcmp(employee_list[i].employee_name, search_name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void give_bonus(Employee *employee_list, int total_employees)
{
    double salary_threshold;
    
    printf("Pleasse enter a salary threshold: ");
    scanf("%lf", &salary_threshold);

    for (int i = 0; i < total_employees; i++)
    {
        if (employee_list[i].employee_salary < salary_threshold)
        {
            double old_salary = employee_list[i].employee_salary;
            employee_list[i].employee_salary *= 1.1;
            printf("Updated %s's salary from: %.2lf to: %.2lf\n", employee_list[i].employee_name, old_salary, employee_list[i].employee_salary);
        }
    }
}

int main()
{
    Employee *employee_list = NULL;
    int total_employees = 0;
    int user_choice;

    while (true)
    {
        printf("\n---- Welcome to the employee management system ----\n");
        printf("1) Insert employee records\n"
               "2) Display all employees\n"
               "3) Search employee by ID\n"
               "4) Search employee by name\n"
               "5) Apply bonus to employees\n"
               "6) Exit\n");
        printf("please enter your choice: ");
        scanf("%d", &user_choice);

        int index;

        switch (user_choice)
        {
            case 1:
                total_employees += insert_employees(&employee_list, total_employees);
                break;
            
            case 2:
                if (total_employees > 0)
                {
                    display_all_employees(employee_list, total_employees);
                }
                else
                {
                    printf("No employee records to display.\n");
                }
                break;
            
            case 3:
                index = search_employee_by_id(employee_list, total_employees);
                if (index != -1)
                {
                    display_employee(employee_list[index]);
                }
                else
                {
                    printf("Employee not found.\n");
                }
                break;
            
            case 4:
                index = search_employee_by_name(employee_list, total_employees);
                if (index != -1)
                {
                    display_employee(employee_list[index]);
                }
                else
                {
                    printf("Employee not found.\n");
                }
                break;
            
            case 5:
                give_bonus(employee_list, total_employees);
                break;
            
            case 6:
                printf("Ending program; Goodbye!\n");
                free(employee_list);
                return 0;
            
            default:
                printf("Invalid chioce, Please try Again.\n");
        }
    }

    return 0;
}
