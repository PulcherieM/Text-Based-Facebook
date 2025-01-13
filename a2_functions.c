

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#define THREE 3

// Your solution goes here

// I have to implement the adding user first so that it can be called when the user inputs 1, in the main menu

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
    user_t *new_node = malloc(sizeof(user_t));

    assert(new_node != NULL);
    strcpy(new_node->username, username);
    strcpy(new_node->password, password);

    new_node->friends = NULL;
    new_node->next = NULL;
    new_node->posts = NULL;

    // move to insertion point;
    user_t *previous, *current;
    previous = NULL;
    current = users;
    // checks if current username is less than username,
    // if current is null its not true so doesnt execute
    while (current != NULL && strcmp(current->username, username) < 0)
    {
        previous = current;
        current = current->next;
    }
    // insert before current

    new_node->next = current;
    // insert after previous (or at beginning if previous is NULL)
    if (previous == NULL)
    {
        // Insert at the beginning
        users = new_node;
    }
    else
    {
        // Insert after previous
        previous->next = new_node;
    }
    return users;
    // returns to the main menu
    print_menu();
}

/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
    user_t *current;
    for (current = users; current != NULL; current = current->next)
    {
        if (strcmp(current->username, username) == 0)
        {                   // checks if para username, is in the list of users-username
            return current; // if yes, return the pointer to where the username is located
        }
    }
    return NULL;
}

/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
    friend_t *friend_created = malloc(sizeof(friend_t));

    strcpy(friend_created->username, username);
    friend_created->next = NULL; // important!!
    return friend_created;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend)
{
    // Create a new friend node using the provided friend name
    friend_t *temp = create_friend(friend);

    // do this when either the friends list is empty or the new friends name will be the first node in the list
    if (user->friends == NULL || strcmp(user->friends->username, temp->username) > 0)
    {
        // insert the new friend at the beginning of the list
        temp->next = user->friends;
        user->friends = temp;
        return;
    }
    else
    {
        friend_t *current = user->friends;
        while (current != NULL)
        {
            // checking to see if theres a next node
            if (current->next != NULL)
            {
                // if the friend we are trying to add is smaller than the friend already in the list
                if (strcmp(friend, current->next->username) < 0)
                {
                    temp->next = current->next;
                    current->next = temp;
                    return;
                }
            }
            else
            {
                // if we are at the last node
                current->next = temp;
                return;
            }
            current = current->next;
        }
    }
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{

    // case 1 no friends
    if (user->friends == NULL)
    {
        printf("no friends to delete\n");
        return false;
    }

    friend_t *to_del = user->friends;
    friend_t *previous = NULL;

    // if the friend name inputed is not in the list of friends
    while (to_del != NULL && strcmp(to_del->username, friend_name) != 0)
    {
        printf("no friend to delete\n");
        break;
    }

    // alt shif f

    // finding the friend to delete
    while (to_del != NULL && strcmp(to_del->username, friend_name) != 0)
    { // you stop going trough the list when you find the username
        previous = to_del;
        to_del = to_del->next;
    }

    if (to_del == NULL)
    { // end of list
        printf("friend not in friend list\n");
        return false;
    }

    if (previous == NULL)
    { // meaning theres no node before the first node, meaning to del is the head of linked list
        user->friends = to_del->next;
    }
    else
    {
        previous->next = to_del->next;
    }
    free(to_del);
    to_del = NULL;
    printf("****************************************************\n");
    printf("%s has been sucessfully deleted\n", friend_name);
    printf("****************************************************\n");
    printf("\n");
    printf("Updated list of %s's friends\n", user->username);

    display_user_friends(user);
    return true;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{

    post_t *new_node = malloc(sizeof(post_t));
    assert(new_node != NULL);
    strcpy(new_node->content, text); // Copy the content into the new post node
    new_node->next = NULL;

    return new_node;
}

/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text)
{
    /*
    parameter user: the user whos posts are being managed
    parameter text: the content of the users post

    */
    post_t *new_node = create_post(text);

    new_node->next = user->posts; // Insert the node at the head of the stack's linked list
    user->posts = new_node;       // Update the user's posts to point to the new head
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user)
{
    // basically pop function

    post_t *to_remove = user->posts;
    if (to_remove == NULL)
    {
        printf("NO POSTS TO REMOVE\n");
        return false;
    }

    else
    {

        user->posts = user->posts->next;
        free(to_remove);
        to_remove = NULL;
        display_all_user_posts(user);
        return true;
    }
}

/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user)
{
    /*
    displays LIFO, so user->posts is the last post to be added and it will display in that order

    */

    printf("\n--- Posts by %s ---\n", user->username);
    post_t *current = user->posts; // Start at the head of the user's posts list.
    int post_number = 1;

    if (current == NULL)
    {
        printf("No posts to display.\n");
        return;
    }

    while (current != NULL)
    {
        printf("%d. %s\n", post_number++, current->content); // Display the content of each post.
        current = current->next;                             // Move to the next post.
    }
}

