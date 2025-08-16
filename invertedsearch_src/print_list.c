#include "inverted_search.h"

void print_list(Slist *head)
{
    if (head == NULL)//check result is empty or not
    {
        printf("INFO : List is empty\n");
        return;
    }
    printf("List of valid files:\n");
    while (head)//loop until headR becomes null
    {
        printf("%s\n", head->str);//print each digit
        head = head->link;//move to next digit
    }
    printf("\n");
}