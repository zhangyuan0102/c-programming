#include <stdio.h>
#include <stdlib.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;
void retirement(int startAge,
		double initial,
		retire_info working,
		retire_info retired){
  int i,j;
double balance =initial;
for(i = startAge;i < startAge+working.months; i=i+1){
  printf("Age %3d month %2d you have $%.2lf\n",(i/12),(i%12), balance);
  balance = balance + working.contribution +working.rate_of_return/12*balance;
 }
for(j = startAge+working.months;j < startAge+working.months+retired.months; j =j+1){
  printf("Age %3d month %2d you have $%.2lf\n",(j/12),(j%12), balance);
  balance =balance +retired.contribution + retired.rate_of_return/12*balance;
 }
}
int main(void){
  retire_info working;
  working.months=489;
  working.contribution= 1000;
  working.rate_of_return =0.045;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;
  int startAge= 327;
  double initial =21345;
  
  retirement(startAge, initial, working, retired);
	     return 0;
}
	     
