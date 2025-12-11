#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validate.h"
void listContacts(AddressBook *addressBook,int sortCriteria)
{
    if(addressBook->contactCount==0)
    {
        printf("\n\033[0;31mERROR: No Contacts Available in AddressBook to List\033[0m\n");
        return;
    }
    if(sortCriteria==1)
    {
        int sorted_n;
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            sorted_n=0;
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                    sorted_n=1;
                }
                if(sorted_n==0)
                {
                   break;
                }
            }
        }
    }
    else if(sortCriteria==2)
    {
        int sorted_p;
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            sorted_p=0;
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                    sorted_p=1;
                }
            }
            if(sorted_p==0)
            {
               break;
            }
        }
    }
    else if(sortCriteria==3)
    {
        int sorted_m;
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            sorted_m=0;
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)
                {
                    Contact temp=addressBook->contacts[j];
                    addressBook->contacts[j]=addressBook->contacts[j+1];
                    addressBook->contacts[j+1]=temp;
                    sorted_m=1;
                }
            }
             if(sorted_m==0)
            {
                break;
            } 
        }
    }
    printf("\n");
    printf("***********************************************************************************\n");
    printf(" %-3s| %-25s  %-20s  %-25s \n"," S.No","MEMBER NAME","MEMBER PHONENUMBER","MEMBER EMAIL ADDRESS");
    printf("***********************************************************************************\n");
for(int i=0;i<addressBook->contactCount;i++)
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
    loadContactsFromFile(addressBook); // Load contacts from file during initialization (After files)
}

