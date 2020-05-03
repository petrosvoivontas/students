#include "student.h"
#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMenu()
{
  printf("1. Add a new student\n");
  printf("2. Delete a student\n");
  printf("3. Update a student's details\n");
  printf("4. Display a student's (or all students') details\n");
  printf("5. Exit\n\n");
  printf("(Enter a number from 1 to 5 to select an option)\n");
  printf("> ");
}

void print(struct student student_to_print)
{
  printf("%d\t%s\n", student_to_print.id, student_to_print.name);
}

void printStudents(list l)
{
  if (l->size > 0)
  {
    if (l->size == 1)
    {
      printf("ID\tName\n");
      print(*(l->head->s));
      putchar('\n');
    }
    else
    {
      printf("ID\tName\n");

      for (node n = l->head; n != NULL; n = n->next)
        print(*(n->s));

      putchar('\n');
    }
  }
  else
    printf("No students to show\n\n");
}

list load(char *filename)
{
  long size = file_size(filename);
  list l = list_create();

  FILE *file = fopen(filename, "r");
  if (file == NULL || size <= 0)
    return l;

  struct student s;
  while (ftell(file) < size)
  {
    fread(&s, sizeof(struct student), 1, file);
    addStudent(s, l);
  }

  fclose(file);

  return l;
}

void save(char *filename, list l)
{
  FILE *file = fopen(filename, "w");
  if (file == NULL)
    printf("An error occurred while attempting to save the list of students. Try again later\n");
  else if (l->size != 0)
  {
    for (node next_node = l->head; next_node != NULL; next_node = next_node->next)
      fwrite(next_node->s, sizeof(struct student), 1, file);

    fclose(file);
  }
}

int addStudent(struct student student_to_add, list l)
{
  if (l == NULL)
    return 0;

  node new_node = malloc(sizeof(struct _node));
  if (new_node == NULL)
    return 0;

  new_node->next = NULL;
  student s_ptr = malloc(sizeof(struct student));
  if (s_ptr == NULL)
    return 0;
  else
  {
    strcpy(s_ptr->name, student_to_add.name);
    s_ptr->id = student_to_add.id;

    new_node->s = s_ptr;
  }

  return push(l, new_node);
}

student findStudent(int id, list l)
{
  if (l == NULL)
    return NULL;

  for (node next_node = l->head; next_node != NULL; next_node = next_node->next)
  {
    if (next_node->s->id == id)
      return next_node->s;
  }

  return NULL;
}

int deleteStudent(struct student student_to_delete, list l)
{
  if (l == NULL)
    return 0;

  for (node n = l->head; n != NULL; n = n->next)
  {
    if (n->s->id == student_to_delete.id)
      return delete_entry(l, n);
  }

  return 0;
}

// returns the id of the updated student
int updateStudent(struct student student_to_update, list l)
{
  if (l == NULL)
  {
    printf("An error occurred while updating details for student with id %d\n\n", student_to_update.id);

    return 0;
  }

  student current_student = findStudent(student_to_update.id, l);
  char c;
  int new_id;

  handle_input(
          "Enter a new id for this student (-1 to keep the existing id)\n"
          "? ",
          "\nEnter a new id for this student (-1 to keep the existing id)\n"
          "? ",
          "%d",
          &new_id
          );

  putchar('\n');

  if (new_id != -1)
    // manually entering the same id should be equal to entering -1
    while(new_id != current_student->id && findStudent(new_id, l) != NULL)
    {
      if (new_id < 0)
        printf("The id must be a positive integer\n");
      else
        printf("A student with this id already exists\n\n");

      handle_input(
              "Enter a new id for this student (-1 to keep the existing id)\n"
              "? ",
              "\nEnter a new id for this student (-1 to keep the existing id)\n"
              "? ",
              "%d",
              &new_id
              );

      if (new_id == -1)
      {
        new_id = current_student->id;
        break;
      }
    }
  else
    new_id = current_student->id;

  char name[MAXSTRING], info_msg[100], error_msg[200], format[15], *final_name;

  sprintf(
          info_msg,
          "Enter the new name for this student (only the first %d characters will be saved)\n"
          "? ",
          MAXSTRING
          );

  sprintf(
          error_msg,
          "\n(Names must include at least one letter and cannot contain numbers or special characters)\n"
          "\nEnter the student's name (only the first %d characters will be saved)\n"
          "? ",
          MAXSTRING
          );

  sprintf(format, "%%%d[^\n]s", MAXSTRING);

  handle_input(info_msg, error_msg, format, name);

  putchar('\n');

  while((final_name = trim(name)) == NULL || !is_valid_name(final_name))
  {
    printf("(Names must include at least one letter and cannot contain numbers or special characters)\n");
    handle_input(info_msg, error_msg, format, name);
  }

  current_student->id = new_id;
  strcpy(current_student->name, final_name);

  return new_id;
}