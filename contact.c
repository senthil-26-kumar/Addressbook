#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "contact.h"


void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    FILE *fp;
    fp = fopen("contacts.txt", "r");

    if (fp == NULL)
    {
        perror("ERROR");
        return ;
    } 

    int i = 0;
    while (!feof(fp))
    {
        fscanf(fp, " %49[^,],%19[^,],%49[^\n]", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        addressBook->contactCount++;
        i++;
    }

    fclose(fp);
}

void createContact(AddressBook *addressBook)
{
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("\nAddress Book is full\n");
        return ;
    }

    char name[50];
    int attempt = 0;
    while(1)
    {
        printf("\nEnter the name:");
        scanf(" %49[^\n]", name);
        attempt++;
        int flag = 0;

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if((strcasecmp(addressBook->contacts[i].name, name)) == 0)
            {
                flag = 1;
                break;
            }
        }

        if (flag)
        {
            printf("\nEntered name is already present\n");
            if (attempt == 3)
            {
                printf("\n3 Attempts are finished\n");
                return;
            }
            continue;   
        }
        else if (validname(name))
        {
            printf("\nValid Name\n");
            break;
        }
        else
        {
            printf("\nEntered name is Invalid\n");
        }

        if (attempt == 3)
        {
            printf("\n3 Attempts are finished\n");
            return;
        }
    }

    char phone[20];
    attempt = 0;
    while(1)
    {
        printf("\nEnter the phone number:");
        scanf(" %19[^\n]", phone);
        attempt++;
        int flag = 0;

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if((strcasecmp(addressBook->contacts[i].phone, phone)) == 0)
            {
                flag = 1;
                break;
            }
        }

        if (flag)
        {
            printf("\nEntered Phone number is already present\n");
            if (attempt == 3)
            {
                printf("\n3 Attempts are finished\n");
                return;
            }
            continue;   
        }
        else if (validphone(phone))
        {
            printf("\nValid Number\n");
            break;
        }
        else
        {
            printf("\nEntered number is Invalid\n");
        }

        if (attempt == 3)
        {
            printf("\n3 Attempts are finished\n");
            return;
        }
    }

    char email[50];
    attempt = 0;
    while(1)
    {
        printf("\nEnter the email:");
        scanf(" %49[^\n]", email);
        attempt++;
        int flag = 0;

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if((strcasecmp(addressBook->contacts[i].email, email)) == 0)
            {
                flag = 1;
                break;
            }
        }

        if (flag)
        {
            printf("\nEntered Email is already present\n");
            if (attempt == 3)
            {
                printf("\n3 Attempts are finished\n");
                return;
            }
            continue;   
        }
        else if (validemail(email))
        {
            printf("\nValid Email\n");
            break;
        }
        else
        {
            printf("\nEntered Email is Invalid\n");
        }

        if (attempt == 3)
        {
            printf("\n3 Attempts are finished\n");
            return;
        }
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);
    addressBook->contactCount++;

    printf("\nContact is Created\n");
}

