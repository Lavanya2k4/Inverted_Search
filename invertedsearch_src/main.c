#include "inverted_search.h"

//Function to check for duplicate filenames in linked list
int is_duplicate(Slist *head, const char *filename)
{
    while (head)
    {
        if (strcmp(head->str, filename) == 0)
		{
            return 1;
		}
        head = head->link;
    }
    return 0;
}
//Function to check the file is valid then stored into linked list
Slist* add_to_list(Slist *head, const char *filename)
{
    Slist *new = malloc(sizeof(Slist));
    if (new == NULL)
    {
        return NULL;
    }
    strcpy(new->str, filename);
    new->link = head;
    return new;
}
int main(int argc, char *argv[])
{
	/* Define the main function here */
	Slist *head=NULL;
	
	if(argc < 2)
	{
		printf("USE:./a.out <file1.txt> <file2.txt>...\n");
		return FAILURE;
	}
	for(int i=1;i<argc;i++)
	{
	   char *filename=argv[i];
	   //check if the file has .txt entension or not
       if(!strstr(filename,".txt"))
	   {
		 printf("error:The file has not a .txt extension\n");
		 continue;
	   }
	   //check if file is exit or not
		FILE *fp=fopen(filename,"r");
		if(fp == NULL)
		{
			printf("%s file is not opened\n",filename);
			continue;
		}
		//check file contents is present or not
		fseek(fp,0,SEEK_END);
		if(ftell(fp)==0)
		{
			printf("%s file is empty\n",filename);
			fclose(fp);
			continue;
		}
		fclose(fp);
		//check if filename is duplicate or not
		if(is_duplicate(head,filename))
		{
			printf("The file name already exists: %s\n", filename);
			continue;
		}
		// Add to list
        Slist *temp = add_to_list(head, filename);
        if (temp == NULL)
        {
            printf("error: Memory allocation failed for file\n");
            continue;
        }
        head = temp;
        printf("%s File added successfully\n",filename);
    }
    // Print final list
    print_list(head);
	hash_node arr[27] = {0};
	int flag=0;// 0 = only create allowed, 1 = only update allowed, -1 = nothing allowed
	while (1)
    {
		int choice;
		printf("1. Create database\n");
		printf("2. Display database\n");
		printf("3. Save database\n");
		printf("4. Search database\n");
		printf("5. Update database\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		switch (choice)
		{
			
			case 1: // Create
				if (flag == 0)
				{
					create_database(head, arr);
					printf("Database Created Successfully\n");
					flag = -1;
				}
				else if (flag == 1)
				{
					if (head != NULL)
					{
						create_database(head, arr);
						printf("Database Created for new files\n");
						head = NULL;
					}
					else
					{
						printf("INFO:No new files to create database.\n");
					}
				}
				else
				{
					printf("INFO:Create already done. Not allowed again.\n");
				}
				break;

			case 2:
				display_database(arr);
				printf("Display the database successfully\n");
				break;

			case 3:
				save_database(arr);
				break;

			case 4:
				search_database(arr); 
				break;

			case 5:
				if (flag == 0)
				{
					int ret=update_database(arr, &head);
					if(ret == SUCCESS)
					{
                       flag = 1; // allow create only for new files
					}
				}
				else if (flag == 1)
				{
					printf("INFO:Update already done. Not allowed again.\n");
				}
				else
				{
					printf("INFO:Update not allowed after create.\n");
				}
				break;
			default:
				printf("Invalid choice. Try again.\n");
		}
   }
   return SUCCESS;
}
	



