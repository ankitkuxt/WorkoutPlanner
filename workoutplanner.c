#include <stdio.h>
#include <string.h>

#define MAX_WORKOUTS 5
#define MAX_EXERCISES 10
#define MAX_NAME_LENGTH 50

// Structure to represent an exercise
typedef struct {
    char exerciseName[MAX_NAME_LENGTH];
    int sets;
    int reps;
} Exercise;

// Structure to represent a workout for a day
typedef struct {
    char day[MAX_NAME_LENGTH];
    Exercise exercises[MAX_EXERCISES];
    int numExercises;
} Workout;

// Function to add a new exercise to a workout
void addExercise(Workout *workout) {
    if (workout->numExercises < MAX_EXERCISES) {
        Exercise newExercise;
        printf("Enter exercise name: ");
        scanf("%[^\n]s", newExercise.exerciseName);
        printf("Enter sets: ");
        scanf("%d", &newExercise.sets);
        printf("Enter reps: ");
        scanf("%d", &newExercise.reps);

        workout->exercises[workout->numExercises] = newExercise;
        workout->numExercises++;

        printf("%s added successfully!\n",newExercise.exerciseName);
    } else {
        printf("Cannot add more exercises for this workout.\n");
    }
}

// Function to display the workouts for a week
void displayWeek(Workout week[]) {
    printf("\nWeekly Workout Schedule:\n");

    for (int i = 0; i < 7; i++) {
        if (week[i].numExercises > 0) {
            printf("\n%s Workout:\n", week[i].day);
            for (int j = 0; j < week[i].numExercises; j++) {
                printf("Exercise: %s\n Sets: %d\n Reps: %d\n",
                       week[i].exercises[j].exerciseName,
                       week[i].exercises[j].sets,
                       week[i].exercises[j].reps);
            }
        }
    }
}

int main() {
    // Array to store workouts for each day of the week
    Workout week[7];

    // Initialize days of the week
    char daysOfWeek[7][MAX_NAME_LENGTH] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    // Populate week array with days of the week
    for (int i = 0; i < 7; i++) {
        strcpy(week[i].day, daysOfWeek[i]);
        week[i].numExercises = 0;
    }

    int choice;
    int dayIndex;

    do {
        // Display menu
        printf("\nMenu:\n");
        printf("1. Add Exercise\n");
        printf("2. Display Weekly Schedule\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add exercise
                printf("Enter the index of the Day:\n 0:Monday\n 1:Tuesday\n 2:Wednesday\n 3.Thursday\n 4.Friday\n 5.Saturday\n 6.Sunday: ");
                scanf("%d", &dayIndex);

                if (dayIndex >= 0 && dayIndex < 7) {
                    addExercise(&week[dayIndex]);
                } else {
                    printf("Invalid day index.\n");
                }
                break;
            case 2:
                // Display weekly schedule
                displayWeek(week);
                break;
            case 3:
                // Exit the program
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
