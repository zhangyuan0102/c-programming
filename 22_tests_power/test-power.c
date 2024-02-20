#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
unsigned power (unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans){
   if(power(x,y) != expected_ans){
     printf("error");
     exit(EXIT_FAILURE);
   }
}

int main(){
  run_check(0,0,1);
  run_check(0,1,0);
  run_check(1,0,1);
  run_check(1,1,1);
  run_check(10,.5,1);
  run_check(2,31,2147483648);
  run_check(2,32,0);
  run_check(1,-1,1);
  run_check(-1,2,1);
      printf("All test cases passed\n");
    return EXIT_SUCCESS;
}
  
  
