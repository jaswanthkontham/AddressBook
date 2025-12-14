#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validate.h"
void listContacts(AddressBook *addressBook,int sortCriteria) //list contacts with sorting
{
    if(addressBook->contactCount==0) //no contacts available
    {
        printf("\n\033[0;31mERROR: No Contacts Available in AddressBook to List\033[0m\n");
        return;
    }
    if(sortCriteria==1) //sort by name
    {
        int sorted_n;
        for(int i=0;i<addressBook->contactCount-1;i++) 
        {
            sorted_n=0; 
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0) //compare names if jth name is greater than j+1 th name
                {
                    Contact temp=addressBook->contacts[j]; //swapping contacts 
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                    sorted_n=1;
                }
                if(sorted_n==0) //for optimization if already sorted
                {
                   break;
                }
            }
        }
    }
    else if(sortCriteria==2)//sort by phone number
    {
        int sorted_p;
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            sorted_p=0;
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)//compare phone numbers if jth phone number is greater than j+1 th phone number
                {
                    Contact temp=addressBook->contacts[j];//swapping contacts
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                    sorted_p=1;
                }
            }
            if(sorted_p==0)//for optimization if already sorted
            {
               break;
            }
        }
    }
    else if(sortCriteria==3)//sort by email address
    {
        int sorted_m;
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            sorted_m=0;
            for(int j=0;j<addressBook->contactCount-i-1;j++)//comparing email addresses if jth email is greater than j+1 th email
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                {
                    Contact temp=addressBook->contacts[j];//swapping contacts
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                    sorted_m=1;
                }
            }
             if(sorted_m==0) //for optimization if already sorted
            {
                break;
            } 
        }
    }
    printf("\n");
    printf("***********************************************************************************\n");
    printf(" %-3s| %-25s  %-20s  %-25s \n"," S.No","MEMBER NAME","MEMBER PHONENUMBER","MEMBER EMAIL ADDRESS");
    printf("***********************************************************************************\n");
for(int i=0;i<addressBook->contactCount;i++) //listing contacts after sorting
    {
        printf("%4d .",i+1);
        printf("| %-25s | ",addressBook->contacts[i].name);
        printf(" %-15s | ",addressBook->contacts[i].phone);
        printf(" %-25s | ",addressBook->contacts[i].email);
        printf("\n");
    }
}
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    loadContactsFromFile(addressBook); // Load contacts from contacts.csv file during initialization 
}

