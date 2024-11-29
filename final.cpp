#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

// Define a structure to store user details
typedef struct
{
    char name[20];
    char password[20];
    char username[20];
    long PhoneNumber;
    float age;
    long int Personal_id;
    float balance;

} person_details;

// Function prototypes
void createAccount(void);
void login(void);
void transferMoney(void);
void checkBalance(void);
void displayMenu(void);
void delete_user(void);

int main()
{
    int choice;// Variable to store user choice in the menu


    while (1)  // loop for displaying the main menu
	{
        displayMenu();// calling menu options function
        printf("Enter your choice: ");
        scanf("%d", &choice);

         // calling function based on user choice
        switch (choice) {
            case 1:
                createAccount();// Create a new account
                break;
            case 2:
                login();// Login to an existing account
                break;
            case 3:
                printf("Exiting the system.\n");// Exit the program
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Display the main menu
void displayMenu()
{
    printf("\n-------- Welcome to the Bank System --------\n");
    printf("1. Create Account\n");
    printf("2. Login \n");
    printf("3. Exit\n");
    printf("--------------------------------------------\n");
}

// Function to create a new account
void createAccount(void)
{
	system("cls"); // Clear the console
    person_details p1;// Variable to hold user details
    char password[20];// Temporary password storage
    char ch;// For reading individual characters
    FILE *accountsFile;// File pointer for accounts file

    // Open the accounts file in append mode
    accountsFile = fopen("accountnames.txt", "a");
    if (!accountsFile) {
        printf("Error opening file for writing!\n");
        return;
    }

     // Collect user details
    printf("\n......Create Account......\n");
    printf("Your Name        : ");
    scanf("%s", p1.name);

    printf("Your Age         : ");
    scanf("%f", &(p1.age));

    printf("Your Personal ID : ");
    scanf("%ld", &(p1.Personal_id));

    printf("Your Phone Number: ");
    scanf("%ld", &(p1.PhoneNumber));

    printf("Your Username    : ");
    scanf("%s", p1.username);

     printf("Your Balance    : ");
     scanf("%f",&(p1.balance));

    printf("Your Password    : ");
    int i = 0;
    while (1) {
        ch = getch();// Read a single character without echoing
        if (ch == 13)// Enter key terminates input
            {
            break;
            }

        if (i < 19)  // Add character to password buffer
		{
            password[i++] = ch;
            printf("*");// Display asterisk for each character
        }
    }
    password[i] = '\0';// Null-terminate the password
    strcpy(p1.password, password);// Copy password to structure

   // Write user details to the file
    fprintf(accountsFile, "Name: %s\n", p1.name);
    fprintf(accountsFile, "Age: %.2f\n", p1.age);
    fprintf(accountsFile, "Personal ID: %ld\n", p1.Personal_id);
    fprintf(accountsFile, "Phone Number: %ld\n", p1.PhoneNumber);
    fprintf(accountsFile, "Username: %s\n", p1.username);
    fprintf(accountsFile, "Password: %s\n", p1.password);
    fprintf(accountsFile, "Balance: %.2f\n", p1.balance);
    fprintf(accountsFile, "-----------------------\n");

    fclose(accountsFile);// Close the file

    printf("\n\nPLEASE WAIT.... YOUR DATA IS PROCESSING....\n");
    printf("ACCOUNT CREATED SUCCESSFULLY!\n");

    system("cls");// Clear the console
}

// Function to transfer money between accounts
void transferMoney(void)
{
	system("cls");
    char username[20];// Sender's username
    char username2[20];// Receiver's username
    float amount;// Transfer amount
    FILE *accountsFile;// File pointer for accounts file
    person_details p;// Temporary user structure
    person_details users[100];  // Array to store all users
    int found = 0, totalUsers = 0;// Flags and counters
     int amount1;
   int amount2;

   // Open the accounts file in read mode
    accountsFile = fopen("accountnames.txt", "r");
    if (!accountsFile) {
        printf("Error opening file for reading!\n");
        return;
    }

    // Load user details into memory
    while (fscanf(accountsFile, "Name: %s\n", p.name) != EOF) {
        fscanf(accountsFile, "Age: %f\n", &p.age);
        fscanf(accountsFile, "Personal ID: %ld\n", &p.Personal_id);
        fscanf(accountsFile, "Phone Number: %ld\n", &p.PhoneNumber);
        fscanf(accountsFile, "Username: %s\n", p.username);
        fscanf(accountsFile, "Password: %s\n", p.password);
        fscanf(accountsFile, "Balance: %f\n", &p.balance);
        fscanf(accountsFile, "-----------------------\n");


        users[totalUsers++] = p; // Close the file
    }

    // Prompt user for details
    fclose(accountsFile);
    printf("\n Please Enter username transfered from : ");
    scanf("%s", username);

     printf("\nPlease Enter username transfered to   : ");
    scanf("%s", username2);

    printf("\n Please Enter the amount to transfer   : ");
    scanf("%f", &amount);

   // Locate sender and receiver in the user list
    for (int i = 0; i < totalUsers; i++)
	{
        if (strcmp(username, users[i].username) == 0)
		{
			 amount1 = users[i].balance;  // from user

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
			 amount2 = users[i].balance;  // to user
        }
        else
        {
        		found  = 1;
		}
    }

     // Check if the sender has enough balance
    if(amount1 < amount)
    {
    	printf("You Don't Have Enough Money For this Transaction...\n");
    	return ;
	}

    int added = amount + amount2; // Add amount to receiver

    int subtractred = amount1 - amount;// Subtract from sender

     // Update balances in memory
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

    if (!found)
	{
        printf("User with username %s not found.\n", username);
        return;
    }
    else
    {
    	printf("\n  Transfered Completed Successfuly ", username);
    	printf("\n-------------------------------------");
	}

     // Save updated balances back to the file
    accountsFile = fopen("accountnames.txt", "w");
    if (!accountsFile)
	{
        printf("Error opening file for writing!\n");
        return;
    }


    for (int i = 0; i < totalUsers; i++) {
        fprintf(accountsFile, "Name: %s\n", users[i].name);
        fprintf(accountsFile, "Age: %.2f\n", users[i].age);
        fprintf(accountsFile, "Personal ID: %ld\n", users[i].Personal_id);
        fprintf(accountsFile, "Phone Number: %ld\n", users[i].PhoneNumber);
        fprintf(accountsFile, "Username: %s\n", users[i].username);
        fprintf(accountsFile, "Password: %s\n", users[i].password);
        fprintf(accountsFile, "Balance: %.2f\n", users[i].balance);
        fprintf(accountsFile, "-----------------------\n");
    }

    fclose(accountsFile);

    //system("cls");
}


void checkBalance(void)
{
	system("cls");

    char username[20];
    FILE *accountsFile;
    person_details p;
    int found = 0;

    printf("\n Please Enter your username      : ");
    scanf("%s", username);

    accountsFile = fopen("accountnames.txt", "r");
    if (!accountsFile)
	{
        printf("Error opening file for reading!\n");
        return;
    }

    while (fscanf(accountsFile, "Name: %s\n", p.name) != -1)
	{
        fscanf(accountsFile, "Age: %f\n", &p.age);
        fscanf(accountsFile, "Personal ID: %ld\n", &p.Personal_id);
        fscanf(accountsFile, "Phone Number: %ld\n", &p.PhoneNumber);
        fscanf(accountsFile, "Username: %s\n", p.username);
        fscanf(accountsFile, "Password: %s\n", p.password);
        fscanf(accountsFile, "Balance: %f\n", &p.balance);
        fscanf(accountsFile, "-----------------------\n");

        if (strcmp(username, p.username) == 0)
		{
            printf("\n %s's current balance is : %.2f \n",p.username, p.balance);
            printf("\n-----------------------------------");
            found = 1;
           break;
        }
    }

    if (!found)
	{
        printf("User with username %s not found.\n", username);
        return ;
    }

    fclose(accountsFile);

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
        fscanf(accountsFile, "Personal ID: %ld\n", &p.Personal_id);
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
		printf("\n \n -------------- User InFormation -------------- \n");
		for(int i =0 ;i < 100 ;i++)
		{
			if(strcmp(username,users[i].username)==0)
			{
				printf("Name        : %s\n"    , users[i].name);
				printf("UserName    : %s\n"    , users[i].username);
				printf("PassWord    : %s \n"   , users[i].password);
				printf("PhoneNumber : %li\n"   , users[i].PhoneNumber);
				printf("Personal ID : %ld\n"    , users[i].Personal_id);
				printf("Age         : %0.1f\n" , users[i].age);

			}

		}

	}
  if (logedin) {
        printf("--------------Login successful!--------------\n");
        int choice;
        do {
            printf("\n1. Transfer Money\n2. Check Balance\n3. delete User\n4. LogOut\n");
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
                    delete_user();
                    break;
                case 4:
                    printf("Logging out...\n");
                    exit(0);
                    break;
            }
        } while (choice != 4);
    } else {
        printf("Invalid username or password.\n");
        exit(0);
    }
fclose(accountsFile);
}
void delete_user(void)
{
    char username[20], password[20];
    FILE *accountsFile, *tempFile;
    person_details p;
    int userDeleted = 0; // Flag to check if the user was deleted

    // Prompt for username and password
    printf("\nEnter UserName To Delete: ");
    scanf("%s", username);

    printf("\nEnter PassWord To Delete: ");
    scanf("%s", password);

    // Open the accounts file for reading
    accountsFile = fopen("accountnames.txt", "r");
    if (!accountsFile) {
        printf("Error opening the accounts file for reading!\n");
        return;
    }

    // Open a temporary file for writing
    tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("Error opening the temporary file for writing!\n");
        fclose(accountsFile);
        return;
    }

    // Process each record in the accounts file
    while (fscanf(accountsFile,
                  "Name: %s\nAge: %f\nPersonal ID: %ld\nPhone Number: %ld\nUsername: %s\nPassword: %s\nBalance: %f\n-----------------------\n",
                  p.name, &p.age, &p.Personal_id, &p.PhoneNumber, p.username, p.password, &p.balance) != -1)
	{

        // Check if this record matches the credentials
        if (strcmp(username, p.username) == 0 && strcmp(password, p.password) == 0) {
            userDeleted = 1; // Mark user as deleted
            printf("\nUser '%s' deleted successfully!\n", username);
            continue; // Skip writing this user to the temp file
        }

        // Write all other records to the temporary file
        fprintf(tempFile,
                "Name: %s\nAge: %.2f\nPersonal ID: %ld\nPhone Number: %ld\nUsername: %s\nPassword: %s\nBalance: %.2f\n-----------------------\n",
                p.name, p.age, p.Personal_id, p.PhoneNumber, p.username, p.password, p.balance);
    }

    // Close both files
    fclose(accountsFile);
    fclose(tempFile);

    // Replace the original file with the temporary file
    if (userDeleted)
	{
        remove("accountnames.txt");
        rename("temp.txt", "accountnames.txt");
    } else
	{
        printf("\nUser not found or incorrect credentials.\n");
        remove("temp.txt"); // Clean up the temporary file
    }
}





