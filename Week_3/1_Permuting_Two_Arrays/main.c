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

void merge_array(int *arr, int l, int m, int r, bool asc);
void merge_sort_array(int *arr, int l, int r, bool asc);

/*
 * Complete the 'twoArrays' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY A
 *  3. INTEGER_ARRAY B
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */
char *twoArrays(int k, int A_count, int *A, int B_count, int *B)
{
  char *ret_val = (char *)malloc(sizeof(char) * 3);

  merge_sort_array(A, 0, A_count - 1, true);
  merge_sort_array(B, 0, B_count - 1, false);

  for (int i = 0; i < A_count; i++)
  {
    printf("%d %d\n", A[i], B[i]);
    if (A[i] + B[i] < k)
    {
      ret_val = "NO";
      return ret_val;
    }
  }

  ret_val = "YES";
  return ret_val;
}

// merge the array
void merge_array(int *arr, int l, int m, int r, bool asc)
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
    if (asc)
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
    }
    else
    {
      if (L[i] >= R[j])
      {
        arr[k] = L[i];
        i++;
      }
      else
      {
        arr[k] = R[j];
        j++;
      }
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
void merge_sort_array(int *arr, int l, int r, bool asc)
{
  if (l < r)
  {
    int m = l + (r - l) / 2;
    merge_sort_array(arr, l, m, asc);     // divide
    merge_sort_array(arr, m + 1, r, asc); // divide
    merge_array(arr, l, m, r, asc);       // conquer
  }
}

int main()
{
  FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

  int q = parse_int(ltrim(rtrim(readline())));

  for (int q_itr = 0; q_itr < q; q_itr++)
  {
    char **first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    char **A_temp = split_string(rtrim(readline()));

    int *A = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
      int A_item = parse_int(*(A_temp + i));

      *(A + i) = A_item;
    }

    char **B_temp = split_string(rtrim(readline()));

    int *B = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
      int B_item = parse_int(*(B_temp + i));

      *(B + i) = B_item;
    }

    char *result = twoArrays(k, n, A, n, B);

    fprintf(fptr, "%s\n", result);
  }

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
