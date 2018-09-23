#:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#
#::::::::: T1 - ORGANIZACAO DE COMPUTADORES 2017/1 :::::::::#
#:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::#

#:::::::::::::::: HASH TABLE DE 16 POSICOES ::::::::::::::::#
#::: NOME: Giovana Meloni Craveiro			nUSP: 9791264 ::#
#::: NOME: João Pedro Ramos Belmiro			nUSP: 9791198 ::#
#::: NOME: Matheus Aparecido do Carmo Alves	nUSP: 9791114 ::#
#::: NOME: Rogers	Silva de Cristo			nUSP: 10355930 :#

#::::::::::::::::: DECLARACAO DE VARIAVEIS :::::::::::::::::#
                        .data
                          
                        .align 2
HASH:					.word  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 # Tabela HASH. Pode ser alterado.
nINSERT:				.word  1							# Opcao 'Inserir'
nREMOVE:				.word  2							# Opcao 'Remover'
nSEARCH:				.word  3							# Opcao 'Buscar'
nVISUALIZE:				.word  4							# Opcao 'Visualizar'
nEND:					.word  5							# Opcao 'Finalizar operacao'
NODE_SIZE:              .word  12
HASH_SIZE:              .word  16                           # Pode alterar o tamanho da Tabela HASH

                        .align 0
str_welcome:			.asciiz "Bem vindo ao manipulador de HASH TABLES de 16 posicoes\n"
str_op_show:			.asciiz "As opcoes de interacao sao: \n"
str_ops:				.asciiz "1. Insercao\n2. Remocao\n3. Busca\n4.Visualizacao\n5. Finaliza a execucao\n"
str_ops_select:			.asciiz "- Digite a opcao desejada: "
str_insert:				.asciiz "\n--- INSERCAO ---\n Digite o numero que deseja inserir na HASH: "
str_remove:				.asciiz "\n---  REMOCAO ---\n Digite o numero que deseja remover da HASH: "
str_search:				.asciiz "\n---   BUSCA  ---\n Digite o numero que deseja buscar na HASH: "
str_visualize:			.asciiz "\n--- VISUALIZACAO ---\n"
str_end:				.asciiz "\nExecucao finalizada. Agradecemos a preferencia.\n"
str_hindice:            .asciiz " indice: "
str_posicao:            .asciiz "\n posicao: "
str_space:              .asciiz " " 
str_ddot_space:         .asciiz ": "
str_openc:              .asciiz "("
str_closec:             .asciiz ")"
str_new_line:			.asciiz "\n"


#::::::::::::::::::::::: INSTRUCOES ::::::::::::::::::::::::#
                        .text
                        .globl main

main:
                        # 0. Inicializacao das 16 posicoes da Tabela HASH. Insercao de listas nos indices
                        lw      $t0, HASH_SIZE
                        add     $a0, $zero, $t0      # Passa as 16 posicoes da HASH para $a0
                        jal     CREATE_HASH
                        
                        # 1. Variaveis locais do programa + inicializacoes
                        li		$t0, 0						# t0 = (op = 0) - Enquanto $t0 for igual 0 ele se mantem no looping

                        # 2. Iniciando o programa para o usuario - interface
                        li		$v0, 4						# Codigo para impressao de string
                        la		$a0, str_welcome  			# String de boas vindas
                        syscall							    # Sistema, imprima!

                        la		$a0, str_op_show	 	    # String que apresenta as opcoes
                        syscall								# Sistema, imprima!

                        la		$a0, str_ops 		 		# String que mostra as opcoes
                        syscall								# Sistema, imprima!

op_loop:						
                        # 3. Manipulando a HASH enquanto o usuario nao desejar sair do programa
                        lw		$t7, nEND					# Carrega o valor de END em $t7 para comparação abaixo
                        beq		$t0, $t7, opEND			    # Se valor de nEND == $t0, vá para opEND

                        li		$v0, 4						# Codigo para impressao de string
                        la		$a0, str_ops_select   	    # 'Digite a opcao desejada'
                        syscall								# Sistema, imprima!

                        li		$v0, 5 						# Codigo para leitura de inteiro
                        syscall								# Sistema, leia!
                        add		$t0, $zero,	$v0			    # Salva em $t0 o valor de entrada