/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user)
{
    /*
displays LIFO, so user->posts is the last post to be added and it will display in that order

*/

    friend_t *current = user->friends; // Start at the head of the user's friends list.
    int post_number = 1;

    if (current == NULL)
    {
        printf("No friends to display.\n");
        return;
    }

    while (current != NULL)
    {
        printf("%d. %s\n", post_number++, current->username); // Display each friend in alphabeticall order, from choice one, it adds in
        // alphabetical, so when the function "returns"(doesnt return cuz void, but whrn the function terminates).
        // it remembers all friends that were added and keeps their alphabetical order
        current = current->next; // Move to the next friend.
    }
}

/*
   Function that displays "number" of posts for a given user.
   After displaying "number" posts, it prompts if you want to display
   more posts.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_posts_by_n(user_t *users, int number)
{
    char user_ans[2];

    printf("\n--- Posts by %s ---\n", users->username);
    post_t *current = users->posts; // Start at the head of the user's posts list.
    int post_number = 1;
    int count = 0;

    if (current == NULL)
    {
        printf("No posts to display.\n");
        return;
    }

    while (current != NULL)
    {
        printf("%d. %s\n", post_number++, current->content); // Display the content of each post.
        count++;
        current = current->next; // Move to the next post.

        // put where if count is 3 and its empty display no posts to display

        if (count <= THREE && current == NULL)
        {
            printf("\n");
            printf("No more posts to display\n");
            printf("\n");
            return;
        }

        if (count % number == 0)
        {
            printf("Would you like to display more?: (Y/y) or (N/n) \n");
            scanf("%s", user_ans);
            if (*user_ans == 'Y' || *user_ans == 'y')
            {
                continue;
            }
            else if (*user_ans == 'N' || *user_ans == 'n')
            {
                return;
            }
        }
    }
    printf("All posts have been displayed\n");
}

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
    user_t *current;
    post_t *posts;
    friend_t *friends;

    // check when theres no users
    /* but when theres no users theres no nodes to delete

    */
    // delete evry users friends
    for (current = users; current != NULL; current = current->next)
    {

        for (friends = current->friends; friends != NULL;)
        {
            friend_t *temp = friends->next;
            free(friends);
            friends = temp;
        }
        current->friends = NULL;

        // delete evry users posts
        for (posts = current->posts; posts != NULL;)
        {
            post_t *temp = posts->next;
            free(posts);
            posts = temp;
        }
        current->posts = NULL;
    }
    // delete every user
    for (current = users; current != NULL;)
    {
        user_t *user_hold = current->next;
        free(current);
        current = user_hold;
    }
    users = NULL;
}

void print_menu()
{
    int user_choice;

    printf("************************************************** \n MAIN MENU \n**************************************************\n");
    printf(" 1. Register a new user \n 2. Manage a user's profile (change password) \n 3. Manage a user's posts (add/remove) \n 4. Manage a user's friends (add/remove) \n 5. Display a user's posts \n 6. Exit\n");
    printf("Enter your choice: ");
    printf("\n");
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters
        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;
        token = strtok(NULL, ",");
        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}

// c instead of s
