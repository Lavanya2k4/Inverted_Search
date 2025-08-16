#include "inverted_search.h"

void display_database(hash_node arr[])
{
    printf("1.index  2.word      3.filecount    4.filename       5.wordcount    6.filename    7.wordcount\n");
    printf("----------------------------------------------------------------------------------------------\n");
    //run the loop for all  hash indexes 
    for (int i = 0; i < 27; i++)
    {
        //check hash link is null or not
        if (arr[i].link != NULL)
        {
            main_node *main_temp = arr[i].link;
            //traverse all mainnodes
            while (main_temp != NULL)
            {
                // Print index, word, and file count
                printf("%-8d %-12s %-13d", i, main_temp->word, main_temp->file_count);

                sub_node *sub_temp = main_temp->sub_link;
                //traverse all subnodes
                while (sub_temp != NULL)
                {
                    //print filename and word count
                    printf(" %-16s %-13d", sub_temp->filename, sub_temp->word_count);
                    sub_temp = sub_temp->link;//move to next sub node
                }
                printf("\n");
                main_temp = main_temp->main_link;//move to next main node
            }
        }
    }
    printf("----------------------------------------------------------------------------------------------\n");
}