#::: switch(op) :::#
                        lw		$t6, nINSERT			    # Carrega o valor de nINSERT (1) em $t6
                        beq 	$t0, $t6, opINSERT  		# Caso o valor digitado tenha sido 1, vá para opINSERT
                                                            # Caso contrário, continue a execução

                        lw		$t6, nREMOVE           	    # Carrega o valor de nINSERT (2) em $t6
                        beq		$t0, $t6, opREMOVE  		# Caso o valor digitado tenha sido 2, vá para opREMOVE
                                                            # Caso contrário, continue a execução

                        lw		$t6, nSEARCH           	    # Carrega o valor de nINSERT (3) em $t6
                        beq 	$t0, $t6, opSEARCH  		# Caso o valor digitado tenha sido 3, vá para opSEARCH
                                                            # Caso contrário, continue a execução

                        lw		$t6, nVISUALIZE        	    # Carrega o valor de nINSERT (4) em $t6
                        beq 	$t0, $t6, opVISUALIZE		# Caso o valor digitado tenha sido 4, vá para opVISUALIZE
                                                            # Caso contrário, continue a execução

                        j 		op_loop

#::: switch(op) == nINSERT :::#
opINSERT:									
                        li		$v0, 4						# Codigo para impressao de string
                        la		$a0, str_insert		  		# 'Voce selecionou a operacao de INSERCAO...'
                        syscall								# Sistema, imprima!

                      
                        # a. Capturando o numero que sera INSERIDO na HASH
                        li		$v0, 5						# Codigo para leitura de inteiro
                        syscall								# Sistema, leia!
                        add		$t0, $zero,	$v0			    # Salva em $t0 o valor de entrada
                        
                        # b. Tratamento de entradas -1 e entradas negativas
                        li		$t1, -1						# Armazena -1 em $t1 para comparacao abaixo
                        beq     $t0, $t1, op_loop			# Se $t0 == -1, va para op_loop. Caso contrario, continue a insercao
                        blt     $t0, $zero, opINSERT        # Se $t0 < 0, va para opINSERT. Caso contrario, continue a insercao
                          
                        # c. Calculando o indice
                        lw      $t3, HASH_SIZE              # Tamnhado da Hash($t3) = 16 
                        div     $t0, $t3                    # Dividindo a entrada do usuario ($t0) por 16 (tamanho da tabela HASH)
                        mfhi    $t3                         # Salva o resto em $t3
                        la      $a0, HASH                   # Salvando o endereco da HASH($a0)
                        mul     $t3, $t3, 4                 # Multiplicando o resto por 4 ($t3 = $t3 * 4) para indexar por WORD
                        add     $a0, $a0, $t3               # Adicionando o resto ($t3) para a cabeca da lista ($a0)
						lw      $a0, 0($a0)                 # Deferenciando o $a0(ponteiro pra cabeca)
						
                        # d. Iniciacando a insercao
                        move    $a1, $t0
						jal     INSERT  
                        
                        j 		opINSERT					# Volte para o inicio da operacao opINSERT

#::: switch(op) == nREMOVE :::#
opREMOVE:
                        li		$v0, 4						# Codigo para impressao de string
                        la		$a0, str_remove		  		# 'Voce selecionou a operacao de REMOCAO...'
                        syscall								# Sistema, imprima!

                        # a. Capturando o numero que sera REMOVIDO na HASH
                        li		$v0, 5						# Codigo para leitura de inteiro
                        syscall								# Sistema, leia!
                        add		$t0, $zero,	$v0			    # Salva em $t0 o valor de entrada

                        # b. Tratamento de entradas -1 e entradas negativas
                        li		$t1, -1						# Armazena -1 em $t1 para comparacao abaixo
                        beq     $t0, $t1, op_loop			# Se $t0 == -1, va para op_loop. Caso contrario, volte ao menu
                        blt     $t0, $zero, opREMOVE        # Se $t0 < 0, va para opREMOVE. Caso contrario, continue a remocao
                          
                        # c. Iniciacando a remocao
                        add     $a0, $zero, $t0
						jal REMOVE
                          
                        j 		opREMOVE					# Volte para o inicio da operacao opREMOVE

