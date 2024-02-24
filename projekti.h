#ifndef PROJEKTI_H
#define PROJEKTI_H

typedef struct{
	int studentNum; //student number
	char lastName[30]; // last name of the student
	char firstName[20]; // first name of the student
	int points[6];	// student's points
	int sofp; // sum of points	
}Student;

int nofStudents;

Student *init(void); // initialize Student sturct
Student *addStudent(Student *s, int studentNum, char *lastName, char *firstName);
void updatePoints(Student *s,int studentNum, int round, int points);
void printResults(Student *s);
int writeFile(const char *fileName, Student *s);
Student *loadFile(const char *filename, Student *s, int extend);
int compareAlpha(const void* a, const void* b);
int comparePoints(const void *a, const void *b);
void freeStudent(Student *s);
int validateStudent(Student *s,  int studentNum, char *lastName, char *firstName);
Student *validateStudents(Student *s);

#endif // PROJEKTI_H