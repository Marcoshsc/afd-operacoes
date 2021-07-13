#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./cli.h"

CLI_Item *getItem(char *name, int position, int number_values)
{
  CLI_Item *item = malloc(sizeof(CLI_Item));
  item->name = name;
  item->position = position;
  item->number_values = number_values;
  return item;
}

CLI_Value *createCLIValue(char *value)
{
  CLI_Value *cli_value = malloc(sizeof(CLI_Value));
  cli_value->value = value;
  cli_value->next = NULL;
}

CLI_Item *searchItem(CLI_Params params, char *value)
{
  for (int i = 0; i < params.items_size; i++)
  {
    if (!strcmp(params.items[i]->name, value))
    {
      return params.items[i];
    }
  }
  return NULL;
}

void registerParam(CLI_Params *params, char *name, int number_values)
{
  if (params->items_size == params->size)
  {
    params->size += 1;
    params->items = realloc(params->items, sizeof(CLI_Item *) * params->size);
  }
  params->items[params->items_size] = getItem(name, params->items_size, number_values);
  params->items_size++;
}

CLI_Params *getParams(int initial_size)
{
  CLI_Params *params = malloc(sizeof(CLI_Params));
  params->size = initial_size;
  params->items_size = 0;
  params->items = malloc(sizeof(CLI_Item *) * initial_size);
}

CLI_Value *getValuesLinkedList(CLI_Item *item, char *argv[], int *current_index)
{

  CLI_Value *head = NULL;
  CLI_Value *prev = NULL;
  for (int j = 0; j < item->number_values; j++)
  {
    (*current_index)++;
    CLI_Value *value = createCLIValue(argv[*current_index]);
    if (prev)
    {
      prev->next = value;
    }
    else
    {
      head = value;
    }
    prev = value;
  }
  return head;
}

void populateValuesArray(CLI_Params *cli_params, CLI_Value **values, int size, int argc, char *argv[])
{
  int i = 0;
  while (i < argc - 1)
  {
    CLI_Item *item = searchItem(*cli_params, argv[i]);
    // If parameter is registered, store it on the array.
    if (item)
    {
      CLI_Value *head = getValuesLinkedList(item, argv, &i);
      values[item->position] = head;
    }
    i++;
  }
}

CLI_Result *readCLI(CLI_Params *cli_params, int argc, char *argv[])
{
  CLI_Result *result = malloc(sizeof(CLI_Result));

  result->params = cli_params;
  result->size = cli_params->items_size;

  CLI_Value **values = malloc(sizeof(CLI_Value *) * result->size);
  for (int i = 0; i < result->size; i++)
  {
    values[i] = NULL;
  }

  populateValuesArray(cli_params, values, result->size, argc, argv);
  result->values = values;
  return result;
}

CLI_Value *getCLIValue(CLI_Result result, char *param)
{
  CLI_Item *item = searchItem(*result.params, param);
  return result.values[item->position];
}

void freeCLI(CLI_Result *result)
{
  for (int i = 0; i < result->size; i++)
  {
    freeLinkedList(result->values[i]);
  }
  freeCLIParams(result->params);
  free(result->values);
  free(result);
}

void freeLinkedList(CLI_Value *head)
{
  if (head == NULL || head->next == NULL)
  {
    free(head);
  }
  else
  {
    freeLinkedList(head->next);
    free(head);
  }
}

void freeCLIParams(CLI_Params *params)
{
  for (int i = 0; i < params->items_size; i++)
  {
    free(params->items[i]);
  }
  free(params->items);
  free(params);
}
