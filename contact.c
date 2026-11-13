#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
// #include "populate.h"
#include<ctype.h>
// Global array to store indices of matched contacts
int arr[MAX_CONTACTS];


// -------To list contacts-------
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    switch(sortCriteria){
        case 1 : printf("Sorting by name : \n");
        for(int i = 0;i<addressBook->contactCount-1;i++){
           for(int j = 0;j<addressBook->contactCount-i-1;j++){
            if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0){
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
           }
        }
        printf("Index No Name\t\tPhone\t\tEmail\n");
        for(int i=0;i<addressBook->contactCount;i++){
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        case 2 : printf("Sorting by Phone : \n");
        for(int i = 0;i<addressBook->contactCount-1;i++){
           for(int j = 0;j<addressBook->contactCount-i-1;j++){
            if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0){
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
           }
        }
        printf("Index No Name\t\tPhone\t\tEmail\n");
        for(int i=0;i<addressBook->contactCount;i++){
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;
        case 3 : printf("Sorting by Email : \n");
        for(int i = 0;i<addressBook->contactCount-1;i++){
           for(int j = 0;j<addressBook->contactCount-i-1;j++){
            if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0){
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j+1];
                addressBook->contacts[j+1] = temp;
            }
           }
        }
        printf("Index No Name\t\tPhone\t\tEmail\n");
        for(int i=0;i<addressBook->contactCount;i++){
            printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        }
        break;   
    }
}


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//--------------create contact-------------//
void Name(char *name, int *status);
void Phone(char *phone, AddressBook *addressBook, int *status);
void Email(char *email, AddressBook *addressBook, int *status);
int validateName(char *name);
int validatePhone(char *phone,AddressBook *addressBook);
int unique( char *phone,AddressBook *addressBook);
int validateEmail(char *email, AddressBook *addressBook);
int uniqueEmail(char *email, AddressBook *addressBook);

void createContact(AddressBook *addressBook)
{
    if(addressBook->contactCount == MAX_CONTACTS)
    {
        printf("Address Book is Full\n");
        return;
    }

    char name[50];
    char phone[20];
    char email[50];

    int status = 1;

    Name(name, &status);
    if(status == 0)
        return;

    Phone(phone, addressBook, &status);
    if(status == 0)
        return;

    Email(email, addressBook, &status);
    if(status == 0)
        return;

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    addressBook->contactCount++;

    printf("Contact Created Successfully\n");
}

void Name(char *name, int *status)
{
    int flag = 0;

    while(flag < 3)
    {
        printf("Enter Name : ");
        scanf(" %[^\n]", name);

        if(validateName(name))
        {
            flag++;

            if(flag == 3)
            {
                printf("Maximum attempts exceeded\n");
                *status = 0;
                return;
            }
        }
        else
        {
            printf("Name successfully created\n");
            *status = 1;
            return;
        }
    }
}

int validateName(char *name)
{
    if(isdigit(name[0])){
        printf("Error : Name should not start with digit\n");
        return 1;
    }

    return 0;
}

void Phone(char *phone, AddressBook *addressBook, int *status)
{
    int flag = 0;

    while(flag < 3)
    {
        printf("Enter Phone Number : ");
        scanf("%19s", phone);

        if(validatePhone(phone, addressBook))
        {
            flag++;
            printf("Error : Invalid Phone Number\n");

            if(flag == 3)
            {
                printf("Maximum attempts exceeded\n");
                *status = 0;
                return;
            }
        }
        else
        {
            printf("Phone number successfully created\n");
            *status = 1;
            return;
        }
    }
}

int validatePhone(char *phone, AddressBook *addressBook)
{
     int i;

    //To check length
    if (strlen(phone) != 10){
    printf("Phone number must contain exactly 10 digits\n");
        return 1;
    }

    //to check whether all are digits
    for (i = 0; phone[i]; i++)
    {
        if (!isdigit(phone[i]))
            return 1;
    }

    //to check the first digit(6-9)
    if (phone[0] < '6' || phone[0] > '9'){
    printf("First digit must be between 6 and 9\n");
        return 1;
    }

    //To check uniqueness
    if (!unique(phone, addressBook))
        return 1;

    return 0;
}

int unique( char *phone,AddressBook *addressBook)
{
for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(phone, addressBook->contacts[i].phone) == 0)
        {
            return 0;   
        }
    }
    return 1; 
}

void Email(char *email, AddressBook *addressBook, int *status)
{
    int flag = 0;

    while(flag < 3)
    {
        printf("Enter Email : ");
        scanf("%49s", email);

        if(validateEmail(email, addressBook))
        {
            flag++;
            printf("Error : Invalid Email\n");

            if(flag == 3)
            {
                printf("Maximum attempts exceeded\n");
                *status = 0;
                return;
            }
        }
        else
        {
            printf("Email successfully created\n");
            *status = 1;
            return;
        }
    }
}

