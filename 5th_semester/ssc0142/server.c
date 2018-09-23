// Server side C/C++ program to demonstrate Socket programming
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <regex.h>

#define X(a) (toupper(a[0]) - 'A')
#define Y(a) (a[1] - '0')

#define ENTER '\n'
#define NAME_SIZE 35
#define PIECE_SIZE 10
#define MOVE_SIZE 10
#define HALF_SEC 500000
#define ONE_SEC 1000000
#define THREE_SEC 3000000
#define PORT 8000


int match(char *str, char *pattern){
    int status;
    regex_t re;
    if(regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0)
        return 0;

    status = regexec(&re, str, (size_t) 0, NULL, 0);
    regfree(&re);

    if(status != 0)
        return 0;

    return 1;
}

char board[10][10];
int WHITE_PIECES = 21, BLACK_PIECES = 21;

void printboard(){
    printf("=================================================\n");
    printf("|     0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9     |\n");
    printf("|    =======================================    |\n");
    printf("| A | %c |   | %c |   | %c |   | %c |   | %c |   | A |\n",board[0][0],board[0][2],board[0][4],board[0][6],board[0][8]);
    printf("|   |---------------------------------------|   |\n");    
    printf("| B |   | %c |   | %c |   | %c |   | %c |   | %c | B |\n",board[1][1],board[1][3],board[1][5],board[1][7],board[1][9]); 
    printf("|   |---------------------------------------|   |\n");    
    printf("| C | %c |   | %c |   | %c |   | %c |   | %c |   | C |\n",board[2][0],board[2][2],board[2][4],board[2][6],board[2][8]);
    printf("|   |---------------------------------------|   |\n");    
    printf("| D |   | %c |   | %c |   | %c |   | %c |   | %c | D |\n",board[3][1],board[3][3],board[3][5],board[3][7],board[3][9]); 
    printf("|   |---------------------------------------|   |\n");    
    printf("| E | %c |   | %c |   | %c |   | %c |   | %c |   | E |\n",board[4][0],board[4][2],board[4][4],board[4][6],board[4][8]);
    printf("|   |---------------------------------------|   |\n");    
    printf("| F |   | %c |   | %c |   | %c |   | %c |   | %c | F |\n",board[5][1],board[5][3],board[5][5],board[5][7],board[5][9]); 
    printf("|   |---------------------------------------|   |\n");    
    printf("| G | %c |   | %c |   | %c |   | %c |   | %c |   | G |\n",board[6][0],board[6][2],board[6][4],board[6][6],board[6][8]);
    printf("|   |---------------------------------------|   |\n");   
    printf("| H |   | %c |   | %c |   | %c |   | %c |   | %c | H |\n",board[7][1],board[7][3],board[7][5],board[7][7],board[7][9]); 
    printf("|   |---------------------------------------|   |\n");                                                                                                                                                                                                   
    printf("| I | %c |   | %c |   | %c |   | %c |   | %c |   | I |\n",board[8][0],board[8][2],board[8][4],board[8][6],board[8][8]);
    printf("|   |---------------------------------------|   |\n");    
    printf("| J |   | %c |   | %c |   | %c |   | %c |   | %c | J |\n",board[9][1],board[9][3],board[9][5],board[9][7],board[9][9]);    
    printf("|    =======================================    |\n");
    printf("|     0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9     |\n");
    printf("=================================================\n");
    printf("| WHITE = %d             |           BLACK = %d |\n",WHITE_PIECES,BLACK_PIECES); 
    printf("=================================================\n\n"); 
    return;
}

void initializeboard(){
    int i, j;
    for(i = 0 ; i < 10 ; i++)
        for(j = 0 ; j < 10 ; j++)
            if(i % 2 == 0 && j % 2 == 0 && i < 4)
                board[i][j] = 'b';
            else if(i % 2 == 1 && j % 1 == 0 && i < 4)
                board[i][j] = 'b';
            else if(i % 2 == 0 && j % 2 == 0 && i > 5)
                board[i][j] = 'w';
            else if(i % 2 == 1 && j % 1 == 0 && i > 5)
                board[i][j] = 'w';
            else
                board[i][j] = ' ';
}

