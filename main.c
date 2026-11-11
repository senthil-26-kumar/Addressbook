#include <stdio.h>
#include "contact.h"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    while(1)
    {
        printf("\n========== ADDRESS BOOK MENU ==========\n");
        printf("1. Create Contact\n");
        printf("2. Search Contact\n");
        printf("3. Edit Contact\n");
        printf("4. Delete Contact\n");
        printf("5. List All Contacts\n");
        printf("6. Save Contacts to File\n");
        printf("7. Exit\n");
        printf("=======================================\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
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
                listContacts(&addressBook);
                break;
            case 6:
                saveContactsToFile(&addressBook);
                break;
            case 7:
                printf("\nExiting...\n");
                Exit(&addressBook);
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
