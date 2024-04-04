#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char firstName[50];
    char lastName[50];
    int group;
    float overallGrade;
} Student;

void displayAllStudents(FILE *file)
{
    Student student;
    rewind(file); // Move the file pointer to the beginning
    fseek(file, 0, SEEK_SET);
    printf("\n%-20s %-20s %-10s %-10s\n", "First Name", "Last Name", "Group", "Overall Grade");
    printf("------------------------------------------------------------------\n");

    while (fscanf(file, "%s %s %d %f", student.firstName, student.lastName, &student.group, &student.overallGrade) != EOF)
    {
        printf("%-20s %-20s %-10d %-10.2f\n", student.firstName, student.lastName, student.group, student.overallGrade);
        printf("----------------------------------------------------------------\n");
    }
    
}

// Function to add a student to the file and maintain sorting by group
void addStudent(FILE *file, char* openingPath, char* tempPath)
{
    Student newStudent;
    FILE *tempFile = fopen(tempPath, "w");
    if (tempFile == NULL)
    {
        printf("Unable to open temporary file.\n");
        return;
    }

    printf("Enter student details (First Name Last Name Group Overall Grade): ");
    scanf("%s %s %d %f", newStudent.firstName, newStudent.lastName, &newStudent.group, &newStudent.overallGrade);

    Student temp;
    int isAdded = 0;
    rewind(file);
    while (fscanf(file, "%s %s %d %f", temp.firstName, temp.lastName, &temp.group, &temp.overallGrade) != EOF)
    {
        if (strcmp(temp.firstName, newStudent.firstName) == 0 && strcmp(temp.lastName, newStudent.lastName) == 0 && temp.group == newStudent.group)
        {
            printf("Duplicate student. The student is not added.\n");
            fprintf(tempFile, "%s %s %d %.2f\n", temp.firstName, temp.lastName, temp.group, temp.overallGrade);
        }
        else if (!isAdded && newStudent.group < temp.group)
        {
            fprintf(tempFile, "%s %s %d %.2f\n", newStudent.firstName, newStudent.lastName, newStudent.group, newStudent.overallGrade);
            isAdded = 1;
            fprintf(tempFile, "%s %s %d %.2f\n", temp.firstName, temp.lastName, temp.group, temp.overallGrade);
            printf("Student added successfully!\n");
        }
        else
        {
            fprintf(tempFile, "%s %s %d %.2f\n", temp.firstName, temp.lastName, temp.group, temp.overallGrade);
        }
    }

    if (!isAdded)
    {
        fprintf(tempFile, "%s %s %d %.2f\n", newStudent.firstName, newStudent.lastName, newStudent.group, newStudent.overallGrade);
    }
    
    fclose(tempFile);
    fclose(file);
    // Replace the original file with the temporary file
    remove(openingPath);
    rename(tempPath, openingPath);
}

