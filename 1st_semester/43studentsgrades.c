/*
*	43 - Students Grades
* This program calculates the students grades.
*/
#include <stdlib.h>
#include <stdio.h>

void freematrix(void **matrix, int nrow){
	int i;
	for(i = 0 ; i < nrow ; i++)
		free(matrix[i]);
	free(matrix);
	return;
}

void calculategrades(char *answers,char **studentanswer, int nquestions, int nstudents){
    int i,j;
    double *grade = (double *)calloc(nstudents,sizeof(double));

    for(i = 0; i < nstudents ; i++){
        for(j = 0; j < nquestions ; j++)
            if(studentanswer[i][j] == answers[j])
				(grade[i]) += 10;
        
        grade[i] /= nquestions;
    }

    for(i = 0; i < nstudents ; i++)
		printf("%.2lf\n",grade[i]);
    
    free(grade);

    return;
}

char *readline(FILE *inputfile, char delim){
	char c, *string = NULL;
	int counter = 0;

	do{
		c = fgetc(inputfile);
		string = (char *)realloc(string, sizeof(char)*(counter+1));
		string[counter++] = c;
	}while (c != 10 && c != 11 && c != 12 && c != 13 && c != EOF && c != delim);
	string[counter-1] = '\0';

	return string;
}

int main (int argc, char **argv){
	//0. Variables
	int i = 0, nquestions = 0, nstudents = 0;
	char *answers = NULL, **studentanswer = NULL;

	//1. Reading the number of questions and students
    scanf("%d%*c%d%*c",&nquestions,&nstudents);

	//2. Reading the correct answers
    answers = readline(stdin,'\n');

	//3. Reading the students answers
    studentanswer = (char **)malloc(sizeof(char *)*nstudents);
    for( i = 0; i < nstudents ; i++)
		*(studentanswer + i) = readline(stdin,'\n');

	//4. Calculating and printing the students grades
    calculategrades(answers,studentanswer,nquestions,nstudents);
    
	//5. Freeing the used memory
	free(answers);
	freematrix((void **)studentanswer,nstudents);

	//6. That's all folks... :)
    return 0;
}