void searchContact(AddressBook *addressBook)
{
    int choice;
    int flag;

    if (addressBook->contactCount == 0)
    {
        printf("\nAddress Book is empty\n");
        return;
    }

    printf("\n========== SEARCH CONTACT ==========\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("3. Search by Email\n");
    printf("====================================\n");
    printf("\nEnter your choice: ");

    if (scanf("%d", &choice) != 1)
    {
        printf("\nInvalid input\n");
        return;
    }

    switch(choice)
    {
        case 1: 
            char name[50];
            printf("\nEnter the name to search:");
            if (scanf(" %49[^\n]", name) != 1)
            {
                printf("\nInvalid input\n");
                return;
            }

            int i;
            flag = 0;
            int j = 0;
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if ((strcasestr(addressBook->contacts[i].name, name)) != NULL)
                {
                    if (flag == 0)
                    {
                        printf("\n+------+----------------------+--------------------+--------------------------------+\n");
                        printf("| %-4s | %-20s | %-18s | %-30s |\n",
                               "S.NO", "Name", "Phone Number", "Email");
                        printf("+------+----------------------+--------------------+--------------------------------+\n");
                    }

                    flag = 1;

                    printf("| %-4d | %-20s | %-18s | %-30s |\n", j+1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    
                    j++;
                }
            }

            if(!flag)
            {
                printf("\nEntered name is not found\n");
            }
            else
            {
                printf("+------+----------------------+--------------------+--------------------------------+\n");
            }

            break;
        case 2: 
            char phone[20];
            printf("\nEnter the number to search:");
            if (scanf(" %19[^\n]", phone) != 1)
            {
                printf("\nInvalid input\n");
                return;
            }

            flag = 0;
            j = 0;
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if ((strcasestr(addressBook->contacts[i].phone, phone)) != NULL)
                {
                    if (flag == 0)
                    {
                        printf("\n+------+----------------------+--------------------+--------------------------------+\n");
                        printf("| %-4s | %-20s | %-18s | %-30s |\n",
                               "S.NO", "Name", "Phone Number", "Email");
                        printf("+------+----------------------+--------------------+--------------------------------+\n");
                    }

                    flag = 1;
                    
                    printf("| %-4d | %-20s | %-18s | %-30s |\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    
                    j++;
                }
            }

            if(!flag)
            {
                printf("\nEntered number is not found\n");
            }
            else
            {
                printf("+------+----------------------+--------------------+--------------------------------+\n");
            }

            break;
        case 3: 
            char email[50];
            printf("\nEnter the email to search:");
            if (scanf(" %49[^\n]", email) != 1)
            {
                printf("\nInvalid input\n");
                return;
            }

            flag = 0;
            j = 0;
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if ((strcasestr(addressBook->contacts[i].email, email)) != NULL)
                {
                    if (flag == 0)
                    {
                        printf("\n+------+----------------------+--------------------+--------------------------------+\n");
                        printf("| %-4s | %-20s | %-18s | %-30s |\n",
                               "S.NO", "Name", "Phone Number", "Email");
                        printf("+------+----------------------+--------------------+--------------------------------+\n");
                    }
                    
                    flag = 1;
                    
                    printf("| %-4d | %-20s | %-18s | %-30s |\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                    
                    j++;
                }
            }

            if(!flag)
            {
                printf("\nEntered email is not found\n");
            }
            else
            {
                printf("+------+----------------------+--------------------+--------------------------------+\n");
            }

            break;
        default:
            printf("\nInvalid choice. Please select 1, 2, or 3.\n");
            break;
        }
}

void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nAddress Book is empty\n");
        return;
    }

    int searchchoice;
    int editchoice;
    int s;
    int count;
    int i, j;
    int flag;

    printf("\n========== EDIT CONTACT ==========\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone Number\n");
    printf("3. Search by Email\n");
    printf("==================================\n");
    printf("\nEnter your choice: ");
    scanf("%d", &searchchoice);

    switch(searchchoice)
    {
        case 1: 
            char name[50];
            printf("\nEnter the name to search:");
            scanf(" %49[^\n]", name);

            flag = 0;
            j = 0;

            for (i = 0; i < addressBook->contactCount; i++)
            {
                if ((strcasestr(addressBook->contacts[i].name, name)) != NULL)
                {
                    if (flag == 0)
                    {
                        printf("\n+------+----------------------+--------------------+--------------------------------+\n");
                        printf("| %-4s | %-20s | %-18s | %-30s |\n",
                               "S.NO", "Name", "Phone Number", "Email");
                        printf("+------+----------------------+--------------------+--------------------------------+\n");
                    }

                    flag = 1;

                    printf("| %-4d | %-20s | %-18s | %-30s |\n", j + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

                    j++;
                }
            }

            if(!flag)
            {
                printf("\nEntered name is not found\n");
                break;
            }
            else
            {
                printf("+------+----------------------+--------------------+--------------------------------+\n");
            }

            printf("\nEnter the serial no to edit : ");
            scanf("%d", &s);

            if (s < 1 || s > j)
            {
                printf("\nInvalid serial number\n");
                break;
            }

            count = 0;

            for (i = 0; i < addressBook->contactCount; i++)
            {
                if ((strcasestr(addressBook->contacts[i].name, name)) != NULL)
                {
                    count++;
                    if (count == s)
                    {
                        printf("\n========== EDIT OPTIONS ==========\n");
                        printf("1. Edit Name\n");
                        printf("2. Edit Phone Number\n");
                        printf("3. Edit Email\n");
                        printf("==================================\n");
                        scanf("%d", &editchoice);
                        switch(editchoice)
                        {
                            case 1:
                                char name[50];
                                int attempt = 0;

                                while(1)
                                {
                                    printf("\nEnter the name:");
                                    scanf(" %49[^\n]", name);
                                    attempt++;
                                    int flag = 0;

                                    for (int j = 0; j < addressBook->contactCount; j++)
                                    {
                                        if (j != i && (strcasecmp(addressBook->contacts[j].name, name)) == 0)
                                        {
                                            flag = 1;
                                            break;
                                        }
                                    }

                                    if (flag)
                                    {
                                        printf("\nEntered name is already present\n");
                                        if (attempt == 3)
                                        {
                                            printf("\n3 Attempts are finished\n");
                                            return;
                                        }
                                        continue;   
                                    }
                                    else if (validname(name))
                                    {
                                        printf("\nValid Name\n");
                                        strcpy(addressBook->contacts[i].name, name);
                                        printf("\nContact is Edited\n");
                                        break;
                                    }
                                    else
                                    {
                                        printf("\nEntered name is Invalid\n");
                                    }

                                    if (attempt == 3)
                                    {
                                        printf("\n3 Attempts are finished\n");
                                        return;
                                    }
                                }
                                break;
                            case 2:
                                char phone[20];
                                attempt = 0;

                                while (1)
                                {
                                    printf("\nEnter the phone number:");
                                    scanf(" %19[^\n]", phone);
                                    attempt++;
                                    int flag = 0;

                                    for (int j = 0; j < addressBook->contactCount; j++)
                                    {
                                        if (j != i && (strcasecmp(addressBook->contacts[j].phone, phone)) == 0)
                                        {
                                            flag = 1;
                                            break;
                                        }
                                    }

                                    if (flag)
                                    {
                                        printf("\nEntered Phone number is already present\n");
                                        if (attempt == 3)
                                        {
                                            printf("\n3 Attempts are finished\n");
                                            return;
                                        }
                                        continue;
                                    }
                                    else if (validphone(phone))
                                    {
                                        printf("\nValid Number\n");
                                        strcpy(addressBook->contacts[i].phone, phone);
                                        printf("\nContact is Edited\n");
                                        break;
                                    }
                                    else
                                    {
                                        printf("\nEntered number is Invalid\n");
                                    }

                                    if (attempt == 3)
                                    {
                                        printf("\n3 Attempts are finished\n");
                                        return;
                                    }
                                }
                                break;
                            case 3:
                                char email[50];
                                attempt = 0;

                                while (1)
                                {
                                    printf("\nEnter the email:");
                                    scanf(" %49[^\n]", email);
                                    attempt++;
                                    int flag = 0;

                                    for (int j = 0; j < addressBook->contactCount; j++)
                                    {
                                        if (j != i && (strcasecmp(addressBook->contacts[j].email, email)) == 0)
                                        {
                                            flag = 1;
                                            break;
                                        }
                                    }

                                    if (flag)
                                    {
                                        printf("\nEntered Email is already present\n");
                                        if (attempt == 3)
                                        {
                                            printf("\n3 Attempts are finished\n");
                                            return;
                                        }
                                        continue;
                                    }
                                    else if (validemail(email))
                                    {
                                        printf("\nValid Email\n");
                                        strcpy(addressBook->contacts[i].email, email);
                                        printf("\nContact is Edited\n");
                                        break;
                                    }
                                    else
                                    {
                                        printf("\nEntered Email is Invalid\n");
                                    }

                                    if (attempt == 3)
                                    {
                                        printf("\n3 Attempts are finished\n");
                                        return;
                                    }
                                    
                                }
                                break;
                            default:
                                printf("\nInvalid choice. Please try again.\n");
                        }
                    }
                }
            }
            break;
        case 2: 
            char phone[20];
            printf("\nEnter the number to search:");
            scanf(" %19[^\n]", phone);

            flag = 0;
            j = 0;
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasestr(addressBook->contacts[i].phone, phone) != NULL)
                {
                    if (flag == 0)
                    {
                        printf("\n+------+----------------------+--------------------+--------------------------------+\n");
                        printf("| %-4s | %-20s | %-18s | %-30s |\n",
                               "S.NO", "Name", "Phone Number", "Email");
                        printf("+------+----------------------+--------------------+--------------------------------+\n");
                    }

                    flag = 1;

                    printf("| %-4d | %-20s | %-18s | %-30s |\n",
                           j + 1,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    j++;
                }
            }

            if(!flag)
            {
                printf("\nEntered number is not found\n");
                break;
            }
            else
            {
                printf("+------+----------------------+--------------------+--------------------------------+\n");
            }

            printf("\nEnter the serial no to edit : ");
            scanf("%d", &s);

            if (s < 1 || s > j)
            {
                printf("\nInvalid serial number\n");
                break;
            }

            count = 0;
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if ((strcasestr(addressBook->contacts[i].phone, phone)) != NULL)
                {
                    count++;
                    if (count == s)
                    {
                        printf("\n========== EDIT OPTIONS ==========\n");
                        printf("1. Edit Name\n");
                        printf("2. Edit Phone Number\n");
                        printf("3. Edit Email\n");
                        printf("==================================\n");
                        printf("\nEnter your choice: ");
                        scanf("%d", &editchoice);
                        switch (editchoice)
                        {
                        case 1:
                            char name[50];
                            int attempt = 0;
                            while (1)
                            {
                                printf("\nEnter the name:");
                                scanf(" %49[^\n]", name);
                                attempt++;
                                int flag = 0;

                                for (int j = 0; j < addressBook->contactCount; j++)
                                {
                                    if (j != i && (strcasecmp(addressBook->contacts[j].name, name)) == 0)
                                    {
                                        flag = 1;
                                        break;
                                    }
                                }

                                if (flag)
                                {
                                    printf("\nEntered name is already present\n");
                                    if (attempt == 3)
                                    {
                                        printf("\n3 Attempts are finished\n");
                                        return;
                                    }
                                    continue;
                                }
                                else if (validname(name))
                                {
                                    printf("\nValid Name\n");
                                    strcpy(addressBook->contacts[i].name, name);
                                    printf("\nContact is Edited\n");
                                    break;
                                }
                                else
                                {
                                    printf("\nEntered name is Invalid\n");
                                }

                                if (attempt == 3)
                                {
                                    printf("\n3 Attempts are finished\n");
                                    return;
                                }
                            }
                            break;
                        case 2:
                            char phone[20];
                            attempt = 0;
                            while (1)
                            {
                                printf("\nEnter the phone number:");
                                scanf(" %19[^\n]", phone);
                                attempt++;
                                int flag = 0;

                                for (int j = 0; j < addressBook->contactCount; j++)
                                {
                                    if (j != i && (strcasecmp(addressBook->contacts[j].phone, phone)) == 0)
                                    {
                                        flag = 1;
                                        break;
                                    }
                                }

                                if (flag)
                                {
                                    printf("\nEntered Phone number is already present\n");
                                    if (attempt == 3)
                                    {
                                        printf("\n3 Attempts are finished\n");
                                        return;
                                    }
                                    continue;
                                }
                                else if (validphone(phone))
                                {
                                    printf("\nValid Number\n");
                                    strcpy(addressBook->contacts[i].phone, phone);
                                    printf("\nContact is Edited\n");
                                    break;
                                }
                                else
                                {
                                    printf("\nEntered number is Invalid\n");
                                }

                                if (attempt == 3)
                                {
                                    printf("\n3 Attempts are finished\n");
                                    return;
                                }
                            }
                            break;
                        case 3:
                            char email[50];
                            attempt = 0;
                            while (1)
                            {
                                printf("\nEnter the email:");
                                scanf(" %49[^\n]", email);
                                attempt++;
                                int flag = 0;

                                for (int j = 0; j < addressBook->contactCount; j++)
                                {
                                    if (j != i && (strcasecmp(addressBook->contacts[j].email, email)) == 0)
                                    {
                                        flag = 1;
                                        break;
                                    }
                                }

                                if (flag)
                                {
                                    printf("\nEntered Email is already present\n");
                                    if (attempt == 3)
                                    {
                                        printf("\n3 Attempts are finished\n");
                                        return;
                                    }
                                    continue;
                                }
                                else if (validemail(email))
                                {
                                    printf("\nValid Email\n");
                                    strcpy(addressBook->contacts[i].email, email);
                                    printf("\nContact is Edited\n");
                                    break;
                                }
                                else
                                {
                                    printf("\nEntered Email is Invalid\n");
                                }

                                if (attempt == 3)
                                {
                                    printf("\n3 Attempts are finished\n");
                                    return;
                                }
                            }
                            break;
                        default:
                            printf("\nInvalid choice. Please try again.\n");
                        }
                    }
                }
            }
            break;
        case 3: 
            char email[50];
            printf("\nEnter the email to search:");
            scanf(" %49[^\n]", email);

            flag = 0;
            j = 0;
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if (strcasestr(addressBook->contacts[i].email, email) != NULL)
                {
                    if (flag == 0)
                    {
                        printf("\n+------+----------------------+--------------------+--------------------------------+\n");
                        printf("| %-4s | %-20s | %-18s | %-30s |\n",
                               "S.NO", "Name", "Phone Number", "Email");
                        printf("+------+----------------------+--------------------+--------------------------------+\n");
                    }

                    flag = 1;

                    printf("| %-4d | %-20s | %-18s | %-30s |\n",
                           j + 1,
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    j++;
                }
            }

            if(!flag)
            {
                printf("\nEntered email is not found\n");
                break;
            }
            else
            {
                printf("+------+----------------------+--------------------+--------------------------------+\n");
            }

            printf("\nEnter the serial no to edit : ");
            scanf("%d", &s);

            if (s < 1 || s > j)
            {
                printf("\nInvalid serial number\n");
                break;
            }

            count = 0;
            for (i = 0; i < addressBook->contactCount; i++)
            {
                if ((strcasestr(addressBook->contacts[i].email, email)) != NULL)
                {
                    count++;
                    if (count == s)
                    {
                        printf("\n========== EDIT OPTIONS ==========\n");
                        printf("1. Edit Name\n");
                        printf("2. Edit Phone Number\n");
                        printf("3. Edit Email\n");
                        printf("==================================\n");
                        printf("\nEnter your choice: ");
                        scanf("%d", &editchoice);
                        switch (editchoice)
                        {
                        case 1:
                            char name[50];
                            int attempt = 0;
                            while (1)
                            {
                                printf("\nEnter the name:");
                                scanf(" %49[^\n]", name);
                                attempt++;
                                int flag = 0;

                                for (int j = 0; j < addressBook->contactCount; j++)
                                {
                                    if (j != i && (strcasecmp(addressBook->contacts[j].name, name)) == 0)
                                    {
                                        flag = 1;
                                        break;
                                    }
                                }

                                if (flag)
                                {
                                    printf("\nEntered name is already present\n");
                                    if (attempt == 3)
                                    {
                                        printf("\n3 Attempts are finished\n");
                                        return;
                                    }
                                    continue;
                                }
                                else if (validname(name))
                                {
                                    printf("\nValid Name\n");
                                    strcpy(addressBook->contacts[i].name, name);
                                    printf("\nContact is Edited\n");
                                    break;
                                }
                                else
                                {
                                    printf("\nEntered name is Invalid\n");
                                }

                                if (attempt == 3)
                                {
                                    printf("\n3 Attempts are finished\n");
                                    return;
                                }
                            }
                            break;
                        case 2:
                            char phone[20];
                            attempt = 0;
                            while (1)
                            {
                                printf("\nEnter the phone number:");
                                scanf(" %19[^\n]", phone);
                                attempt++;
                                int flag = 0;

                                for (int j = 0; j < addressBook->contactCount; j++)
                                {
                                    if (j != i && (strcasecmp(addressBook->contacts[j].phone, phone)) == 0)
                                    {
                                        flag = 1;
                                        break;
                                    }
                                }

                                if (flag)
                                {
                                    printf("\nEntered Phone number is already present\n");
                                    if (attempt == 3)
                                    {
                                        printf("\n3 Attempts are finished\n");
                                        return;
                                    }
                                    continue;
                                }
                                else if (validphone(phone))
                                {
                                    printf("\nValid Number\n");
                                    strcpy(addressBook->contacts[i].phone, phone);
                                    printf("\nContact is Edited\n");
                                    break;
                                }
                                else
                                {
                                    printf("\nEntered number is Invalid\n");
                                }

                                if (attempt == 3)
                                {
                                    printf("\n3 Attempts are finished\n");
                                    return;
                                }
                            }
                            break;
                        case 3:
                            char email[50];
                            attempt = 0;
                            while (1)
                            {
                                printf("\nEnter the email:");
                                scanf(" %49[^\n]", email);
                                attempt++;
                                int flag = 0;

                                for (int j = 0; j < addressBook->contactCount; j++)
                                {
                                    if (j != i && (strcasecmp(addressBook->contacts[j].email, email)) == 0)
                                    {
                                        flag = 1;
                                        break;
                                    }
                                }

                                if (flag)
                                {
                                    printf("\nEntered Email is already present\n");
                                    if (attempt == 3)
                                    {
                                        printf("\n3 Attempts are finished\n");
                                        return;
                                    }
                                    continue;
                                }
                                else if (validemail(email))
                                {
                                    printf("\nValid Email\n");
                                    strcpy(addressBook->contacts[i].email, email);
                                    printf("\nContact is Edited\n");
                                    break;
                                }
                                else
                                {
                                    printf("\nEntered Email is Invalid\n");
                                }

                                if (attempt == 3)
                                {
                                    printf("\n3 Attempts are finished\n");
                                    return;
                                }
                            }
                            break;
                        default:
                            printf("\nInvalid choice. Please try again.\n");
                        }
                    }
                }
            }
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
    }
    return ;
}