int validateEmail(char *email, AddressBook *addressBook)
{
    int i;
    int a = 0;
    int b = 0;

    // Should not start with digit
    if (isdigit(email[0]))
        return 1;

    // Count '@' and '.'
    for (i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
            a++;

        if (email[i] == '.')
            b++;
    }

    if (a != 1 || b != 1)
        return 1;

    // Check .com
    char *dot = strrchr(email, '.');

    if (dot == NULL)
        return 1;

    if (strcmp(dot, ".com") != 0)
        return 1;

    // Locate @ and .
    char *start = strchr(email, '@');
    char *end = strrchr(email, '.');

    if (start == NULL || end == NULL || start > end)
        return 1;

    // Username validation (before @)
    for (i = 0; i < start - email; i++)
    {
        if (!(islower(email[i]) || isdigit(email[i])))
            return 1;
    }

    // Domain validation (after @ and before .)
    start++;

    while (start < end)
    {
        if (!islower(*start))
            return 1;

        start++;
    }

    // Unique Email
    if (!uniqueEmail(email, addressBook))
        return 1;

    return 0;
}
int uniqueEmail(char *email, AddressBook *addressBook)
{
    int i;

    for (i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(email, addressBook->contacts[i].email) == 0)
            return 0;
    }

    return 1;
}

//------------------------Search contact-----------------------//
int validateSearchPhone(char *phone);
int validateSearchEmail(char *email);
int searchContact(AddressBook *addressBook)
{
    int choice;

    while(1)
    {
        printf("\nSearch By\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
       if (scanf("%d", &choice) != 1)
       {
        printf("Invalid Choice\n");
        while(getchar() != '\n');   // clear input buffer
        continue;
    }

        switch(choice)
        {
            case 1:
{
    char name[50];
    int flag = 0;

    while(flag < 3)
    {
        printf("Enter Name: ");
        scanf(" %[^\n]", name);

        if(validateName(name))
        {
            flag++;
            printf("Invalid Name\n");

            if(flag == 3)
            {
                printf("Maximum attempts exceeded\n");
                break;
            }
        }
        else
        {
            int count = 0;

            printf("\nS.No\tName\t\tPhone\t\tEmail\n");
              for(int i = 0; i < addressBook->contactCount; i++)
{
    if(strcmp(name, addressBook->contacts[i].name) == 0)
    {
        arr[count] = i;

        printf("%d\t%s\t%s\t%s\n",
               count + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);

        count++;
    }
}
            if(count == 0)
            {
                printf("Contact Not Found\n");
                break;
            }

            int serial;

            printf("Enter Serial Number: ");
            scanf("%d", &serial);

            if(serial >= 1 && serial <= count)
            {
                return arr[serial - 1];
            }

            printf("Invalid Serial Number\n");
            break;
        }
    }

    break;
}

            case 2:
            {
                char phone[20];
                int flag=0;

                while(flag<3)
                {
                    printf("Enter Phone: ");
                    scanf("%19s",phone);

                    if(validateSearchPhone(phone))
                    {
                        flag++;

                        printf("Invalid Phone Number\n");

                        if(flag==3)
                        {
                            printf("Maximum attempts exceeded\n");
                            break;
                        }
                    }
                    else
                    {

                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            if(strcmp(phone,addressBook->contacts[i].phone)==0)
                            {
                                printf("\n%d\t%s\t%s\t%s\n",
                                       i+1,
                                       addressBook->contacts[i].name,
                                       addressBook->contacts[i].phone,
                                       addressBook->contacts[i].email);

                                return i;
                            }
                        }
                            printf("Contact Not Found\n");

                        break;
                    }
                }

                break;
            }

            case 3:
            {
                char email[50];
                int flag=0;

                while(flag<3)
                {
                    printf("Enter Email: ");
                    scanf("%49s",email);

                    if(validateSearchEmail(email))
                    {
                        flag++;

                        printf("Invalid Email\n");

                        if(flag==3)
                        {
                            printf("Maximum attempts exceeded\n");
                            break;
                        }
                    }
                    else
                    {
                        for(int i=0;i<addressBook->contactCount;i++)
                        {
                            if(strcmp(email,addressBook->contacts[i].email)==0)
                            {
                                printf("\n%d\t%s\t%s\t%s\n",
                                       i+1,
                                       addressBook->contacts[i].name,
                                       addressBook->contacts[i].phone,
                                       addressBook->contacts[i].email);

                                return i;
                            }
                        }

                            printf("Contact Not Found\n");

                        break;
                    }
                }

                break;
            }

            case 4:
                return -1;

            default:
                printf("Invalid Choice\n");
        }
    }
}
int validateSearchPhone(char *phone)
{
    if(strlen(phone) != 10)
        return 1;

    for(int i = 0; phone[i] != '\0'; i++)
    {
        if(!isdigit(phone[i]))
            return 1;
    }

    if(phone[0] < '6' || phone[0] > '9')
        return 1;

    return 0;
}

