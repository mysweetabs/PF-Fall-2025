#include <stdbool.h>        // yeo, beyond cooked; disintegrated at this point
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    CS,
    SE,
    CY,
    AI
} Batch;
const char *BATCH_NAMES[] = {"CS", "SE", "CY", "AI"};

typedef enum
{
    IEEE,
    ACM,
    BOTH
} Membership;
const char *MEMBERSHIP_NAMES[] = {"IEEE", "ACM", "BOTH"};

typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    int student_id;
    char full_name[100];
    Batch batch;
    Membership membership;
    Date registration_date;
    Date date_of_birth;
    Membership interest;
} Student;

typedef struct
{
    Student *student_list;
    int student_count;
    int student_capacity;
} Database;

void save_database(const char *filename, Database *db);

void init_database(Database *db)
{
    db->student_capacity = 10;
    db->student_count = 0;
    db->student_list = (Student *)malloc(db->student_capacity * sizeof(Student));
    if (db->student_list == NULL)
    {
        perror("Failed to initialize database");
        exit(1);
    }
}

void free_database(Database *db)
{
    free(db->student_list);
    db->student_list = NULL;
    db->student_count = 0;
    db->student_capacity = 0;
}

int find_student_by_id(Database *db, int student_id)
{
    for (int i = 0; i < db->student_count; i++)
    {
        if (db->student_list[i].student_id == student_id)
        {
            return i;
        }
    }
    return -1;
}

void add_student(Database *db, Student new_student)
{
    if (find_student_by_id(db, new_student.student_id) != -1)
    {
        printf("Error! Student ID %d already exists.\n", new_student.student_id);
        return;
    }

    if (db->student_count >= db->student_capacity)
    {
        db->student_capacity *= 2;
        Student *temp = realloc(db->student_list, db->student_capacity * sizeof(Student));
        if (temp == NULL)
        {
            perror("Failed to expand database");
            return;
        }
        db->student_list = temp;
    }

    db->student_list[db->student_count] = new_student;
    db->student_count++;
    printf("Student %s registered successfully.\n", new_student.full_name);
}

void load_database(const char *filename, Database *db)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("No existing database file found. Starting fresh.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size > 0)
    {
        int student_count = file_size / sizeof(Student);
        if (student_count > db->student_capacity)
        {
            db->student_capacity = student_count;
            Student *temp = realloc(db->student_list, db->student_capacity * sizeof(Student));
            if (temp == NULL)
            {
                perror("Failed to allocate memory for loading database");
                fclose(file);
                return;
            }
            db->student_list = temp;
        }

        size_t items_read =
            fread(db->student_list, sizeof(Student), student_count, file);
        if (items_read > 0)
        {
            db->student_count = items_read;
            printf("Loaded %d student(s) from %s.\n", db->student_count, filename);
        }
    }
    fclose(file);
}

void save_database(const char *filename, Database *db)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("Error opening file for saving");
        return;
    }

    if (db->student_count > 0)
    {
        fwrite(db->student_list, sizeof(Student), db->student_count, file);
    }

    printf("Database successfully saved to %s.\n", filename);
    fclose(file);
}

void print_student(Student s)
{
    printf("ID: %-7d | Name: %-20s | Batch: %-15s | Membership: %-5s\n", s.student_id,
           s.full_name, BATCH_NAMES[s.batch], MEMBERSHIP_NAMES[s.membership]);
}

void handle_register_student(Database *db)
{
    Student s;
    printf("please enter Student ID: ");
    scanf("%d", &s.student_id);

    while (getchar() != '\n')
        ;

    printf("please enter full name: ");
    scanf("%99[^\n]", s.full_name);

    printf("please enter batch (0:CS, 1:SE, 2:CY, 3:AI): ");
    int batch_choice;
    scanf("%d", &batch_choice);
    s.batch = (Batch)batch_choice;

    printf("please enter membership (0:IEEE, 1:ACM, 2:BOTH): ");
    int mem_choice;
    scanf("%d", &mem_choice);
    s.membership = (Membership)mem_choice;

    s.registration_date = (Date){2024, 1, 1};
    s.date_of_birth = (Date){2002, 1, 1};
    s.interest = s.membership;

    add_student(db, s);
}

void handle_view_all(Database *db)
{
    if (db->student_count == 0)
    {
        printf("No student records found.\n");
        return;
    }
    printf("\n--- All student registrations ---\n");
    for (int i = 0; i < db->student_count; i++)
    {
        print_student(db->student_list[i]);
    }
    printf("\n");
}

void handle_update_student(Database *db)
{
    int student_id;
    printf("please enter Student ID to update: ");
    scanf("%d", &student_id);

    int idx = find_student_by_id(db, student_id);
    if (idx == -1)
    {
        printf("Error@ Student with ID %d not found.\n", student_id);
        return;
    }

    printf("Current details:\n");
    print_student(db->student_list[idx]);

    printf("please enter new Batch (0:CS, 1:SE, 2:CY, 3:AI): ");
    int batch_choice;
    scanf("%d", &batch_choice);
    db->student_list[idx].batch = (Batch)batch_choice;

    printf("please enter new Membership (0:IEEE, 1:ACM, 2:BOTH): ");
    int mem_choice;
    scanf("%d", &mem_choice);
    db->student_list[idx].membership = (Membership)mem_choice;

    printf("Student record updated successfully.\n");
}

void handle_delete_student(Database *db)
{
    int student_id;
    printf("please enter Student ID: ");
    scanf("%d", &student_id);

    int idx = find_student_by_id(db, student_id);
    if (idx == -1)
    {
        printf("Error! Student with ID %d not found.\n", student_id);
        return;
    }

    db->student_list[idx] = db->student_list[db->student_count - 1];
    db->student_count--;

    printf("Student with ID %d has been deleted.\n", student_id);
}

void handle_batch_report(Database *db)
{
    printf("Generate report for which Batch (0:CS, 1:SE, 2:CY, 3:AI): ");
    int batch_choice;
    scanf("%d", &batch_choice);
    Batch b = (Batch)batch_choice;

    printf("\n--- Report for Batch: %s ---\n", BATCH_NAMES[b]);
    int found_count = 0;
    for (int i = 0; i < db->student_count; i++)
    {
        if (db->student_list[i].batch == b)
        {
            print_student(db->student_list[i]);
            found_count++;
        }
    }
    if (found_count == 0)
    {
        printf("No students found for this batch.\n");
    }
    printf("\n");
}

void print_menu()
{
    printf("\n---- IEEE/ACM Membership Manager ----\n");
    printf("1) Register a new student\n");
    printf("2) Update student information\n");
    printf("3) Delete a student registration\n");
    printf("4) View all registrations\n");
    printf("5) Generate batch-wise report\n");
    printf("6) Exit\n");
    printf("please enter your choice: ");
}

int main()
{
    const char *FILENAME = "members.dat";
    Database db;

    init_database(&db);
    load_database(FILENAME, &db);

    int choice = 0;
    while (choice != 6)
    {
        print_menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            handle_register_student(&db);
            break;
        case 2:
            handle_update_student(&db);
            break;
        case 3:
            handle_delete_student(&db);
            break;
        case 4:
            handle_view_all(&db);
            break;
        case 5:
            handle_batch_report(&db);
            break;
        case 6:
            printf("ending software; Goodbye!\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    save_database(FILENAME, &db);
    free_database(&db);

    return 0;
}