void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nAddress Book is empty\n");
        return;
    }

    int choice;
    int count;
    int s;
    int i, j;
    int flag;
    char confirm;

    printf("\nSearch contact to Delete:\n");
    printf("1. Search by Name\n");
    printf("2. Search by Phone number\n");
    printf("3. Search by Email\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        char name[50];
        printf("\nEnter the name to search:");
        if (scanf(" %49[^\n]", name) != 1)
        {
            printf("Invalid input\n");
            return;
        }

        flag = 0;
        j = 0;

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if ((strcasestr(addressBook->contacts[i].name, name)) != NULL)
            {
                if (flag == 0)
                {
                    printf("\n+------+----------------------+--------------------+--------------------------------+\n");
                    printf("| %-4s | %-20s | %-18s | %-30s |\n",
                           "S.NO", "Name", "Phone Number", "Email");
                    printf("+------+----------------------+--------------------+--------------------------------+\n");
                }

                flag = 1;

                printf("| %-4d | %-20s | %-18s | %-30s |\n",
                       j + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);

                j++;
            }
        }

        if (!flag)
        {
            printf("\nEntered name is not found\n");
            break;
        }
        else
        {
            printf("+------+----------------------+--------------------+--------------------------------+\n");
        }

        printf("\nEnter the serial no to delete : ");
        scanf("%d", &s);

        if(s < 1 || s > j)
        {
            printf("\nInvalid serial number\n");
            break;
        }

        count = 0;

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if ((strcasestr(addressBook->contacts[i].name, name)) != NULL)
            {
                count++;
                if (count == s)
                {
                    printf("\nContact selected for deletion:\n");

                    printf("+----------------------+--------------------+--------------------------------+\n");
                    printf("| %-20s | %-18s | %-30s |\n",
                           "Name", "Phone Number", "Email");
                    printf("+----------------------+--------------------+--------------------------------+\n");

                    printf("| %-20s | %-18s | %-30s |\n",
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    printf("+----------------------+--------------------+--------------------------------+\n");
                    
                    printf("\nAre you sure you want to delete this contact?\n");
                    printf("Enter Y to confirm or N to cancel: ");
                    scanf(" %c", &confirm);

                    if (confirm == 'Y' || confirm == 'y')
                    {
                        for (j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--;
                        printf("\nContact deleted successfully!\n");
                    }
                    else if (confirm == 'N' || confirm == 'n')
                    {
                        printf("\nDeletion cancelled.\n");
                    }
                    else
                    {
                        printf("\nInvalid confirmation. Deletion cancelled.\n");
                    }
                }
            }
        }

        break;

    case 2:
        char phone[20];
        printf("\nEnter the number to search:");
        if (scanf(" %19[^\n]", phone) != 1)
        {
            printf("Invalid input\n");
            return;
        }

        flag = 0;
        j = 0;

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if ((strcasestr(addressBook->contacts[i].phone, phone)) != NULL)
            {
                if (flag == 0)
                {
                    printf("\n+------+----------------------+--------------------+--------------------------------+\n");
                    printf("| %-4s | %-20s | %-18s | %-30s |\n",
                           "S.NO", "Name", "Phone Number", "Email");
                    printf("+------+----------------------+--------------------+--------------------------------+\n");
                }

                flag = 1;

                printf("| %-4d | %-20s | %-18s | %-30s |\n",
                       j + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);

                j++;
            }
        }

        if (!flag)
        {
            printf("\nEntered number is not found\n");
            break;
        }
        else
        {
            printf("+------+----------------------+--------------------+--------------------------------+\n");
        }

        printf("\nEnter the serial no to delete : ");
        scanf("%d", &s);

        if (s < 1 || s > j)
        {
            printf("\nInvalid serial number\n");
            break;
        }

        count = 0;

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if ((strcasestr(addressBook->contacts[i].phone, phone)) != NULL)
            {
                count++;
                if (count == s)
                {
                    printf("\nContact selected for deletion:\n");

                    printf("+----------------------+--------------------+--------------------------------+\n");
                    printf("| %-20s | %-18s | %-30s |\n",
                           "Name", "Phone Number", "Email");
                    printf("+----------------------+--------------------+--------------------------------+\n");

                    printf("| %-20s | %-18s | %-30s |\n",
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    printf("+----------------------+--------------------+--------------------------------+\n");
                    
                    printf("\nAre you sure you want to delete this contact?\n");
                    printf("Enter Y to confirm or N to cancel: ");
                    scanf(" %c", &confirm);

                    if (confirm == 'Y' || confirm == 'y')
                    {
                        for (j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--;
                        printf("\nContact deleted successfully!\n");
                    }
                    else if (confirm == 'N' || confirm == 'n')
                    {
                        printf("\nDeletion cancelled.\n");
                    }
                    else
                    {
                        printf("\nInvalid confirmation. Deletion cancelled.\n");
                    }
                }
            }
        }

        break;

    case 3:
        char email[50];
        printf("\nEnter the email to search:");
        if (scanf(" %49[^\n]", email) != 1)
        {
            printf("Invalid input\n");
            return;
        }

        flag = 0;
        j = 0;

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if ((strcasestr(addressBook->contacts[i].email, email)) != NULL)
            {
                if (flag == 0)
                {
                    printf("\n+------+----------------------+--------------------+--------------------------------+\n");
                    printf("| %-4s | %-20s | %-18s | %-30s |\n",
                           "S.NO", "Name", "Phone Number", "Email");
                    printf("+------+----------------------+--------------------+--------------------------------+\n");
                }

                flag = 1;

                printf("| %-4d | %-20s | %-18s | %-30s |\n",
                       j + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);

                j++;
            }
        }

        if (!flag)
        {
            printf("\nEntered email is not found\n");
            break;
        }
        else
        {
            printf("+------+----------------------+--------------------+--------------------------------+\n");
        }

        printf("\nEnter the serial no to delete : ");
        scanf("%d", &s);

        if (s < 1 || s > j)
        {
            printf("\nInvalid serial number\n");
            break;
        }

        count = 0;

        for (i = 0; i < addressBook->contactCount; i++)
        {
            if ((strcasestr(addressBook->contacts[i].email, email)) != NULL)
            {
                count++;
                if (count == s)
                {
                    printf("\nContact selected for deletion:\n");

                    printf("+----------------------+--------------------+--------------------------------+\n");
                    printf("| %-20s | %-18s | %-30s |\n",
                           "Name", "Phone Number", "Email");
                    printf("+----------------------+--------------------+--------------------------------+\n");

                    printf("| %-20s | %-18s | %-30s |\n",
                           addressBook->contacts[i].name,
                           addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);

                    printf("+----------------------+--------------------+--------------------------------+\n");
                    
                    printf("\nAre you sure you want to delete this contact?\n");
                    printf("Enter Y to confirm or N to cancel: ");
                    scanf(" %c", &confirm);

                    if (confirm == 'Y' || confirm == 'y')
                    {
                        for (j = i; j < addressBook->contactCount - 1; j++)
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--;
                        printf("\nContact deleted successfully!\n");
                    }
                    else if (confirm == 'N' || confirm == 'n')
                    {
                        printf("\nDeletion cancelled.\n");
                    }
                    else
                    {
                        printf("\nInvalid confirmation. Deletion cancelled.\n");
                    }
                }
            }
        }

        break;

    default:
        printf("\nInvalid choice. Please try again.\n");
    }
}

