#include<stdio.h>
#include<stdlib.h>
void rotate(char matrix[10][10]){
  int i,j;
  char temp[10][10];
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      temp[i][j] = matrix [i][j];
    }
  }
  for(i=0;i<10;i++){
    for(j=0;j<10;j++){
      matrix[i][j]= temp [9-j][i];
    }
  }
}
