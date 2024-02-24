
# Student Management System - C-course exercise

## Description
A simple C program to manage student records. This project allows for adding student records, updating points, validating for duplicates, and saving/loading data from files.

## Installation and Compilation
To compile this program, ensure you have GCC (GNU Compiler Collection) installed. Navigate to the directory containing the source code and run the following command:

```bash
gcc -o student_management main.c
```

## Usage
Run the compiled program from the command line:

```bash
./student_management
```

Follow the on-screen prompts to interact with the system. The program supports the following commands:

- `A <studentNum> <lastName> <firstName>`: Add a new student.
- `U <studentNum> <round> <points>`: Update points for a student.
- `L`: List all students.
- `W <filename>`: Write student data to a file.
- `O <filename> <extend>`: Load student data from a file. Set `extend` to 1 to append to current data, 0 to replace.
- `Q`: Quit the program.

## Functionality
- **Add Student**: Add a new student with a unique ID, name, and initial points.
- **Update Points**: Update the points for a specific student.
- **Print Results**: Display the list of students sorted by points.
- **Write/Read to/from File**: Save and load student data to and from a file.
- **Duplicate Validation**: Automatically checks and corrects duplicate student IDs when loading from a file.

## Author
Sami Härkönen

## License
This project is licensed under the No License.