void listContacts(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nAddress Book is empty\n");
        return;
    }

    int i;

    printf("\n+------+----------------------+--------------------+--------------------------------+\n");
    printf("| %-4s | %-20.20s | %-18.18s | %-30.30s |\n", "S.NO", "Name", "Phone Number", "Email");
    printf("+------+----------------------+--------------------+--------------------------------+\n");
    for (i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-4d | %-20.20s | %-18.18s | %-30.30s |\n", i + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("+------+----------------------+--------------------+--------------------------------+\n");

    return;
}

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp;
    fp = fopen("contacts.txt", "w");

    if (fp == NULL)
    {
        perror("ERROR");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fp);
    printf("\nContacts saved successfully!\n");
}

void Exit(AddressBook *addressBook)
{
    exit(0);
}

int validname(char name[])
{
    if(name[0] == ' ' || name[0] == '\0')
    {
        printf("\nName cannot be empty or start with a space\n");
        return 0;
    }
    
    int count = 0;

    for (int i = 0; name[i] !='\0';i++)
    {
        if ((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z') || (name[i] == ' '))
        {
            count++;
        }
        else
        {
            printf("\nName should contains alphabets and space only\n");
            return 0;
        }
    } 

    return 1;
}

int validphone(char phone[])
{
    if(phone[0] == ' ' || phone[0] == '\0')
    {
        printf("\nPhone number cannot be empty or contain spaces\n");
        return 0;
    }

    int len = strlen(phone);
    if (len != 10)
    {
        printf("\nPhone number should contains ten numbers only\n");
        return 0;
    }

    int count = 0;
    for (int i = 0; phone[i] != '\0';i++)
    {
        if (phone[i] >= '0' && phone[i] <= '9')
        {
            count++;
        }
        else if (phone[i] == ' ')
        {
            printf("\nPhone number cannot contain spaces\n");
            return 0;
        }
        else
        {
            printf("\nPhone number should contains numbers only\n");
            return 0;
        }
    }

    return 1;
}

int validemail(char email[])
{
    if (email[0] == ' ' || email[0] == '\0')
    {
        printf("\nEmail cannot be empty or contain spaces\n");
        return 0;
    }
    
    int i;
    int atcount = 0;

    for (i = 0; email[i] != '\0'; i++)
    {
        if (email[i] >= 'A' && email[i] <= 'Z')
        {
            printf("\nEmail shouldn't contain upper case\n");
            return 0;
        }
        if (email[i] == '@')
        {
            atcount++;
        }
    }

    if(atcount != 1)
    {
        printf("\nEmail should exactly contain one '@'\n");
        return 0;
    }

    char *ptr1;
    ptr1 = strchr(email, '@');

    if (ptr1 == email || ptr1[1] == '\0')
    {
        printf("\n'@' shouldn't present at first or at the last of the email\n");
        return 0;
    }

    for (i = 0; email[i] != '\0'; i++)
    {
        if ((email[i] >= 'a' && email[i] <= 'z') || (email[i] >= '0' && email[i] <= '9') || email[i] == '@' || email[i] == '.')
        {
            continue;
        }
        else
        {
            printf("\nEmail contains invalid characters\n");
            return 0;
        }
    }

    char *ptr2;
    ptr2 = strstr(email, ".com");

    if (ptr2 == NULL)
    {
        printf("\nEmail should contain '.com'\n");
        return 0;
    }
    
    if (strcmp(ptr2, ".com") != 0)
    {
        printf("\n'.com' should be present only at the end of the email\n");
        return 0;
    }

    return 1;
}