void lose(){
    printf("========================================================================================\n");
    printf("||                                                                 888                ||\n");   
    printf("||           ooooo          .oooooo.    .oooooo..o oooooooooooo   88888               ||\n"); 
    printf("||           `888'         d8P'  `Y8b  d8P'    `Y8 `888'     `8   '888'               ||\n"); 
    printf("||            888         888      888 Y88bo.       888            888                ||\n"); 
    printf("||            888         888      888  `8Y8888o.   888oooo8        Y                 ||\n"); 
    printf("||            888         888      888      `8Y88b  888    8                          ||\n"); 
    printf("||            888       o `88b    d88' oo     .d8P  888       o    888                ||\n"); 
    printf("||           o888ooooood8  `Y8bood8P'  8""88888P'  o888ooooood8    888                ||\n");       
    printf("========================================================================================\n\n");     
    return;
}

void win(){
    printf("========================================================================================\n");
    printf("||                                                                 888                ||\n");                                                                                                                   
    printf("||              oooooo   oooooo     oooo ooooo ooooo      ooo     88888               ||\n");  
    printf("||               `888.    `888.     .8'  `888' `888b.     `8'     '888'               ||\n");  
    printf("||                `888.   .8888.   .8'    888   8 `88b.    8       888                ||\n");  
    printf("||                 `888  .8'`888. .8'     888   8   `88b.  8        Y                 ||\n");  
    printf("||                  `888.8'  `888.8'      888   8     `88b.8                          ||\n");  
    printf("||                   `888'    `888'       888   8       `888       888                ||\n");  
    printf("||                    `8'      `8'       o888o o8o        `8       888                ||\n");      
    printf("========================================================================================\n\n");                                              
    return;
}

void letsstart(){
    printf("========================================================================================\n");
    printf("||         ooooo        oooooooooooo ooooooooooooo o8o  .oooooo..o                    ||\n");      
    printf("||         `888'        `888'     `8 8'   888   `8 `YP d8P'    `Y8                    ||\n");      
    printf("||          888          888              888       '  Y88bo.                         ||\n");      
    printf("||          888          888oooo8         888           `7Y8888o.                     ||\n");      
    printf("||          888          888    8         888               `8Y88b                    ||\n");      
    printf("||          888       o  888       o      888          oo     .d8P                    ||\n");      
    printf("||         o888ooooood8 o888ooooood8     o888o         88888888P'                     ||\n");
    printf("||                                                                             888    ||\n");                                                                                                                                                                                                     
    printf("||     .oooooo..o ooooooooooooo       .o.       ooooooooo.   ooooooooooooo    88888   ||\n");      
    printf("||    d8P'    `Y8 8'   888   `8      .888.      `888   `Y88. 8'   888   `8    '888'   ||\n");      
    printf("||    Y88bo.           888          .8'888.      888   .d88'      888          888    ||\n");      
    printf("||     `8Y8888o.       888         .8' `888.     888ooo88P'       888           Y     ||\n");  
    printf("||        `8Y88b       888        .88ooo8888.    888`88b.         888                 ||\n");     
    printf("||    oo     .d8P      888       .8'     `888.   888  `88b.       888          888    ||\n");      
    printf("||    88888888P'      o888o     o88o     o8888o o888o  o888o     o888o         888    ||\n");      
    printf("========================================================================================\n\n");
    initializeboard();                                                                                                                                                                                                         
    return;
}

