#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

// Structures for the Fields
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

// Structures for the Contact deatils
typedef struct {
    // Array of structures for the Fields sturucture
    Contact contacts[MAX_CONTACTS];
    // To keep the track no of contact count
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void loadContactsFromFile(AddressBook *addressBook);
#endif
