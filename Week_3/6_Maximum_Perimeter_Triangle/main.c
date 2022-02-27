#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline();
char *ltrim(char *);
char *rtrim(char *);
char **split_string(char *);

int parse_int(char *);

void merge_sort_array(int *arr, int l, int r);
void merge_array(int *arr, int l, int m, int r);

/*
 * Complete the 'maximumPerimeterTriangle' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY sticks as parameter.
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */
int *maximumPerimeterTriangle(int sticks_count, int *sticks, int *result_count)
{
  merge_sort_array(sticks, 0, sticks_count - 1);

  int *triangle = (int *)malloc(sizeof(int) * 3);
  triangle[0] = 0;
  triangle[1] = 0;
  triangle[2] = 0;
  *result_count = 3;
  bool found = false;

  for (int i = 0; i < sticks_count - 2; i++)
  {
    int a = sticks[i];
    int b = sticks[i + 1];
    int c = sticks[i + 2];

    if (a + b > c)
    {
      if (triangle[0] + triangle[1] + triangle[2] == 0 || c > triangle[2] || a > triangle[0])
      {
        triangle[0] = a;
        triangle[1] = b;
        triangle[2] = c;
        found = true;
      }
    }
  }

  if (found)
    return triangle;

  triangle[0] = -1;
  *result_count = 1;
  return triangle;
}

// merge the array
void merge_array(int *arr, int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  i = 0;
  j = 0;
  k = l;
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }
  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }
}

// mergesort algorithm
void merge_sort_array(int *arr, int l, int r)
{
  if (l < r)
  {
    int m = l + (r - l) / 2;
    merge_sort_array(arr, l, m);     // divide
    merge_sort_array(arr, m + 1, r); // divide
    merge_array(arr, l, m, r);       // conquer
  }
}

int main()
{
  FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

  int n = parse_int(ltrim(rtrim(readline())));

  char **sticks_temp = split_string(rtrim(readline()));

  int *sticks = malloc(n * sizeof(int));

  for (int i = 0; i < n; i++)
  {
    int sticks_item = parse_int(*(sticks_temp + i));

    *(sticks + i) = sticks_item;
  }

  int result_count;
  int *result = maximumPerimeterTriangle(n, sticks, &result_count);

  for (int i = 0; i < result_count; i++)
  {
    fprintf(fptr, "%d", *(result + i));

    if (i != result_count - 1)
    {
      fprintf(fptr, " ");
    }
  }

  fprintf(fptr, "\n");

  fclose(fptr);

  return 0;
}

char *readline()
{
  size_t alloc_length = 1024;
  size_t data_length = 0;

  char *data = malloc(alloc_length);

  while (true)
  {
    char *cursor = data + data_length;
    char *line = fgets(cursor, alloc_length - data_length, stdin);

    if (!line)
    {
      break;
    }

    data_length += strlen(cursor);

    if (data_length < alloc_length - 1 || data[data_length - 1] == '\n')
    {
      break;
    }

    alloc_length <<= 1;

    data = realloc(data, alloc_length);

    if (!data)
    {
      data = '\0';

      break;
    }
  }

  if (data[data_length - 1] == '\n')
  {
    data[data_length - 1] = '\0';

    data = realloc(data, data_length);

    if (!data)
    {
      data = '\0';
    }
  }
  else
  {
    data = realloc(data, data_length + 1);

    if (!data)
    {
      data = '\0';
    }
    else
    {
      data[data_length] = '\0';
    }
  }

  return data;
}

char *ltrim(char *str)
{
  if (!str)
  {
    return '\0';
  }

  if (!*str)
  {
    return str;
  }

  while (*str != '\0' && isspace(*str))
  {
    str++;
  }

  return str;
}

char *rtrim(char *str)
{
  if (!str)
  {
    return '\0';
  }

  if (!*str)
  {
    return str;
  }

  char *end = str + strlen(str) - 1;

  while (end >= str && isspace(*end))
  {
    end--;
  }

  *(end + 1) = '\0';

  return str;
}

char **split_string(char *str)
{
  char **splits = NULL;
  char *token = strtok(str, " ");

  int spaces = 0;

  while (token)
  {
    splits = realloc(splits, sizeof(char *) * ++spaces);

    if (!splits)
    {
      return splits;
    }

    splits[spaces - 1] = token;

    token = strtok(NULL, " ");
  }

  return splits;
}

int parse_int(char *str)
{
  char *endptr;
  int value = strtol(str, &endptr, 10);

  if (endptr == str || *endptr != '\0')
  {
    exit(EXIT_FAILURE);
  }

  return value;
}
