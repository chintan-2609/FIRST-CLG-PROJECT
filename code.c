#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float gpa;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void saveToFile() {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return;
    }
    fwrite(&student_count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("Records saved successfully.\n");
}

void loadFromFile() {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No existing records found.\n");
        return;
    }
    fread(&student_count, sizeof(int), 1, file);
    fread(students, sizeof(Student), student_count, file);
    fclose(file);
    printf("Records loaded successfully.\n");
}

void addStudent() {
    if (student_count >= MAX_STUDENTS) {
        printf("Maximum student limit reached.\n");
        return;
    }
    Student s;
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    getchar(); // clear newline
    fgets(s.name, MAX_NAME_LENGTH, stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; // Remove newline
    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    students[student_count++] = s;
    printf("Student added successfully.\n");
}

void viewStudents() {
    if (student_count == 0) {
        printf("No records found.\n");
        return;
    }
    printf("\n%-10s %-20s %-10s\n", "ID", "Name", "GPA");
    printf("====================================\n");
    for (int i = 0; i < student_count; i++) {
        printf("%-10d %-20s %-10.2f\n", students[i].id, students[i].name, students[i].gpa);
    }
}

void deleteStudent() {
    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("Record deleted successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Record not found.\n");
    }
}

void updateStudent() {
    int id, found = 0;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("Enter new name: ");
            getchar(); // clear newline
            fgets(students[i].name, MAX_NAME_LENGTH, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove newline
            printf("Enter new GPA: ");
            scanf("%f", &students[i].gpa);

            printf("Record updated successfully.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Record not found.\n");
    }
}

void menu() {
    int choice;
    while (1) {
        printf("\n--- Student Record Management ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Delete Student\n");
        printf("4. Update Student\n");
        printf("5. Save Records\n");
        printf("6. Load Records\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: deleteStudent(); break;
            case 4: updateStudent(); break;
            case 5: saveToFile(); break;
            case 6: loadFromFile(); break;
            case 0: 
                printf("Exiting...\n");
                exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }
}

int main() {
    loadFromFile();
    menu();
    return 0;
}
