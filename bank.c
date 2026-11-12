/* BANK MANAGEMENT SYSTEM
   BCA Data Science - Semester 1
   Compile: gcc bank.c -o bank
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Account
{
    int accountNumber;
    char name[50];
    char mobile[15];
    char accountType[20];
    float balance;
};

int main()
{
    struct Account a[100];
    int count = 0;
    int choice, i, search, found;
    float amount;
    char name[50];
    FILE *fp;

    // Load previously saved accounts
    fp = fopen("accounts.txt", "r");

    if (fp != NULL)
    {
        while (count < 100 &&
               fscanf(fp, "%d|%49[^|]|%14[^|]|%19[^|]|%f\n",
               &a[count].accountNumber,
               a[count].name,
               a[count].mobile,
               a[count].accountType,
               &a[count].balance) == 5)
        {
            count++;
        }

        fclose(fp);
    }

    do
    {
        printf("\n====================================\n");
        printf("       BANK MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Create New Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Account Balance\n");
        printf("5. Search Account\n");
        printf("6. Display All Accounts\n");
        printf("7. Transfer Money\n");
        printf("8. Exit\n");

        printf("====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            // CREATE ACCOUNT
            case 1:

                if (count >= 100)
                {
                    printf("Bank account limit reached!\n");
                    break;
                }

                printf("\nEnter Account Number: ");
                scanf("%d", &search);

                found = 0;

                for (i = 0; i < count; i++)
                {
                    if (a[i].accountNumber == search)
                    {
                        found = 1;
                        break;
                    }
                }

                if (found)
                {
                    printf("Account number already exists!\n");
                    break;
                }

                a[count].accountNumber = search;

                printf("Enter Customer Name: ");
                scanf(" %49[^\n]", a[count].name);

                printf("Enter Mobile Number: ");
                scanf("%14s", a[count].mobile);

                printf("Enter Account Type (Savings/Current): ");
                scanf("%19s", a[count].accountType);

                printf("Enter Opening Balance: ");
                scanf("%f", &a[count].balance);

                if (a[count].balance < 0)
                {
                    printf("Invalid opening balance!\n");
                    break;
                }

                count++;

                printf("\nAccount Created Successfully!\n");
                break;

            // DEPOSIT MONEY
            case 2:

                printf("\nEnter Account Number: ");
                scanf("%d", &search);

                found = 0;

                for (i = 0; i < count; i++)
                {
                    if (a[i].accountNumber == search)
                    {
                        found = 1;

                        printf("Enter Deposit Amount: ");
                        scanf("%f", &amount);

                        if (amount > 0)
                        {
                            a[i].balance += amount;

                            printf("Money Deposited Successfully!\n");
                            printf("Updated Balance: Rs. %.2f\n",
                                   a[i].balance);
                        }
                        else
                        {
                            printf("Invalid Amount!\n");
                        }

                        break;
                    }
                }

                if (!found)
                    printf("Account Not Found!\n");

                break;

            // WITHDRAW MONEY
            case 3:

                printf("\nEnter Account Number: ");
                scanf("%d", &search);

                found = 0;

                for (i = 0; i < count; i++)
                {
                    if (a[i].accountNumber == search)
                    {
                        found = 1;

                        printf("Enter Withdrawal Amount: ");
                        scanf("%f", &amount);

                        if (amount <= 0)
                        {
                            printf("Invalid Amount!\n");
                        }
                        else if (amount <= a[i].balance)
                        {
                            a[i].balance -= amount;

                            printf("Withdrawal Successful!\n");
                            printf("Remaining Balance: Rs. %.2f\n",
                                   a[i].balance);
                        }
                        else
                        {
                            printf("Insufficient Balance!\n");
                        }

                        break;
                    }
                }

                if (!found)
                    printf("Account Not Found!\n");

                break;

            // BALANCE ENQUIRY
            case 4:

                printf("\nEnter Account Number: ");
                scanf("%d", &search);

                found = 0;

                for (i = 0; i < count; i++)
                {
                    if (a[i].accountNumber == search)
                    {
                        found = 1;

                        printf("\nAccount Details\n");
                        printf("--------------------------\n");
                        printf("Account Number: %d\n",
                               a[i].accountNumber);
                        printf("Customer Name: %s\n",
                               a[i].name);
                        printf("Balance: Rs. %.2f\n",
                               a[i].balance);

                        break;
                    }
                }

                if (!found)
                    printf("Account Not Found!\n");

                break;

            // SEARCH ACCOUNT
            case 5:

                printf("\nEnter Account Number: ");
                scanf("%d", &search);

                found = 0;

                for (i = 0; i < count; i++)
                {
                    if (a[i].accountNumber == search)
                    {
                        found = 1;

                        printf("\nAccount Found!\n");
                        printf("Account Number: %d\n",
                               a[i].accountNumber);
                        printf("Name: %s\n", a[i].name);
                        printf("Mobile: %s\n", a[i].mobile);
                        printf("Account Type: %s\n",
                               a[i].accountType);
                        printf("Balance: Rs. %.2f\n",
                               a[i].balance);

                        break;
                    }
                }

                if (!found)
                    printf("Account Not Found!\n");

                break;

            // DISPLAY ALL ACCOUNTS
            case 6:

                if (count == 0)
                {
                    printf("\nNo Accounts Available!\n");
                }
                else
                {
                    printf("\n========== ALL ACCOUNTS ==========\n");

                    for (i = 0; i < count; i++)
                    {
                        printf("\nAccount Number: %d\n",
                               a[i].accountNumber);
                        printf("Name: %s\n", a[i].name);
                        printf("Mobile: %s\n", a[i].mobile);
                        printf("Account Type: %s\n",
                               a[i].accountType);
                        printf("Balance: Rs. %.2f\n",
                               a[i].balance);
                        printf("----------------------------------\n");
                    }
                }

                break;

            // TRANSFER MONEY
            case 7:

                printf("\nEnter Sender Account Number: ");
                scanf("%d", &search);

                found = -1;

                for (i = 0; i < count; i++)
                {
                    if (a[i].accountNumber == search)
                    {
                        found = i;
                        break;
                    }
                }

                if (found == -1)
                {
                    printf("Sender Account Not Found!\n");
                    break;
                }

                printf("Enter Receiver Account Number: ");
                scanf("%d", &search);

                int receiver = -1;

                for (i = 0; i < count; i++)
                {
                    if (a[i].accountNumber == search)
                    {
                        receiver = i;
                        break;
                    }
                }

                if (receiver == -1)
                {
                    printf("Receiver Account Not Found!\n");
                    break;
                }

                if (found == receiver)
                {
                    printf("Cannot transfer to the same account!\n");
                    break;
                }

                printf("Enter Transfer Amount: ");
                scanf("%f", &amount);

                if (amount <= 0)
                {
                    printf("Invalid Amount!\n");
                }
                else if (amount <= a[found].balance)
                {
                    a[found].balance -= amount;
                    a[receiver].balance += amount;

                    printf("Transfer Successful!\n");
                    printf("Remaining Balance: Rs. %.2f\n",
                           a[found].balance);
                }
                else
                {
                    printf("Insufficient Balance!\n");
                }

                break;

            // EXIT
            case 8:

                fp = fopen("accounts.txt", "w");

                if (fp != NULL)
                {
                    for (i = 0; i < count; i++)
                    {
                        fprintf(fp, "%d|%s|%s|%s|%.2f\n",
                                a[i].accountNumber,
                                a[i].name,
                                a[i].mobile,
                                a[i].accountType,
                                a[i].balance);
                    }

                    fclose(fp);

                    printf("\nAccount Records Saved Successfully!\n");
                }
                else
                {
                    printf("Unable to Save Records!\n");
                }

                printf("Thank You for Using Our Bank!\n");
                break;

            default:

                printf("Invalid Choice! Please Try Again.\n");
        }

    } while (choice != 8);

    return 0;
}