void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook) //create new contact
{
    char name[30];
    char phone[15];
    char mail[30];
    int rtn;
    getchar();
    //printf("")
    do
    {
        printf("\33[1m\nEnter your name: \33[0m"); 
        scanf("%[^\n]",name); //taking name as  input
        getchar();
        rtn= validate_name(name); //make validation if name is valid or not in validate.c
    } while (rtn==0);
    int rtn_phone;
    do
    {
        printf("\33[1mEnter your Phone Number: \33[0m");
        scanf("%10[^\n]",phone);
        getchar();
        rtn_phone=validate_phone(phone);////make validation if phone is valid or not in validate.c
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(phone,addressBook->contacts[i].phone)==0) //checking for duplicate phone number
            {
                printf("\033[0;31mERROR:*%s* This Phone Number Already Exists in AddressBook\033[0m\n",phone);
                rtn_phone=0;
            }
        }
    } while (rtn_phone==0);
    int rtn_mail;
    do
    {
        printf("\33[1mEnter your Email Address: \33[0m");
         scanf("%[^\n]",mail);
         getchar();
         rtn_mail=validate_mail(mail);//make validation if email is valid or not in validate.c
         for(int i=0;i<addressBook->contactCount;i++)
         {
            if(strcmp(mail,addressBook->contacts[i].email)==0)//checking for duplicate email address
            {
                printf("\033[0;31mERROR:*%s* This Email Address Already Exists in AddressBook\033[0m\n",mail);
                rtn_mail=0;
            }
         }
    } while (rtn_mail==0); //NOT SUCCESS
    strcpy(addressBook->contacts[addressBook->contactCount].name,name); //storing contact details in addressbook structure
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,mail);
    addressBook->contactCount++;
    printf("\n");
    printf("\33[32;1mSUCCESS: Contact Created Successfully!\33[0m\n");
}
void searchContact(AddressBook *addressBook) //search existing contact
{
    int choice;
    do
    {
        printf("\n");
        printf("\33[32;1mSearch Contact By:\n\33[0m"); 
        printf("\33[32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\33[0m\n");
        printf("\33[1m1. Name\n2. Phone Number\n3. Email Address\n4. exit to main menu\n\33[0m");
        printf("\n\33[34;1mSearch By [Enter your choice]: \33[0m");
        scanf("%d",&choice); //taking choice as input
        getchar();
        printf("\n");
        switch (choice)
        {
            case 1: //search by name
                char val_name[30];
                int rtn_n;
                do
                {
                    printf("Enter Name to be searched:");
                    scanf("%[^\n]",val_name);
                    getchar();
                    rtn_n=validate_name(val_name); //validating name
                    if(rtn_n==1)
                    {   int count=1;
                        for(int i=0;i<addressBook->contactCount;i++) //iterating through contacts
                        {
                            if(strcmp(val_name,addressBook->contacts[i].name)==0) //comparing input name with stored contact names
                            {
                                if(count==1)
                                {
                                    printf("\n");
                                    printf("\33[32mAvailable Contacts using *%s* Name\33[0m\n",val_name);
                                    printf("********************************************************\n"); 
                                }
                                printf("%s |",addressBook->contacts[i].name); //printing contact details if found
                                printf("%s |",addressBook->contacts[i].phone);
                                printf("%s",addressBook->contacts[i].email);
                                printf("\n");
                                count=0;
                            }
                        }
                        if(count==1) //no contact found
                        {
                            printf("\033[0;31mERROR: Contact Not Found\033[0m\n");
                            break;
                        }
                    }    
                }while(rtn_n==0); //NOT SUCCESS
                break;
            case 2:     //search by phone number
                char val_phone[15];
                int rtn_p;
                do
                {
                    printf("Enter Phone Number to be searched:");
                    scanf("%10[^\n]",val_phone);
                    getchar();
                    rtn_p=validate_phone(val_phone);  //validating phone number
                    if(rtn_p==1)
                    {   int count=1;
                        for(int i=0;i<addressBook->contactCount;i++) //iterating through contacts
                        {
                            if(strcmp(val_phone,addressBook->contacts[i].phone)==0) //comparing input phone number with stored contact phone numbers
                            {   
                                printf("\n\33[32mContact Found\33[0m\n");
                                printf("%s |",addressBook->contacts[i].name);
                                printf("%s |",addressBook->contacts[i].phone);
                                printf("%s",addressBook->contacts[i].email);
                                printf("\n");
                                count--;
                            }
                        }
                        if(count==1) //no contact found
                        {
                            printf("\033[0;31mERROR: Contact Not Found\033[0m\n");
                            break;
                        }
                    }    
                }while(rtn_p==0); //NOT SUCCESS
                break;
            case 3://search by email address
                char val_mail[50];
                int rtn_m;
                do
                {
                    printf("Enter Email to be searched:");
                    scanf("%[^\n]",val_mail);
                    getchar();
                    rtn_m=validate_mail(val_mail);
                    if(rtn_m==1)
                    {   int count=1;
                        for(int i=0;i<addressBook->contactCount;i++) //iterating through contacts
                        {
                            if(strcmp(val_mail,addressBook->contacts[i].email)==0)
                            {
                                //comparing input email with stored contact emails
                                printf("%s |",addressBook->contacts[i].name);
                                printf("%s |",addressBook->contacts[i].phone);
                                printf("%s",addressBook->contacts[i].email);
                                printf("\n");
                                count--;
                            }
                        }
                        if(count==1) 
                        { //no contact found
                            printf("\033[0;31mERROR: Contact Not Found\033[0m\n");
                            break;
                        }
                    }    
                } while(rtn_m==0);//NOT SUCCESS
                break; 
            case 4:
                printf("\33[32mExiting to AddressBook Main Menu.........\n\33[0m");
                sleep(1);
                printf("**********************************************\n");
                return;
                break;    
            default:
                printf("\033[0;31mERROR: Invalid Choice\033[0m\n"); //invalid choice
                break;
            }
    }while(choice!=4);//continue until user wants to exit to main menu
}

