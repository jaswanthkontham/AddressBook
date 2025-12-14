/*  
    Name: Kontham Jaswanth Kumar  
    Date: 09/12/2025  
    Description of the Project:
        Address Book Project is a C-based console application designed to manage contacts 
        with details such as name, phone number, and email. The project supports creating, 
        editing, deleting, searching, listing, and validating contacts with persistent 
        storage handled through a CSV file.

        It allows users to interact with the address book efficiently through a 
        menu-driven interface, ensuring proper validation for name, phone number, 
        and email fields.

        Below are the functionalities provided by this project:

        Create Contact:  
            Add new contacts with name, phone number, and email.  
            Supports validation for all input fields.  
            Allows creating multiple contacts in a single session.

        List Contacts:  
            Displays all contacts in a formatted table.  
            Supports sorting contacts alphabetically by name, phone number, or email.  

        Search Contacts:  
            Search for contacts by name, phone number, or email.  
            Displays all matching results and handles multiple matches appropriately.

        Edit Contact:  
            Modify name, phone number, email, or all fields of a contact.  
            Supports selecting the exact contact when multiple matches are found.  
            Ensures the updated details are validated and stored correctly.

        Delete Contact:  
            Remove a contact using name, phone number, or email.  
            Automatically shifts remaining contacts and updates the list.  
            Handles deletion when multiple contacts share the same name.

        Save Contacts:  
            Writes all contact entries into a CSV file (contacts.csv) for persistent storage.  
            Includes the contact count and ensures safe data writing.

        Load Contacts:  
            Reads all contact data from the CSV file at program startup.  
            Restores the contact list with proper count for immediate use.

*/
#include <stdio.h>
#include "contact.h"
#include "validate.h"
#include "unistd.h"
int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initializing the address book

    do {
        printf("\n                              ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
        printf("                              \33[32m┃                   Address Book Management System                     ┃\n\33[0m");
        printf("                              ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
        printf("\33[32;1m\nAddress Book Menu:\n\33[0m");
        printf("\33[32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\33[0m");
        printf("\33[1m1. Create contact\n\33[0m");
        printf("\33[1m2. Search contact\n\33[0m");
        printf("\33[1m3. Edit contact\n\33[0m");
        printf("\33[1m4. Delete contact\n\33[0m");
        printf("\33[1m5. List all contacts\n\33[0m");
    	printf("\33[1m6. Save contacts\n\33[0m");
        printf("\33[1m7. Exit\n\33[0m");
        printf("\n\33[34;1mEnter your choice: \33[0m");
        scanf("%d", &choice);
        if(choice<1 || choice>7) //if choice is invalid
        {
            printf("\033[0;31mERROR: Invalid Choice! Please Enter Valid Choice from Menu\033[0m\n");
            return 0;
        }
        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5: 
                int sortChoice;
                do
                {
                    printf("\n\33[32;1mSort Contacts By:\33[0m\n");
                    printf("\33[32m━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\33[0m");
                    printf("\33[1m1. Name\n2. Phone Number\n3. Email Address\n\33[0m");
                    printf("\n\33[34;1mEnter your choice: \33[0m");
                    scanf("%d", &sortChoice);         
                    if(sortChoice<1 || sortChoice>3)
                    {
                        printf("\033[0;31mERROR: Invalid Choice\033[0m\n"); //invalid choice
                    }
                } while (sortChoice<1 || sortChoice>3);
                listContacts(&addressBook,sortChoice); //listing contacts based on sort criteria name/phone/email
                break;
            case 6:
                printf("\33[32;1mSaving the Contacts and Exiting...\33[0m\n");
                sleep(1);
                saveContactsToFile(&addressBook); //saving contacts to file
                return 0;
                break;
            case 7:
                return 0;
                break;    
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 7);
    
       return 0;
}