#::: switch(op) == nSEARCH :::#
opSEARCH:
                        li		$v0, 4						# Codigo para impressao de string
                        la		$a0, str_search		  		# 'Voce selecionou a operacao de BUSCA...'
                        syscall								# Sistema, imprima!

                        # a. Capturando o numero que sera BUSCADO na HASH
                        li		$v0, 5						# Codigo para leitura de inteiro
                        syscall								# Sistema, leia!
                        add		$t0, $zero,	$v0			    # Salva em $t0 o valor de entrada

                        # b. Tratamento de entradas -1 e entradas negativas
                        li		$t1, -1						# Armazena -1 em $t1 para comparacao abaixo
                        beq     $t0, $t1, op_loop		    # Se $t0 == -1, va para op_loop. Caso contrario, continue a insercao
                        blt     $t0, $zero, opSEARCH        # Se $t0 < 0, va para opSEARCH. Caso contrario, continue a insercao

                        # c. Iniciacando a busca
                        add     $a0, $zero, $t0             # $a0 recebe o numero  que se busca
						jal     BUSCA                       # Realizando a busca
						
                        j 		opSEARCH					# Volte para o inicio da operacao opSEARCH

#::: switch(op) == nVISUALIZE :::#
opVISUALIZE:
                        li		$v0, 4						# Codigo para impressao de string
                        la		$a0, str_visualize	  	    # 'Voce selecionou a operacao de VISUALIZACAO.'
                        syscall								# Sistema, imprima!

                        # a. Iniciacando a visualizacao
					    jal     VISUALIZE
                          
                        j 		op_loop

#::: switch(op) == nEND :::#
opEND:
                        # 3. Encerrando o programa
                        li		$v0, 4						# Codigo para impressao de string
                        la		$a0, str_end				# 'Execucao finalizada....'
                        syscall								# Sistema, imprima!

                        li		$v0, 10						# Codigo para finalizacao do programa
                        syscall								# Sistema, finalize!

#(0.a):::::::::::::::::::::: CREATE_HASH ::::::::::::::::::::::#
CREATE_HASH:
                        # a. Empilhando os atributos da funcao
                        addi    $sp, $sp, -8                # Alocando espaco na pilha
                        sw      $ra, 0($sp)                 # Salva o endereco de retorno
                        sw      $a0, 4($sp)                 # Salva n indices
                        
                        # b. Criando a tabela HASH de n ($a0) posicoes
                        la      $t0, HASH                   # A cabeça da lista($t0) recebe o endereco da HASH
                        li      $t1, 0                      # contador ($t1) = 0
                        lw      $t2, 4($sp)                 # $t2 = numero de indices da HASH
Hash_loop:  
                        jal     CREATE_LIST
                        sw      $v0, 0($t0)                 # 
                        
                        addi    $t0, $t0, 4                 # Incrementando o indice da Hash
                        addi    $t1, $t1, 1                 # Contador += 1
                        blt     $t1, $t2, Hash_loop         # Se o contador($t2) for menor que o tamanho da hash, continue a criar listas
                        
                        # c. Desempilhando e retornando a chamada da funcao
                        lw      $ra, 0($sp)                 # Carrega endereco de retorno
                        lw      $a0, 4($sp)                 # Carrega n indices
                        addi    $sp, $sp, 8                 # Desalocando espaco na pilha
                        
                        jr      $ra

#(1.a)::::::::::::::::::::::: INSERCAO ::::::::::::::::::::::::#
#:::::::::::::::::INFO:::::::::::::::::#
# Args: a0 no cabeca da lista
#       a1 e o valor do numero a ser inserido (chave da tabela HASH)
# retorno nullo
INSERT:
                        # a. Empilhando os atributos da funcao
                	    addi    $sp, $sp, -12  
                        sw      $ra, 0($sp)                 # save endereco de retorno
                        sw      $a0, 4($sp)                 # save ponteiro para a cabeca da lista
                        sw      $a1, 8($sp)                 # save valor da chave da tabela HASH
  
                        # b. Criando o no a ser inserido
                		jal CREATE_NODE  	    	        # alocando espaco para o no
                		move    $s0, $v0                    # s0 = novo no da lista
                        lw      $s1, 0($s0)		    	    # s1 = valor do novo no da lista
                        la      $s2, 4($s0)                 # s2 = ponteiro anterior do novo no  --por enquanto é nulo
                        la      $s3, 8($s0)                 # s3 = ponteiro proximo do novo no   --por enquanto é nulo
            
                        # c. Buscando o valor da posicao na lista
                        lw      $t1, 8($sp)                 # t1 = valor chave da HASH
                        lw      $t2, 4($sp)                 # t2 = endereco da cabeca da lista
                        lw      $t2, 8($t2)                 # t2 = lista_cabeca->prox
                        lw      $t0, 4($sp)                 # t0 = anterior_a_t2 = prox->ant  = endereco da cabeca da lista
                    