// Function to delete a student from the file by first name, last name, and group
void deleteStudent(FILE *file, char* openingPath, char* tempPath)
{
    char searchFirstName[50];
    char searchLastName[50];
    int searchGroup;
    
    FILE *tempFile = fopen(tempPath, "w"); // Create a temporary file for writing
    
    if (tempFile == NULL)
    {
        printf("Error creating temporary file.\n");
        exit(1);
    }

    printf("Enter student details (First Name Last Name Group): ");
    scanf("%s %s %d", searchFirstName, searchLastName, &searchGroup);

    Student student;
    int found = 0; // Flag to track if the student was found
    rewind(file);
    while (fscanf(file, "%s %s %d %f", student.firstName, student.lastName, &student.group, &student.overallGrade) != EOF)
    {
        if (strcmp(student.firstName, searchFirstName) == 0 &&
            strcmp(student.lastName, searchLastName) == 0 &&
            student.group == searchGroup)
        {
            // Skip this student (do not copy to the temporary file)
            found = 1;
            continue;
        }
        fprintf(tempFile, "%s %s %d %.2f\n", student.firstName, student.lastName, student.group, student.overallGrade);
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove(openingPath);
    rename(tempPath, openingPath);

    if (found)
    {
        printf("Student deleted successfully!\n");
    }
    else
    {
        printf("Student not found. No changes made.\n");
    }
}

// Function to search students by first name
void searchByFirstName(FILE *file)
{
    char searchName[50];
    rewind(file);
    printf("Enter first name to search: ");
    scanf("%s", searchName);

    Student student;
    printf("\n%-20s %-20s %-10s %-10s\n", "First Name", "Last Name", "Group", "Overall Grade");
    printf("------------------------------------------------------------\n");

    while (fscanf(file, "%s %s %d %f", student.firstName, student.lastName, &student.group, &student.overallGrade) != EOF)
    {
        if (strcmp(student.firstName, searchName) == 0)
        {
            printf("%-20s %-20s %-10d %-10.2f\n", student.firstName, student.lastName, student.group, student.overallGrade);
            printf("------------------------------------------------------------\n");
        }
    }
}

// Function to search students by last name
void searchByLastName(FILE *file)
{
    char searchName[50];
    rewind(file);
    printf("Enter last name to search: ");
    scanf("%s", searchName);

    Student student;
    printf("\n%-20s %-20s %-10s %-10s\n", "First Name", "Last Name", "Group", "Overall Grade");
    printf("------------------------------------------------------------\n");

    while (fscanf(file, "%s %s %d %f", student.firstName, student.lastName, &student.group, &student.overallGrade) != EOF)
    {
        if (strcmp(student.lastName, searchName) == 0)
        {
            printf("%-20s %-20s %-10d %-10.2f\n", student.firstName, student.lastName, student.group, student.overallGrade);
            printf("------------------------------------------------------------\n");
        }
    }
}

// Function to search students by group
void searchByGroup(FILE *file)
{
    int searchGroup;
    rewind(file);
    printf("Enter group number to search: ");
    scanf("%d", &searchGroup);

    Student student;
    printf("\n%-20s %-20s %-10s %-10s\n", "First Name", "Last Name", "Group", "Overall Grade");
    printf("------------------------------------------------------------\n");

    while (fscanf(file, "%s %s %d %f", student.firstName, student.lastName, &student.group, &student.overallGrade) != EOF)
    {
        if (student.group == searchGroup)
        {
            printf("%-20s %-20s %-10d %-10.2f\n", student.firstName, student.lastName, student.group, student.overallGrade);
            printf("------------------------------------------------------------\n");
        }
    }
}

// Function to display the menu
void displayMenu()
{
    printf("\n=== Student Management System ===\n");
    printf("1. Display all students\n");
    printf("2. Add a student\n");
    printf("3. Delete a student\n");
    printf("4. Search by first name\n");
    printf("5. Search by last name\n");
    printf("6. Search by group\n");
    printf("7. Switch to another file\n");
    printf("0. Quit\n");
    printf("Enter your choice: ");
}

int main()
{
    bool changeFile = true;
    FILE *studentFile;
    char fileName[128];
    char tempfilePath[256];
    char openingFilePath[256];
    
    
    while(changeFile){
        changeFile = false;
        printf("Enter the name of the file to (edit or make): ");
        scanf("%s", fileName);
        char *username = getenv("USERPROFILE");
        if (username == NULL) {
           printf("Could not get username!\n");
           system("pause");
           return 1;
        }
        sprintf(tempfilePath, "%s\\Desktop\\temp.txt", username);
        sprintf(openingFilePath, "%s\\Desktop\\%s.txt", username, fileName);
        
        studentFile = fopen(openingFilePath, "r");
            if(studentFile){
                printf("File already exists.\nEditing mode!\n");
                system("pause");
                fclose(studentFile);
                system("cls");
            }
            else
            {
                printf("Making a new file!\n");
                system("pause");
                system("cls");
            }
        
        int choice = -1;
        bool active = true;
        while (active)
        {
            studentFile = fopen(openingFilePath, "a+");

            if (studentFile == NULL) {
                printf("Error opening file!\n");
                system("pause");
                return 1;
            }
            
            displayMenu();
            scanf("%d", &choice);
            switch (choice)
            {
            case 0:
                system("cls");
                printf("Exiting the program. Goodbye!\n");
                system("pause");
                fclose(studentFile); // Close the file before exiting
                active = false;
                exit(0);
            case 1:
                system("cls");
                displayAllStudents(studentFile);
                fclose(studentFile);
                break;
            case 2:
                 system("cls");
                addStudent(studentFile, openingFilePath, tempfilePath);
                break;
            case 3:
                system("cls");
                displayAllStudents(studentFile);
                deleteStudent(studentFile, openingFilePath, tempfilePath);
                break;
            case 4:
                 system("cls");
                searchByFirstName(studentFile);
                fclose(studentFile);
                break;
            case 5:
                 system("cls");
                searchByLastName(studentFile);
                fclose(studentFile);
                break;
            case 6:
                 system("cls");
                searchByGroup(studentFile);
                fclose(studentFile);
                break;
            case 7:
                system("cls");
                fclose(studentFile);
                active = false;
                changeFile = true;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
    }
    return 0;
}
