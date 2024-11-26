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

	char buffer[255];
	for (int i = 0; i < 5; i++)
	{
		fgets(buffer, sizeof(buffer), f);
	}

	
	if (record == 0)
	{
		printf("No records.\n");
		return;
	}

	printf("CMS: Here are all the records found in the table StudentRecords.\n");
	printf("ID\tName\t\tProgramme\t\tMark\n");

	while (fscanf(f, "%d %[^\t] %[^\t] %f", &sr.studentID, sr.studentName, sr.Programme, &sr.Marks) == 4)
	{
		printf("%d\t%s\t%s\t%.2f\n", sr.studentID, sr.studentName, sr.Programme, sr.Marks);
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
	printf("CMS: A new record with ID=%d  is successfully inserted.\n", new.studentID);

	fclose(f);
}

void save()
{
	printf("CMS: The database file P9_7-CMS.txt is successfully saved.");
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

	}
}
