#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projekti.h"



int nofStudents = 0; // number of students

Student *init(void){
	nofStudents = 0;
	Student *s = malloc(sizeof(Student));
	s[0].studentNum = 0;
	s[0].lastName[0] = '\0';
    s[0].firstName[0] = '\0';
	s[0].sofp = 0;
	memset(s[0].points, 0, sizeof(int)*6);

	return s;
}

int validateStudent(Student *s,  int studentNum, char *lastName, char *firstName){
	if (studentNum < 0 || lastName == NULL || firstName == NULL) {
		printf("Invalid input for studen\n");
		return 0;
	}
	int i = 0;
	while(i < nofStudents){
		if(s[i].studentNum == studentNum){
			printf("Student number %d already used\n", studentNum);
			return 0;
		}
		i++;
	}
	return 1;
}

Student *addStudent(Student *s, int studentNum, char *lastName, char *firstName){
	int i = nofStudents;
	if (!validateStudent(s, studentNum, lastName, firstName)) {
		return s;
	}
	Student *newStudent = realloc(s, sizeof(Student)*(i+1));
	if(newStudent == NULL){
		free(s);
		return init();
	}
	nofStudents = i+1;

	newStudent[i].studentNum = studentNum;
	strcpy(newStudent[i].lastName, lastName);
	strcpy(newStudent[i].firstName, firstName);
	newStudent[i].sofp = 0;
	memset(newStudent[i].points, 0, sizeof(int)*6);

	return newStudent;
}


void updatePoints(Student *s, int studentNum, int round, int points){
	int i = 0; int sofp = 0; 
	while(i < nofStudents){
		if(s[i].studentNum == studentNum){
			// update point for student
			s[i].points[round] = points;
			for(int j = 0; j<6; j++){
				// update sum of points for student
				sofp = sofp + s[i].points[j];
			}
			s[i].sofp = sofp;
			return;
		}
		i++;
	}
	printf("Student not found\n");

}

// Compare funcions for qsort, sorts students by their points and if two or more students have the same sofp then sorts by their lastname.

int compareAlpha(const void* a, const void* b){
	const Student *student_a = a;
	const Student *student_b = b;

	int res = strcmp(student_a->lastName, student_b->lastName);
	return res;

}

int comparePoints(const void *a, const void *b){
	const Student *student_a = a;
	const Student *student_b = b;

	if(student_a->sofp > student_b->sofp){
		return -1;
	}else if(student_a->sofp < student_b->sofp){
		return 1;
	}else{
		return compareAlpha(a, b);
	}
}

void printResults(Student *s){
	if (s == NULL) {
		printf("No students\n");
		return;
	}
	if(nofStudents>1){	// Sort if number of students > 1
		qsort(s, nofStudents, sizeof(Student), comparePoints);
	}

	for(int i = 0; i < nofStudents;i++){
		printf("%06d %s %s %d ", s[i].studentNum, s[i].lastName, s[i].firstName, s[i].sofp);
		for(int j = 0; j<6; j++){
			printf("%d ", s[i].points[j]);
		}
		printf("\n");
	}
}

int writeFile(const char* filename, Student* s){
	FILE *f = fopen(filename,"w");
	if(f == NULL){
		return 1;
	}
	
	for(int i = 0; i < nofStudents; i++){
		
		fprintf(f, "%06d %s %s %d ", s[i].studentNum, s[i].lastName, s[i].firstName, s[i].sofp);
		for(int j = 0; j<6; j++){
			fprintf(f, "%d ", s[i].points[j]);
		}
		fprintf(f,"\n");

		
	}

	fclose(f);
	return 0;
}


Student *loadFile(const char *filename, Student *s, int extend){
	FILE *f = fopen(filename,"r");
	if(f==NULL){
		perror("Error opening file\n");
		return s;
	}
	// extend file to existing students or not
	int i = extend == 1 ? nofStudents : 0;
	char line[100] = "";
	while(fgets(line,sizeof(line),f)){
		s = realloc(s, sizeof(Student)*(i+1));
		if (s == NULL) {
			perror("Error reallocating memory\n");
			free(s);
			fclose(f);
			return init(); // Initialize a new student list
        }
		// Data not validated
		if(!sscanf(line,"%d %s %s %d %d %d %d %d %d %d", &s[i].studentNum, s[i].lastName, s[i].firstName, &s[i].sofp,
		&s[i].points[0], &s[i].points[1], &s[i].points[2], &s[i].points[3], &s[i].points[4], &s[i].points[5])) {
			fprintf(stderr, "Wrong data format in file\n");
			free(s);
			fclose(f);
			return init();
		}
		i++;																														  
	}
	nofStudents = i;

	fclose(f);
	if (extend == 1) {
		printf("File extended to current students. Validating data.\n");
	} else {
		printf("Validating data.\n");
	}
	
	return validateStudents(s);
}

Student *validateStudents(Student *students) {
    for (int i = 0; i < nofStudents; i++) {
        for (int j = i + 1; j < nofStudents; j++) {
            if (students[i].studentNum == students[j].studentNum) {
                // Found a duplicate - handle it
                int newID = students[j].studentNum;
                int duplicateFound;
                do {
                    duplicateFound = 0;
                    newID++; // Increment ID to find a unique one
                    // Check if the new ID is also a duplicate
                    for (int k = 0; k < nofStudents; k++) {
                        if (k != j && students[k].studentNum == newID) {
                            duplicateFound = 1;
                            break;
                        }
                    }
                } while (duplicateFound);
				printf("Student %s %s had duplicate student number: %d. Changed to new student number %d\n",  students[j].firstName, students[j].lastName, students[j].studentNum, newID);
                students[j].studentNum = newID; // Assign a unique ID
            }
        }
    }
	printf("Success\n");
	return students;
}


void freeStudent(Student *s){
	free(s);
}

int main(void){
	Student *s = init();
	int round; int points; int extend; char filename[20]; int studentNum; char lastName[30]; char firstName[20];
	int done = 1;
	while(done == 1){
		char buffer[80];
		fgets(buffer, 80, stdin);
	switch(buffer[0]){
		case 'A': 
			sscanf(buffer,"A %d %s %s", &studentNum, lastName, firstName);
			s = addStudent(s,studentNum, lastName, firstName);
			break;
		case 'U': 
			sscanf(buffer,"U %d %d %d", &studentNum, &round, &points);
			updatePoints(s, studentNum, round, points);
			break;
		case 'L':
			printResults(s);
			break;

		case 'W':
			sscanf(buffer, "W %s", filename);
			writeFile(filename, s);
			break;

		case 'O':
			sscanf(buffer, "O %s %d", filename, &extend);
			s = loadFile(filename, s, extend);
			break;

		case 'Q':
			freeStudent(s); 
			done = 0;
			break;

		default:
			printf("What??\n");
			break;
	}
}

	return 0;
}