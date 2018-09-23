# escrever um código em assembly MIPS que implemente o 
# seguinte código em C:
#
#      while (save[i] == k)
#		i = i + j;
#
# Sem perda de generalidade, para a execução, considerar estes dados:
#      int i=0, j=1, k=10;
#      int save[]={10,10,10,10,10,10,10,10,10,10,5,5};

# este codigo possui dois desvios (um condicional e outro 
# incondicional) dentro do loop. A questao e: como reduzir o 
# numero de instrucoes executadas sem perder a funcionalidade.
# Considerando apenas o loop, sao executadas 7 instrucoes a 
# cada iteracao, sendo que sao usadas (neste exemplo) 10 iteracoes 
# completas e mais uma que determina a saida.
#
# numero de instrucoes = 7 * 10 + 5 = 75
# nr de instrucoes com sll: 6* 10 + 5 = 65
.data
.align 2
save:	.word 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 5, 5

.text
.align 2
.globl main

main:
	li $s3, 0			# i = 0	
	li $s4, 1			# j = 1
	li $s5, 10		    # k = 10
	la $s6, save		# $s6 = endereco[save]

# ***** comeca a contar as instrucoes a partir daqui

loop:	
	add $t1, $s3, $s3	# Reg temporario $t1 = 2 * i
	add $t1, $t1, $t1	# Reg temporario $t1 = 4 * i
	add $t1, $t1, $s6	# $t1 =endereco de save[i]
	lw $t0, 0($t1)		# Reg temporario $t0 = save[i]
	bne $t0, $s5, exit	# desvia para exit se save[i] != k
	add $s3, $s3, $s4	# i = i + j
	j loop			# desvia para loop

# ***** conta o numero de instrucoes ate aqui

exit:	
	li $v0, 10		# codigo da chamada de sistema EXIT
	syscall		# chamada de sist.setada em $v0
