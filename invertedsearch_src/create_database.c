#include "inverted_search.h"

void create_database(Slist *head, hash_node arr[])
{
    Slist *temp = head;
    //travese the list until reaches null
    while (temp != NULL)
    {
        FILE *fp = fopen(temp->str, "r");//open file in readmode
        if (fp == NULL)
        {
            printf("%s file could not be opened\n", temp->str);
            temp = temp->link;//move to next file
            continue;
        }
        char word[50];
        while (fscanf(fp, "%s", word) != EOF)//read words from file
        {
            printf("%s\n",word);
            int index;
            char first = word[0];
            if (isalpha(first))
            {
                index = tolower(first) % 97; //calculate index for a-z -> 0-25
            }
            else
            {
                index = 26;//index for non-alphabetic characters
            }
            if (index < 0 || index > 26)
            {
                printf("Invalid index for word %s\n", word);
                continue;//skip invalid index
            }
            //case1:check hash table index empty or not
            if (arr[index].link == NULL)
            {
                // Create main node and sub node for new word
                main_node *new_main = malloc(sizeof(main_node));
                sub_node *new_sub = malloc(sizeof(sub_node));
                //intialize main nide witg word
                strcpy(new_main->word, word);
                new_main->file_count = 1;
                new_main->main_link = NULL;
                //intialize sub node with filename and word count
                strcpy(new_sub->filename, temp->str);
                new_sub->word_count = 1;
                new_sub->link = NULL;
                //link subnode to main node
                new_main->sub_link = new_sub;
                arr[index].link = new_main;//add to the hash table
            }
            else
            {
                main_node *n_pointer = arr[index].link;
                int found_word = 0;

                while (n_pointer != NULL)
                {
                    if (strcmp(n_pointer->word, word) == 0)
                    {
                        found_word = 1;
                        sub_node *s_pointer = n_pointer->sub_link;
                        int found_file = 0;

                        while (s_pointer != NULL)
                        {
                            if (strcmp(s_pointer->filename, temp->str) == 0)
                            {
                                s_pointer->word_count++;//increment word count if file found
                                found_file = 1;
                                break;
                            }
                            s_pointer = s_pointer->link;
                        }
                        //case2:word exist ,but file is new
                        if (!found_file)
                        {
                            //create new_subnode
                            sub_node *new_sub = malloc(sizeof(sub_node));
                            strcpy(new_sub->filename, temp->str);
                            new_sub->word_count = 1;
                            new_sub->link = n_pointer->sub_link;
                            n_pointer->sub_link = new_sub;
                            n_pointer->file_count++;//increment filecount
                        }
                        break;
                    }

                    n_pointer = n_pointer->main_link;//move to the next main node
                }
                //case3:word doesnt exist in hash table index for first letter 
                if (!found_word)
                {
                    //create main node and sub node 
                    main_node *new_main = malloc(sizeof(main_node));
                    sub_node *new_sub = malloc(sizeof(sub_node));

                    strcpy(new_main->word, word);
                    new_main->file_count = 1;
                    new_main->main_link = arr[index].link;

                    strcpy(new_sub->filename, temp->str);
                    new_sub->word_count = 1;
                    new_sub->link = NULL;

                    new_main->sub_link = new_sub;
                    arr[index].link = new_main;//add to hashtable
                }
            }
        }

        fclose(fp);
        temp = temp->link;//move to the nextfile in the list
    }
}
