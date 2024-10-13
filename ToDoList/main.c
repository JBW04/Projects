#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TITLE_LENGTH 100

// Structure to represent the task
struct Task {
    char title[MAX_TITLE_LENGTH];
    int isCompleted;
};

// Array to store tasks
struct Task toDoList[MAX_TASKS];
int taskCount = 0; // Keeps track of the number of tasks


// Function to add a task
void addTask() {
    if (taskCount < MAX_TASKS) {
        printf("Enter a task title: ");
        getchar(); //Clears the newline charter from the previous input
        fgets(toDoList[taskCount].title, MAX_TITLE_LENGTH, stdin);
        toDoList[taskCount].title[strcspn(toDoList[taskCount].title, "\n")] = 0;
        toDoList[taskCount].isCompleted = 0;
        taskCount++;
        printf("Task added succesfully!\n");
    } else {
        printf("To-Do list is full\n");
    }
}

void viewTask() {
    if (taskCount == 0) {
        printf("Your To-Do List is empty.\n");
    } else {
        printf("\nYour To-Do List:\n");
        for(int i = 0; i < taskCount; i++) {
            printf("%d. %s [%s]\n", i + 1,toDoList[i].title, toDoList[i].isCompleted ? "Completed" : "Not Completed");
        }
    }

}

void completeTask() {
    int taskNumber;
    printf("Enter the task number to mark as complete");
    scanf("%d", &taskNumber);

    if (taskNumber > 0 && taskNumber <= taskCount) {
        toDoList[taskNumber - 1].isCompleted= 1;
        printf("Task %d marked as complete!\n");
    }else {
        printf("Invalid task number\n");
    }
}

void deleteTask() {
    int taskNumber;
    printf("Enter the task number to delete: ");
    scanf("%d", &taskNumber);

    if (taskNumber > 0 && taskNumber <= taskCount) {
        //Shifts the remaining tasks
        for(int i = taskNumber - 1; i < taskCount - 1; i++) {
            toDoList[i] = toDoList[i + 1];
        }
        taskCount--;
        printf("Task %d deleted successfully!\n", taskNumber);
    } else {
        printf("Invalid task number\n");
    }
}

int main(void) {
    int choice;

    do {
        printf("\n----- To-Do-List -----\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Delete Tasks\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTask();
                break;
            case 3:
                completeTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }while (choice != 5);

    return 0;
}
