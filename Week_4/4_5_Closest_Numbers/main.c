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

/*
 * Complete the 'closestNumbers' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

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

// BUT THIS CODE DOES NOT RUN IN HACKERRANK'S COMPILER
// FOR ANY ARRAY OVER 10,000
// IT SHOWS COMPILER ERROR
int *closestNumbers(int arr_count, int *arr, int *result_count)
{

  int *final_arr = NULL;
  int count = 0;
  int min_diff = abs(arr[1] - arr[0]);

  // sorting the array first
  // using merge sort
  merge_sort_array(arr, 0, arr_count - 1);

  for (int i = 2; i < arr_count; i++)
    if (arr[i] - arr[i - 1] < min_diff)
      min_diff = arr[i] - arr[i - 1];

  for (int i = 1; i < arr_count; i++)
    if (arr[i] - arr[i - 1] == min_diff)
    {
      // printf("%d %d ",arr[i-1],arr[i]);
      if (count == 0)
      {
        final_arr = (int *)malloc(sizeof(int) * 2);
        final_arr[0] = arr[i - 1];
        final_arr[1] = arr[i];
        count = 2;
      }
      else
      {
        final_arr = (int *)realloc(final_arr, count + 2);
        final_arr[count] = arr[i - 1];
        final_arr[count + 1] = arr[i];
        count += 2;
      }
    }

  // for(int i = 2; i < arr_count; i++){
  //     int diff = abs(arr[i] - arr[i - 1]);
  //     if( diff < min_diff){
  //         if(count!=2){
  //             free(final_arr);
  //             count = 2;
  //             final_arr = (int*)malloc(sizeof(int)*count);
  //         }
  //         min_diff = diff;
  //         final_arr[0] = arr[i-1];
  //         final_arr[1] = arr[i];
  //     }else if(diff == min_diff){
  //         final_arr = (int*)realloc((void*)final_arr, count+2);
  //         final_arr[count] = arr[i-1];
  //         final_arr[count+1] = arr[i];
  //         count += 2;
  //     }
  // }

  // printf("here\n");

  *result_count = count;
  // for(int i =0; i< *result_count; i++){
  //     printf("%d ", final_arr[i]);
  // }
  //     printf("\n");

  return final_arr;
}

int main()
{
  FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

  int n = parse_int(ltrim(rtrim(readline())));

  char **arr_temp = split_string(rtrim(readline()));

  int *arr = malloc(n * sizeof(int));

  for (int i = 0; i < n; i++)
  {
    int arr_item = parse_int(*(arr_temp + i));

    *(arr + i) = arr_item;
  }

  int result_count;
  int *result = closestNumbers(n, arr, &result_count);

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

  free(result);

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