int validateSearchEmail(char *email)
{
    int at = 0, dot = 0;

    if(isdigit(email[0]))
        return 1;

    for(int i = 0; email[i] != '\0'; i++)
    {
        if(email[i] == '@')
            at++;

        if(email[i] == '.')
            dot++;
    }

    if(at != 1 || dot != 1)
        return 1;

    char *ptr1 = strchr(email, '@');
    char *ptr2 = strrchr(email, '.');

    if(ptr1 == NULL || ptr2 == NULL || ptr1 > ptr2)
        return 1;

    if(strcmp(ptr2, ".com") != 0)
        return 1;

    for(int i = 0; i < ptr1 - email; i++)
    {
        if(!(islower(email[i]) || isdigit(email[i])))
            return 1;
    }

    ptr1++;

    while(ptr1 < ptr2)
    {
        if(!islower(*ptr1))
            return 1;

        ptr1++;
    }

    return 0;
}

//-----------------------Edit contacts------------------------//
int uniqueEditPhone(char *phone, AddressBook *addressBook, int index);
int uniqueEditEmail(char *email, AddressBook *addressBook, int index);
void editContact(AddressBook *addressBook)
{
    int index = searchContact(addressBook);

    if(index == -1)
        return;

    int choice;

    printf("\nEdit Contact\n");
    printf("1. Edit Name\n");
    printf("2. Edit Phone\n");
    printf("3. Edit Email\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
        {
            char name[50];
            int flag = 0;

            while(flag < 3)
            {
                printf("Enter New Name: ");
                scanf(" %[^\n]",name);

                if(validateName(name))
                {
                    flag++;
                    printf("Invalid Name\n");

                    if(flag == 3)
                    {
                        printf("Maximum attempts exceeded\n");
                        return;
                    }
                }
                else
                {
                    strcpy(addressBook->contacts[index].name,name);
                    printf("Name Updated Successfully\n");
                    return;
                }
            }
            break;
        }

        case 2:
        {
            char phone[20];
            int flag = 0;

            while(flag < 3)
            {
                printf("Enter New Phone: ");
                scanf("%19s",phone);

                if(validateSearchPhone(phone))
                {
                    flag++;
                    printf("Invalid Phone Number\n");
                }
                else if(!uniqueEditPhone(phone,addressBook,index))
                {
                    flag++;
                    printf("Phone Number Already Exists\n");
                }
                else
                {
                    strcpy(addressBook->contacts[index].phone,phone);
                    printf("Phone Updated Successfully\n");
                    return;
                }

                if(flag == 3)
                {
                    printf("Maximum attempts exceeded\n");
                    return;
                }
            }
            break;
        }

        case 3:
        {
            char email[50];
            int flag = 0;

            while(flag < 3)
            {
                printf("Enter New Email: ");
                scanf("%49s",email);

                if(validateSearchEmail(email))
                {
                    flag++;
                    printf("Invalid Email\n");
                }
                else if(!uniqueEditEmail(email,addressBook,index))
                {
                    flag++;
                    printf("Email Already Exists\n");
                }
                else
                {
                    strcpy(addressBook->contacts[index].email,email);
                    printf("Email Updated Successfully\n");
                    return;
                }

                if(flag == 3)
                {
                    printf("Maximum attempts exceeded\n");
                    return;
                }
            }
            break;
        }

        case 4:
            return;

        default:
            printf("Invalid Choice\n");
    }
}
int uniqueEditPhone(char *phone, AddressBook *addressBook, int index)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(i == index)
            continue;

        if(strcmp(phone, addressBook->contacts[i].phone) == 0)
            return 0;
    }

    return 1;
}
int uniqueEditEmail(char *email, AddressBook *addressBook, int index)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(i == index)
            continue;

        if(strcmp(email, addressBook->contacts[i].email) == 0)
            return 0;
    }

    return 1;
}

//---------------------Delete contacts--------------------------//
void deleteContact(AddressBook *addressBook)
{
    int index = searchContact(addressBook);

    if(index == -1)
        return;

    char choice;

    printf("\nContact Details:\n");
    printf("Name  : %s\n", addressBook->contacts[index].name);
    printf("Phone : %s\n", addressBook->contacts[index].phone);
    printf("Email : %s\n", addressBook->contacts[index].email);

    printf("\nAre you sure you want to delete this contact? (Y/N): ");
    scanf(" %c", &choice);

    if(choice == 'Y' || choice == 'y')
    {
        for(int i = index; i < addressBook->contactCount - 1; i++)
        {
            addressBook->contacts[i] = addressBook->contacts[i + 1];
        }

        addressBook->contactCount--;

        printf("Contact Deleted Successfully\n");
    }
    else if(choice == 'N' || choice == 'n')
    {
        printf("Deletion Cancelled\n");
    }
    else
    {
        printf("Invalid Choice\n");
    }
}
