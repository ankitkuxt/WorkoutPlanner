#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Exercise
typedef struct Exercise {
    char name[50];
    int sets;
    int reps;
    struct Exercise *next;
} Exercise;

// Structure for Day
typedef struct Day {
    char name[15];
    Exercise *exercises;
    struct Day *next;
} Day;

// Structure for User
struct User currentUser;
struct User {
    char username[50];
    char password[50];
    //Day *days;
    //struct User *next;
} User;


// Function to create a new exercise node
Exercise *createExerciseNode(char name[], int sets, int reps) {
    Exercise *newExercise = (Exercise *)malloc(sizeof(Exercise));
    if (newExercise == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newExercise->name, name);
    newExercise->sets = sets;
    newExercise->reps = reps;
    newExercise->next = NULL;
    return newExercise;
}

// Function to create a new day node
Day *createDayNode(char name[]) {
    Day *newDay = (Day *)malloc(sizeof(Day));
    if (newDay == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newDay->name, name);
    newDay->exercises = NULL;
    newDay->next = NULL;
    return newDay;
}

// Function to create a new user node
/*User *createUserNode(char username[]) {
    User *newUser = (User *)malloc(sizeof(User));
    if (newUser == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newUser->username, username);
    newUser->days = NULL;
    newUser->next = NULL;
    return newUser;
}*/

// Function to add an exercise to a specific day
void addExercise(Day *head, char dayName[], char exerciseName[], int sets, int reps) {
    Day *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, dayName) == 0) {
            Exercise *newExercise = createExerciseNode(exerciseName, sets, reps);
            newExercise->next = temp->exercises;
            temp->exercises = newExercise;
            return;
        }
        temp = temp->next;
    }
    printf("Day not found.\n");
}

// Function to delete an exercise from a specific day
void deleteExercise(Day *head, char dayName[], char exerciseName[]) {
    Day *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, dayName) == 0) {
            Exercise *prev = NULL;
            Exercise *curr = temp->exercises;
            while (curr != NULL) {
                if (strcmp(curr->name, exerciseName) == 0) {
                    if (prev == NULL)
                        temp->exercises = curr->next;
                    else
                        prev->next = curr->next;
                    free(curr);
                    printf("Exercise deleted successfully.\n");
                    return;
                }
                prev = curr;
                curr = curr->next;
            }
            printf("Exercise not found.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Exercise not added on this day of your Routine.\n");
}

// Function to display all exercises for each day
void display(Day *head) {
    Day *temp = head;
    while (temp != NULL) {
        printf("Day: %s\n", temp->name);
        Exercise *exercise = temp->exercises;
        while (exercise != NULL) {
            printf(" - %s (Sets: %d, Reps: %d)\n", exercise->name, exercise->sets, exercise->reps);
            exercise = exercise->next;
        }
        temp = temp->next;
    }
}

void signUp(){
    struct User newUser;
    printf("Enter your username:");
    scanf("%s",newUser.username);
    printf("Enter your password:");
    scanf("%s",newUser.password);

    FILE *file = fopen("users.txt","a");
    fprintf(file,"%s %s\n",newUser.username,newUser.password);
    fclose(file);

    printf("Account created successfully!\n");
}

int userExists(char *username, char *password){
    FILE *file = fopen("users.txt","r");
    if(file == NULL){
        return 0;
    }

    char storedUsername[50];
    char storedPassword[50];
    while(fscanf(file, "%s %s\n", storedUsername, storedPassword) != EOF){
        if(strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0){
            fclose(file);
            return 1;

        }
    }
    fclose(file);
    return 0;
}

// Function to add a new user
/*User *addUser(User *head, char username[]) {
    User *newUser = createUserNode(username);
    newUser->next = head;
    return newUser;
}*/

int main() {
    // Initialize user
    //User *users = NULL;
    //char username[50];


    // Initialize days of the week
    Day *head = createDayNode("Monday");
    head->next = createDayNode("Tuesday");
    head->next->next = createDayNode("Wednesday");
    head->next->next->next = createDayNode("Thursday");
    head->next->next->next->next = createDayNode("Friday");
    head->next->next->next->next->next = createDayNode("Saturday");
    head->next->next->next->next->next->next = createDayNode("Sunday");

    //users->days = head;

    int choice;
    char dayName[15];
    char exerciseName[50];
    int sets, reps;
   int loggedIn = 0;

    while(1){
        if(!loggedIn){
            printf("Welcome to Workout Planner\n");
            printf("1. Login\n");
            printf("2. SignUp\n");
            printf("3. Exit\n");
            printf("Enter Your Choice: ");
            scanf("%d", &choice);

            switch(choice){
        case 1:
            printf("Enter your Username: ");
            scanf("%s", currentUser.username);
            printf("Enter your password: ");
            scanf("%s", currentUser.password);

            if(userExists(currentUser.username, currentUser.password)){
                printf("Login Successful!\n");
                loggedIn = 1;
            }
            else{
                printf("PLEASE SIGN UP IF YOU ARE A NEW USER\n");
            }
            break;

        case 2:
            signUp();
            break;
        case 3:
            printf("Exiting the program.\n");
            exit(0);

        default:
            printf("invalid choice. TRY AGAIN!!");
        }
    }
    else{
        printf("1. Add Exercise\n");
        printf("2. Delete Exercise\n");
        printf("3. Display Exercises\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter day name (e.g., Monday): ");
                scanf("%s", dayName);
                printf("Enter exercise name: ");
                scanf("%s", exerciseName);
                printf("Enter number of sets: ");
                scanf("%d", &sets);
                printf("Enter number of reps: ");
                scanf("%d", &reps);
                addExercise(head, dayName, exerciseName, sets, reps);
                break;
            case 2:
                printf("Enter day name (e.g., Monday): ");
                scanf("%s", dayName);
                printf("Enter exercise name: ");
                scanf("%s", exerciseName);
                deleteExercise(head, dayName, exerciseName);
                break;
            case 3:
                display(head);
                break;
            case 4:
                printf("Logging out...\n");
                loggedIn = 0;
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    }
    }
    return 0;

}


