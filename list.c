#include <stdio.h>
#include <stdlib.h>

#include "list.h"

list list_create()
{
  list l = malloc(sizeof(struct _list));
  if (l == NULL)
  {
    printf("An error occurred while loading students' list\n");
    abort();
  }

  l->head = NULL;
  l->tail = NULL;
  l->size = 0;

  return l;
}

void list_destroy(list l)
{
  if (l != NULL)
  {
    node next_for_deletion = l->head;
    for (int i = 0; i < l->size; ++i)
    {
      node tmp_next = next_for_deletion->next;
      free(next_for_deletion->s);
      free(next_for_deletion);


      next_for_deletion = tmp_next;
    }

    free(l);
  }
}

int push(list l, node node_to_push)
{
  if (l == NULL || node_to_push == NULL)
    return 0;

  if (l->size == 0)
  {
    l->head = node_to_push;
    l->tail = node_to_push;
    ++l->size;

    return 1;
  }
  else
  {
    l->tail->next = node_to_push;
    l->tail = node_to_push;
    ++l->size;

    return 1;
  }
}

int delete_entry(list l, node node_to_delete)
{
  if (l->size == 1)
  {
    l->head = NULL;
    l->tail = NULL;
    --l->size;

    free(node_to_delete->s);
    free(node_to_delete);

    return 1;
  }
  else if (l->head == node_to_delete)
  {
    l->head = node_to_delete->next;
    --l->size;

    free(node_to_delete->s);
    free(node_to_delete);

    return 1;
  }
  else
  {
    node prev_node = l->head;
    for (int i = 0; i < l->size; ++i)
    {
      if (prev_node->next == node_to_delete)
      {
        prev_node->next = node_to_delete->next;

        if (l->tail == node_to_delete)
          l->tail = prev_node;

        --l->size;

        free(node_to_delete->s);
        free(node_to_delete);

        return 1;
      }

      prev_node = prev_node->next;
    }
  }

  return 0;
}