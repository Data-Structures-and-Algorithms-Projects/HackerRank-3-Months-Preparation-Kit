
int *bubble_sort_array(int n, int *arr);
void swap(int *x, int *y);

/*
 * Complete the 'findMedian' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

int findMedian(int arr_count, int *arr)
{
  int *sorted_arr = bubble_sort_array(arr_count, arr);
  int median = 0;

  for (int i = 0; i < arr_count; i++)
  {
    printf("%d\n", sorted_arr[i]);
  }

  int n = arr_count / 2;
  median = sorted_arr[n];

  return median;
}

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

int *bubble_sort_array(int n, int *arr)
{
  int *arr_final = (int *)malloc(sizeof(int) * n);

  for (int i = 0; i < n - 1; i++)
  {
    arr_final[i] = arr[i];
    for (int j = 0; j < n - 1 - i; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        swap(&arr_final[j], &arr_final[j + 1]);
      }
    }
  }
  return arr_final;
}

int main()
{
  int arr_count = 7;
  int arr[] = {1, 3, 2, 6, 1, 2, 1};

  int median = findMedian(arr_count, arr);
  printf("%d\n", median);

  return 0;
}