while:              
                        beq     $t2, $zero, Rearrange       # Se proximo ($t2) == null ($zero) va para Rearrange...
                        lw      $t3, 0($t2)                 # Senao carregue o valor do proximo (0($t2)) em $t2 (anteriormente um endereco)
                        
                        blt     $t1, $t3, Rearrange         # Se valor da chave da HASH ($t1) >= valor do proximo item ($t2) va para Rearrange...
                        la      $t0, ($t2)                  # t0 (anterior) = t2 (proximo)
                        lw      $t2, 8($t2)                 # t2 (proximo) = t2->proximo
                        j       while                       # Senao, volte para while
                    
                    
Rearrange:  
                        # d. Rearranjando os ponteiros
                        sw      $t0, 0($s2)                 # novo_no->anterior = no_anterior_a_posicao_correta_de_insercao
                        sw      $t2, 0($s3)                 # novo_no->proximo = next = no_proximo_a_posicao_correta_de_insercao
                    
                        beq     $t2, $zero, Null            # Se o prox($t2) == null($zero), va para Null
                        addi    $t2, $t2, 4                 # $t2 = $t2->anterior
                        la      $t1, ($s0)                  # $t1 = endereco do novo no
                        sw      $t1, ($t2)                  # no_proximo_a_posicao_correta_de_insercao ($t2) = endereco do novo no ($t1)
Null:
                        addi    $t0, $t0, 8                 # $t0 = $t0->prox
                        la      $t1, ($s0)                  # t1 = novo no
                        sw      $t1, 0($t0)                 # no_anterior_a_posicao_correta_de_insercao = novo_no
                    
                        # e. Desempilhando a funcao e retornando a chamada da funcao...
                        lw      $ra, 0($sp)
                        lw      $a0, 4($sp)
                        lw      $a1, 8($sp)
                        addi    $sp, $sp, 12
                    
                        jr      $ra
                    
#(1.b):::::::::::::::::::: CREATE_NODE ::::::::::::::::::::::::#
CREATE_NODE:
                        # a. Empilhando o endereco de retorno na stack...
                      	addi    $sp, $sp, -8
                        sw      $ra, 0($sp)
                        sw      $a1, 4($sp)
                    
                        # b. Alocando espaco para o novo no...
                        lw      $a0, NODE_SIZE              # a0 = tamanho do no
                        jal     ALLOC_NEW_OBJ               # alocando espaco na memoria
    
                        # c. Criando o novo no...
                        sw      $a1, 0($v0)                 # node->value = value
                        sw      $zero, 4($v0)               # node->prev = null
                        sw      $zero, 8($v0)               # node->next = null
    
                        # d. Desempilhando a funcao e retornando a chamada
                        lw      $ra, 0($sp)
                        lw      $a1, 4($sp)
                        addi    $sp, $sp, 8
                        
                      	jr      $ra

#(1.c):::::::::::::::::::: ALLOC_NEW_OBJ ::::::::::::::::::::::::#
ALLOC_NEW_OBJ:
                        # a. Criando a pilha da funcao...
                      	addi    $sp, $sp, -8
                        sw      $ra, 0($sp)
                        sw      $a0, 4($sp)
                    
                        # b. Allocando espaco na memoria de tamanho $a0...
                        li $v0, 9					        # funcao sbrk(alocacao da heap)
                        syscall
                        
                        # c. Desempilhando a funcao e retornando em $v0 o ponteiro que aponta para o 
                        #   espaco alocando.
                        lw      $ra, 0($sp)
                        lw      $a0, 4($sp) 
                        addi    $sp, $sp, 8
    
                        jr      $ra

#(1.d):::::::::::::::::::: CREATE_LIST ::::::::::::::::::::::::#
CREATE_LIST:
                        # a. Empilhando o endereco de retorno na stack
                      	addi    $sp, $sp, -4
                        sw      $ra, 0($sp)
    
                        # b. Criando o no da cabeca da lista...                  
                        li      $a1, -1
                        jal     CREATE_NODE
                      
                        # c. desempilhando o endereco de retorno da stack
                        lw      $ra, 0($sp)
                        addi    $sp, $sp, 4
                  	
                  	    jr      $ra

