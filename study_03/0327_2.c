#include <stdio.h>
#include <stdlib.h>

// /*
int main()
{


    int size =100;
    int** ptr_1 = NULL;
    ptr_1 = malloc(size* sizeof(int*));



    // Dynamic memory allocation!
    for (int i=0; i<size; i++)
    {
        ptr_1[i] = malloc(size *sizeof(int));
    }



    printf("%d\n", ptr_1[119]);
    // free(ptr_1);


    // cleanup resources
    for (int i=0; i<size; i++)
    {
        free(ptr_1[i]);
    }
}
    // */