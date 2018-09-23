
#:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#::::::::: T1 - ORGANIZACAO DE COMPUTADORES 2017/1 :::::::::#
#:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#

#:::::::::::::::: HASH TABLE DE 16 POSICOES ::::::::::::::::#
#::: NOME: Giovana Meloni Craveiro					nUSP: 9791264
#::: NOME: João Pedro Ramos Belmiro					nUSP: 9791198
#::: NOME: Matheus Aparecido do Carmo Alves	        nUSP: 9791114
#::: NOME: Rogers	Silva de Cristo					nUSP: 10355930

#::::::::::::::::: DECLARACAO DE VARIAVEIS :::::::::::::::::#
                .data
		        .align 2
 
space:          .asciiz " "
enter:          .asciiz "\n"
open:          .asciiz "("
close:          .asciiz ")"
ListSize:		.word 4				# tamanho de uma lista(apenas um ponteiro para a cabeca)
NodeSize:		.word 12			# tamanho do no(3 words = 12 bytes) chave, ponteiro ant, ponteiro next
vector:         .word 18, 15, 12, 11, 8, 6, 4, 2, 1

                .align 0
                .text
                .globl main

#::::::::::::::::::::::: INSTRUCOES ::::::::::::::::::::::::#
main:

    lw $a0, NodeSize
    jal CreateList
    
    move $t7, $v0   #copiando o no para o t0
    
    move $a0, $v0
    addi $a1, $zero, 9
    jal InsertList
    
    move $a0, $t7
    addi $a1, $zero, 5
    jal InsertList
    
    move $a0, $t7
    addi $a1, $zero, 16
    jal InsertList
    
    #cabeca ------------------
    li $v0, 1
    lw $a0, 4($t7) #imprimindo o prev
    syscall

    li $v0, 4
    la $a0, space
    syscall

    li $v0, 1
    lw $a0, 0($t7) #imprimindo o valor      
    syscall
    
    li $v0, 4
    la $a0, open
    syscall
    
    li $v0, 1
    la $a0, 0($t7)
    syscall
    
    li $v0, 4
    la $a0, close
    syscall
    
    li $v0, 4
    la $a0, space
    syscall
    
    li $v0, 1
    lw $a0, 8($t7)  #imprimindo o next
    syscall
    
    li $v0, 4
    la $a0, enter
    syscall
    
    # 5 -------------------
    lw $t7, 8($t7)
    
    li $v0, 1
    lw $a0, 4($t7) #imprimindo o prev
    syscall

    li $v0, 4
    la $a0, space
    syscall

    li $v0, 1
    lw $a0, 0($t7) #imprimindo o valor
    syscall
    
    li $v0, 4
    la $a0, open
    syscall
    
    li $v0, 1
    la $a0, 0($t7)
    syscall
    
    li $v0, 4
    la $a0, close
    syscall
    
    li $v0, 4
    la $a0, space
    syscall
    
    li $v0, 1
    lw $a0, 8($t7)  #imprimindo o next
    syscall
    
    li $v0, 4
    la $a0, enter
    syscall
    
     # 9 -------------------
    lw $t7, 8($t7)
    
    li $v0, 1
    lw $a0, 4($t7) #imprimindo o prev
    syscall

    li $v0, 4
    la $a0, space
    syscall

    li $v0, 1
    lw $a0, 0($t7) #imprimindo o valor
    syscall
    
    li $v0, 4
    la $a0, open
    syscall
    
    li $v0, 1
    la $a0, 0($t7)
    syscall
    
    li $v0, 4
    la $a0, close
    syscall
    
    li $v0, 4
    la $a0, space
    syscall
    
    li $v0, 1
    lw $a0, 8($t7)  #imprimindo o next
    syscall
    
    li $v0, 4
    la $a0, enter
    syscall
    
     # 16 -------------------
    lw $t7, 8($t7)
    
    li $v0, 1
    lw $a0, 4($t7) #imprimindo o prev
    syscall

    li $v0, 4
    la $a0, space
    syscall

    li $v0, 1
    lw $a0, 0($t7) #imprimindo o valor
    syscall
    
    li $v0, 4
    la $a0, open
    syscall
    
    li $v0, 1
    la $a0, 0($t7)
    syscall
    
    li $v0, 4
    la $a0, close
    syscall
    
    li $v0, 4
    la $a0, space
    syscall
        
    li $v0, 1
    lw $a0, 8($t7)  #imprimindo o next
    syscall
    
    li $v0, 4
    la $a0, enter
    syscall
    
    li $v0, 10      #encerrando a funcao
    syscall
    
#::::::::::::::::::::: AllocNewObject ::::::::::::::::::::::#
# Args: a0 e o tamanho a ser alocado
# Func: Aloca espaco necessario para o objeto
# retorno: retorna em $v0 o endereco que aponta pra estrutura
AllocNewObject:
    #a. Criando a pilha da funcao...
                  	addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $a0, 4($sp)
                    
    #b. Allocando espaco na memoria de tamanho $a0...
                    li $v0, 9					# funcao sbrk(alocacao da heap)
                    syscall
                        
    #c. Desempilhando a funcao e retornando em $v0 o ponteiro que aponta para o 
    #   espaco alocando.
                    lw $ra, 0($sp)
                    lw $a0, 4($sp) 
                    addi $sp, $sp, 8

                    jr $ra
                        
