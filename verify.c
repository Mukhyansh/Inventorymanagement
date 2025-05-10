#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void clear()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void signup()
{
    FILE *fp = fopen("verification.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }
    clear();
    char name[200];
    printf("Enter Your Username: ");
    if (fgets(name, sizeof(name), stdin) == NULL)
    {
        printf("Error reading username\n");
        fclose(fp);
        return;
    }
    name[strcspn(name, "\n")] = '\0';
    char pass[200];
    printf("Enter Your Password: ");
    if (fgets(pass, sizeof(pass), stdin) == NULL)
    {
        printf("Error reading password\n");
        fclose(fp);
        return;
    }
    pass[strcspn(pass, "\n")] = '\0';
    fprintf(fp, "%s\n", name);
    fprintf(fp, "%s\n", pass);
    fclose(fp);
    printf("Signup successful!\n");
    login();
}

bool login(){
    clear();
    char username[200];
    printf("Enter Your Username: ");
    if (fgets(username, sizeof(username), stdin) == NULL)
    {
        printf("Error reading username\n");
        return false;
    }
    username[strcspn(username, "\n")] = '\0';
    char password[200];
    printf("Enter Your Password: ");
    if (fgets(password, sizeof(password), stdin) == NULL)
    {
        printf("Error reading password\n");
        return false;
    }
    password[strcspn(password, "\n")] = '\0';
    FILE *ptr = fopen("verification.txt", "r");
    if (ptr == NULL)
    {
        printf("Error opening file\n");
        return false;
    }
    bool found = false;
    char line[200];
    char user[200];
    char pass[200];
    while (fgets(line, sizeof(line), ptr))
    {
        line[strcspn(line, "\n")] = '\0';
        if (strncmp(line, "--------------------------------", 32) == 0)
        {
            continue;
        }
        strcpy(user, line);
        if (fgets(line, sizeof(line), ptr) == NULL)
        {
            break;
        }
        line[strcspn(line, "\n")] = '\0';
        strcpy(pass, line);
        if (strcmp(user, username) == 0 && strcmp(pass, password) == 0)
        {
            found = true;
            break;
        }
        if (fgets(line, sizeof(line), ptr) == NULL)
        {
            break;
        }
    }
    if (found)
    {
        printf("Verified!");
    }
    else
    {
        printf("Not Verified! Invalid username or password.\n");
    }
    fclose(ptr);
    return found;
}
