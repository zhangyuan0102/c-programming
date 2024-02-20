#include<stdio.h>
#include<stdlib.h>

size_t maxSeq(int * array, size_t n);

int main()    {
  size_t ans;
  int array1[5] = {-5,-3,1,0,2};
  int array2[]  = {-999,-2,0,1,100,101};
  int array3[]  = {111,99,86,72,0,-1,-100};
  int array4[]  = {0};
  int array5[]  = {};
  int array6[100]={1,2,3,4,5,9,10,11,12,1,2,3,4,5,-2,-1,0};
  int array7[] ={-1,0,1,-5,2,3};
  int array8[] ={-3,-4,-5,0,1,2};
         ans = maxSeq(array1,5);
  if(ans !=3){return EXIT_FAILURE;}
         ans = maxSeq(array2,6);
  if(ans !=6){return EXIT_FAILURE;}
         ans = maxSeq(array3,7);
  if(ans !=1){return EXIT_FAILURE;}
         ans = maxSeq(array4,1);
  if(ans !=1){return EXIT_FAILURE;}
         ans = maxSeq(array5,0);
  if(ans !=0){return EXIT_FAILURE;}
         ans = maxSeq(array6,100);
  if(ans !=9){return EXIT_FAILURE;}
  ans =maxSeq(array7,6);
  if(ans !=3){return EXIT_FAILURE;}
  ans =maxSeq(array8,6);
  if(ans !=4){return EXIT_FAILURE;}
       return EXIT_SUCCESS;
}
