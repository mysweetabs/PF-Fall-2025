#include <stdlib.h>         //We stil haven't done our POE thingy; so sad
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct BookStruct
{
    int id;
    int score;
} Book;

int len = 0;

int find_book(Book *book_list, int book_id)
{
    for (int i = 0; i < len; i++)
    {
        if (book_list[i].id == book_id)
            return i;
    }
    return -1;
}

void add(Book *book_list, const int cap, int book_id, int book_score)
{
    int idx = find_book(book_list, book_id);
    
    if (idx != -1)
    {
        book_list[idx].score = book_score;
        Book temp = book_list[idx];
        for (int i = idx; i < len - 1; i++)
        {
            book_list[i] = book_list[i + 1];
        }
        book_list[len - 1] = temp;
        return;
    }

    if (len == cap)
    {
        for (int i = 0; i < cap - 1; i++)
        {
            book_list[i] = book_list[i + 1];
        }
        book_list[cap - 1].id = book_id;
        book_list[cap - 1].score = book_score;
    }
    
    else
    {
        book_list[len].id = book_id;
        book_list[len].score = book_score;
        len++;
    }
}

int access_book(Book *book_list, int book_id)
{
    int idx = find_book(book_list, book_id);

    if (idx == -1)
    {
        return -1;
    }

    int found_score = book_list[idx].score;
    Book temp = book_list[idx];

    for (int i = idx; i < len - 1; i++)
    {
        book_list[i] = book_list[i + 1];
    }

    book_list[len - 1] = temp;

    return found_score;
}

int main()
{
    int capacity, ops_count;
    scanf("%d %d", &capacity, &ops_count);

    Book *book_list = (Book *)malloc(sizeof(Book) * capacity);

    char operation[7];
    int book_id, book_score;

    for (int i = 0; i < ops_count; i++)
    {
        scanf("%6s", operation);

        if (strcmp(operation, "ADD") == 0)
        {
            scanf("%d %d", &book_id, &book_score);
            add(book_list, capacity, book_id, book_score);
        }

        else if (strcmp(operation, "ACCESS") == 0)
        {
            scanf("%d", &book_id);
            int score_val = access_book(book_list, book_id);
            printf("%d\n", score_val);
        }
    }

    free(book_list);
    
    return 0;
}