#::::::::::::::::::::::: createList ::::::::::::::::::::::::# 
#
#--- INFO
# Args: nao recebe argumentos
# func:aloca espaco para uma lista e inicializa-a 
# retorno: retorna em $v0 um ponteiro para a lista
CreateList:
    #a. Empilhando o endereco de retorno na stack
                  	addi $sp, $sp, -4
                    sw $ra, 0($sp)
    
    #b. Criando o no da cabeca da lista...                  
                    li $a1, -1
                    jal CreateNode
                      
    #c. desempilhando o endereco de retorno da stack
                    lw $ra, 0($sp)
                    addi $sp, $sp, 4
                  	
                  	jr $ra

#::::::::::::::::::::::: CreateNode ::::::::::::::::::::::::# 
#
#--- INFO
# Args: a1 e o valor do novo no
# func: cria um no da lista e inicializa-o
# retorno: retorna em $v0 um ponteiro que aponta para o novo no
CreateNode:
    #a. Empilhando o endereco de retorno na stack...
                  	addi $sp, $sp, -8
                    sw $ra, 0($sp)
                    sw $a1, 4($sp)
                    
    #b. Alocando espaco para o novo no...
                    lw $a0, NodeSize    # a0 = tamanho do no
                    jal AllocNewObject  # alocando espaco na memoria
    
    #c. Criando o novo no...
                    sw $a1, 0($v0)     # node->value = value
                    sw $zero, 4($v0)   # node->prev = null
                    sw $zero, 8($v0)   # node->next = null
    
    #d. Desempilhando a funcao e retornando a chamada
                    lw $ra, 0($sp)
                    lw $a1, 4($sp)
                    addi $sp, $sp, 8
                    
                  	jr $ra


#::::::::::::::::::::::: createList ::::::::::::::::::::::::#  
#--- C
#void insertList(t_list *lista, t_item item){
#		
#       //0. Variaveis locais a funcao
#       t_node *p, *new_node;
#		p = *lista;
#	
#       //1. Criando o no a ser inserido
#		new_node = createNode();
#	
#       //2. Busca a posicao na lista
#		while(p->prox != NULL && p->prox->item < item) p = p->prox;
#	
#		//3. Rearranjando os ponteiros
#		new_node->ant = p;
#		new_node->prox = p->prox;
#		if(p->prox != NULL) p->prox->ant = new_node;
#		p->prox = new_node;
#	}
#--- INFO
# Args: a0 no cabeca da lista
#       a1 e o valor do numero a ser inserido (chave da tabela HASH)
# retorno nullo
InsertList: 
            #a. Empilhando os atributos da funcao
                	addi $sp, $sp, -12  
                    sw $ra, 0($sp)              # save endereco de retorno
                    sw $a0, 4($sp)              # save ponteiro para a cabeca da lista
                    sw $a1, 8($sp)              # save valor da chave da tabela HASH
  
            #b. Criando o no a ser inserido
            		jal CreateNode  	    	# alocando espaco para o no
            		move $s0, $v0               # s0 = novo no da lista
                    lw $s1, 0($s0)		    	# s1 = valor do novo no da lista
                    la $s2, 4($s0)              # s2 = ponteiro anterior do novo no  --por enquanto é nulo
                    la $s3, 8($s0)              # s3 = ponteiro proximo do novo no   --por enquanto é nulo
            
            #c. Buscando o valor da posicao na lista
                    lw $t1, 8($sp)              # t1 = valor chave da HASH
                    lw $t2, 4($sp)              # t2 = endereco da cabeca da lista
                    lw $t2, 8($t2)              # t2 = lista_cabeca->prox
                    lw $t0, 4($sp)              # t0 = anterior_a_t2 = prox->ant  = endereco da cabeca da lista
                    
while:              
                    beq $t2, $zero, Rearrange   # Se proximo ($t2) == null ($zero) va para Rearrange...
                    lw  $t3,     0($t2)             # Senao carregue o valor do proximo (0($t2)) em $t2 (anteriormente um endereco)
                    
                    blt $t1, $t3, Rearrange     # Se valor da chave da HASH ($t1) >= valor do proximo item ($t2) va para Rearrange...
                    la  $t0, ($t2)              # t0 (anterior) = t2 (proximo)
                    lw  $t2, 8($t2)             # t2 (proximo) = t2->proximo
                    j while                     # Senao, volte para while
                    
            #d. Rearranjando os ponteiros
Rearrange:  
                    sw $t0, 0($s2)            # novo_no->anterior = no_anterior_a_posicao_correta_de_insercao
                    sw $t2, 0($s3)            # novo_no->proximo = next = no_proximo_a_posicao_correta_de_insercao
                    
                    beq $t2, $zero, Null      # Se o prox($t2) == null($zero), va para Null
                    addi  $t2, $t2, 4         # $t2 = $t2->anterior
                    la    $t1, ($s0)          # $t1 = endereco do novo no
                    sw    $t1, ($t2)          # no_proximo_a_posicao_correta_de_insercao ($t2) = endereco do novo no ($t1)
Null:
                    addi  $t0, $t0, 8         # $t0 = $t0->prox
                    la    $t1, ($s0)         # t1 = novo no
                    sw    $t1, 0($t0)         # no_anterior_a_posicao_correta_de_insercao = novo_no
                    
            #e. Desempilhando a funcao e retornando a chamada da funcao...
                    lw  $ra,    0($sp)
                    lw  $a0,    4($sp)
                    lw  $a1,    8($sp)
                    addi $sp, $sp, 12
                    
                    jr  $ra