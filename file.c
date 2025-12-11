#include <stdio.h>
#include "file.h"
#include "unistd.h"
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;
    if((fp=fopen("contacts.csv","w"))==NULL) //open file in write mode and check for error
    {
        fprintf(stderr,"\33[31mError: Unable to open file for writing contacts.\33[0m\n");
        return;
    }
    fprintf(fp,"#%d\n",addressBook->contactCount); //write contact count as first line
    for(int i=0;i<addressBook->contactCount;i++)
    {
        //write each contact's details to file in CSV format using fprintf because fprintf can format output in human readable way
        fprintf(fp,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("\33[32mContacts Saved Successfully\33[0m\n");
    fclose(fp); //close file after writing
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fp;
    if((fp=fopen("contacts.csv","r"))==NULL) //open file in right mode and check for error
    {
        fprintf(stderr,"\33[31mError: Unable to open file for reading contacts.\33[0m\n");
        return;
    }
    fscanf(fp,"#%d\n",&addressBook->contactCount); //load contact count from file
    for(int i=0;i<addressBook->contactCount;i++)
    {
        //load each contact's details from file using fscanf because fscanf can format input in human readable way
        fscanf(fp," %[^,],%[^,],%[^\n]",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fp); //close file after reading
    
}