void saveAndExit(AddressBook *addressBook) 
{
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
    printf("\n");
    sleep(1);
    printf("\33[32mSUCCESS: Contact Created Successfully!\33[0m\n");
}
void searchContact(AddressBook *addressBook) 
{
    int choice;
    int inv_choice =0;
    do
    {
        printf("\n");
        printf("Search Contact By:\n");
        printf("******************************\n");
        printf("1. Name\n2. Phone Number\n3. Email Address\n4. exit to main menu\n");
        printf("Search by[Enter Your Choice]:");
        scanf("%d",&choice);
        getchar();
        printf("\n");
        printf("**********************************************\n");
        if(choice<1 || choice>4)
        {
            inv_choice=1;
        }
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
                        if(strcmp(val_name,addressBook->contacts[i].name)==0)
                        {
                            if(count==1)
                            {
                                printf("\n");
                                printf("\33[32mAvailable Contacts using *%s* Name\33[0m\n",val_name);
                                printf("********************************************************\n"); 
                            }
                            printf("%s |",addressBook->contacts[i].name);
                            printf("%s |",addressBook->contacts[i].phone);
                            printf("%s",addressBook->contacts[i].email);
                            printf("\n");
                            count=0;
                        }
                    }
                    if(count==1)
                    {
                        printf("\033[0;31mERROR: Contact Not Found\033[0m\n");
                        break;
                    }
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
                        if(strcmp(val_phone,addressBook->contacts[i].phone)==0)
                        {   
                            printf("\n\33[32mContact Found\33[0m\n");
                            printf("%s |",addressBook->contacts[i].name);
                            printf("%s |",addressBook->contacts[i].phone);
                            printf("%s",addressBook->contacts[i].email);
                            printf("\n");
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
                rtn_m=validate_mail(val_mail);
                if(rtn_m==1)
                {   int count=1;
                    for(int i=0;i<addressBook->contactCount;i++)
                    {
                        if(strcmp(val_mail,addressBook->contacts[i].email)==0)
                        {
                            printf("%s |",addressBook->contacts[i].name);
                            printf("%s |",addressBook->contacts[i].phone);
                            printf("%s",addressBook->contacts[i].email);
                            printf("\n");
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
        case 4:
            printf("Exiting to AddressBook Main Menu\n");
            printf("**********************************************\n");
            return;
            break;    
        default:
        printf("\033[0;31mERROR: Invalid Choice\033[0m\n");
        break;
        }
    }while(inv_choice==1);
}

void editContact(AddressBook *addressBook)
{
    int e_choice;
    do
    {
        printf("\n");
        printf("Edit Contact By:\n");
        printf("******************************\n");
        printf("1. Name\n2. Phone Number\n3. Email Address\n4. exit to main menu\n");
        printf("Edit by[Enter Your Choice]:");
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
                        e_rtn_name=validate_name(e_name);
                        if(e_rtn_name)
                        {
                            int e_count=0;
                            int e;
                            int e_arr[50];
                            for(e=0;e<addressBook->contactCount;e++)
                            {
                                if(strcmp(e_name,addressBook->contacts[e].name)==0)
                                {   
                                    if(e_count==0)
                                    {
                                        printf("\n");
                                        printf("Available Contacts using *%s* Name\n",e_name);
                                        printf("********************************************************\n"); 
                                    }
                                    printf("%d .",e+1);
                                    printf("%s |",addressBook->contacts[e].name);
                                    printf(" %s |",addressBook->contacts[e].phone);
                                    printf(" %s",addressBook->contacts[e].email);
                                    e_count++;
                                    e_arr[e_count-1]=e;
                                    printf("\n");
                                }
                            }  
                            if(e_count)
                            {
                                printf("Please specify Index of Contact to edit.\n");
                                int index;
                                printf("Enter Index:");
                                scanf("%d",&index);
                                getchar();
                                int j,check=0;
                                for(j=0;j<e_count;j++)
                                {
                                    if(index-1==e_arr[j])
                                    {
                                        check=1;
                                        break;
                                    }
                                }
                                if(check==0)
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
                                    sleep(1);
                                    printf("\33[32mContact Updated Successfully! from *%s* to %s \33[0m\n",e_name,new_ename);
                                    break;
                                }
                                else
                                {
                                    printf("\033[0;31mEDIT ABORTED.\033[0m\n");
                                    break;
                                }    
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
                char e_phone[15];
                int e_rtn_phone;
                    do
                    {
                        printf("Enter PhoneNumber to Edit: ");
                        scanf("%10[^\n]",e_phone);
                        getchar();
                        e_rtn_phone=validate_phone(e_phone);
                        if(e_rtn_phone)
                        {
                            int temp=-1;
                            for(int i=0;i<addressBook->contactCount;i++)
                            {
                                if(strcmp(e_phone,addressBook->contacts[i].phone)==0)
                                {  
                                    printf("\n");
                                    printf("\33[32mAvailable Contact using *%s* PhoneNumber\33[0m\n",e_phone);
                                    printf("********************************************************\n"); 
                                    printf("%d .",i+1);
                                    printf("%s |",addressBook->contacts[i].name);
                                    printf(" %s |",addressBook->contacts[i].phone);
                                    printf(" %s",addressBook->contacts[i].email);
                                    printf("\n");
                                    temp=i;
                                }
                            }  
                            if(temp<0)
                            {
                                printf("\033[0;31mERROR: Contact Not Found to Edit\033[0m\n");
                                break;
                            }
                            if(temp>=0)
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
                                    sleep(1);
                                    printf("\33[32mContact Updated Successfully! from *%s* to %s \33[0m\n",e_phone,new_ephone);
                                    break;
                                }
                                else
                                {
                                    printf("\033[0;31mEDIT ABORTED.\033[0m\n");
                                    break;
                                }    
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
                    getchar();
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
                        if(flag==0)
                        {
                        printf("\033[0;31mERROR: Contact Not Found to Edit\033[0m\n");
                        break;
                        }
                        if(flag)
                        {
                            char new_email[30];
                            printf("Enter New Email for Contact *%s*: ",e_mail);
                            scanf("%[^\n]",new_email);
                            getchar();
                            int new_rtn_mail=validate_mail(new_email);
                            for(int i=0;i<addressBook->contactCount;i++)
                            {
                                if(strcmp(new_email,addressBook->contacts[i].email)==0)
                                {
                                    printf("\033[0;31m%s ERROR: This Email Already Exists in AddressBook\033[0m\n",new_email);   
                                    new_rtn_mail=0;
                                }
                            }
                            if(new_rtn_mail==1)
                            {
                                strcpy(addressBook->contacts[temp].email,new_email);
                                sleep(1);
                                printf("\33[32mContact Updated Successfully! from *%s* to %s\33[0m] \n",e_mail,new_email);
                                break;
                            }
                            else
                            {
                                printf("\033[0;31mEDIT ABORTED.\033[0m\n");
                                break;
                            }    
                        }
                    }    
                
                } while(e_rtn_mail==0);
                    break;
                case 4:
                    printf("Exiting to AddressBook Main Menu\n");
                    printf("**********************************************\n");
                    return;            
            }
    }while (e_choice!=4);
}
void deleteContact(AddressBook *addressBook)
{
    char d_name[30];
    char d_phone[15];
    char d_mail[30];
    int d_choice;
    do
    {
        printf("\n");
        printf("Delete Contact By:\n");
        printf("******************************\n");
        printf("1.Name\n2.PhoneNumber\n3.Email Address\n4.Exit To Main Menu\n");
        printf("Enter YOur Choice: ");
        scanf("%d",&d_choice);
        getchar();
        switch(d_choice)
        {
            case 1:
            int rtn_d_name;
            do
            {
                printf("Enter Name of the Contact to  Delete: \n");
                scanf("%[^\n]",d_name);
                getchar();
                rtn_d_name=validate_name(d_name);
                if(rtn_d_name)
                {
                    int d_count=0;
                    for(int i=0;i<addressBook->contactCount;i++)
                    {  
                        if(strcmp(d_name,addressBook->contacts[i].name)==0)
                        {
                            if(d_count==0)
                            {
                                printf("\n");
                                printf("\33[32mAvailable Contacts using *%s* Name\33[0m\n",d_name);
                                printf("********************************************************\n"); 
                            }
                            d_count++;
                            printf("%s |",addressBook->contacts[i].name);
                            printf("%s |",addressBook->contacts[i].phone);
                            printf("%s",addressBook->contacts[i].email);
                            printf("\n");
                        }
                    }
                    if(d_count==0)
                    {
                        printf("\033[0;31mERROR: Contact Not Found to Delete\033[0m\n");
                        break;
                    }
                    else if(d_count==1)
                    {
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            if(strcmp(d_name,addressBook->contacts[i].name)==0)
                            {
                                for(int j=i;j<addressBook->contactCount-1;j++)
                                {
                                    addressBook->contacts[j]=addressBook->contacts[j+1];
                                }
                                addressBook->contactCount--;
                                printf("\n");
                                printf("\33[33m Deleting Contact from AddressBook\33[0m\n");
                                sleep(2);
                                printf("\033[32m SUCCESS: Contact Deleted Successfully!\033[0m\n");
                                break;
                            
                            }
                        }
                    }
                    if(d_count>1)
                    {
                     char temp_d_phone_mail[30];
                                printf("Multiple Contacts Found with same Name, Please enter your PhoneNumber/Email of %s\n",d_name);
                                scanf("%29[^\n]",temp_d_phone_mail);
                                getchar();
                                int found=0;
                                int index;
                                for(int i=0;i<addressBook->contactCount;i++)
                                {
                                    if(strcmp(temp_d_phone_mail,addressBook->contacts[i].phone)==0)
                                    {
                                        index=i;
                                        found=1;
                                        for(int j=index;j<addressBook->contactCount-1;j++)
                                        {
                                            addressBook->contacts[j]=addressBook->contacts[j+1];
                                        }
                                        printf("\n");
                                        printf("\33[33m Deleting Contact from AddressBook\33[0m\n");
                                        sleep(2);
                                        printf("\033[32m SUCCESS: Contact Deleted Successfully!\033[0m\n");
                                        addressBook->contactCount--;
                                        break;
                                    }
                                    else if(strcmp(temp_d_phone_mail,addressBook->contacts[i].email)==0)
                                    {
                                        index=i;
                                        found=1;
                                        for(int j=index;j<addressBook->contactCount-1;j++)
                                        {
                                            addressBook->contacts[j]=addressBook->contacts[j+1];
                                        }
                                        printf("\n");
                                        printf("\33[33m Deleting Contact from AddressBook\33[0m\n");
                                        sleep(2);
                                        printf("\033[32m SUCCESS: Contact Deleted Successfully!\033[0m\n");
                                        addressBook->contactCount--;
                                        break;
                                    }
                                }
                                if(found==0)
                                {
                                    printf("\033[0;31mERROR: Contact Not Found to Edit\033[0m\n");
                                    break;
                                }
                    }            
                }
            } while (rtn_d_name==0);
            break;
            case 2:
                int rtn_d_phone;
                do
                {
                    printf("Enter PhoneNumber of the Contact to  Delete: \n");
                    scanf("%[^\n]",d_phone);
                    getchar();
                    rtn_d_phone=validate_phone(d_phone);
                    if(rtn_d_phone)
                    {
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            if(strcmp(d_phone,addressBook->contacts[i].phone)==0)
                            {
                                printf("\n");
                                printf("\33[32mAvailable Contact using *%s* PhoneNumber\33[0m\n",d_phone);
                                printf("********************************************************\n"); 
                                printf("%d .",i+1);
                                printf("%s |",addressBook->contacts[i].name);
                                printf("%s |",addressBook->contacts[i].phone);
                                printf("%s",addressBook->contacts[i].email);
                                printf("\n");
                                for(int j=i;j<addressBook->contactCount-1;j++)
                                {
                                    addressBook->contacts[j]=addressBook->contacts[j+1];
                                }
                                addressBook->contactCount--;
                                printf("\n");
                                printf("\33[33m Deleting Contact from AddressBook\33[0m\n");
                                sleep(2);
                                printf("\033[32m SUCCESS: Contact Deleted Successfully!\033[0m\n");
                            
                            }
                        }
                    }
                } while (rtn_d_phone==0);
            break;
            case 3:
                int rtn_d_mail;
                do
                {
                    printf("Enter EmailAddress of the Contact to  Delete: \n");
                    scanf("%[^\n]",d_mail);
                    getchar();
                    rtn_d_mail=validate_mail(d_mail);
                    if(rtn_d_mail)
                    {
                        int d_count=0;
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            if(strcmp(d_mail,addressBook->contacts[i].email)==0)
                            {
                                d_count=1;
                                printf("\n");
                                printf("\33[32mAvailable Contact using *%s* EmailAddress[33[0m\n",d_mail);
                                printf("********************************************************\n"); 
                                printf("%d .",i+1);
                                printf("%s |",addressBook->contacts[i].name);
                                printf("%s |",addressBook->contacts[i].phone);
                                printf("%s",addressBook->contacts[i].email);
                                printf("\n");
                                for(int j=i;j<addressBook->contactCount-1;j++)
                                {
                                    addressBook->contacts[j]=addressBook->contacts[j+1];
                                }
                                addressBook->contactCount--;
                                printf("\n");
                                printf("\33[33m Deleting Contact from AddressBook\33[0m\n");
                                sleep(2);
                                printf("\033[32m SUCCESS: Contact Deleted Successfully!\033[0m\n");
                            }
                        }
                        if(d_count==0)
                        {
                            printf("\033[0;31mERROR: Contact Not Found to Delete\033[0m\n");
                            break;
                        }    
                        
                    }
                } while (rtn_d_mail==0);
            break;
            case 4:
            return;
            break;
            default:
            printf("Invalid Choice\n");
            break;
        }
    } while (d_choice!=4);  
}
