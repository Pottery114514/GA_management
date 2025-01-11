// Graduate Exam Management System

#include <stdio.h>
#include <string.h>
#define MAX_STUDENTS 100//考生数量<100

typedef struct {//考生信息结构体
    char name[50];
    char admissionNumber[20];
    char major[50];
    int isFreshGraduate;
    int scores[4]; // [政治, Math, English, MajorSubject]
} Student;

Student students[MAX_STUDENTS];//考生信息数组
int studentCount = 0;

//功能一览
void addStudent();
void deleteStudent();
void queryStudent();
void sortStudents();
void showAdminMenu();
void queryScore();
void showStudentMenu();
void showMainMenu();

// Helper function to load and save data
void loadData();
void saveData();

// Admin functions
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student list is full. Cannot add more students.\n");
        return;
    }

    Student newStudent;
    printf("输入姓名: ");
    scanf("%s", newStudent.name);
    printf("学号: ");
    scanf("%s", newStudent.admissionNumber);
    printf("专业: ");
    scanf("%s", newStudent.major);
    printf("是否应届生? (1 for Yes, 0 for No): ");
    scanf("%d", &newStudent.isFreshGraduate);
    printf("输入成绩 (政治 数学 英语 专业课程): ");
    for (int i = 0; i < 4; i++) {
        scanf("%d", &newStudent.scores[i]);
    }

    students[studentCount++] = newStudent;
    printf("已录入考生信息.\n");
    saveData();
}

void deleteStudent() {
    char admissionNumber[20];
    printf("请输入要删除考生的学号: ");
    scanf("%s", admissionNumber);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].admissionNumber, admissionNumber) == 0) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            printf("已删除考生信息.\n");
            saveData();
            return;
        }
    }

    printf("Student not found.\n");
}

void queryStudent() {
    char admissionNumber[20];
    printf("请输入学号: ");
    scanf("%s", admissionNumber);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].admissionNumber, admissionNumber) == 0) {
            printf("姓名: %s\n", students[i].name);
            printf("学号: %s\n", students[i].admissionNumber);
            printf("专业: %s\n", students[i].major);
            printf("是否应届: %s\n", students[i].isFreshGraduate ? "Yes" : "No");
            printf("成绩: 政治: %d, 数学: %d, 英语: %d, 专业课程: %d\n",
                   students[i].scores[0], students[i].scores[1], students[i].scores[2], students[i].scores[3]);
            return;
        }
    }

    printf("Student not found.\n");
}

void sortStudents() {
    int subjectIndex;
    printf("输入排序依据 (0: 政治, 1: 数学, 2: 英语, 3: 专业课程): ");
    scanf("%d", &subjectIndex);

    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (students[j].scores[subjectIndex] < students[j + 1].scores[subjectIndex]) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("已按照%d成绩进行排序.\n", subjectIndex);
}

void showAdminMenu() {
    int choice;
    while (1) {
        printf("\nAdministrator Menu:\n");
        printf("1. 录入考生信息\n");
        printf("2. 删除考生信息\n");
        printf("3. Query Student\n");
        printf("4. Sort Students\n");
        printf("5. 返回主菜单\n");
        printf("输入选项: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                queryStudent();
                break;
            case 4:
                sortStudents();
                break;
            case 5:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Student functions
void queryScore() {
    char admissionNumber[20];
    printf("Enter your admission number: ");
    scanf("%s", admissionNumber);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].admissionNumber, admissionNumber) == 0) {
            printf("Name: %s\n", students[i].name);
            printf("Scores: 政治: %d, Math: %d, English: %d, Major Subject: %d\n",
                   students[i].scores[0], students[i].scores[1], students[i].scores[2], students[i].scores[3]);
            return;
        }
    }

    printf("Student not found.\n");
}

void showStudentMenu() {
    int choice;
    while (1) {
        printf("\nStudent Menu:\n");
        printf("1. Query Score\n");
        printf("2. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                queryScore();
                break;
            case 2:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Main menu
void showMainMenu() {
    int choice;
    while (1) {
        printf("\nMain Menu:\n");
        printf("1. Administrator Menu\n");
        printf("2. Student Menu\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showAdminMenu();
                break;
            case 2:
                showStudentMenu();
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Load and save data
void loadData() {
    FILE *file = fopen("info.txt", "r");
    if (!file) {
        printf("No existing data file found. Starting fresh.\n");
        return;
    }

    studentCount = 0;
    while (fscanf(file, "%s %s %s %d %d %d %d %d",
                  students[studentCount].name,
                  students[studentCount].admissionNumber,
                  students[studentCount].major,
                  &students[studentCount].isFreshGraduate,
                  &students[studentCount].scores[0],
                  &students[studentCount].scores[1],
                  &students[studentCount].scores[2],
                  &students[studentCount].scores[3]) == 8) {
        studentCount++;
    }

    fclose(file);
}

void saveData() {
    FILE *file = fopen("info.txt", "w");
    if (!file) {
        printf("Error saving data.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %s %s %d %d %d %d %d\n",
                students[i].name,
                students[i].admissionNumber,
                students[i].major,
                students[i].isFreshGraduate,
                students[i].scores[0],
                students[i].scores[1],
                students[i].scores[2],
                students[i].scores[3]);
    }

    fclose(file);
}

int main() {
    loadData();
    showMainMenu();
    saveData();
    return 0;
}
