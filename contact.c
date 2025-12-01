#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validate.h"
void listContacts(AddressBook *addressBook)//, int sortCriteria) 
{
    getchar();
    printf("\n");
    printf("**********************************************************************************\n");
    printf(" %-3s| %-25s  %-20s  %-25s \n"," S.No","  MEMBER NAME","MEMBER PHONENUMBER","MEMBER EMAIL ADDRESS");
    printf("**********************************************************************************\n");
for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%4d .",i+1);
        printf("| %-25s | ",addressBook->contacts[i].name);
        printf(" %-15s | ",addressBook->contacts[i].phone);
        printf(" %-25s |",addressBook->contacts[i].email);
        printf("\n");
    }
    // Sort contacts based on the chosen criteria
}
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0
    ;
    populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    char name[30];
    char phone[15];
    char mail[30];
  int rtn;
  getchar();
    do
    {
        printf("Enter your name: ");
        scanf("%[^\n]",name);
        getchar();
        rtn= validate_name(name);
    } while (rtn==0);
    int rtn_phone;
    do
    {
        printf("Enter your Phone Number: ");
        scanf("%10[^\n]",phone);
        getchar();
        rtn_phone=validate_phone(phone);//make validation
        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(phone,addressBook->contacts[i].phone)==0)
            {
                printf("\033[0;31m%sERROR: This Phone Number Already Exists in AddressBook\033[0m\n",phone);
                rtn_phone=0;
            }
        }
    } while (rtn_phone==0);
    int rtn_mail;
    do
    {
        printf("Enter your Email Address: ");
         scanf("%[^\n]",mail);
         getchar();
         rtn_mail=validate_mail(mail);//make validation
         for(int i=0;i<addressBook->contactCount;i++)
         {
            if(strcmp(mail,addressBook->contacts[i].email)==0)
            {
                printf("\033[0;31m%s ERROR: This Email Address Already Exists in AddressBook\033[0m\n",mail);
                rtn_mail=0;
            }
         }
    } while (rtn_mail==0); //NOT SUCCESS
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email,mail);
    addressBook->contactCount++;
	/* Define the logic to create a Contacts */
}
void searchContact(AddressBook *addressBook) 
{
    do
    {
        printf("\n");
        printf("Search Contact By:\n");
        printf("1. Name\n2. Phone Number\n3. Email Address\n4. exit to main menu\n");
        printf("Search by[Enter Your Choice]:");
        int choice;
        scanf("%d",&choice);
        printf("\n");
        printf("**********************************************\n");
        if(choice==4)
        {
            printf("Exiting to AddressBook Main Menu\n");
            printf("**********************************************\n");
            return;
        }
        printf("Here the avalilable contacts are:\n");
        listContacts(addressBook);
        switch (choice)
        {
        case 1:
            char val_name[30];
            int rtn_n;
            do
            {
                printf("Enter Name to be searched:");
                scanf("%[^\n]",val_name);
                getchar();
                rtn_n=validate_name(val_name);
                if(rtn_n==1)
                {   int count=1;
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        //printf("Comparing with: %s\n",addressBook->contacts[i].name);
                        if(strcmp(val_name,addressBook->contacts[i].name)==0)
                        {
                            printf("Contact Found:\n");
                            printf("Name: %s\n",addressBook->contacts[i].name);
                            printf("Phone Number: %s\n",addressBook->contacts[i].phone);
                            printf("Email Address: %s\n",addressBook->contacts[i].email);
                            count++;
                        }
                    }
                    if(count==1)
                    {
                        printf("\033[0;31mERROR: Contact Not Found\033[0m\n");
                        break;
                    }
                    // elseif(count!=1)
                    // {
                    //     for(int i=0;i<count;i++)
                    //     {
                            
                    //     }
                    // }
                }    
            }while(rtn_n==0);
            break;
        case 2:    
            char val_phone[15];
            int rtn_p;
            do
            {
                printf("Enter Phone Number to be searched:");
                scanf("%10[^\n]",val_phone);
                getchar();
                rtn_p=validate_phone(val_phone);
                if(rtn_p==1)
                {   int count=1;
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        //printf("Comparing with: %s\n",addressBook->contacts[i].name);
                        if(strcmp(val_phone,addressBook->contacts[i].phone)==0)
                        {
                            printf("Contact Found:\n");
                            printf("Name: %s\n",addressBook->contacts[i].name);
                            printf("Phone Number: %s\n",addressBook->contacts[i].phone);
                            printf("Email Address: %s\n",addressBook->contacts[i].email);
                            count--;
                        }
                    }
                    if(count==1)
                    {
                        printf("\033[0;31mERROR: Contact Not Found\033[0m\n");
                        break;
                    }
                }    
            }while(rtn_p==0);
            break;
        case 3:
            char val_mail[50];
            int rtn_m;
            do
            {
                printf("Enter Email to be searched:");
                scanf("%[^\n]",val_mail);
                getchar();
                rtn_m=validate_mail(val_phone);
                if(rtn_m==1)
                {   int count=1;
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        //printf("Comparing with: %s\n",addressBook->contacts[i].name);
                        if(strcmp(val_mail,addressBook->contacts[i].email)==0)
                        {
                            printf("Contact Found:\n");
                            printf("Name: %s\n",addressBook->contacts[i].name);
                            printf("Phone Number: %s\n",addressBook->contacts[i].phone);
                            printf("Email Address: %s\n",addressBook->contacts[i].email);
                            count--;
                        }
                    }
                    if(count==1)
                    {
                        printf("\033[0;31mERROR: Contact Not Found\033[0m\n");
                        break;
                    }
                }    
            } while(rtn_m==0);
            break; 
        default:
        printf("\033[0;31mERROR: Invalid Choice\033[0m\n");
            break;
        }
    }while(1);

    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
    int e_choice;
    do
    {
    printf("\n");
        printf("Edit Contact By:\n");
        printf("1. Name\n2. Phone Number\n3. Email Address\n4. exit to main menu\n");
        printf("Edit by[Enter Your Choice]:");
        scanf("%d",&e_choice);
        getchar();
        printf("\n");
        printf("**********************************************\n");
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
                        e_rtn_name=validate_name(e_name);
                        if(e_rtn_name)
                        {
                            int e_count=0;
                            printf("Available Contacts using /*%s*/ Name\n",e_name);
                            for(int i=0;i<addressBook->contactCount;i++)
                            {
                                if(strcmp(e_name,addressBook->contacts[i].name)==0)
                                {   
                                    printf("%d .",i+1);
                                    printf("%s |",addressBook->contacts[i].name);
                                    printf(" %s |",addressBook->contacts[i].phone);
                                    printf(" %s",addressBook->contacts[i].email);
                                    e_count++;
                                    printf("\n");
                                }
                            }  
                            for(int i=0;i<addressBook->contactCount;i++)
                            if(e_count)
                            {
                                printf("Please specify Index of Contact to edit.\n");
                                int index;
                                printf("Enter Index:");
                                scanf("%d",&index);
                                getchar();
                                if(index<0 || index>addressBook->contactCount)
                                {
                                    printf("\033[0;31mERROR: Invalid Index Selected\033[0m\n");
                                    break;
                                }
                                char new_ename[30];
                                printf("Enter New Name for Contact *%s*: ",e_name);
                                scanf("%[^\n]",new_ename);
                                getchar();
                                int new_rtn_name=validate_name(new_ename);
                                if(new_rtn_name==1)
                                {
                                    strcpy(addressBook->contacts[index-1].name,new_ename);
                                    printf("Contact Updated Successfully! from *%s* to %s \n",e_name,new_ename);
                                    break;
                                }
                                else
                                {
                                    printf("\033[0;31mEDIT ABORTED.\033[0m\n");
                                   // goto()
                                    break;
                                }    
                                
                                // printf("Enter Phone number or Email to identify contact of %s Person\n",e_name);
                                // break;
                            }
                            if(e_count==0)
                            {
                                printf("\033[0;31mERROR: Contact Not Found to Edit\033[0m\n");
                                break;
                            }
                        }
                    } while (e_rtn_name==0);
                    break;
                case 2:
                char e_phone[30];
                    int e_rtn_phone;
                    do
                    {
                        printf("Enter PhoneNumber to Edit: ");
                        scanf("%[^\n]",e_phone);
                        getchar();
                        e_rtn_phone=validate_phone(e_phone);
                        if(e_rtn_phone)
                        {
                            int temp=0;
                            int flag=0;
                            printf("********************************************************\n");
                            printf("Available Contacts using *%s* PhoneNumber\n",e_phone);
                            printf("********************************************************\n");
                            for(int i=0;i<addressBook->contactCount;i++)
                            {
                                if(strcmp(e_phone,addressBook->contacts[i].phone)==0)
                                {   
                                    printf("%d .",i+1);
                                    printf("%s |",addressBook->contacts[i].name);
                                    printf(" %s |",addressBook->contacts[i].phone);
                                    printf(" %s",addressBook->contacts[i].email);
                                    printf("\n");
                                    temp=i;
                                    flag=1;
                                }
                                else
                                {
                                    temp=-1;
                                }
                            }  
                            if(temp<0)
                            {
                                printf("\033[0;31mERROR: Contact Not Found to Edit\033[0m\n");
                                break;
                            }
                            if(flag)
                            {
                                char new_ephone[15];
                                printf("Enter New PhoneNumber for Contact *%s*: ",e_phone);
                                scanf("%10[^\n]",new_ephone);
                                getchar();
                                int new_rtn_phone=validate_phone(new_ephone);
                                for(int i=0;i<addressBook->contactCount;i++)
                                {
                                    if(strcmp(new_ephone,addressBook->contacts[i].phone)==0)
                                    {
                                        printf("\033[0;31m%s ERROR: This PhoneNumber Already Exists in AddressBook\033[0m\n",new_ephone);   
                                        new_rtn_phone=0;
                                    }
                                }
                                if(new_rtn_phone==1)
                                {
                                    strcpy(addressBook->contacts[temp].phone,new_ephone);
                                    printf("Contact Updated Successfully! from *%s* to %s \n",e_phone,new_ephone);
                                    break;
                                }
                                else
                                {
                                    printf("\033[0;31mEDIT ABORTED.\033[0m\n");
                                   // goto()
                                    break;
                                }    
                                
                                // printf("Enter Phone number or Email to identify contact of %s Person\n",e_name);
                                // break;
                            }

                        }
                    } while (e_rtn_phone==0);
                    break;
                case 3:
                char e_mail[30];
                int e_rtn_mail;
                do
                {
                    printf("Enter Email to Edit:");
                    scanf("%[^\n]",e_mail);
                    int e_rtn_mail=validate_mail(e_mail);

                    if(e_rtn_mail)
                    {
                        int flag=0;
                        int temp=0;
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            if(strcmp(e_mail,addressBook->contacts[i].email)==0)
                            {
                                printf("%s",addressBook->contacts[i].name);
                                printf("%s",addressBook->contacts[i].phone);
                                printf("%s",addressBook->contacts[i].email);
                                printf("\n");
                                flag=1;
                                temp=i;
                            }
                            
                        }
                        if(temp==0)
                        {
                        printf("\033[0;31mERROR: Contact Not Found to Edit\033[0m\n");
                        break;
                        }
                        if(flag)
                        {
                            char new_email[30];
                            printf("Enter New PhoneNumber for Contact *%s*: ",e_mail);
                            scanf("%[^\n]",new_email);
                            getchar();
                            int new_rtn_mail=validate_phone(new_email);
                            for(int i=0;i<addressBook->contactCount;i++)
                            {
                                if(strcmp(new_email,addressBook->contacts[i].email)==0)
                                {
                                    printf("\033[0;31m%s ERROR: This PhoneNumber Already Exists in AddressBook\033[0m\n",new_email);   
                                    new_rtn_mail=0;
                                }
                            }
                            if(new_rtn_mail==1)
                            {
                                strcpy(addressBook->contacts[temp].email,new_email);
                                printf("Contact Updated Successfully! from *%s* to %s \n",e_mail,new_email);
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEDIT ABORTED.\033[0m\n");
                                // goto()
                                break;
                            }    
                            
                            // printf("Enter Phone number or Email to identify contact of %s Person\n",e_name);
                            // break;
                        }
                    }    
                
                } while(e_rtn_mail==0);
                    break;
                case 4:
                    printf("Exiting to AddressBook Main Menu\n");
                    printf("**********************************************\n");
                    return;            
            }
    }while (1);
}
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
   
}
