=====================================================================================
ooooooooo.   oooooooooooo       .o.       oooooooooo.   ooo        ooooo oooooooooooo 
`888   `Y88. `888'     `8      .888.      `888'   `Y8b  `88.       .888' `888'     `8 
 888   .d88'  888             .8"888.      888      888  888b     d'888   888         
 888ooo88P'   888oooo8       .8' `888.     888      888  8 Y88. .P  888   888oooo8    
 888`88b.     888    "      .88ooo8888.    888      888  8  `888'   888   888    "    
 888  `88b.   888       o  .8'     `888.   888     d88'  8    Y     888   888       o 
o888o  o888o o888ooooood8 o88o     o8888o o888bood8P'   o8o        o888o o888ooooood8 
=====================================================================================

Olá! Este arquivo texto possui o intuito de se descutir um pouco sobre a compilação 
referente ao sistema desenvolvido como Trabalho 1 da disciplina Redes de Computadores
oferecida no semestre 1/2018 pelo ICMC/USP no curso de Bacharelado de Ciências de Com_
putação (BCC).

Toda a execução e funcionalidades encontram-se explicadas no arquivo ".pdf".
Dentro do ".zip", existe um arquivo Makefile que facilita a compilação e execução do 
programa.
Para executar pelo Makefile basta realizar as seguintes operações:

- Terminal/Console 1:
$ make srv & make runsrv

- Terminal/Console 2:
$ make srv & make runsrv

Para executar por linhas de comandos, sugere-se:

- Terminal/Console 1:
$ gcc server.c -o srv -Wall -lm -I.
$ ./srv

- Terminal/Console 2:
$ gcc client.c -o clt -Wall -lm -I.
$ ./clt

Todas as dependencias devem ser tratas e as bibliotecas necessárias instaladas.

Mais informações no ".pdf"!!!

Atenciosamente, o grupo.