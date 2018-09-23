import sys
import time
import numpy as np
import numpy.linalg as lin
import matplotlib.pyplot as plt
from gaussseidel import gaussseidel,sassenfeld

NSIDES = 4
UP = 0
LEFT = 1
DOWN = 2
RIGHT = 3

def printwelcome():
    print "| Trabalho 1 de Calculo numerico - Equilibrio Termico em uma Placa"
    print "| Alunos: Caio Ferreira Bernardo     - 9276936"
    print "| Matheus Aparecido do Carmo Alves   - 9791114"
    return

def createcoefmatrix(n,T,b):
    A = np.zeros((n*n,n*n))
    for i in range(0,n):
        for j in range(0,n):
            A[i*n + j, i*n + j] = 4 
            #analisando a quina
            if((i == 0 or i == n-1) and (j == 0 or j == n-1)):
                if(i == 0):
                    b[i*n + j] = b[i*n + j] + T[UP]
                    A[i*n + j,(i+1)*n + j] = -1
                else:
                    b[i*n + j] = b[i*n + j] + T[LEFT]
                    A[i*n + j,(i-1)*n + j] = -1
                if(j == 0):
                    b[i*n + j] = b[i*n + j] + T[DOWN]
                    A[i*n + j,i*n + j+1] = -1
                else:
                    b[i*n + j] = b[i*n + j] + T[RIGHT]
                    A[i*n + j,i*n + j-1] = -1
            #analisando a borda
            elif(i == 0 or j == 0 or i == n-1 or j == n-1):
                if(i == 0):
                    b[i*n + j] = T[UP]
                    A[i*n + j, i*n + j+1] = -1
                    A[i*n + j, i*n + j-1] = -1
                    A[i*n + j, (i+1)*n + j] = -1
                elif(j == 0):
                    b[i*n + j] = T[LEFT]
                    A[i*n + j, i*n + j+1] = -1
                    A[i*n + j, (i+1)*n + j] = -1
                    A[i*n + j, (i-1)*n + j] = -1
                elif(i == n-1):
                    b[i*n + j] = T[DOWN]
                    A[i*n + j, i*n + j+1] = -1
                    A[i*n + j, i*n + j-1] = -1
                    A[i*n + j, (i-1)*n + j] = -1
                else:
                    b[i*n + j] = T[RIGHT]
                    A[i*n + j, i*n + j-1] = -1
                    A[i*n + j, (i+1)*n + j] = -1
                    A[i*n + j, (i-1)*n + j] = -1
            
            #analisando o interior
            else:
                A[i*n + j, (i+1)*n + j] = -1;
                A[i*n + j, i*n + j+1] = -1;
                A[i*n + j, (i-1)*n + j] = -1;
                A[i*n + j, i*n + j-1] = -1;
    
    return(A)

# Ponto de Equilibrio Termico em uma Placa
def main():
    #0. Apresentacao do programa
    printwelcome()
    
    #1. Solicitando a entrada das temperaturas para as bordas da placa
    print "Entre com os valores para as temperaturas na borda da placa:"
    T = np.zeros((NSIDES))
    for i in range(0,NSIDES):
        T[i] = int(input("> T%d: "% (i+1)))
    
    #2. Definindo a ordem da matriz
    n = int(input("Entre com o valor de n para construir a matriz n x n:\n> "))
    
    #3. Definindo um valor maximo para o numero de iteracoes no sistema
    itmax = int(input("Entre com um valor para o numero de iteracoes maximo:\n> "))
    
    #4. Discretizando e resolvendo o problema
    #a. criando as matrizes/vetores necessarios
    inicio = time.time()
    b = np.zeros((n*n,1))
    x0 = np.ones((n*n,1))
    A = createcoefmatrix(n,T,b)

    #b. verificando o criterio de sassenfeld/convergencia do metodo
    if(sassenfeld(A)):
       print("\nO sistema converge.")
    else:
       print("\nO sistema nao converge.")
        
    #c. aplicando o metodo de Gauss-Seidel 
    result = gaussseidel(A,b,x0,0.00001,itmax, n)
        
    #d. imprimindo o resultado
    sys.stdout.write("Resultado obtido:\n\tx^%d = " % itmax)
    print(result[len(result)-1])
       
    #e. imprimindo o tempo de execucao do algoritmo
    fim = time.time()
    sys.stdout.write("Tempo de execucao (segundos): ")
    print(fim-inicio)

    #f. formatando um grafico para apresentar a convergencia do sistema
    eps = []
    for i in range(0,len(result)):
        eps.append(lin.norm(b-(np.dot(A,np.transpose(result[i])))))
        
    plt.plot(eps, label="%d pontos" %n)
    plt.legend(loc='upper right', frameon=False)
    plt.title("Convergencia")
    plt.grid(True)
    plt.xlabel("Numero de Iteracoes")
    plt.ylabel("Eps")
    plt.show()
    
    #5. Isso eh tudo pessoal :) ...
if __name__ == '__main__':
    main()