#(2.a):::::::::::::::::::::: REMOCAO ::::::::::::::::::::::::::#
REMOVE:
                        # a. Empilhando o endereco de retorno na stack
                        add     $sp, $sp, -8                # aumentando o tamanho da pilha
                        sw      $ra, 0($sp)                 # armazenando o endereco de retorno na pilha
                        sw      $a0, 4($sp)                 # armazenando o a0(valor do item a ser removido) na pilha
                        
                        # b. Calculando o indice do elemento
                        lw      $t3, HASH_SIZE              # Tamanho da HASH($t3) = 16 
                        div     $a0, $t3                    # Dividindo a entrada do usuario ($t0) por 16 (tamanho da tabela HASH)
                        mfhi    $t3                         # Salva o resto[indice] em $t3
                        add     $a1, $zero, $t3             # Salva o resto[indice]($t3) em $a1
                        
						
						# c. Carregando a lista do indice encontrado
                        la      $a0, HASH                   # Salvando o endereco da HASH($a0)
                        mul     $t3, $t3, 4                 # Multiplicando o resto por 4 ($t3 = $t3 * 4) para indexar por WORD
                        add     $a0, $a0, $t3               # Adicionando o resto ($t3) para a cabeca da lista ($a0)
						lw      $a0, 0($a0)                 # Deferenciando o $a0(ponteiro pra cabeca)
                        
                        lw      $a2, 4($sp)                 # Armazenando em $a2 o valor do item(recuperado da pilha)
                        
                        # d. Buscando o endereco do no
                        jal SEARCH_LIST

                        beq     $v0, $zero, IsNull          # Caso o retorno de SEARCH_LIST seja 0, o no a ser removido nao existe
                                                            # Entao saimos da iteracao sem remover nada

                        lw      $t1, 4($v0)                 # ($t1) = no anterior ao no a ser removido(4($v0))
                        lw      $t2, 8($v0)                 # ($t2) = no posterior ao no a ser removido(8($v0))
                        sw      $t2, 8($t1)                 # 8($t1) proximo do anterior = ($t2) proximo do no a ser removido
                        
                        beq     $t2, $zero, IsNull          # caso o 8($v0)(proximo no do no a ser removido) for null
                                                            # pular essa atribuicao para nao acessar memoria invalida
                                                            
                        sw      $t1, 4($t2)                 # 4($t1) anterior do prox = ($t1) anterior do no a ser removido
                        
IsNull:
                        
                        # e. desempilhando o endereco de retorno da stack
                        lw      $a0, 4($sp)                 #Carregando o a0 com o valor do item removido (recuperado da pilha)
                        lw      $ra, 0($sp)                 #Carregando em $ra o endereco de retorno
                        add     $sp, $sp, 8                 #Desempilhando
                        
                        jr      $ra
                        

#(3.a)::::::::::::::::::::::: BUSCA :::::::::::::::::::::::::::#
BUSCA:
                        # a. Empilhando o endereco de retorno na stack
                      	addi    $sp, $sp, -8                # Empilhando...
                        sw      $ra, 0($sp)                 # Salvando o endereco de retorno
                        sw      $a0, 4($sp)                 # Salvando o valor do elemento procurado($a0)
                        
                        # b. Calculando o indice do elemento
                        lw      $t3, HASH_SIZE              # Tamanho da HASH($t3) = 16 
                        div     $a0, $t3                    # Dividindo a entrada do usuario ($t0) por 16 (tamanho da tabela HASH)
                        mfhi    $t3                         # Salva o resto[indice] em $t3
                        add     $a1, $zero, $t3             # Salva o resto[indice]($t3) em $a1
                        
						
						# c. Carregando a lista do indice encontrado
                        la      $a0, HASH                   # Salvando o endereco da HASH($a0)
                        mul     $t3, $t3, 4                 # Multiplicando o resto por 4 ($t3 = $t3 * 4) para indexar por WORD
                        add     $a0, $a0, $t3               # Adicionando o resto ($t3) para a cabeca da lista ($a0)
						lw      $a0, 0($a0)                 # Deferenciando o $a0(ponteiro pra cabeca)
						
                            
                        # d. Buscando o elemento na lista
                        #- Caso ele exista, sera impresso na tela o indice da HASH e eh retornado o ponteiro para o elemento encontrado
                        #- Caso contrario, eh impresso -1 na tela
                        lw      $a2, 4($sp)                 # Armazenando em $a2 o valor do item(recuperado da pilha)
                        add     $a3, $zero, $zero           # Passando um contador de posicao para a funcao
                        jal     SEARCH_LIST                 # Realizando uma busca na lista
                        
                        move    $t5, $v0                    # Armazenando ponteiro para o no(retorno($v0)) em $t5
                        bne     $t5, $zero, Found           # Se o ponteiro para o no($t5) == 0, va para NotNull
                        
                        # e. Imprimindo -1 uma vez que o elemento nao foi encontrado
                        li      $v0, 1                      # Codigo para impressao de inteiro
                        addi    $a0, $zero, -1              # Carregando o valor -1
                        syscall                             # Sistema, imprima!
                        
                        j EndFoundVerf