void editContact(AddressBook *addressBook) //edit existing contact
{
    int e_choice;
    do
    {
        printf("\n");
        printf("\33[32;1mEdit Contact By:\n\33[0m");
        printf("\33[32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\33[0m\n");
        printf("\33[1m1. Name\n2. Phone Number\n3. Email Address\n4. exit to main menu\n\33[0m");
        printf("\n\33[34;1mEdit By [Enter your choice]: \33[0m");
        scanf("%d",&e_choice);
        getchar();
        printf("\n");
            switch(e_choice)
            {
                case 1:
                    char e_name[30];
                    int e_rtn_name;
                    do
                    {
                        printf("Enter Name to Edit: ");
                        scanf("%[^\n]",e_name);
                        getchar();
                        e_rtn_name=validate_name(e_name); //validating name
                        if(e_rtn_name)
                        {
                            int e_count=0;
                            int e;
                            int e_arr[50];
                            for(e=0;e<addressBook->contactCount;e++) //iterating through contacts
                            {
                                if(strcmp(e_name,addressBook->contacts[e].name)==0) //comparing input name with stored contact names
                                {   
                                    if(e_count==0)
                                    {
                                        printf("\n");
                                        printf("Available Contacts using *%s* Name\n",e_name);
                                        printf("********************************************************\n"); 
                                    }
                                    printf("%d .",e+1);
                                    printf("%s |",addressBook->contacts[e].name);//printing contact details if found
                                    printf(" %s |",addressBook->contacts[e].phone);
                                    printf(" %s",addressBook->contacts[e].email);
                                    e_count++;
                                    e_arr[e_count-1]=e; //storing indices of matching contacts
                                    printf("\n");
                                }
                            }  
                            if(e_count) //if contacts found
                            {
                                printf("Please specify Index of Contact to edit.\n");
                                int index; //taking index as input
                                printf("Enter Index:");
                                scanf("%d",&index);
                                getchar();
                                int j,check=0;
                                for(j=0;j<e_count;j++) //checking for valid index
                                {
                                    if(index-1==e_arr[j]) //comparing input index with stored indices of matching contacts
                                    {
                                        check=1;
                                        break;
                                    }
                                }
                                if(check==0) //invalid index
                                {
                                    printf("\033[0;31mERROR: Invalid Index Selected\033[0m\n");
                                    break;
                                }
                                char new_ename[30];
                                printf("Enter New Name for Contact *%s*: ",e_name);
                                scanf("%[^\n]",new_ename);
                                getchar();
                                int new_rtn_name=validate_name(new_ename); //validating new name
                                if(new_rtn_name==1) //if valid
                                {
                                    strcpy(addressBook->contacts[index-1].name,new_ename); //updating name
                                    sleep(1);
                                    printf("\33[32mContact Updated Successfully! from *%s* to %s \33[0m\n",e_name,new_ename);
                                    break;
                                }
                                else
                                {
                                    printf("\033[0;31mEDIT ABORTED.\033[0m\n"); //if not valid
                                    break;
                                }    
                            }
                            if(e_count==0) //no contact found
                            {
                                printf("\033[0;31mERROR: Contact Not Found to Edit\033[0m\n");
                                break;
                            }
                        }
                    } while (e_rtn_name==0);
                    break;
                case 2: //edit by phone number
                char e_phone[15];
                int e_rtn_phone;
                    do
                    {
                        printf("Enter PhoneNumber to Edit: ");
                        scanf("%10[^\n]",e_phone);
                        getchar();
                        e_rtn_phone=validate_phone(e_phone); //validating phone number
                        if(e_rtn_phone)
                        {
                            int temp=-1;
                            for(int i=0;i<addressBook->contactCount;i++) //iterating through contacts
                            {
                                if(strcmp(e_phone,addressBook->contacts[i].phone)==0) //comparing input phone number with stored contact phone numbers
                                {  
                                    printf("\n");
                                    printf("\33[32mAvailable Contact using *%s* PhoneNumber\33[0m\n",e_phone);
                                    printf("********************************************************\n"); 
                                    printf("%d .",i+1);
                                    printf("%s |",addressBook->contacts[i].name); //printing contact details if found
                                    printf(" %s |",addressBook->contacts[i].phone);
                                    printf(" %s",addressBook->contacts[i].email);
                                    printf("\n");
                                    temp=i;
                                }
                            }  
                            if(temp<0) //no contact found
                            {
                                printf("\033[0;31mERROR: Contact Not Found to Edit\033[0m\n");
                                break;
                            }
                            if(temp>=0) //if contact found
                            {
                                char new_ephone[15];
                                int new_rtn_phone=0;
                                do
                                {  
                                    printf("\nEnter New PhoneNumber for Contact *%s*: ",e_phone);
                                    scanf("%10[^\n]",new_ephone);
                                    getchar();
                                    int new_rtn_phone=validate_phone(new_ephone); //validating new phone number
                                    for(int i=0;i<addressBook->contactCount;i++) //iterating through contacts
                                    {
                                        if(strcmp(new_ephone,addressBook->contacts[i].phone)==0) //checking for duplicate phone number
                                        {
                                            printf("\033[0;31m%s ERROR: This PhoneNumber Already Exists in AddressBook\033[0m\n",new_ephone);   
                                            new_rtn_phone=0;
                                        }
                                    }
                                    if(new_rtn_phone==1) //if valid
                                    {
                                        strcpy(addressBook->contacts[temp].phone,new_ephone); //updating phone number
                                        sleep(1);
                                        printf("\n\33[32mContact Updated Successfully! from *%s* to %s \33[0m\n",e_phone,new_ephone);
                                        break;
                                    }
                                    
                                }while (new_rtn_phone==0);
                            }
                        }
                    } while (e_rtn_phone==0); //NOT SUCCESS
                    break;
                case 3: //edit by email address
                char e_mail[30];
                int e_rtn_mail;
                do
                {
                    printf("Enter Email to Edit:");
                    scanf("%[^\n]",e_mail);
                    getchar();
                    int e_rtn_mail=validate_mail(e_mail); //validating email address

                    if(e_rtn_mail)
                    {
                        int flag=0;
                        int temp=0;
                        for(int i=0;i<addressBook->contactCount;i++) //iterating through contacts
                        {
                            if(strcmp(e_mail,addressBook->contacts[i].email)==0) // comparing input email with stored contact emails
                            { 
                                printf("\n");
                                printf("\33[32mAvailable Contact using *%s* Email Address\33[0m\n",e_mail);
                                printf("********************************************************\n"); 
                                printf("%d .",i+1);
                                printf("%s |",addressBook->contacts[i].name); //printing contact details if found
                                printf(" %s |",addressBook->contacts[i].phone);
                                printf(" %s",addressBook->contacts[i].email);
                                printf("\n");
                                flag=1;
                                temp=i;
                            } 
                        }
                        if(flag==0) //no contact found
                        {
                        printf("\033[0;31mERROR: Contact Not Found to Edit\033[0m\n");
                        break;
                        }
                        if(flag) //if contact found
                        {
                            char new_email[30];
                            int new_rtn_mail=0;
                            do
                            {
                                printf("\nEnter New Email for Contact *%s*: ",e_mail);
                                scanf("%[^\n]",new_email);
                                getchar();
                                new_rtn_mail=validate_mail(new_email); //validating new email address
                                for(int i=0;i<addressBook->contactCount;i++)
                                {
                                    if(strcmp(new_email,addressBook->contacts[i].email)==0) //checking for duplicate email address
                                    {
                                        printf("\033[0;31m%s ERROR: This Email Already Exists in AddressBook\033[0m\n",new_email);   
                                        new_rtn_mail=0;
                                    }
                                }
                                if(new_rtn_mail==1)
                                {
                                    strcpy(addressBook->contacts[temp].email,new_email); //updating email address
                                    sleep(1);
                                    printf("\33[32mContact Updated Successfully! from *%s* to %s\33[0m] \n",e_mail,new_email);
                                    break;
                                }
                            } while (new_rtn_mail==0);
                        }
                    }    
                
                } while(e_rtn_mail==0); //NOT SUCCESS
                    break;
                case 4:
                    printf("\33[32mExiting to AddressBook Main Menu.........\n\33[0m");
                    sleep(1);
                    printf("**********************************************\n");
                    return;   
                    break; 
                default:
                    printf("\033[0;31mERROR: Invalid Choice\033[0m\n"); //invalid choice
                    break;            
            }
    }while (e_choice!=4); //continue until user wants to exit to main menu
}
void deleteContact(AddressBook *addressBook) //delete existing contact
{
    char d_name[30];
    char d_phone[15];
    char d_mail[30];
    int d_choice;
    do
    {
        printf("\n");
        printf("\33[32;1mDelete Contact By:\n\33[0m");
        printf("\33[32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\33[0m\n");
        printf("\33[1m1.Name\n2.PhoneNumber\n3.Email Address\n4.Exit To Main Menu\n\33[0m");
        printf("\n\33[34;1mDelete By [Enter your choice]: \33[0m");
        scanf("%d",&d_choice);
        getchar();
        switch(d_choice) 
        {
            case 1: //delete by name
                int rtn_d_name;
                do
                {
                    printf("Enter Name of the Contact to  Delete: ");
                    scanf("%[^\n]",d_name);
                    getchar();
                    rtn_d_name=validate_name(d_name); //validating name
                    if(rtn_d_name)
                    {
                        int d_count=0;
                        for(int i=0;i<addressBook->contactCount;i++)//iterating through contacts
                        {  
                            if(strcmp(d_name,addressBook->contacts[i].name)==0) //comparing input name with stored contact names
                            {
                                if(d_count==0)
                                {
                                    printf("\n");
                                    printf("\33[32mAvailable Contacts using *%s* Name\33[0m\n",d_name);
                                    printf("********************************************************\n"); 
                                }
                                d_count++;
                                printf("%s |",addressBook->contacts[i].name); //printing contact details if found
                                printf("%s |",addressBook->contacts[i].phone);
                                printf("%s",addressBook->contacts[i].email);
                                printf("\n");
                            }
                        }
                        if(d_count==0) //no contact found
                        {
                            printf("\033[0;31mERROR: Contact Not Found to Delete\033[0m\n");
                            break;
                        }
                        else if(d_count==1) //if only one contact found
                        {
                            for(int i=0;i<addressBook->contactCount;i++)
                            {
                                if(strcmp(d_name,addressBook->contacts[i].name)==0) //comparing input name with stored contact names
                                {
                                    for(int j=i;j<addressBook->contactCount-1;j++)
                                    {
                                        addressBook->contacts[j]=addressBook->contacts[j+1]; //shifting contacts to delete the contact
                                    }
                                    addressBook->contactCount--; //decreasing contact count
                                    printf("\n");
                                    printf("\33[33m Deleting Contact from AddressBook\33[0m\n");
                                    sleep(2);
                                    printf("\033[32m SUCCESS: Contact Deleted Successfully!\033[0m\n");
                                    break;
                                
                                }
                            }
                        }
                        if(d_count>1) //if multiple contacts found
                        {
                            char temp_d_phone_mail[30];
                            //int rtn_d_email=0;
                            int rtn_d_phone=0;
                            do
                            {
                                printf("\n\33[34;1mMultiple Contacts Found with same Name, Please enter your PhoneNumber/Email of %s :\33[0m",d_name);
                                scanf("%29[^\n]",temp_d_phone_mail);
                                getchar();
                                rtn_d_phone=validate_phone(temp_d_phone_mail);
                                //rtn_d_email=validate_mail(temp_d_phone_mail);
                                if(rtn_d_phone)
                                {
                                int found=0;
                                int index;
                                for(int i=0;i<addressBook->contactCount;i++) //iterating through contacts
                                {
                                    if(strcmp(temp_d_phone_mail,addressBook->contacts[i].phone)==0) //comparing input phone number with stored contact phone numbers
                                    {
                                        index=i;
                                        found=1;
                                        for(int j=index;j<addressBook->contactCount-1;j++) //shifting contacts to delete the contact
                                        {
                                            addressBook->contacts[j]=addressBook->contacts[j+1];
                                        }
                                        printf("\n");
                                        printf("\33[33m Deleting Contact from AddressBook\33[0m\n");
                                        sleep(2);
                                        printf("\033[32;1m SUCCESS: Contact Deleted Successfully!\033[0m\n");
                                        addressBook->contactCount--;//decreasing contact count
                                        break;
                                    }
                                    else if(strcmp(temp_d_phone_mail,addressBook->contacts[i].email)==0) //comparing input email with stored contact emails
                                    {
                                        index=i;
                                        found=1;
                                        for(int j=index;j<addressBook->contactCount-1;j++)//shifting contacts to delete the contact
                                        {
                                            addressBook->contacts[j]=addressBook->contacts[j+1];
                                        }
                                        printf("\n");
                                        printf("\33[33m Deleting Contact from AddressBook\33[0m\n");
                                        sleep(2);
                                        printf("\033[32;1m SUCCESS: Contact Deleted Successfully!\033[0m\n");
                                        addressBook->contactCount--;//decreasing contact count
                                        break;
                                    }
                                    
                                }
                                if(found==0) //no contact found with given phone/email
                                {
                                    printf("\033[0;31mERROR: Contact Not Found to Edit\033[0m\n");
                                    break;
                                }
                                }
                                
                            } while (rtn_d_phone==0);
                        }            
                    }
                } while (rtn_d_name==0); //NOT SUCCESS
                    break;
                case 2: //delete by phone number
                    int rtn_d_phone;
                    do
                    {
                        printf("Enter PhoneNumber of the Contact to  Delete: ");
                        scanf("%[^\n]",d_phone);
                        getchar();
                        rtn_d_phone=validate_phone(d_phone); //validating phone number
                        if(rtn_d_phone)
                        {
                            int d_count=0;
                            for(int i=0;i<addressBook->contactCount;i++) 
                            {
                                if(strcmp(d_phone,addressBook->contacts[i].phone)==0) //comparing input phone number with stored contact phone numbers
                                {
                                    d_count=1;
                                    printf("\n");
                                    printf("\33[32mAvailable Contact using *%s* PhoneNumber\33[0m\n",d_phone);
                                    printf("********************************************************\n"); 
                                    printf("%d .",i+1);
                                    printf("%s |",addressBook->contacts[i].name); //printing contact details if found
                                    printf("%s |",addressBook->contacts[i].phone);
                                    printf("%s",addressBook->contacts[i].email);
                                    printf("\n");
                                    for(int j=i;j<addressBook->contactCount-1;j++) //shifting contacts to delete the contact
                                    {
                                        addressBook->contacts[j]=addressBook->contacts[j+1];
                                    }
                                    addressBook->contactCount--; //decreasing contact count
                                    printf("\n");
                                    printf("\33[33m Deleting Contact from AddressBook\33[0m\n");
                                    sleep(2);
                                    printf("\033[32;1m SUCCESS: Contact Deleted Successfully!\033[0m\n");
                                
                                }
                            }
                            if(d_count==0) //no contact found
                            {
                                printf("\033[0;31mERROR: Contact Not Found to Delete\033[0m\n");
                                break;
                            }  
                        }
                    } while (rtn_d_phone==0);
                    break;
            case 3: //delete by email address
                int rtn_d_mail;
                do
                {
                    printf("Enter EmailAddress of the Contact to  Delete: ");
                    scanf("%[^\n]",d_mail);
                    getchar();
                    rtn_d_mail=validate_mail(d_mail); //validating email address
                    if(rtn_d_mail)
                    {
                        int d_count=0;
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            if(strcmp(d_mail,addressBook->contacts[i].email)==0) //comparing input email with stored contact emails
                            {
                                d_count=1;
                                printf("\n");
                                printf("\33[32mAvailable Contact using *%s* EmailAddress\33[0m\n",d_mail);
                                printf("********************************************************\n"); 
                                printf("%d .",i+1);
                                printf("%s |",addressBook->contacts[i].name); //printing contact details if found
                                printf("%s |",addressBook->contacts[i].phone);
                                printf("%s",addressBook->contacts[i].email);
                                printf("\n");
                                for(int j=i;j<addressBook->contactCount-1;j++) //shifting contacts to delete the contact
                                {
                                    addressBook->contacts[j]=addressBook->contacts[j+1];
                                }
                                addressBook->contactCount--; //decreasing contact count
                                printf("\n");
                                printf("\33[33m Deleting Contact from AddressBook\33[0m\n");
                                sleep(2);
                                printf("\033[32;1m SUCCESS: Contact Deleted Successfully!\033[0m\n");
                            }
                        }
                        if(d_count==0) //no contact found
                        {
                            printf("\033[0;31mERROR: Contact Not Found to Delete\033[0m\n");
                            break;
                        }    
                        
                    }
                } while (rtn_d_mail==0); //NOT SUCCESS
                break;
            case 4: //exit to main menu
                printf("\33[32mExiting to AddressBook Main Menu.........\n\33[0m");
                sleep(1);
                printf("**********************************************\n");
                return;
                break;
            default:
                printf("\033[0;31mERROR: Invalid Choice\033[0m\n"); //invalid choice
                break;
        }
    } while (d_choice!=4);   //continue until user wants to exit to main menu
}
