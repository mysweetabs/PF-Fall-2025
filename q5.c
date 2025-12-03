#include <errno.h>          // i dunno whose idea this was, but GGs; im cooked
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_CAP 4
#define MAX_LINE 1024

typedef struct
{
    char **lines;
    int line_count;
    int capacity;
} Editor;

Editor *create_editor()
{
    Editor *ed = (Editor *)malloc(sizeof(Editor));
    if (!ed)
    {
        fprintf(stderr, "Error! Failed to allocate editor structure\n");
        return NULL;
    }

    ed->lines = (char **)malloc(INIT_CAP * sizeof(char *));
    if (!ed->lines)
    {
        fprintf(stderr, "Error! Failed to allocate lines array\n");
        free(ed);
        return NULL;
    }

    ed->line_count = 0;
    ed->capacity = INIT_CAP;

    printf("Editor created with capacity: %d\n", ed->capacity);
    return ed;
}

int grow_capacity(Editor *ed)
{
    int new_capacity = ed->capacity * 2;

    char **temp = (char **)realloc(ed->lines, new_capacity * sizeof(char *));
    if (!temp)
    {
        fprintf(stderr, "Error! Failed to grow capacity\n");
        return 0;
    }

    ed->lines = temp;
    ed->capacity = new_capacity;
    printf("Capacity grown to: %d\n", ed->capacity);
    return 1;
}

int insert_line(Editor *ed, int idx, const char *text)
{
    if (!ed || !text)
        return 0;
    if (idx < 0 || idx > ed->line_count)
    {
        fprintf(stderr, "Error! Invalid index %d\n", idx);
        return 0;
    }

    if (ed->line_count >= ed->capacity)
    {
        if (!grow_capacity(ed))
            return 0;
    }

    char *new_line = (char *)malloc((strlen(text) + 1) * sizeof(char));
    if (!new_line)
    {
        fprintf(stderr, "Error! Failed to allocate line memory\n");
        return 0;
    }
    strcpy(new_line, text);

    if (idx < ed->line_count)
    {
        memmove(&ed->lines[idx + 1], &ed->lines[idx],
                (ed->line_count - idx) * sizeof(char *));
    }

    ed->lines[idx] = new_line;
    ed->line_count++;
    return 1;
}

int delete_line(Editor *ed, int idx)
{
    if (!ed)
        return 0;
    if (idx < 0 || idx >= ed->line_count)
    {
        fprintf(stderr, "Error! Invalid index %d\n", idx);
        return 0;
    }

    free(ed->lines[idx]);

    if (idx < ed->line_count - 1)
    {
        memmove(&ed->lines[idx], &ed->lines[idx + 1],
                (ed->line_count - idx - 1) * sizeof(char *));
    }

    ed->line_count--;
    return 1;
}

void print_all_lines(Editor *ed)
{
    if (!ed)
        return;

    printf("\n---- Editor buffer (Lines: %d, Capacity: %d) ----\n", ed->line_count,
           ed->capacity);

    if (ed->line_count == 0)
    {
        printf("[Empty buffer]\n");
        return;
    }

    for (int i = 0; i < ed->line_count; i++)
    {
        printf("%3d: %s\n", i + 1, ed->lines[i]);
    }
    printf("\n");
}

int shrink_to_fit(Editor *ed)
{
    if (!ed || ed->line_count == 0)
        return 0;

    if (ed->line_count < ed->capacity)
    {
        char **temp = (char **)realloc(ed->lines, ed->line_count * sizeof(char *));
        if (!temp)
        {
            fprintf(stderr, "Warning! Failed to shrink capacity\n");
            return 0;
        }

        ed->lines = temp;
        ed->capacity = ed->line_count;
        printf("Capacity shrunk to: %d\n", ed->capacity);
        return 1;
    }
    return 0;
}

int save_to_file(Editor *ed, const char *filename)
{
    if (!ed || !filename)
        return 0;

    FILE *file = fopen(filename, "w");
    if (!file)
    {
        fprintf(stderr, "Error! Cannot open file '%s' - %s\n", filename,
                strerror(errno));
        return 0;
    }

    for (int i = 0; i < ed->line_count; i++)
    {
        fprintf(file, "%s\n", ed->lines[i]);
    }

    fclose(file);
    printf("Saved %d lines to '%s'\n", ed->line_count, filename);
    return 1;
}

int load_from_file(Editor *ed, const char *filename)
{
    if (!ed || !filename)
        return 0;

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Error! Cannot open file '%s' - %s\n", filename,
                strerror(errno));
        return 0;
    }

    char buffer[MAX_LINE];
    int loaded_count = 0;

    while (fgets(buffer, MAX_LINE, file))
    {

        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }

        if (!insert_line(ed, ed->line_count, buffer))
        {
            fprintf(stderr, "Error! Failed to load line %d\n", loaded_count + 1);
            fclose(file);
            return 0;
        }
        loaded_count++;
    }

    fclose(file);
    printf("Loaded %d lines from '%s'\n", loaded_count, filename);
    return 1;
}

void free_all(Editor *ed)
{
    if (!ed)
        return;

    for (int i = 0; i < ed->line_count; i++)
    {
        free(ed->lines[i]);
    }

    free(ed->lines);

    free(ed);

    printf("All memory has been freed\n");
}

void show_menu()
{
    printf("\n---- FAST NUCES text editor ----\n");
    printf("1) Insert line\n");
    printf("2) Delete line\n");
    printf("3) Print all\n");
    printf("4) Shrink to fit\n");
    printf("5) Save to file\n");
    printf("6) Load from file\n");
    printf("7) Exit\n");
    printf("Plase enter your choice: ");
}

int main()
{
    Editor *ed = create_editor();
    if (!ed)
        return 1;

    int choice, line_idx;
    char text[MAX_LINE], filename[100];

    while (1)
    {
        show_menu();
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            printf("please enter line number (1-%d): ", ed->line_count + 1);
            scanf("%d", &line_idx);
            getchar();
            printf("please enter text: ");
            fgets(text, MAX_LINE, stdin);
            text[strcspn(text, "\n")] = 0;
            insert_line(ed, line_idx - 1, text);
            break;

        case 2:
            printf("please enter line number to delete: ");
            scanf("%d", &line_idx);
            getchar();
            delete_line(ed, line_idx - 1);
            break;

        case 3:
            print_all_lines(ed);
            break;

        case 4:
            shrink_to_fit(ed);
            break;

        case 5:
            printf("please enter filename: ");
            scanf("%s", filename);
            getchar();
            save_to_file(ed, filename);
            break;

        case 6:
            printf("please enter filename: ");
            scanf("%s", filename);
            getchar();
            load_from_file(ed, filename);
            break;

        case 7:
            free_all(ed);
            printf("ending software; Goodbye!\n");
            return 0;

        default:
            printf("Invalid choice\n");
        }
    }

    return 0;
}
