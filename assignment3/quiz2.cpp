#include <stdio.h>
#include <stdlib.h>

int main()
{
    cout << select
}

// A and B are each sorted into ascending order, and 0 <= k < |A|+|B| 
// Returns the element that would be stored at index k if A and B were
// combined into a single array that was sorted into ascending order.
int select (int* A, int* B, k)
{
    return selectRecursive(A, 0, |A|-1, B, 0, |B|-1, k)
}

int selectRecursive(int* A, int loA, int hiA, int* B, int loB, int hiB, int k)
{
    // A[loA..hiA] is empty
    if (hiA < loA)
        return B[k-loA]
    // B[loB..hiB] is empty
    if (hiB < loB)
        return A[k-loB]
    // Get the midpoints of A[loA..hiA] and B[loB..hiB]
    i = (loA+hiA)/2
    j = (loB+hiB)/2
    // Figure out which one of four cases apply
    if (A[i] > B[j])
        if (k <= i+j)
            return selectRecursive(A, $1, $2, B, $3, $4, k);
        else
            return selectRecursive(A, $5, $6, B, $7, $8, k);            
    else
        if (k <= i+j)
            return selectRecursive(A, $9, $10, B, $11, $12, k);
        else
            return selectRecursive(A, $13, $14, B, $15, $16, k);
}