void welcome(){
    printf("========================================================================================\n");
    printf("||           oooo                            oooo                                     ||\n");
    printf("||           `888                            `888                                     ||\n");
    printf("||  .ooooo.   888 .oo.    .ooooo.   .ooooo.   888  oooo   .ooooo.  oooo d8b  .oooo.o. ||\n");
    printf("|| d88' `YY8  888P8Y88b  d88' `88b d88' `8Y8  888 .8P'   d88' `88b `888''8P d88(  88  ||\n");
    printf("|| 888        888   888  888ooo888 888        888888.    888ooo888  888     `YY88b.   ||\n");
    printf("|| 888   .o8  888   888  888    .o 888   .o8  888 `88b.  888    .o  888     o.  )88b  ||\n");
    printf("|| `Y8bod8P' o888o o888o `Y8bod8P' `Y8bod8P' o888o o888o `Y8bod8P' d888b    888888P'  ||\n");
    printf("||                            Server Console Version                                  ||\n");
    printf("========================================================================================\n");
    printf("||            > PRESS ENTER TO CONECT TO THE SERVER AND PLAY !!! <                    ||\n");
    printf("========================================================================================\n");
    while(getc(stdin) != ENTER);
    return;
}

void owprintf(char *string, double wait_time){
    printf("\r%s",string);
    fflush( stdout );
    usleep(wait_time);
}

void flushprintf(char *string, double wait_time){
    printf("%s",string);
    fflush( stdout );
    usleep(wait_time);
}

int validmove(char *piece, char *move){
    int i, count = 0, move_flag = 0;
    if(board[X(move)][Y(move)] != ' '){
        printf(":: Invalid Move - Not Empty Space ::\n");
        return 0;
    }
            
    if(move[0] == piece[0] || move[1] == piece[1]){
        printf(":: Invalid Move - Line/Col Move ::\n");
        return 0;
    }
    
    if(board[X(piece)][Y(piece)] == 'w'){
        if(move[0] > (piece[0]+2) && move[0] < (piece[0]-2)){
            printf(":: Invalid Move - Out of Range - class 1 ::\n");
            return 0;
        }
        if(move[1] > (piece[1]+2) && move[1] < (piece[1]-2)){
            printf(":: Invalid Move - Out of Range - class 2 ::\n");
            return 0;
        }
        if(move[0] != (piece[0]-1) && move[0] != (piece[0]-2) && move[0] != (piece[0]+2)){
            printf(":: Invalid Move - Wrong Way ::\n");
            return 0;
        }
        if(move[0] == (piece[0]-2) && move[1] == (piece[1]+2)){
            if(toupper(board[X(piece)-1][Y(piece)+1]) != 'B'){
                printf(":: Invalid Move - Out of Range - class 3 ::\n");
                return 0;
            }
        }
        if(move[0] == (piece[0]-2) && move[1] == (piece[1]-2)){
            if(toupper(board[X(piece)-1][Y(piece)-1]) != 'B'){
                printf(":: Invalid Move - Out of Range - class 4 ::\n");
                return 0;
            }
        }
        if(move[0] == (piece[0]+2) && move[1] == (piece[1]+2)){
            if(toupper(board[X(piece)+1][Y(piece)+1]) != 'B'){
                printf(":: Invalid Move - Out of Range - class 5 ::\n");
                return 0;
            }
        }
        if(move[0] == (piece[0]+2) && move[1] == (piece[1]-2)){
            if(toupper(board[X(piece)+1][Y(piece)-1]) != 'B'){
                printf(":: Invalid Move - Out of Range - class 6 ::\n");
                return 0;
            }
        }
        if((move[0] + move[1] - piece[0] - piece[1]) % 2 != 0){
            printf(":: Invalid Move - Not Diagonal Move ::\n");
            return 0;
        }
                
        move_flag = 1;
    }
    else{
            
        for(i = 1 ; i < 10 && !move_flag && move[0]-'A'+i < 10 && move[1]-'A'+i < 10 ; i++){
            if(move[0]+i == piece[0] && move[1]+i == piece[1]){
                move_flag = 1;
                break;
            }
            if(toupper(board[X(move)+i][Y(move)+i]) == 'W'){
                break;
            }
            if(toupper(board[X(move)+i][Y(move)+i]) == 'B'){
                count++;
            }
        }
                
        for(i = 1 ; i < 10 && !move_flag && move[0]-'A'-i >= 0 && move[1]-'0'-i >= 0 ; i++){
            if(move[0]-i == piece[0] && move[1]-i == piece[1]){
                move_flag = 1;
                break;
            }
            if(toupper(board[X(move)-i][Y(move)-i]) == 'W'){
                break;
            }
            if(toupper(board[X(move)-i][Y(move)-i]) == 'B'){
                count++;
            }
        }
        
        for(i = 1 ; i < 10 && !move_flag && move[0]-'A'-i >= 0 && move[1]-'0'+i < 10 ; i++){
            if(move[0]-i == piece[0] && move[1]+i == piece[1]){
                move_flag = 1;
                break;
            }
            if(toupper(board[X(move)-i][Y(move)+i]) == 'W'){
                break;
            }
            if(toupper(board[X(move)-i][Y(move)+i]) == 'B'){
                count++;
            }
        }
        
        for(i = 1 ; i < 10 && !move_flag && move[0]-'A'+i < 10 && move[1]-'0'-i >= 0 ; i++){
            if(move[0]+i == piece[0] && move[1]-i == piece[1]){
                move_flag = 1;
                break;
            }
            if(toupper(board[X(move)+i][Y(move)-i]) == 'W'){
                break;
            }
            if(toupper(board[X(move)+i][Y(move)-i]) == 'B'){
                count++;
            }
        }
        
        if(move_flag == 0)
            printf(":: Invalid Move - Not Diagonal Move ::\n");
        else if(count > 2){
            printf(":: Invalid Move - Many Pieces on the Way (%d)::\n",count);
            move_flag = 0;
        }
    }
    return move_flag;
}

