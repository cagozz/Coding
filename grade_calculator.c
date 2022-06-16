#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
format of list.txt
---------------

Name Surname Lab(out of 10) Assignment(out of 25) Midterm(out of 100) Final(out of 100)

example:

John Smith 10.0 24.0 88.5 67.5
Jessie Green 9.8 23.4 94.1 88.2

->they must be separated with space

*/

//student structure to store information of students
typedef struct Student
{
    char name[50];
    char surname[50];
    double lab;
    double assignment;
    double midtermGrade;
    double finalGrade;
    double total;
}student;

//all function prototypes
student *loadStudentTable(char [], int*);
void displayStudentTable(student*, int);
int search(student*, int, char*);
void sort(student*, int);
void displayPersonStats(student*, int);

int main(int argc, char *argv[])//to take given file name
{
    student *studentTable;//
    int studentNumber = 0;
    int opt, searchOutput;
    char name[50];

    studentTable = loadStudentTable(argv[1], &studentNumber);//loadStudentTable creates table and send its memory address to studentTable(actually, it means return array)

    displayStudentTable(studentTable, studentNumber);//to display student table

    do//to display menu again and again until user presses 3
    {
        printf("\nPress 1 for search, 2 for sort and 3 for exit: ");
        fflush(stdin);
        scanf("%d", &opt);

        if(opt == 1)
        {
            do
            {
                printf("Enter the name of the student: ");
                fflush(stdin);
                gets(name);//takes name of student to search

                searchOutput = search(studentTable, studentNumber, name);/*this function takes table and name of student.
                If there is a student with that name, function returns location of student. Otherwise it returns -1.*/

                if(searchOutput == -1)//to display error
                    printf("That student is unknown! Please try again!\n");
            }while(searchOutput == -1);//to ask again and again

            displayPersonStats(studentTable, searchOutput);//this function displays stats of student according to one's location in table
        }
        else if(opt == 2)
        {
            sort(studentTable, studentNumber);//it sorts students according to final or total(it is explained detailer in function)
            displayStudentTable(studentTable, studentNumber);//after sorting, it displays table again
        }
        else if(opt == 3)
        {
            printf("Bye!");//to exit
        }

    }while(opt != 3);

    return 0;
}

student *loadStudentTable(char fileName[50], int *studentNumber)
{
    FILE *infoFile;//to take information from files
    FILE *counterFile;//to count how many line there is
    student *studentTable;//it is actual table
    char charCounter;//to count how many line there is
    int line;//counter

    infoFile = fopen(fileName, "r");//open file
    while(infoFile == NULL)//check if it is opened or not.
    {
        printf("This file does not exist, please enter again: ");//if not it asks file name again and again
        gets(fileName);
        infoFile = fopen(fileName, "r");
    }

    counterFile = fopen(fileName, "r");//open file again to count its line number
    do
    {
        charCounter = fgetc(counterFile);//takes character
        if(charCounter == '\n')//if there is LF, it increments studentNumber
            (*studentNumber)++;
    }while(charCounter != EOF);//when charCounter encounter with end of file, counting finishes
    fclose(counterFile);

    (*studentNumber)++;//last line does not have '\n' so studentNumber must be increased one more time.

    studentTable = (student*)malloc((*studentNumber)*sizeof(student));//according to line number, memory is allocated

    if(studentTable == NULL)//to check if it is allocated or not.
    {
        printf("studentTable array was not created/allocated..");
        exit(0);
    }

    for(line = 0; line < (*studentNumber); line++)//to take information from file line by line
    {
        fscanf(infoFile, "%s %s %lf %lf %lf %lf", studentTable[line].name, studentTable[line].surname, &studentTable[line].lab,
                                                  &studentTable[line].assignment, &studentTable[line].midtermGrade, &studentTable[line].finalGrade);
    }

    for(line = 0; line < *studentNumber; line++)//to calculate total score of students
    {
        studentTable[line].total = studentTable[line].lab + studentTable[line].assignment + 0.3*studentTable[line].midtermGrade + 0.35*studentTable[line].finalGrade;
    }

    printf("Student records file (%s) has been successfully loaded!\n", fileName);

    return studentTable;//it returns all table(actually starting memory address of array)
}

void displayStudentTable(student *studentTable, int studentNumber)//its aim is only displaying student table line by line
{
    int count;

    printf("Following records have been loaded:\n");
    printf("Name Surname\t\tLab\t\tAssignment\tMidterm\t\tFinal\t\tTotal\n\n");

    for(count = 0; count < studentNumber; count++)
    {
        printf("%s %s\t\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.2lf\t\t%.2lf\n", studentTable[count].name, studentTable[count].surname, studentTable[count].lab,
                                                                       studentTable[count].assignment, studentTable[count].midtermGrade,
                                                                       studentTable[count].finalGrade, studentTable[count].total);
    }
}

int search(student *studentTable, int studentNumber, char *name)
{
    int count;
    char *partsOfName[30];

    //assumed user writes name and surname with two parts
    partsOfName[0] = strtok(name, " ");//name
    partsOfName[1] = strtok(NULL, " ");//surname

    for(count = 0; count < studentNumber; count++)
    {
        if(!strcmp(partsOfName[0], studentTable[count].name) && !strcmp(partsOfName[1], studentTable[count].surname))//it compares names and surnames
        {
            return count;//if function find student, it returns location of student
        }
    }

    return -1;//if function cannot find student, it returns -1
}

void sort(student *studentTable, int studentNumber)
{
    char opt;
    student store;//to swapping
    int count, swapped;//counting and checking swap

    printf("Sort by (F: Final, T: Total): ");
    fflush(stdin);
    scanf("%c", &opt);

    if(opt == 'F')
    {
        do//it sorts table with bubble sorting algorithm.
        {
            swapped = 0;
            for(count = studentNumber-1; count > 0; count--)
            {
                if(studentTable[count].finalGrade > studentTable[count-1].finalGrade)
                {
                    //it takes two element of table and according to final notes, it swaps them or not
                    store = studentTable[count];
                    studentTable[count] = studentTable[count-1];
                    studentTable[count-1] = store;
                    swapped = 1;
                }
            }
        }while(swapped);
    }
    else if(opt == 'T')
    {
        do//same algorithm but according to total scores
        {
            swapped = 0;
            for(count = studentNumber-1; count > 0; count--)
            {
                if(studentTable[count].total > studentTable[count-1].total)
                {
                    store = studentTable[count];
                    studentTable[count] = studentTable[count-1];
                    studentTable[count-1] = store;
                    swapped = 1;
                }
            }
        }while(swapped);
    }
}

void displayPersonStats(student *studenTable, int studentLine)//it takes student table, and displays student stats according to location(studentLine)
{
    printf("\n%s %s has %.2lf from Lab, %.2lf from Assignments, %.2lf from Midterm and %.2lf from Final, with the total of %.2lf.\n",
           studenTable[studentLine].name, studenTable[studentLine].surname, studenTable[studentLine].lab, studenTable[studentLine].assignment,
           studenTable[studentLine].midtermGrade, studenTable[studentLine].finalGrade, studenTable[studentLine].total);
}

