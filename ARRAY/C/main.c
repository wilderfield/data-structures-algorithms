#include <stdio.h>
#include <stdlib.h>

#define SIZE 8 // preprocessor string substitution // Should not use in CPP

int main ()
{

  int i;    // Iterator
  int val;  // Variable to hold data

  // Static Array
  int sarray[SIZE];
  
  for(i=0;i<SIZE;i++)
  {
    val = i*i; 
    printf("Setting static array element %i to %i\n",i,val);
    sarray[i] = val;
  }
  
  for(i=0;i<SIZE;i++)
  {
    val = sarray[i];
    printf("Getting static array element %i as %i\n",i,val);
  }
 
  // Dynamic Array
  int* darray;

  printf("Allocate dynamic array\n");
  darray = (int*) malloc(SIZE*sizeof(int));

  for(i=0;i<SIZE;i++)
  {
    val = i+i; 
    printf("Setting dynamic array element %i to %i\n",i,val);
    darray[i] = val;
  }

  for(i=0;i<SIZE;i++)
  {
    val = darray[i];
    printf("Getting dynamic array element %i as %i\n",i,val);
  }
 
  printf("Free dynamic array\n");
  free(darray);

  return 0;

}
