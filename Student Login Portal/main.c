#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int passwordLength;
int generateRandomNumber();
void generateRandomPassword();
int checkUserName();
int signUp();
int login();

struct User {
    char name[512];
    char password[512];
} user;

int main()
{
    srand(time(NULL));
    int choice, choice1;
    printf("Welcome!\n");
    printf("Do you want to (1) Login or (2) Signup?\n");
    scanf("%d", &choice1);
    getchar();
    if (choice1 == 2)
    {
        signUp();
    } else if (choice1 == 1) { 
        login();
    } else {
        main();
    }
    return 0;
}

int generateRandomNumber()
{
    int r;
    while (1)
    {
        r = (rand() % (122 + 1 - 48)) + 48;
        if (((r <= 57) && (r >= 48)) || ((r <= 90) && (r >= 65)) || ((r <= 97) && (r >= 122)))
        {
            return r;
        }
    }
}

void generateRandomPassword()
{
    int i, randomNumber;
    int length = passwordLength;
    for (i = 0; i < length; i++)
    {
        randomNumber = generateRandomNumber();
        user.password[i] = randomNumber;
    }
}

int checkUserName()
{
    printf("Please enter username(NOTE : Username is NOT case-sensitive) : ");
    gets(user.name);
    int i=0;
    while (user.name[i])
    {
        user.name[i] = tolower(user.name[i]);
        i++;
    }
    char temp[512];
    FILE *fptr;
    fptr = fopen("database.txt", "r");
    if (fptr == NULL)
    {
        printf("Error opening databse file.\n");
        return 1;
    }
    while (fgets(temp, 2*512, fptr) != NULL)
    {
        char *temp1 = strtok(temp, " ");
        if (strstr(temp1, user.name) != NULL)
        {
            printf("Username already exists. Please enter a different username.\n");
            checkUserName();
        }
    }
    fclose(fptr);
    return 0;
}

int signUp()
{
    checkUserName();
    int choice;
    do
    {
        printf("What do you want to do?\n (1) Generate random password\n (2) Type your own password\n");
        scanf("%d", &choice);
    } while (choice != 1 && choice != 2);
    if (choice == 1)
    {
        printf("So you want to generate random password\n");
        printf("Please enter password length : ");
        scanf("%d", &passwordLength);
        generateRandomPassword();
        printf("Your password is : ");
        for (int i = 0; i < passwordLength; i++)
        {
            printf("%c", user.password[i]);
        }
    } else {
        printf("Please enter your password(NOTE : Password should be alphanumeric) : ");
        gets(user.password);
        getchar();
        puts(user.password);
    }
    printf("\nCongratulations! You have successfully signed in.\n\n");
    return 0;
}

int login()
{
    printf("Please enter your username : ");
    gets(user.name);
    int i=0;
    char *buffer[512];
    while (user.name[i])
    {
        user.name[i] = tolower(user.name[i]);
        i++;
    }
    i = 0;
    char temp[512];
    FILE *fptr;
    fptr = fopen("database.txt", "r");
    if (fptr == NULL)
    {
        printf("Error opening databse file.\n");
        return 1;
    }
    while (fgets(temp, 512, fptr) != NULL)
    {
        char *temp1 = strtok(temp, " ");
        while (temp1 != NULL)
        {
            buffer[i] = temp1;
            temp1 = strtok(NULL, " ");
            i++;
        }
        printf("%s ", buffer[0]);
        printf("%s ", buffer[2]);
        if (strcmp(buffer[0], user.name) == 0)
        {
            printf("Please enter your password : ");
            gets(user.password);
            if (strcmp(buffer[1], user.password) == 0)
            {
                printf("Login Successful\n");
                fclose(fptr);
                return 0;
            }
        }
        /*while (temp1 != NULL)
        {
            if (strcmp(temp1, user.name) == 0)
            {
                temp1 = strtok(NULL, " ");
                printf("Please enter your password : ");
                gets(user.password);
                if (strcmp(temp1, user.password) == 0)
                {
                    printf("Login Successful\n");
                    return 0;
                }
            }
        }*/
    }
    fclose(fptr);
    printf("Incorrect Username/Password\n");
    login();
}

