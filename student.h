#ifndef STUDENT_H
#define STUDENT_H
#define MAXSTRING 50

#include "list.h"

struct student
{
  int id;
  char name[MAXSTRING];
};

// Prints the menu
void printMenu();

// Prints a student's details
void print(struct student student_to_print);

// Prints all the students in a list
void printStudents(list l);

// Reads students from a file and returns a list containing them
list load(char *filename);

// Writes each student in a list, in a file
void save(char *filename, list l);

// Adds a student to a list
int addStudent(struct student student_to_add, list l);

// Searches for a student by their id and returns it
student findStudent(int id, list l);

// Deletes a student from a list
int deleteStudent(struct student student_to_delete, list l);

// Updates the details of a student in a list and returns the new id
int updateStudent(struct student student_to_update, list l);

#endif
