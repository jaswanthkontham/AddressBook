#include "contact.h"
// Dummy contact data
static Contact dummyContacts[] = {
    {"John Doe", "1234567890", "john@gmail.com"},
    {"Alice Smith", "0987654321", "alice@gmail.com"},
    {"Bob Johnson", "1112223333", "bob@gmail.com"},
    {"Ian Lewis", "8889990022", "ian_lewis@gmail.com"},
    {"Carol White", "4445556666", "carol@gmail.com"},
    {"David Brown", "7778889999", "david@gmail.com"},
    {"Eve Davis", "6665554444", "eve@gmail.com"},
    {"Frank Miller", "3334445555", "frank@gmail.com"},
    {"Grace Wilson", "2223334444", "grace@gmail.com"},
    {"Hannah Clark", "5556667777", "hannah@gmail.com"},
    {"Ian Lewis", "8889990011", "ianlewis@gmail.com"},
    {"Ian Lewis", "8889990033", "ian.lewis@gmail.com"}
};

void populateAddressBook(AddressBook* addressBook)
{
    int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]); // Calculate number of dummy contacts
   // Add dummy contacts to address book until maximum capacity is reached
    for (int i = 0; i < numDummyContacts && addressBook->contactCount < MAX_CONTACTS; ++i) 
    {
        addressBook->contacts[addressBook->contactCount++] = dummyContacts[i];// Add dummy contact to address book
    } 
}