struct sockaddr_in createUDPSockserver(int *server_fd){
    //0. Variables
    struct sockaddr_in address;
    int opt = 1, addrlen = sizeof(address);

    printf("========================================================================================\n");
    owprintf("|| Conecting...                                                                       ||",HALF_SEC);
    owprintf("|| Conecting.                                                                         ||",HALF_SEC);
    owprintf("|| Conecting..                                                                        ||",HALF_SEC);
    owprintf("|| Conecting...                                                                       ||\n",HALF_SEC);

    //1. Creating socket file descriptor (SERVER SOCKET)
    if(((*server_fd) = socket(AF_INET, SOCK_DGRAM, 0)) == 0){
        perror("1. socket not created (FAIL D:)\n");
        exit(EXIT_FAILURE);
    }
    flushprintf("||  Socket created     ",HALF_SEC);

    //2. Attaching socket to the port
    if(setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR | SO_BROADCAST, &opt, sizeof(opt))){
        perror("2. socket not attached (FAIL)\n");
        exit(EXIT_FAILURE);
    }
    flushprintf("Socket Attached     ",HALF_SEC);

    //3. Defining the address
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    flushprintf("Address Defined     ",HALF_SEC);

    //4. Forcefully attaching socket to the port
    if(bind(*server_fd, (struct sockaddr *)&address, addrlen)<0){
        perror("4. bind failed (FAIL)\n");
        exit(EXIT_FAILURE);
    }
    flushprintf("Socket Binded          ||\n",ONE_SEC);

    printf("|| Conected !!!                                                                       ||\n");
    printf("========================================================================================\n");
    //5. Returning server fd
    return address;
}

