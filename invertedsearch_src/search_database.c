#include "inverted_search.h"
void search_database(hash_node arr[])
{
    char word[50];
    printf("Enter the word: ");
    scanf("%s", word);

    int ind;
    char first = word[0];
    //if it is an alpha
    if (isalpha(first))
    {
        //find the hash index of a-z or A-Z(0-25)
        ind = tolower(first) % 97;
    }
    else
    {
        //non alpha
        ind = 26;
    }
    //pointer to start the main node
    main_node *search_temp1 = arr[ind].link;
    int found = 0;
    //traverse main node list
    while (search_temp1 != NULL)
    {
        //compare newnode word with word
        if (strcmp(search_temp1->word, word) == 0)
        {
            found = 1;
            printf("Word: %s\n", word);//print found word
            printf("Found in %d file(s):\n", search_temp1->file_count);//print filecount
            printf("---------------------------------\n");
            //create one newsubnode
            sub_node *search_temp2 = search_temp1->sub_link;//pointer to the subnode list
            //traverse subnode list
            while (search_temp2 != NULL)
            {
                printf("%s: %d time(s)\n", search_temp2->filename, search_temp2->word_count);
                printf("-----------------------------\n");
                search_temp2 = search_temp2->link;//move next sub node
            }
            break;//exit after word found
        }
        search_temp1 = search_temp1->main_link;//move next main node
    }
    //if word not found 
    if (!found)
    {
        printf("Word '%s' not found in the database.\n", word);
    }
}
