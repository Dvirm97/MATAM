#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define THRESHOLD 10


typedef int (*cmp_t)(const void *, const void *);

#define LEN 6



//***********************my shit*****************
typedef void* Element;
typedef bool (*CmpFunction)(Element, Element);void merge_sort(Element*, size_t, CmpFunction, size_t);
void merge_sort_aux(char*, int, char*, CmpFunction, size_t);
//void merge(char*,int, char*, int, char*, CmpFunction, size_t);
bool intComp(Element, Element);
bool doubleComp(Element, Element);
bool charComp(Element, Element);
//********************************************

void mergeSort(void *, size_t, size_t, cmp_t);
void byteSwap(void *, void *, size_t);

static void mergeSort_recurse(void *, void *, int, int, size_t, cmp_t);
static void merge(void *, void *, int, int, int, size_t, cmp_t);
static void insertionSort(void *, size_t, size_t, cmp_t);
int cmp(const void *, const void *);



int main() {

    /*int a[LEN] = {3, 4, 1, 2, 5, 6};
    merge_sort((Element*)a, LEN, intComp, sizeof(int));
    for (int i = 0; i < LEN; i++)
        printf("%d ", a[i]);
    printf("\n");

    double b[LEN] = {3.2, 3.1, 1.0, 5.2, 5.0, 6.5};
    for (int i = 0; i < LEN; i++)
        printf("%lf ", b[i]);
    printf("\n");

    merge_sort((Element*) b, LEN, doubleComp, sizeof(double));
    for (int i = 0; i < LEN; i++)
        printf("%lf ", b[i]);
    printf("\n");

   char c[6] = {'a', 'd', 'c', 'z', 'c', 'g'};
    for (int i = 0; i < LEN; i++)
        printf("%c ", c[i]);
    printf("\n");
    merge_sort((Element*)c, LEN, charComp, sizeof(char));
    for (int i = 0; i < LEN; i++)
        printf("%c ", c[i]);
   */


    size_t i;
    int arr[] = {19, 56, 25, 17, 100, 58, 72, 1000, 98, 36, 14, 78, 125};
    double b[] = {19.2, 19.1, 0, -1.1, -2, 22000};

    size_t nitems = sizeof(arr) / sizeof(arr[0]);
    size_t bsize = sizeof(b) / sizeof(b[0]);

    mergeSort(arr, nitems, sizeof(int), cmp);
    mergeSort(b, bsize, sizeof(double), cmp);


    printf("Sorted int Array: ");

    for( i =0; i < nitems; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\nSorted double Array: ");

    for( i =0; i < bsize; i++)
    {
        printf("%.2lf ", b[i]);
    }


    printf("\n");


    return 0;
}

int cmp(const void *a, const void *b)
{
   const int *A = a;
   const int *B = b;
   return (*A > *B) - (*A < *B);
}

void mergeSort(void *base, size_t nitems, size_t memSize, cmp_t cmp)
{
    char *tempArr = (char *)malloc(sizeof(char) * memSize * nitems);


    if(tempArr != NULL)
    {
        mergeSort_recurse(base, tempArr, 0, (int)(nitems - 1), memSize, cmp);
        free(tempArr);
        insertionSort(base, nitems, memSize, cmp);
    }
}

static void mergeSort_recurse(void *base, void *tempArr, int start, int end, size_t memSize, cmp_t cmp)
{
    if(end - start < THRESHOLD) return;


    int splitIndex = start + ((end - start) / 2); /*Makes it less likely for an overflow to occur.*/

    mergeSort_recurse(base, tempArr, start, splitIndex, memSize, cmp);
    mergeSort_recurse(base, tempArr, splitIndex + 1, end, memSize, cmp);
    merge(base, tempArr, start, splitIndex, end, memSize, cmp);
}

static void merge(void *base, void *tempArr, int start, int splitIndex, int end, size_t memSize, cmp_t cmp)
{
    char *leftElement;
    char *rightElement;
    char *tempElement;


    int leftIndex = start; /*Starting index for the left sub array.*/
    int rightIndex = splitIndex + 1;/*Starting index for the right sub array. */
    int tempArrIndex = start; /*Starting index for the temp array. */

    while(leftIndex <= splitIndex && rightIndex <= end)
    {
        leftElement = ((char *)base + (leftIndex * memSize)); /*offsetting to the element at left and right Index.*/
        rightElement = ((char *)base + (rightIndex * memSize));


        if(cmp(leftElement, rightElement) < 0)
        {
            tempElement = ((char *)tempArr + (tempArrIndex * memSize));
            memcpy(tempElement, leftElement, memSize);
            leftIndex++;
            tempArrIndex++;
        }
        else
        {
            tempElement = ((char *)tempArr + (tempArrIndex * memSize));
            memcpy(tempElement, rightElement, memSize);
            rightIndex++;
            tempArrIndex++;
        }
    }

    while(leftIndex <= splitIndex)
    {
        leftElement = ((char *)base + (leftIndex * memSize));
        tempElement = ((char *)tempArr + (tempArrIndex * memSize));
        memcpy(tempElement, leftElement, memSize);
        leftIndex++;
        tempArrIndex++;
    }


    while(rightIndex <= end)
    {
        rightElement = ((char *)base + (rightIndex * memSize));
        tempElement = ((char *)tempArr + (tempArrIndex * memSize));
        memcpy(tempElement, rightElement, memSize);
        rightIndex++;
        tempArrIndex++;
    }

    for(leftIndex = start; leftIndex <= end; leftIndex++)
    {
        leftElement = ((char *)base + (leftIndex * memSize));
        tempElement = ((char *)tempArr + (leftIndex * memSize));
        memcpy(leftElement, tempElement, memSize);
    }
}

static void insertionSort(void *base, size_t nitems, size_t memSize, int (*cmp)(const void *, const void *))
{
    char *start = base;
    char *lastPtr = start + (nitems * memSize);
    char *top;


    for(top = start + memSize; top < lastPtr; top += memSize)
    {
        char *previous = top;
        char *current = previous - memSize;


        while(current >= start && cmp(previous, current) < 0)
        {
            byteSwap(previous, current, memSize);
            previous = current;
            current -= memSize;
        }
    }
}

void byteSwap(void *a, void *b, size_t memSize)
{
    char *aa = a;
    char *bb = b;


    do
    {
        char tmp = *aa;
        *aa++ = *bb;
        *bb++ = tmp;
    }
    while(--memSize > 0);
}

//************************************************************my shit*******************
/*void merge_sort(Element* a, int start, int end, size_t n, CmpFunction compare, size_t size) {
    char* a_aux = (char*)malloc(sizeof(char) * size * n);
    if(!a_aux) return;
    merge_sort_aux(a, n, a_aux, compare, size);
    free(a_aux);
}

void merge_sort_aux(char* a, int n, char* a_aux, CmpFunction compare, size_t size)
{
    if ( n < 2 )
        return;
    merge_sort_aux(a, n/2, a_aux, compare, size);
    merge_sort_aux(a + size*(n/2), n-n/2, a_aux, compare, size);
    merge(a, n/2, a + size*(n/2), n-n/2, a_aux, compare, size);
    memcpy(a, a_aux, n*size);
}

void merge(char * a, int na, char* b, int nb, char* c, CmpFunction compare,size_t size)
{
    int ia, ib, ic;
    for ( ia = ib = ic = 0; ia < na && ib < nb; ){
        Element* a_value = malloc(sizeof(char)*size);
        Element* b_value = malloc(sizeof(char)*size);;
        for(int i=0;i<size;i++){
            *(a_value+i)=*(a+ia+i);
        }
        *(c+(ic*size)) = compare((Element)(*(a+(ia*size))),
              (Element )(*(b+(ib*size)))) ? *(a+(ia*size)) : *(b+(ib*size));
        ic++; ia++; ib++;
    }
    for ( ; ia < na; ){
        *(c+(ic*size))= *(a+(ia*size));
        ic++; ia++;
    }

    for ( ; ib < nb; ){
        *(c+(ic*size))= *(b+(ib*size));
        ic++; ib++;
    }
}

 bool intComp(Element a, Element b){
     return ((int)a < (int)b);
 }

bool doubleComp(Element a, Element b){
    return ((double*)a < (double*)b);
}

bool charComp(Element a, Element b){
    return ((char)a < (char)b);
}*/