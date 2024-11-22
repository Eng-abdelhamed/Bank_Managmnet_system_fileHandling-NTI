#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
typedef struct 
{
    char name[20];
    char password[20];
    char username[20];
    long PhoneNumber;
    float age;
    int Personal_id;
    float balance;
	  
} person_details;

void createAccount(void);
void login(void);
void transferMoney(void);
void checkBalance(void);
void displayMenu(void);
int main() 
{
    int choice;


    while (1) 
	{
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                login();
                switch(choice)
                {
				
                	printf("Enter your choice: ");
                	//case 1:
                	//	display_information();
                	//	break;
                	case 2:
                		checkBalance();
                		break;
                    case 3:
                    	transferMoney();
                    	break;
                    default:
                    	printf("Invalid choice! Please try again.\n");
                    	exit(0);
                    	
                    	}
                break;
            case 3:
                printf("Exiting the system.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void displayMenu() 
{
    printf("\n-------- Welcome to the Bank System --------\n");
    printf("1. Create Account\n");
    printf("2. Login \n");
    printf("3. Exit\n");
    printf("--------------------------------------------\n");
}

void createAccount(void) 
{
	system("cls");
    person_details p1;
    char password[20];
    char ch;
    FILE *accountsFile;

    accountsFile = fopen("accountnames.txt", "a"); 
    if (!accountsFile) {
        printf("Error opening file for writing!\n");
        return;
    }

    printf("\n......Create Account......\n");
    printf("Your Name        : ");
    scanf("%s", p1.name);

    printf("Your Age         : ");
    scanf("%f", &(p1.age));

    printf("Your Personal ID : ");
    scanf("%d", &(p1.Personal_id));

    printf("Your Phone Number: ");
    scanf("%ld", &(p1.PhoneNumber));

    printf("Your Username    : ");
    scanf("%s", p1.username);
    
     printf("Your Balance    : ");
     scanf("%f",&(p1.balance));

    printf("Your Password    : ");
    int i = 0;
    while (1) {
        ch = getch();
        if (ch == 13) { 
            break;
        }
        
        if (i < 19) 
		{ 
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    strcpy(p1.password, password);

  
    fprintf(accountsFile, "Name: %s\n", p1.name);
    fprintf(accountsFile, "Age: %.2f\n", p1.age);
    fprintf(accountsFile, "Personal ID: %d\n", p1.Personal_id);
    fprintf(accountsFile, "Phone Number: %ld\n", p1.PhoneNumber);
    fprintf(accountsFile, "Username: %s\n", p1.username);
    fprintf(accountsFile, "Password: %s\n", p1.password);
    fprintf(accountsFile, "Balance: %.2f\n", p1.balance);
    fprintf(accountsFile, "-----------------------\n");

    fclose(accountsFile);

    printf("\n\nPLEASE WAIT.... YOUR DATA IS PROCESSING....\n");
    printf("ACCOUNT CREATED SUCCESSFULLY!\n");
    
    system("cls");
}

void transferMoney(void) 
{
	system("cls");
    char username[20];
    char username2[20];
    float amount;
    FILE *accountsFile;
    person_details p;
    person_details users[100];  
    int found = 0, totalUsers = 0;
     int amount1;
   int amount2;

    accountsFile = fopen("accountnames.txt", "r");
    if (!accountsFile) {
        printf("Error opening file for reading!\n");
        return;
    }

    while (fscanf(accountsFile, "Name: %s\n", p.name) != EOF) {
        fscanf(accountsFile, "Age: %f\n", &p.age);
        fscanf(accountsFile, "Personal ID: %d\n", &p.Personal_id);
        fscanf(accountsFile, "Phone Number: %ld\n", &p.PhoneNumber);
        fscanf(accountsFile, "Username: %s\n", p.username);
        fscanf(accountsFile, "Password: %s\n", p.password);
        fscanf(accountsFile, "Balance: %f\n", &p.balance);
        fscanf(accountsFile, "-----------------------\n");

        
        users[totalUsers++] = p;
    }

    fclose(accountsFile);
    printf("\nEnter username transfered from : ");
    scanf("%s", username);
     printf("\nEnter username transfered to : ");
    scanf("%s", username2);
    printf("Enter the amount to transfer: ");
    scanf("%f", &amount);
    
   
    for (int i = 0; i < totalUsers; i++) 
	{
        if (strcmp(username, users[i].username) == 0) 
		{
			 amount1 = users[i].balance; 
			
        }
        else
        {
        	found  = 1;
		}
    }
    for (int i = 0; i < totalUsers; i++) 
	{
        if (strcmp(username2, users[i].username) == 0) 
		{
			 amount2 = users[i].balance; 
        }
        else
        {
        		found  = 1;
		}
    }
    int added = amount + amount2; 
    int subtractred = amount1 - amount;
    
       for (int i = 0; i < totalUsers; i++) 
	{
        if (strcmp(username, users[i].username) == 0) 
		{
			 users[i].balance  = subtractred ; 
        }
        else
        {
        		found  = 1;
		}
    }
    for (int i = 0; i < totalUsers; i++) 
	{
        if (strcmp(username2, users[i].username) == 0) 
		{
		     users[i].balance = added; 
        }
        else
        {
        		found  = 1;
		}
    }

    if (!found) {
        printf("User with username %s not found.\n", username);
        return;
    }

    
    accountsFile = fopen("accountnames.txt", "w");
    if (!accountsFile) {
        printf("Error opening file for writing!\n");
        return;
    }

    
    for (int i = 0; i < totalUsers; i++) {
        fprintf(accountsFile, "Name: %s\n", users[i].name);
        fprintf(accountsFile, "Age: %.2f\n", users[i].age);
        fprintf(accountsFile, "Personal ID: %d\n", users[i].Personal_id);
        fprintf(accountsFile, "Phone Number: %ld\n", users[i].PhoneNumber);
        fprintf(accountsFile, "Username: %s\n", users[i].username);
        fprintf(accountsFile, "Password: %s\n", users[i].password);
        fprintf(accountsFile, "Balance: %.2f\n", users[i].balance);
        fprintf(accountsFile, "-----------------------\n");
    }

    fclose(accountsFile);
    
    system("cls");
}


void checkBalance(void) 
{
//	system("cls");
	
    char username[20];
    FILE *accountsFile;
    person_details p;
    int found = 0;

    printf("\nEnter your username: ");
    scanf("%s", username);

    accountsFile = fopen("accountnames.txt", "r");
    if (!accountsFile) {
        printf("Error opening file for reading!\n");
        return;
    }

    while (fscanf(accountsFile, "Name: %s\n", p.name) != -1) {
        fscanf(accountsFile, "Age: %f\n", &p.age);
        fscanf(accountsFile, "Personal ID: %d\n", &p.Personal_id);
        fscanf(accountsFile, "Phone Number: %ld\n", &p.PhoneNumber);
        fscanf(accountsFile, "Username: %s\n", p.username);
        fscanf(accountsFile, "Password: %s\n", p.password);
        fscanf(accountsFile, "Balance: %f\n", &p.balance);
        fscanf(accountsFile, "-----------------------\n");

        if (strcmp(username, p.username) == 0) {
            printf("Your current balance is: %.2f\n", p.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User with username %s not found.\n", username);
    }

    fclose(accountsFile);
    system("cls");
}
void login(void)
{
	system("cls");
	int logedin = 0;
	person_details p;
	person_details users[100];
	int flag = 0;
	int counter =0;
	char password[20];
	char username[20];
FILE *accountsFile;
	
	printf("Enter Your UserName :");
	scanf("%s",username);
	
	printf("Enter Your PassWord :");
	scanf("%s",password);
	
	accountsFile = fopen("accountnames.txt", "r");
    if (!accountsFile) {
        printf("Error opening file for reading!\n");
        return;
    }
	   while (fscanf(accountsFile, "Name: %s\n", p.name) != -1) {
        fscanf(accountsFile, "Age: %f\n", &p.age);
        fscanf(accountsFile, "Personal ID: %d\n", &p.Personal_id);
        fscanf(accountsFile, "Phone Number: %ld\n", &p.PhoneNumber);
        fscanf(accountsFile, "Username: %s\n", p.username);
        fscanf(accountsFile, "Password: %s\n", p.password);
        fscanf(accountsFile, "Balance: %f\n", &p.balance);
        fscanf(accountsFile, "-----------------------\n");
        users[counter++] = p;
    }
    for(int i  =0 ;i < 100 ;i++)
    {
    	if(strcmp(username,users[i].username)==0 && strcmp(password,users[i].password)==0)
    	{
    		flag  = 1;
    		break;
		}
	}
	if(flag == 0)
	{
		printf("There Is No Account for %s",username);
		return ;
	}
	else
	{
		logedin = 1;
		printf("Login Successfull \n");
		for(int i =0 ;i < 100 ;i++)
		{
			if(strcmp(username,users[i].username)==0)
			{
				printf("Name       : %s\n", users[i].name);
				printf("PhoneNumber: %li\n", users[i].PhoneNumber);
				printf("Age: %f\n", users[i].age);
				printf("Age: %f\n", users[i].age);
				printf("Age: %f\n", users[i].age);
				printf("Age: %f\n", users[i].age);
			}
			
		}

	}
  if (logedin) {
        printf("Login successful!\n");
        int choice;
        do {
            printf("\n1. Transfer Money\n2. Check Balance\n3. Logout\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    transferMoney();
                    break;
                case 2:
                    checkBalance();
                    break;
                case 3:
                    printf("Logging out...\n");
                    break;
                default:
                    printf("Invalid choice. Try again.\n");
            }
        } while (choice != 3);
    } else {
        printf("Invalid username or password.\n");
    }
fclose(accountsFile);
}


