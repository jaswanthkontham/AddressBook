#include <stdio.h>
#include "file.h"
#include "unistd.h"
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;
    if((fp=fopen("contacts.csv","w"))==NULL)
    {
        fprintf(stderr,"\33[31mError: Unable to open file for writing contacts.\33[0m\n");
        return;
    }
    fprintf(fp,"#%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("\33[32mContacts Saved Successfully\33[0m\n");
    fclose(fp);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp;
    if((fp=fopen("contacts.csv","r"))==NULL)
    {
        fprintf(stderr,"\33[31mError: Unable to open file for reading contacts.\33[0m\n");
        return;
    }
    fscanf(fp,"#%d\n",&addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fp," %[^,],%[^,],%[^\n]",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp);
    
}
