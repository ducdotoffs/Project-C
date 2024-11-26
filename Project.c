#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct // define the structure for student records
{
    int studentID;
    char studentName[100];
    char Programme[100];
    float Marks;
} StudentRecords;

const char* filename = "P9_7-CMS.txt"; // make this text file a constant string for filename
FILE* f; // declare a pointer to a file structure
StudentRecords sr; // declare variable sr for StudentRecords
int record = 0;

void open()
{
    f = fopen(filename, "r");

    char buffer[255]; 
    for (int i = 0; i < 5; i++)
    {
        fgets(buffer, sizeof(buffer), f);
    }

    if (f == NULL)
    {
        printf("Could not open file.\n");
        return;
    }

    while (fscanf(f, "%d %[^\t] %[^\t] %f", &sr.studentID, sr.studentName, sr.Programme, &sr.Marks) == 4)
    {
        record++;
        fclose(f);
        printf("CMS: The database file P9_7-CMS.txt is successfully opened.\n");
    }
}

void show()
{
    f = fopen(filename, "r");
    if (f == NULL) {
    printf("Could not open file.\n");
    return;
    }

    if (record == 0)
    {
        printf("No records.\n");
        return;
    }

    printf("CMS: Here are all the records found in the table StudentRecords.\n");
    printf("%-8s\t%-16s\t%-20s\t%s\n", "ID", "Name", "Programme", "Mark");

    char buffer[255]; 
    for (int i = 0; i < 5; i++) {
        fgets(buffer, sizeof(buffer), f);
    }
     while (fscanf(f, "%d %[^\t] %[^\t] %f", &sr.studentID, sr.studentName, sr.Programme, &sr.Marks) == 4) {
        // Adjust the format specifiers to align the columns
        printf("%-8d\t%-16s\t%-20s\t%.2f\n", sr.studentID, sr.studentName, sr.Programme, sr.Marks); 
    }
    fclose(f);
}

void insert()
{
    f = fopen(filename, "a+");
    StudentRecords new;

    char buffer[255];
    for (int i = 0; i < 5; i++)
    {
        fgets(buffer, sizeof(buffer), f);
    }

    printf("INSERT ID= ");
    scanf("%d", &new.studentID);
    getchar();

    while (fscanf(f, "%d %[^\t] %[^\t] %f", &sr.studentID, sr.studentName, sr.Programme, &sr.Marks) == 4)
    {

        if (sr.studentID == new.studentID)
        {
            printf("CMS: The record with ID=%d already exists.\n", new.studentID);

            do
            {
                printf("INSERT ID= ");
                scanf("%d", &new.studentID);
                getchar();
            } while (sr.studentID == new.studentID);

        }

    }

    printf("Name= ");
    fgets(new.studentName, sizeof(new.studentName), stdin);
    new.studentName[strcspn(new.studentName, "\n")] = '\0';

    printf("Progamme= ");
    fgets(new.Programme, sizeof(new.Programme), stdin);
    new.Programme[strcspn(new.Programme, "\n")] = '\0';

    printf("Mark= ");
    scanf("%f", &new.Marks);
    getchar();

    fprintf(f, "%d\t%s\t%s\t%.2f\n", new.studentID, new.studentName, new.Programme, new.Marks);
    printf("CMS: A new record with ID=%d is successfully inserted.\n", new.studentID);

    fclose(f);
}

void save()
{
    printf("CMS: The database file P9_7-CMS.txt is successfully saved.");
}

void update() {
    int ID, newID;
    char newName[100];
    char newProgramme[100];
    float newMark;

    printf("P9_7: UPDATE ID=");
    if (scanf("%d", &ID) != 1) {
        printf("CMS: Invalid input. Please enter a valid ID.\n");
        fflush(stdin);
        return;
    }
    getchar(); // Consume the newline

    // Open the file in read mode ("r") first to check if the record exists
    f = fopen(filename, "r"); 
    if (f == NULL) {
        printf("CMS: Error opening database file.\n");
        return;
    }

    char buffer[255];
    for (int i = 0; i < 5; i++) {
        fgets(buffer, sizeof(buffer), f);
    }

    int found = 0;
    StudentRecords temp;

    while (fscanf(f, "%d %[^\t] %[^\t] %f", &temp.studentID, temp.studentName, temp.Programme, &temp.Marks) == 4) {
        if (temp.studentID == ID) {
            found = 1;
            break; 
        }
    }

    fclose(f); // Close the file

    if (!found) {
        printf("CMS: The record with ID=%d does not exist.\n", ID);
        return;
    }

    // If the record exists, reopen the file in update mode ("r+")
    f = fopen(filename, "r+"); 
    if (f == NULL) {
        printf("CMS: Error opening database file.\n");
        return;
    }

    // Get new data for each field
    printf("P9_7: UPDATE ID=");
    if (scanf("%d", &newID) != 1) {
        printf("CMS: Invalid input. Please enter a valid ID.\n");
        fflush(stdin);
        fclose(f);
        return;
    }
    getchar();

    printf(" Name=");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = 0;

    printf(" Programme=");
    fgets(newProgramme, sizeof(newProgramme), stdin);
    newProgramme[strcspn(newProgramme, "\n")] = 0;

    printf(" Mark=");
    if (scanf("%f", &newMark) != 1) {
        printf("CMS: Invalid input. Please enter a valid mark.\n");
        fflush(stdin);
        fclose(f);
        return;
    }
    getchar();

    // Find the record again and update it
    rewind(f); // Rewind the file pointer to the beginning
    for (int i = 0; i < 5; i++) {
        fgets(buffer, sizeof(buffer), f);
    }

    while (fscanf(f, "%d %[^\t] %[^\t] %f", &temp.studentID, temp.studentName, temp.Programme, &temp.Marks) == 4) {
        if (temp.studentID == ID) {

            // Calculate the length of the old data
            int oldLength = snprintf(NULL, 0, "%d\t%s\t%s\t%.2f\n",
                                     temp.studentID, temp.studentName, temp.Programme, temp.Marks);

            // Move the file pointer back to the beginning of the record
            fseek(f, -oldLength, SEEK_CUR);

            // Overwrite with new data, padding with spaces to match the old length
            fprintf(f, "%-8d\t%-16s\t%-20s\t%.2f%*s",
                    newID, newName, newProgramme, newMark, oldLength - 44, "");

            break;
        }
    }

    printf("CMS: The record with ID=%d is successfully updated.\n", ID);
    fclose(f);
}
int main()
{
    char select[255];
    while (1)
    {
        printf("\nEnter a command (OPEN, SHOW ALL, INSERT, QUERY, UPDATE, DELETE, SAVE, EXIT):\n");
        fgets(select, 255, stdin);
        select[strcspn(select, "\n")] = '\0';

        if (strcmp(select, "OPEN") == 0)
        {
            open();
        }
        else if (strcmp(select, "SHOW ALL") == 0)
        {
            show();
        }
        else if (strcmp(select, "INSERT") == 0)
        {
            insert();
        }
        else if (strcmp(select, "SAVE") == 0)
        {
            save();
        }
        else if (strcmp(select, "UPDATE") == 0)
        {
            update(); // This now calls the updated update() function
        }

    }
}