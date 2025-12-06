#include <stdio.h>
#include "contact.h"
#include "validate.h"
#include "unistd.h"
int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("******************************\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if(choice<1 || choice>7)
        {
            printf("\033[0;31mERROR: Invalid Choice! Please Enter Valid Choice from Menu\033[0m\n");
            return 0;
        }
        
        switch (choice) {
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
            printf("\n\33[32mSort Contacts By:\33[0m\n");
            printf("1. Name\n2. Phone Number\n3. Email Address\n");
            printf("Enter your choice: ");
            int sortChoice;
            scanf("%d", &sortChoice);         
                listContacts(&addressBook,sortChoice);
                break;
            case 6:
                printf("\33[32mSaving and Exiting...\33[0m\n");
                sleep(1);
                saveContactsToFile(&addressBook);
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
