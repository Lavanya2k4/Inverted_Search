#include "inverted_search.h"
int delete_element(Slist **head, char *filename)
{
    //check list empty or not
    if (*head == NULL)
    {
        return FAILURE;//empty-> return failure
    }
    Slist *temp = *head;//pointer to the current  node
    Slist *prev = NULL;//pointer to the previous node
    //traverse the list
    while (temp != NULL)
    {
        //compare the nodes file name with input
        if (strcmp(temp->str, filename) == 0)
        {
            if (prev == NULL)//deleting head node
            {
                *head = temp->link;
            }
            else
            { 
                prev->link = temp->link;//deleting middle or last node
            }
            free(temp);//free temp
            return SUCCESS;
        }
        //move prev and temp 
        prev = temp;
        temp = temp->link;
    }
    return FAILURE;//file name not found in list
}
int update_database(hash_node arr[], Slist **head)
{
    char filename[100];
    printf("Enter the database file (.txt):\n");
    scanf("%s", filename);
    //validate fileextension
    if (strstr(filename, ".txt") == NULL)
    {
        printf("Error: Enter a valid .txt file\n");
        return FAILURE;
    }
    //open file in read mode
    FILE *fp = fopen(filename, "r");
    //check file is opened or not
    if (fp == NULL)
    {
        printf("DATABASE file not found or empty\n");
        return FAILURE;
    }
    char word[50];
    int index, filecount;
    char word1 = getc(fp);//read first character of file
    fseek(fp, -2, SEEK_END);//move to end and read second last character
    char word2 = getc(fp);//read character before EOF
     //validate database file format
    if (word1 != '#' || word2 != '#')
    {
        printf("Entered file is NOT a valid DATABASE file\n");
        fclose(fp);
        return FAILURE;
    }
    fseek(fp, 0, SEEK_SET);//reset the file pointer to start
    //loop to read each word block fromm database
    while (fscanf(fp, "#%d;%[^;];%d;", &index, word, &filecount) == 3)
    {
        printf("Index: %d, Word: %s, Filecount: %d\n", index, word, filecount);
        for (int i = 0; i < filecount; i++)//loop through all files for this word
        {
            char file_name[100];
            int word_count;
            //read the filename and word count stop if it is in miss order or next line start with # 
            if (fscanf(fp, "%[^;];%d;", file_name, &word_count) != 2 || file_name[0] == '#')
            {
                break; 
            }
            delete_element(head, file_name);//if is already present remove the file from list
            main_node *main_temp = arr[index].link;//point to first mainnode at this index
            main_node *found = NULL;
            //search the word in main node list
            while (main_temp)
            {
                if (strcmp(main_temp->word, word) == 0)
                {
                    found = main_temp;
                    break;
                }
                main_temp = main_temp->main_link;
            }
            //word not found
            if (found == NULL)
            {
                //Create new main_node
                main_node *new_main = malloc(sizeof(main_node));
                strcpy(new_main->word, word);
                new_main->file_count = 1;
                new_main->sub_link = NULL;
                new_main->main_link = arr[index].link;
                arr[index].link = new_main;

                found = new_main;
            }
            else
            {
                found->file_count++;//increment file count the word already exist
            }
            // Create and insert new sub_node
            sub_node *new_sub = malloc(sizeof(sub_node));
            strcpy(new_sub->filename, file_name);
            new_sub->word_count = word_count;
            new_sub->link = found->sub_link;
            found->sub_link = new_sub;
        }
        // Skip to next line i.e until newline or end of the file
        int ch;
        while ((ch = fgetc(fp)) != '\n' && ch != EOF);
    }

    fclose(fp);//close the file
    return SUCCESS;
}