Found:
                        # i. Imprimindo o valor do indice da hash, ja que o elemento foi encontrado
                        li      $v0, 4                     # Codigo para impressao de uma string
                        la      $a0, str_hindice           # Carregando a string "indice:"
                        syscall                            # Sistema, imprima!
                        
                        li      $v0, 1                     # Codigo para impressao de inteiro
                        move    $a0, $a1                   # Carregando o valor do indice
                        syscall                            # Sistema, imprima!
                        
                        li      $v0, 4                     # Codigo para impressao de uma string
                        la      $a0, str_posicao           # Carregando a string "\nposicao:"
                        syscall                            # Sistema, imprima!

                        
                        li      $v0, 4                     # Codigo para impressao de uma string
                        la      $a0, str_openc             # Carregando a string "("
                        syscall                            # Sistema, imprima!
                        
                        li      $v0, 1                     # Codigo para impressao de um inteiro
                        move    $a0, $a3                   # Carregando o valor da posicao em que o elemento foi encontrado
                        syscall                            # Sistema, imprima!
                        
                        li      $v0, 4                     # Codigo para impressao de uma string
                        la      $a0, str_closec            # Carregando a string ")"
                        syscall                            # Sistema, imprima!
                        
EndFoundVerf:
                        li      $v0, 4                     # Codigo para impressao de string
                        la      $a0, str_new_line          # Carregando o pulo de linha "\n"
                        syscall                            # Sistema, imprima!
                        
                        # f. desempilhando o endereco de retorno da stack
                        lw      $a0, 4($sp)                 # Carregando o valor do elemento procurado em $a0
                        lw      $ra, 0($sp)                 # Carregando o endereco de retorno
                        addi    $sp, $sp, 12                # Desempilhando
                  	
                  	    jr      $ra

#(3.b):::::::::::::::::::: SEARCH_LIST :::::::::::::::::::::::#
SEARCH_LIST:             
                        #a. Empilhando a funcao na pilha
                        addi    $sp, $sp, -16               # Empilhando...
                        sw      $ra, 0($sp)                 # Salva o endereco de retorno
                        sw      $a0, 4($sp)                 # Salva a cabeca da lista
                        sw      $a1, 8($sp)                 # Salva o valor de indice
                        sw      $a2, 12($sp)                # Salva o valor buscado
                        
                        #b. Buscando o elemento
                        lw      $t0, 4($sp)                 # no ($t0) = endereco da cabeca da lista (4($sp))
                        lw      $t0, 8($t0)                 # no ($t0) = primeiro elemento (cabeca da lista) (Pula o -1 da cabeca)
SListRun:                
                        beq     $t0, $zero, SEndListRun     # Se o proximo elemento ($t1) for null ($zero), va para EndListRun
                        
                        lw      $t1, 0($t0)                 # Carrega o valor do no
                        beq     $t1, $a2, SEndListRun       # Se o valor buscado($a1) == valor do no($t1), va para SEndListRun!
                        
                        lw      $t0, 8($t0)                 # no ($t0) = proximo do no ($t0)
                        addi    $a3, $a3, 1                 # contador_de_posicao += 1
                        j       SListRun                    # Retornando ao laco

SEndListRun:            

                        # a. Retornando o ponteiro para o elemento ja que ele foi encontrado
                        move     $v0, $t0                   # Carregando o ponteiro para o elemento
                        
                        # b. Desempilhando a funcao na pilha e retornando ao ponto de chamada
                        lw      $ra, 0($sp)                 # Carrega o endereco de retorno
                        lw      $a0, 4($sp)                 # Carrega o cabeca da lista
                        lw      $a1, 8($sp)                 # Carrega o valor do indice
                        lw      $a2, 12($sp)                # Carrega o valor buscado
                        addi    $sp, $sp, 16                # Desempilhando...
                        
                        jr      $ra   

