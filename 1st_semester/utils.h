#ifndef _UTILS_H_
#define _UTILS_H_

//------ Defines and Structures ------
typedef enum{
	INVALID = -1,
	FALSE = 0,
	TRUE = 1
}boolean;





//------ Memory functions ------
/*		void freematrix(void **matrix, int nrow)
* This function frees a general matrix from HEAP memory.
* The matrix needs to be correctly allocated in the memory.
* Otherwise, the function will generate a SEGFAULT ERROR.
*/
void freematrix(void **, int );





//------ General functions
/*		void swap(void *a, void *b)
* This function swaps the content of a pointer A with the
* content of a pointer B.
*/
void swap(void *, void *);





//------ Math functions 
/*		double stddeviation(double *vec, int n, double m)
* This function calculates the standard deviation in a double
* vector with the size n and the mean m.
*/
double stddeviation(double *, int , double );

/*		double mean(double *vec, int n)
* This function calculates the mean in a double vector with
* the size n.
*/
double mean(double *, int );

/*
*	boolean inrange(int a, int low, int hi)
* This function tests a parameter 'a' between a lower and 
* upper bound. If is in range, returns TRUE. Else, FALSE.
*/
boolean inrange(int , int , int );

/*		double harmonicmean(double *vector, int n, boolean aflag)
* This function calculates the harmonic mean of a number vector.
* The parameter "aflag" indicates the amortized propriety that can
* be TRUE or FALSE.
*/
double harmonicmean(double *, int , boolean );

/*		int newtonbinomial(int i, int j)
* This function calculates the binomial of a numeric pair
*/
int newtonbinomial(int , int );

/*		int *eratosthenes(int threshold, int *nprimes)
* This function finds all prime numbers up to any given limit.
*/
int *eratosthenes(int , int *);




//------ Matrix manipulation ------
/*		void printintmatrix(int **matrix, int nrow, int ncol)
* This function prints an int matrix (stdout). 
*/
void printintmatrix(int **matrix, int nrow, int ncol);

/*		void initializeintmatrix(int **matrix, int nrow, int ncol, int init)
* This function sets all elements in an int matrix with a standard value.
*/
void initializeintmatrix(int **, int , int , int );

/*		void setintmatrix(int **matrix, int row, int col, int set)
* This function sets an element in an int matrix with a standard value.
*/
void setintmatrix(int **, int , int , int );

/*		void createintmatrix(int ***matrix, int nrow, int ncol)
* This function creates an int matrix in the memory.
*/
void createintmatrix(int ***, int , int );






//------ String/Vector manipulation ------
/*		void printintvec(int *vec, int size)
* This function prints a integer vector.
*/
void printintvec(int *, int );

/*		int occurrences(void *string, size_t size, size_t nelem, void *elem)
* This function count the occurrences of an element in a pointer.
*/
int occurrences(void *, size_t , size_t , void *);

/*		int countlower(char *string)
* This function count the lower chars in a string.
*/
int countlower(char *);

/*		int countupper(char *string)
* This function count the upper chars in a string.
*/
int countupper(char *);


/*		void tolower_(char **string)
* This function turns all characters in a string in lower
* characters.
* Exemple: StRiNg (original) -> string (to lower)
*/
void tolower_(char **);

/*		char *readline(FILE *inputfile, char delim)
* This function reads a string from an inputfile.
* It always allocate the string on HEAP memory.
*/
char *readline(FILE *, char );

#endif
