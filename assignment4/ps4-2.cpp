#include <stdio.h>

int f (int[] A, int k) ;

int main()
{
	int arr[8] = {0,1,2,3,4,5,6,7};
	int sum;

	sum = f(arr, 5);
}

int f (int[] A, int k) 
{
    int sum = 0;
    int stop = partition(A, select(A, k));
    for (int i = 0; i < stop; i++) {
        sum += A[i];
    }	
	return sum;
}

int partition(int[] A, int k)
{

}

int select(int A[], int k)
{
	
}