#(4.a):::::::::::::::::::: VISUALIZACAO :::::::::::::::::::::::#
VISUALIZE:
                        # a. Empilhando a funcao na pilha
                        addi    $sp, $sp, -4
                        sw      $ra, 0($sp)
    
                        # b. Percorrendo cada indice da HASH e imprimindo a lista do indice acessado
                        la      $t0, HASH                   # Salvando endereco da hash ($t0)
                        li      $t1, 0                      # Contador de indice da hash ($t1)
                        lw      $t3, HASH_SIZE              # limitador ($t3) recebe o tamanho da HASH(16)[$t3]
                        mul     $t3, $t3, 4                 # limitador($t3) recebe = limitador * tamanho da palavra(4bytes)
                        add     $t2, $t0, $t3               # Limite do endereco da hash($t2) = endereco da Hash + 16 * 4(64)
HashRun:
                        add     $a0, $zero, $t0             # Carregando em $a0 a cabeca da lista a ser impressa (chave HASH)
                        add     $a1, $zero, $t1             # Carregando em $a1 o valor do indice a ser impresso
                        jal     PRINT_LIST                  # Imprimindo a lista
                        
                        addi    $t0, $a0, 4                 # Incrementando o indice da hash
                        addi    $t1, $a1, 1                 # Incrementando o contador de indices
                        blt     $t0, $t2, HashRun           # Se o endereco atual da hash($t0) for menor que 16($t2) entao continue a percorrer os indices
                        
                        # c. Desempilhando e encerrando a funcao
                        lw      $ra, 0($sp)                 # Carrega o endereco de retorno
                        addi    $sp, $sp, 4                 # Desempilhando
                        
                        jr      $ra

#(4.b):::::::::::::::::::: PRINT_LIST :::::::::::::::::::::::#
PRINT_LIST:             
                        #a. Empilhando a funcao na pilha
                        addi    $sp, $sp, -12               # Empilhando...
                        sw      $ra, 0($sp)                 # Salva o endereco de retorno
                        sw      $a0, 4($sp)                 # Salva a cabeca da lista
                        sw      $a1, 8($sp)                 # Salva o contador de indice
                        
                        #b. Imprimindo os elementos da lista enquanto nao encontrar um endereco nullo
                        li      $v0, 1                      # Codigo para impressao de inteiro
                        add    $a0, $zero, $a1              # Carregando o indice da lista
                        syscall                             # Sistema, imprima!
                        
                        li      $v0, 4                      # Codigo para impressao de inteiro
                        la      $a0, str_ddot_space         # Carregando a string ": "
                        syscall                             # Sistema, imprima!
                        
                        lw      $t0, 4($sp)                 # no ($t0) = endereco da cabeca da lista (4($sp))
                        lw      $t0, 0($t0)                 # no ($t0) = primeiro elemento (cabeca da lista) (Pula o -1 da cabeca)
                        lw      $t1, 8($t0)                 # Proximo do no $t0 ($t1)

ListRun:                
                        beq     $t1 , $zero, EndListRun     # Se o proximo elemento ($t1) for null ($zero), va para EndListRun
                        lw      $t0, 8($t0)                 # no ($t0) = proximo do no ($t0)
                        lw      $t1, 8($t0)                 # no ($t1) = proximo do no ($t0)
                    
                        li      $v0, 1                      # Codigo para impressao de inteiro
                        lw      $a0, 0($t0)                 # Carregando o valor do no
                        syscall                             # Sistema, imprima!
                        
                        li      $v0, 4                      # Codigo para impressao de string
                        la      $a0, str_space              # Carregando um espaco " "
                        syscall                             # Sistema, imprima!
                        
                        j       ListRun                     # Retornando ao laco

EndListRun:
                        li      $v0, 4                      # Codigo para impressao de inteiro
                        la      $a0, str_new_line           # Carregando um pulo de linha "\n"
                        syscall    
                        
                        # c. Desempilhando a funcao na pilha e retornando ao ponto de chamada
                        lw      $ra, 0($sp)                 # Carrega o endereco de retorno
                        lw      $a0, 4($sp)                 # Carrega o cabeca da lista
                        lw      $a1, 8($sp)                 # Carrega o valor do indice
                        addi    $sp, $sp, 12                # Desempilhando...
                        
                        jr      $ra