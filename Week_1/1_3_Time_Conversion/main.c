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

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
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
char *timeConversion(char *s)
{
  char *time = (char *)malloc(sizeof(char) * 8);

  char str_hr[2], new_str_hr[2];
  int hr = 0;
  str_hr[0] = s[0];
  str_hr[1] = s[1];
  hr = atoi(str_hr);

  if (s[8] == 'P')
  {
    hr += 12;
    if (hr >= 24)
      hr = 12; // just so 12 pm does not reach 24 & should be 0
  }
  else if (hr == 12)
    hr = 0;

  // a 2 digit number xy is based on 10x + y format
  int x = hr / 10; // x is quotient
  int y = hr % 10; // y is remainder

  if (x < 1)
  {
    // for first digit of hour
    new_str_hr[0] = '0';
  }
  else
  {
    new_str_hr[0] = x + '0';
  }
  // for second digit of hour
  new_str_hr[1] = y + '0'; // adding '0' to any number between 0-9 will convert it into a char

  // copying hour values
  for (int i = 0; i < 3; i++)
  {
    time[i] = new_str_hr[i];
  }

  // copying the same minutes and seconds
  for (int i = 2; i < 8; i++)
  {
    time[i] = s[i];
  }

  return time;
}

int main()
{
  FILE *fptr = fopen(getenv("OUTPUT_PATH"), "w");

  char *s = readline();

  char *result = timeConversion(s);

  fprintf(fptr, "%s\n", result);

  fclose(fptr);

  // freeing the allocated memory
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