int main(int argc, char const **argv){
    //0. Variables
    int winner = 0, turn = 0;
    char player[NAME_SIZE], opponent[NAME_SIZE], op_turn[10], pl_turn[10];
    char piece[PIECE_SIZE] = "", move[MOVE_SIZE] = "";

    int server_fd, msg_flag, sent_flag;
    struct sockaddr_in address_s, address_c;
    socklen_t address_c_len = sizeof(address_c);

    //1. Entering in game server
    welcome();
    address_s = createUDPSockserver(&server_fd);
    if(address_s.sin_port != htons(PORT)){
        printf("> There was an error... shutting down the system.\n");
        return 0;
    }

    //2. Choosing your name
    printf("========================================================================================\n");
    printf("> What is your name? R: "); scanf("%s",(char *)&player);
    printf("========================================================================================\n");
    flushprintf("> Looking for an opponent connection...\n",HALF_SEC);

    //3. Sending the ready info
    //sendto server the message with len and dont wait the confirmation of address with this size
    if ((msg_flag = recvfrom(server_fd, (void *)opponent,NAME_SIZE,MSG_WAITALL,(struct sockaddr * restrict)&address_c,&address_c_len)) < 0){
        perror("> There was an error in recvfrom... shutting down the system.");
        exit(EXIT_FAILURE);
    }

    //4. Waiting for an opponent
    //recvfrom server a message and store in buffer with size BUFFER_SIZE and wait all dependencies from address with len
    flushprintf("> Opponents are online! Waiting for your opponent.\n",HALF_SEC);
    sent_flag = sendto(server_fd ,player,NAME_SIZE,MSG_CONFIRM,(const struct sockaddr *)&address_c,address_c_len);
    if(sent_flag < 0){
        printf("> There was an error... shutting down the system.\n");
        return 0;
    }
    if((msg_flag = recvfrom(server_fd, (void *)opponent,NAME_SIZE,MSG_WAITALL,(struct sockaddr * restrict)&address_c,&address_c_len)) < 0){
        perror("> There was an error in recvfrom... shutting down the system.");
        exit(EXIT_FAILURE);
    }
    
    printf("> Your opponent will be %s. Good Lucky, Mr(s) %s...\n\n\t\t\t",opponent,player);
    fflush( stdout );
    usleep(THREE_SEC);
    flushprintf("3",ONE_SEC);
    owprintf("\t\t\t2",ONE_SEC);
    owprintf("\t\t\t1\n",ONE_SEC);

    //5. LETS GET STARTED!!
    letsstart();
    usleep(ONE_SEC);
    printboard();
    while(!winner){
        //a. PLAYER TURN
        piece[0] = '\0';
        move[0] = '\0';
        turn = 0;
        pl_turn[0] = 'N'; pl_turn[1] = '\0';
        while(match((char *)pl_turn,"^[Nn][Oo]*$")){
            if(turn == 0){
                //i. reading the play
                printf("Your turn! Choose the piece (WHITE) and the movement.\n");
                printf("> Write the piece and the move coordinate, respectively (letter-number)\n");
                printf("> Exemple: G0 F1\n");
                while(strcmp(piece,"") == 0 && strcmp(move,"") == 0){
                    scanf("%s %s",(char *)&piece,(char *)&move);
                    if(!match((char *)piece,"^[a-jA-J][0-9]$") || !match((char *)move,"^[a-jA-J][0-9]$")){
                        printf(":: Invalid Command. Write the piece and the move coordinate, respectively (letter-number)::\n");
                        piece[0] = '\0';
                        move[0] = '\0';
                    }
                    else if(toupper(board[toupper(piece[0])-'A'][piece[1]-'0']) != 'W'){
                        printf(":: Invalid Piece Coordinate. ::\n");
                        piece[0] = '\0';
                        move[0] = '\0';
                    }
                    else if(!validmove((char *)piece,(char *)move)){
                        piece[0] = '\0';
                        move[0] = '\0';
                    }
                }

                //ii. sending the informations to the opponent
                sent_flag = sendto(server_fd ,piece,PIECE_SIZE,MSG_CONFIRM,(const struct sockaddr *)&address_c,address_c_len);
                if(sent_flag < 0){
                    printf("> There was an error... shutting down the system.\n");
                    return 0;
                }
                sent_flag = sendto(server_fd ,move,MOVE_SIZE,MSG_CONFIRM,(const struct sockaddr *)&address_c,address_c_len);
                if(sent_flag < 0){
                    printf("> There was an error... shutting down the system.\n");
                    return 0;
                }

                //iii. updating and printing the board
                if(X(move) == 0)
                    board[X(move)][Y(move)] = toupper(board[X(piece)][Y(piece)]);
                else
                    board[X(move)][Y(move)] = board[X(piece)][Y(piece)];

                while(X(piece) != X(move) && Y(piece) != Y(move)){
                    if(toupper(board[X(piece)][Y(piece)]) == 'B')
                        BLACK_PIECES--;

                    if(X(piece) < X(move) && Y(piece) < Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]++;piece[1]++;
                    }
                    if(X(piece) > X(move) && Y(piece) > Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]--;piece[1]--;
                    }
                    
                    if(X(piece) > X(move) && Y(piece) < Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]--;piece[1]++;
                    }
                    if(X(piece) < X(move) && Y(piece) > Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]++;piece[1]--;
                    }
                }
                printboard();
            }
            else{
                //i. reading the play
                printf("Additional Move No %d. (Insert the move for piece %s)\n",turn,piece);
                printf("> To cancel the operation write EXIT.\n");
                while(strcmp(move,"") == 0){
                    scanf("%s",(char *)&move);
                    if(match((char *)move,"^[Ee][Xx][Ii][Tt]$"))
                        break;
                    if(!match((char *)move,"^[a-jA-J][0-9]$")){
                        printf(":: Invalid Move. Write the move coordinate (letter-number)::\n");
                        move[0] = '\0';
                    }
                    else if(!validmove((char *)piece,(char *)move)){
                        move[0] = '\0';
                    }
                }

                //ii. verifying the exit condition
                if(match((char *)move,"^[Ee][Xx][Ii][Tt]$")){
                    sent_flag = sendto(server_fd ,move,MOVE_SIZE,MSG_CONFIRM,(const struct sockaddr *)&address_c,address_c_len);
                    if(sent_flag < 0){
                        printf("> There was an error... shutting down the system.\n");
                        return 0;
                    }
                    break;            
                }          

                //iii. sending the information to the opponent
                sent_flag = sendto(server_fd ,move,MOVE_SIZE,MSG_CONFIRM,(const struct sockaddr *)&address_c,address_c_len);
                if(sent_flag < 0){
                    printf("> There was an error... shutting down the system.\n");
                    return 0;
                }

                //iii. updating and printing the board
                if(X(move) == 0)
                    board[X(move)][Y(move)] = toupper(board[X(piece)][Y(piece)]);
                else
                    board[X(move)][Y(move)] = board[X(piece)][Y(piece)];

                while(X(piece) != X(move) && Y(piece) != Y(move)){
                    if(toupper(board[X(piece)][Y(piece)]) == 'B')
                        BLACK_PIECES--;

                    if(X(piece) < X(move) && Y(piece) < Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]++;piece[1]++;
                    }
                    if(X(piece) > X(move) && Y(piece) > Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]--;piece[1]--;
                    }
                    
                    if(X(piece) > X(move) && Y(piece) < Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]--;piece[1]++;
                    }
                    if(X(piece) < X(move) && Y(piece) > Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]++;piece[1]--;
                    }
                }
                printboard();
            }

            //iv. sending the turn info to the opponent
            pl_turn[0] = '\0';
            while(!match((char *)pl_turn,"^[Yy][Ee]*[Ss]*$") && !match((char *)pl_turn,"^[Nn][Oo]*$")){
                printf("Did you finish your turn (Y/N), %s? > ",player);
                scanf("%s",(char *)&pl_turn);
            }
            sent_flag = sendto(server_fd ,pl_turn,10,MSG_CONFIRM,(const struct sockaddr *)&address_c,address_c_len);
            if(sent_flag < 0){
                printf("> There was an error... shutting down the system.\n");
                return 0;
            }
            if(match((char *)pl_turn,"^[Nn][Oo]*$")){
                piece[0] = move[0];
                piece[1] = move[1];
                piece[2] = '\0';
                move[0] = '\0';
                turn++;
            }
        }

        //a. OPPONENT TURN
        turn = 0;
        op_turn[0] = 'N'; op_turn[1] = '\0';
        while(match((char *)op_turn,"^[Nn][Oo]*$")){
            printf("Opponent's turn. Waiting for him to play.\n");
            if(turn == 0){
                //i. receiving the piece
                if((msg_flag = recvfrom(server_fd, (void *)piece,PIECE_SIZE,MSG_WAITALL,(struct sockaddr *)&address_c,&address_c_len)) < 0){
                    perror("> There was an error in recvfrom... shutting down the system.");
                    exit(EXIT_FAILURE);
                }
                //ii. receiving the move
                if((msg_flag = recvfrom(server_fd, (void *)move,MOVE_SIZE,MSG_WAITALL,(struct sockaddr *)&address_c,&address_c_len)) < 0){
                    perror("> There was an error in recvfrom... shutting down the system.");
                    exit(EXIT_FAILURE);
                }
                printf("Opponent's Move: %s %s\n",piece,move);
                
                //iii. updating and printing the board
                board[X(move)][Y(move)] = board[X(piece)][Y(piece)];
                while(X(piece) != X(move) && Y(piece) != Y(move)){
                    if(toupper(board[X(piece)][Y(piece)]) == 'W')
                        WHITE_PIECES--;
                    if(X(piece) < X(move) && Y(piece) < Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]++;piece[1]++;
                    }
                    if(X(piece) > X(move) && Y(piece) > Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]--;piece[1]--;
                    }
                    
                    if(X(piece) > X(move) && Y(piece) < Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]--;piece[1]++;
                    }
                    if(X(piece) < X(move) && Y(piece) > Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]++;piece[1]--;
                    }
                }
                printboard();
            }
            else{
                //i. receiving the move
                if((msg_flag = recvfrom(server_fd, (void *)move,MOVE_SIZE,MSG_WAITALL,(struct sockaddr *)&address_c,&address_c_len)) < 0){
                    perror("> There was an error in recvfrom... shutting down the system.");
                    exit(EXIT_FAILURE);
                }

                //ii. verifying the exit condition
                if(match((char *)move,"^[Ee][Xx][Ii][Tt]$"))
                    break;            
                

                printf("Opponent's Move: %s %s\n",piece,move);
                
                //iii. updating and printing the board
                board[X(move)][Y(move)] = board[X(piece)][Y(piece)];
                while(X(piece) != X(move) && Y(piece) != Y(move)){
                    if(toupper(board[X(piece)][Y(piece)]) == 'W')
                        WHITE_PIECES--;
                    if(X(piece) < X(move) && Y(piece) < Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]++;piece[1]++;
                    }
                    if(X(piece) > X(move) && Y(piece) > Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]--;piece[1]--;
                    }
                    
                    if(X(piece) > X(move) && Y(piece) < Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]--;piece[1]++;
                    }
                    if(X(piece) < X(move) && Y(piece) > Y(move)){
                        board[X(piece)][Y(piece)] = ' ';
                        piece[0]++;piece[1]--;
                    }
                }
                printboard();
            }

            //iv. receiving the turn info
            if((msg_flag = recvfrom(server_fd, (void *)op_turn,10,MSG_WAITALL,(struct sockaddr *)&address_c,&address_c_len)) < 0){
                perror("> There was an error in recvfrom... shutting down the system.");
                exit(EXIT_FAILURE);
            }
            piece[0] = move[0];
            piece[1] = move[1];
            piece[2] = '\0';
            move[0] = '\0';
            turn++;
        }

        //e. Verifying if the game finishes and reseting the variables
        if(WHITE_PIECES == 0 || BLACK_PIECES == 0)
            winner = (BLACK_PIECES == 0)?(1):(2);
    }

    //6. Printing the result
    if(winner == 1)
        win();
    else
        lose();

    //7. That's all folks :) ....
    return 0;
}