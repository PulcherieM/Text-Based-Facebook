
// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#define THREE 3

int main()
{

    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);

    /*
      {
        user_t *temp = users;
        printf("\nckpt %d", __LINE__);
        while(temp!=NULL)
        {
            printf("\n\nusername: %s", temp->username);

            friend_t *testF = temp->friends;
            printf("\nfriend: %s", testF);

            while(testF != NULL)
            {
                printf("\nfriend name: %s", testF->username);
                testF = testF->next;
            }
            temp = temp->next;
        }
    }
    */

    unsigned short int user_choice;
    user_t *database = users; // TO start the program with users in the csv file //an empty list
    char post_input[250];

    printf("********************* Welcome to Text-Based Facebook ********************* \n");
    printf("\n");
    printf("\n");
    do
    {

        print_menu();
        printf("\n");
        scanf("%d", &user_choice);
        if (user_choice <= 0 || user_choice > 6)
        {
            printf("Invalid choice. Please try again\n");
            printf("Enter a valid choice:\n ");

            while (scanf("%d", &user_choice) != 1)
            {
                printf("invalid input:\n");
                while (getchar() != '\n')
                    ;
            }
        }

        // user_t *user_name_input;
        char user_name_input[30];
        char user_password_input[15];
        char friend_name[30];

        switch (user_choice)
        {
        case 1:
            printf("Enter a username:\n ");
            scanf("%s", user_name_input);
            printf("Enter an up to 15 characters password:\n ");
            scanf("%s", user_password_input);
            printf("\n");
            printf("**** User Added! ****\n");
            printf("\n");

            // CALL add_user:
            // returns the head of the list to database
            database = add_user(database, user_name_input, user_password_input);

            break;
        case 2:
            printf("Enter a username to update your password:\n ");
            scanf("%s", user_name_input);

            /* database points to the ordered list, so we use database as parameter 1
             */

            user_t *check_user_in_list = find_user(database, user_name_input);
            /* problem is the if only checks once, like if you write the wrong username
            it will print the menu, then if you choose option 2, amd write the correct username it will say its wrong
            not specified in instructions

            */
            if (check_user_in_list == NULL)
            {
                printf("\n");
                printf("-------------------- User not found --------------------\n");
                printf("\n");
            }

            else if (check_user_in_list != NULL)
            {
                printf("Please enter your old password\n");

                scanf("%s", user_password_input);
                // check if the old password of the entered username mathces

                if (strcmp(user_password_input, check_user_in_list->password) == 0)
                {
                    printf("Enter a new password up to 15 characters\n");
                    scanf("%s", user_password_input);
                    printf("*****Password changed*****\n");
                    printf("\n");
                }
                else
                {
                    printf("Password error message\n");
                }
            }
            break;
        case 3:
            printf("enter a username to manage their posts:\n");
            scanf("%s", user_name_input);
            check_user_in_list = find_user(database, user_name_input);
            if (check_user_in_list == NULL)
            {
                printf("-------------------- User not found --------------------\n");
                break; // Returns to the main menu.
            }

            unsigned short int user_choice_input;

            do
            {
                /*
                a do while so that the post menu gets repeated


                */

                printf("*************************************************************\n");
                printf("      Managing %s's posts             \n", user_name_input);
                printf("*************************************************************\n");
                if (check_user_in_list->posts == NULL)
                {
                    printf("Note: No posts available for %s\n", user_name_input); // user_name_input
                }

                printf("1. Add a new post\n");
                printf("2. Remove a post\n");
                printf("3. Return to main menu\n");
                printf("enter your choice:\n");
                scanf("%d", &user_choice_input);

                // check_user_in_list ==== one individual username
                switch (user_choice_input)
                {
                case 1:
                    printf("enter a post under 250 characters:\n");
                    scanf(" %[^\n]s", post_input);
                    add_post(check_user_in_list, post_input);
                    printf("post added successfully\n");
                    display_all_user_posts(check_user_in_list);

                    // not &post_input cuz post_input is an array of characters,
                    break;
                case 2:
                    printf("deleting most recent post\n");
                    delete_post(check_user_in_list);
                    break;
                case 3:
                    break;

                default:
                    printf("invalid choice, re-enter\n");
                    printf("\n");
                }
            } while (user_choice_input != 3);

            break;

        case 4:
            printf("enter a username to manage their friends:\n");
            scanf("%s", user_name_input);
            // check if the username is in the database of usernames
            check_user_in_list = find_user(database, user_name_input);
            if (check_user_in_list == NULL)
            {
                printf("-------------------- User not found --------------------\n");
                break; // Returns to the main menu.
            }
            do
            {
                /*
            a do while so that the post menu gets repeated

            */
                printf("*******************************************************************\n");
                printf("      Managing %s's friends \n", user_name_input);
                printf("*******************************************************************\n");

                printf("1. Add a new friend\n");
                printf("2. Remove a friend\n");
                printf("3. Return to main menu\n");
                printf("enter your choice:\n");
                scanf("%d", &user_choice_input);

                switch (user_choice_input)
                {
                case 1:
                    printf("enter a friends name\n");
                    scanf("%s", friend_name);
                    add_friend(check_user_in_list, friend_name);
                    printf("friend added to the list\n");
                    break;

                case 2:
                    printf("*******************************************************************\n");

                    printf("List of %s's friend names:\n", user_name_input); // user_name_input
                    printf("*******************************************************************\n");

                    display_user_friends(check_user_in_list);

                    printf("which friend would you like to delete?:\n");
                    scanf("%s", friend_name); // should i have just s

                    delete_friend(check_user_in_list, friend_name);

                    break;
                case 3:
                    break; // returns post menu
                default:
                    printf("invalid choice, re-enter\n");
                    printf("\n");
                }

            } while (user_choice_input != 3);
            break;

        case 5:
            printf("enter a username to display their posts\n");
            scanf("%s", user_name_input);
            // check if the username is in the database of usernames
            check_user_in_list = find_user(database, user_name_input);

            if (check_user_in_list == NULL)
            {
                printf("-------------------- User not found --------------------\n");
                break; // Return to the main menu.
            }
            display_posts_by_n(check_user_in_list, THREE); // make the 3 a constant
                                                           // dispplay the next 3 if theres more posts

            break;

        case 6: // in the do while the loop itterates at least once regardless of the while condition, then when the whole do is done it will evaluate the while
            // if its true then it terminates.
            printf("Goodbye\n");
            teardown(database);
            break;
        default:
            printf("invalid choice, re-enter\n");
            printf("\n");
        }

    } while (user_choice != 6);

    // where I call the functions i implemented in function.c
}
