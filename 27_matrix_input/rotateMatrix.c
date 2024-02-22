#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void rotate(char matrix[10][10])
{
    char temp[100];
    int count =0;
    for (int i =0; i<10;i++)
    {
        for (int j =0;j<10;j++)
        {
            temp[count] = matrix[i][j];
            count++;
        }
    }
    count =0;
    for (int k =0;k<10;k++)
    {
        for (int l =0; l<10;l++)
        {
            matrix[l][9-k] = temp[count];
            count++;
        }
    }
}

int check_matrix(FILE *f)
{
    int row_num = 0;
    char c;
    while ((c=fgetc(f)) != EOF)
    {
        for (int i =0;i<10;i++)
        {
            if (c == '\n') {
                fprintf(stderr,"char error");
                return 0;
            }
            c = fgetc(f);
        }
        if (c != '\n')
        {
            fprintf(stderr,"more than 10 char in a line");
            return 0;
        }
        row_num++;
    }
    if (row_num == 10)
    {
        return 1;
    }
    else
    {
        fprintf(stderr,"do not have 10 row");
        return 0;
    }
    
}

int main(int argc, char ** argv)
{
    if (argc !=2)
    {
        fprintf(stderr,"not enough arguments\n");
        return EXIT_FAILURE;
    }

    FILE *f = fopen(argv[1],"r");
    if (f==NULL){
        perror("Could not open file");
        return EXIT_FAILURE;
    }

    if (check_matrix(f)==0)
    {
        printf("the matrix is not 10*10");
        return EXIT_FAILURE;
    }
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE; }

    f = fopen(argv[1],"r");

    if (f==NULL){
        perror("Could not open file");
        return EXIT_FAILURE;}   



    char matrix[10][10];
    char c;
    for (int i =0;i<10;i++)
    {
        for (int j=0;j<11;j++)
        {
            if ((c=fgetc(f)) != '\n'){
                matrix[i][j] =c;
                
            }
        }
    }
    rotate(matrix);
    for (int x=0;x<10;x++){
        for (int y=0;y<10;y++){
	        printf("%c",matrix[x][y]);
      }
        printf("\n");	
	}
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE; }


    return EXIT_SUCCESS;          
}
