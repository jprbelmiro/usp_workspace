import sys
import numpy as np
import numpy.linalg as lin
from numpy import linalg

def sassenfeld(A):
    #1. Initializing the evaluation vector
    B = np.zeros((len(A)))
    for i in range(0,len(A)):
        #a. calculating the Bi value
        sum = 0
        for j in range(0,i-1):
            sum = sum + A[i,j]*B[j]
        for j in range(i+1,len(A)-1):
            sum = sum + A[i,j]
        
        #b. verifying the sassenfeld's condition
        B[i] = sum/A[i,i]      
        if( B[i] >= 1):
            return(False)
    
    #2. Returning
    return(True)

def gaussseidel(A,b,x0,eps,itmax, n):
    #1. Defining the upper and lower triangle matrices
    L = np.tril(A) 
    R = np.triu(A,1)
    
    #2. Building the constant C matriz and the g vector of Gauss-Seidel Method
    C = lin.solve(-L,R)
    g = lin.solve(L,b)
    
    #3. Applying the Gauss-Seidel Method
    it = 0
    result = []
    while(lin.norm(b-(np.dot(A, x0))) > eps and it < itmax):
        it = it+1
        x0 = C.dot(x0) + g
        
        result.append(np.transpose(x0))
        
    return result
