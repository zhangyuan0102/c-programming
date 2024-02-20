#include<stddef.h>

size_t maxSeq(int * array,size_t n){
int pointer,ans,i;
 pointer =1;
 ans =1;
if(n ==0){
  ans = 0;
 }
 else if(n==1){
   ans = 1;
 }
 else   {
   for(i=0;i<n-1;i++){
     if( array[i]< array[i+1]){
       pointer++;
     }
     else{
       if(pointer>ans){
	 ans =pointer;
       }
       pointer =1;
     }
   }
   if(ans ==1||pointer > ans){
     ans =pointer;
   }
 }
 return ans;
}

