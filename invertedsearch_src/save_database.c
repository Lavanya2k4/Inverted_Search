#include "inverted_search.h"

void save_database(hash_node arr[])
{
    char file[100];
    printf("enter the filename for save database(.txt):");
    scanf("%s",file);
    //check the user enter filename is .txt or not
    if(strstr(file,".txt"))
    {
        FILE *fp=fopen(file,"w");//open the file i  write mode
        //check file is opened or not
        if(fp == NULL)
        {
            printf("error:file is not opened\n");
            return;
        }
        //run the loop all hash indexes
        for(int i=0;i < 27;i++)
        {  
            //check hash table link is null or not
            if(arr[i].link != NULL)
            {
                //start with main node index
                main_node *savemain_temp=arr[i].link;
                //traverse main node list
                while(savemain_temp != NULL)
                {
                    //not empty print word,filecount
                    fprintf(fp,"#%d;%s;%d;",i,savemain_temp->word,savemain_temp->file_count);
                    //starts subnode list
                    sub_node *savesub_temp=savemain_temp->sub_link;
                    //traverse subnode list
                    while(savesub_temp != NULL)
                    {
                        //not empty print filename and word count
                        fprintf(fp,"%s;%d;",savesub_temp->filename,savesub_temp->word_count); 
                        //move to next subnode
                        savesub_temp=savesub_temp->link; 
                    }
                    fprintf(fp,"#");
                    fprintf(fp,"\n");
                    //move to next mainnode
                    savemain_temp=savemain_temp->main_link;
                }
            }
        }
        fclose(fp);
        printf("%s saved successfully into the database\n",file);
    }
    else
    {
        printf("invalid filename\n");
    }
}