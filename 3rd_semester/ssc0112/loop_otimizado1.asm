# código em assembly MIPS que implementa o seguinte código em C:
#
#      while (save[i] == k)
#		i = i + j;
#
# Sem perda de generalidade, para a execução, considerar estes dados:
#      int i=0, j=1, k=10;
#      int save[]={10,10,10,10,10,10,10,10,10,10,5,5};

# este codigo possui apenas um desvio condicional dentro do loop. 
# Considerando esta versao sao executadas 5 instruções antes do 
# loop e dentro do mesmo sao executadas 6 instrucoes a cada 
# iteracao, sendo que sao usadas (neste exemplo) 10 iteracoes 
# completas.
#
# numero de instrucoes = 5 + 10 * 6 = 65
# nr de instrucoes com sll: 4 + 10*5 = 54

.data
.align 2
save:	.word 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 5, 5, 5

.text
.align 2
.globl main

main:
	li $s3, 0		# i = 0	
	li $s4, 1		# j = 1
	li $s5, 10		# k = 10
	la $s6, save	# $s6 = endereco[save]

# ***** comeca a contar as instrucoes a partir daqui

	add $t1, $s3, $s3	# Reg temporario $t1 = 2 * i	0x02734820
	add $t1, $t1, $t1	# Reg temporario $t1 = 4 * i	0x01294820
	add $t1, $t1, $s6	# $t1 =endereco de save[i]		0x01364820
	lw $t0, 0($t1)		# Reg temporario $t0 = save[i]		0x8d280000
	bne $t0, $s5, exit	# Desvia para exit se save[i] != k		0x15150006
loop:
	add $s3, $s3, $s4	# i = i + j						0x02749820
	add $t1, $s3, $s3	# Reg temporario $t1 = 2 * i	0x02734820
	add $t1, $t1, $t1	# Reg temporario $t1 = 4 * i	0x01294820
	add $t1, $t1, $s6	# $t1 =endereco de save[i]		0x01364820
	lw $t0, 0($t1)		# Reg temporario $t0 = save[i]	0x8d280000
	beq $t0, $s5, loop	# Desvia para loop se save[i] == k	0x1115fffa

# ***** conta as instrucoes ate aqui

exit:	li $v0, 10		# codigo da chamada de sistema EXIT
	syscall		# chamada de sist. setada em $v0
