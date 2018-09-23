# código em assembly MIPS que implementa o seguinte código em C:
#
#      while (save[i] == k)
#		i = i + j;
#
# Sem perda de generalidade, para a execução, considerar estes dados:
#      int i=0, j=1, k=10;
#      int save[]={10,10,10,10,10,10,10,10,10,10,5,5};
# este codigo possui apenas um desvio condicional dentro do loop. 
# Considerando esta versao sao executadas 7 instruções antes do 
# loop e dentro do mesmo sao executadas 6 instrucoes a cada 
# iteracao, sendo que sao usadas (neste exemplo) 10 iteracoes 
# completas.
#
# numero de instrucoes = 7 + 10 * 3 = 37
# nr de instrucoes com sll: 5 + 10 * 3 = 35

.data
.align 0
string: .byte 1,2,3,4,5,6
.align 2
save:	.word 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 5, 5, 5

.text
.align 2
.globl main

main:
	li $s3, 0			# i = 0	
	li $s4, 1			# j = 1
	li $s5, 10		     # k = 10
	la $s6, save		# $s6 = endereco[save]

	lw $t8, 0($s6)
# ***** comeca a contar as instrucoes a partir daqui

	add $t2, $s4, $s4	# Reg temporario $t2 = 2 * j
	add $t2, $t2, $t2	# Reg temporario $t2 = 4 * j
	add $t1, $s3, $s3	# Reg temporario $t1 = 2 * i
	add $t1, $t1, $t1	# Reg temporario $t1 = 4 * i
	add $t1, $t1, $s6	# Reg temporario $t1 = end.save[i]
	lw $t0, 0($t1)		# Reg temporario $t0 = save[i]
	bne $t0, $s5, exit	# Desvia para exit se save[i] != k

loop:	
	add $t1, $t1, $t2	# Reg temporario $t1 = [i + m * j]
	lw $t0, 0($t1)		# Reg temporario $t0 = save[i]
	beq $t0, $s5, loop	# Desvia para loop se save[i] == k

# ***** conta as instruções ate aqui

exit:	li $v0, 10		# codigo da chamada de sistema EXIT
	syscall		# chamada de sistema setada em $v0
