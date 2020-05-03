#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "student.h"
#include "helpers.h"

// Maps the user's input to the corresponding module and returns that input
int handle_options(char *filename, list l)
{
  char c;
  int option;
  printMenu();

  handle_input(
          NULL,
          "\n(Enter a number from 1 to 5 to select an option)\n"
          "> ",
          "%d",
          &option
          );

  putchar('\n');

  struct student s;
  student s_ptr;
  int id, old_id, new_id;
  char name[MAXSTRING], format[15];

  switch (option) {
    case 1:
      handle_input(
              "Enter the student's id (-1 to go back)\n"
              "? ",
              "\nEnter the student's id (-1 to go back)\n"
              "> ",
              "%d",
              &id
              );

      while (id < 0 || findStudent(id, l) != NULL)
      {
        if (id == -1)
        {
          putchar('\n');

          return option;
        }
        else if (id < 0)
          printf("\nThe id must be a positive integer\n\n");
        else
          printf("\nA student with this id already exists\n\n");

        handle_input(
                "Enter the student's id (-1 to go back)\n"
                "? ",
                "\nEnter the student's id (-1 to go back)\n"
                "? ",
                "%d",
                &id
                );
      }

      s.id = id;

      printf("\nEnter the student's name (only the first %d characters will be saved)\n", MAXSTRING);
      printf("? ");

      sprintf(format, "%%%d[^\n]s", MAXSTRING);
      while (!scanf(format, name))
      {
        while((c = (char) getchar()) != '\n' && c != EOF);

        printf("\nEnter the student's name (only the first %d characters will be saved)\n", MAXSTRING);
        printf("? ");
      }

      // clean up any unread characters
      while((c = (char) getchar()) != '\n' && c != EOF);

      strcpy(s.name, name);

      if (addStudent(s, l))
      {
        printf("\nID\tName\n");
        print(s);
        printf("\nStudent successfully added\n\n");
        save(filename, l);
      }
      else
        printf("\nAn error occurred while adding a student\n\n");

      break;
    case 2:
      handle_input(
              "Enter the student's id (-1 to go back)\n"
              "? ",
              "\nEnter the student's id (-1 to go back)\n"
              "? ",
              "%d",
              &id
              );

      putchar('\n');

      while(id < 0 || (s_ptr = findStudent(id, l)) == NULL)
      {
        if (id == -1)
          return option;
        else if (id < 0)
          printf("The id must be a positive integer\n\n");
        else
          printf("No student with id %d found\n\n", id);

        handle_input(
                "Enter the student's id (-1 to go back)\n"
                "? ",
                "\nEnter the student's id (-1 to go back)\n"
                "? ",
                "%d",
                &id
                );

        putchar('\n');
      }

      if (deleteStudent(*s_ptr, l))
      {
        printf("The student with id %d has been deleted\n\n", id);
        save(filename, l);
      }
      else
        printf("An error occurred while deleting the student with id %d\n\n", id);

      break;
    case 3:
      handle_input(
              "Enter the student's id (-1 to go back)\n"
              "? ",
              "\nEnter the student's id (-1 to go back)\n"
              "? ",
              "%d",
              &old_id
              );

      putchar('\n');

      if (old_id == -1)
        return option;

      while((s_ptr = findStudent(old_id, l)) == NULL)
      {
        if (old_id < 0)
          printf("The id must be a positive integer\n\n");
        else
          printf("No student with id %d found\n\n", old_id);

        handle_input(
                "Enter the student's id (-1 to go back)\n"
                "? ",
                "\nEnter the student's id (-1 to go back)\n"
                "? ",
                "%d",
                &old_id
                );

        if (old_id == -1)
          return option;
      }

      if ((new_id = updateStudent(*s_ptr, l)))
      {
        printf("Details updated successfully\n");
        printf("\nID\tName\n");
        print(*findStudent(new_id, l));
        putchar('\n');

        save(filename, l);
      }

      break;
    case 4:
      handle_input(
              "Enter a student's id (-2 to view all students | -1 to go back)\n"
              "? ",
              "\nEnter a student's id (-2 to view all students | -1 to go back)\n"
              "? ",
              "%d",
              &id
              );

      putchar('\n');

      while(id < 0 || (s_ptr = findStudent(id, l)) == NULL)
      {
        if (id == -2)
        {
          printStudents(l);
          return option;
        }
        else if (id == -1)
          return option;
        else if (id < 0)
          printf("The id should be a positive integer\n\n");
        else
          printf("No student with id %d found\n\n", id);

        handle_input(
                "Enter a student's id (-2 to view all students | -1 to go back)\n"
                "? ",
                "\nEnter a student's id (-2 to view all students | -1 to go back)\n"
                "? ",
                "%d",
                &id
                );

        putchar('\n');
      }

      printf("ID\tName\n");
      print(*s_ptr);
      putchar('\n');

      break;
    case 5:
      return 5;
    default:
      break;
  }

  return option;
}

int main(int argc, char **argv)
{
  char *filename;
  if (argc == 1)
  {
    printf("You must enter a filename\n");

    return 0;
  }
  else if (argc > 2)
  {
    printf("Enter no more than one filename\n");

    return 0;
  }

  // account for the extra `\0`
  filename = malloc(strlen(argv[1]) + 1);
  if (filename == NULL)
  {
    printf("Try again later\n");
    abort();
  }

  strcpy(filename, argv[1]);

  list l = load(filename);

  int last_option;
  do
  {
    last_option = handle_options(filename, l);
  } while (last_option != 5);

  free(filename);
  list_destroy(l);

  return 0;
}