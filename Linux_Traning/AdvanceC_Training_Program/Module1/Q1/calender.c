#include <stdio.h>
#include <string.h>

#define MAX_TASK 3
#define MAX_LENGTH 50

struct WeekDays {
    char dayName[10];
    char taskList[MAX_TASK][MAX_LENGTH];
    int n; 
};

void input_task(struct WeekDays *calender) {
    int num;
    printf("Enter the number of tasks you want to schedule on %s: ", calender->dayName);
    scanf("%d", &num);

    if (num > MAX_TASK) {
        printf("Maximum number of tasks you can schedule is: %d\n", MAX_TASK);
        return;
    }

    calender->n = num;
    for (int i = 0; i < num; i++) {
        printf("Enter task %d: ", i + 1);
        scanf(" %[^\n]", calender->taskList[i]);  
    }
}

void display_task(struct WeekDays *calender) {
    printf("The list of tasks scheduled on %s:\n", calender->dayName);
    for (int i = 0; i < calender->n; i++) {
        printf("TASK %d: %s\n", i + 1, calender->taskList[i]);
    }
}

int main() {
    struct WeekDays calender[7] = {
        {"MONDAY"},
        {"TUESDAY"},
        {"WEDNESDAY"},
        {"THURSDAY"},
        {"FRIDAY"},
        {"SATURDAY"},
        {"SUNDAY"}
    };

    int choice;

    do {
        printf("\nEnter your choice (1 - Input task, 2 - Display tasks, 3 - Exit): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int day;
                printf("Enter the day number (1-Monday to 7-Sunday): ");
                scanf("%d", &day);
                if (day < 1 || day > 7) {
                    printf("Invalid day.\n");
                    break;
                }
                input_task(&calender[day - 1]);
                break;
            }
            case 2: {
                int day;
                printf("Enter the day number (1-Monday to 7-Sunday): ");
                scanf("%d", &day);
                if (day < 1 || day > 7) {
                    printf("Invalid day.\n");
                    break;
                }
                display_task(&calender[day - 1]);
                break;
            }
            
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}
