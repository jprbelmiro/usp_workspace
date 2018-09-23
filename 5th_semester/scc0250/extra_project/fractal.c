#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#ifdef __linux__
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/freeglut.h>
#endif

//Inicialização de funções
void setZoom(); 
void keyPressEvent(unsigned char k, int x, int y);
void init();
void drawTriangle(GLfloat *f1, GLfloat *f2, GLfloat *f3);
void recursiveTriangle(GLfloat *f1, GLfloat *f2, GLfloat *f3,int deep);
void drawPyramid(GLfloat *f1, GLfloat *f2, GLfloat *f3, GLfloat *f4);
void fractal(GLfloat *f1, GLfloat *f2, GLfloat *f3, GLfloat *f4, int deep);
void display();
void timer(int t);

// Definicoes da Janela
int winw = 800;
int winh = 800;

// Variaveis de Transformacao
double angle = 0;
double increment = 1.5;
double zoom = 0;

//Numero de iteracoes
int deep = 7;
GLfloat pyramid[4][3] = {{-1.0, -1.0, -1.0},
                         { 1.0, -1.0, -1.0},
                         { 0.0, -1.0,  0.732},
                         { 0.0,  1.0, -0.134}};

//Função de zoom
void setZoom() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0 - zoom, 1.0 + zoom, -1.0 - zoom, 1.0 + zoom, -20.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    display();
}

// Função para capturar os eventos do teclado
void keyPressEvent(unsigned char key, int x, int y) {
    switch(key) {
        case '\x1b' :
            // Sai do programa se apertar ESC
            exit(0);
            break;
        case '.' :
            // Aumenta o passo do incremento
            increment++;
            break;
        case ',' :
            // Diminui o passo do incremento
            increment--;
            break;
        case 'i':
            // Zoom in
            if (zoom - 0.1 > -1) zoom -= 0.05;
            setZoom();
            break;
        case 'o':
            // Zoom out
            zoom += 0.05;
            setZoom();
            break;
        case 'a':
            deep = (deep+1) %10;
            break;
        case 'd':
            deep = (deep-1) %10;
            break;
    }
    
}

// Callback para inicializacao da tela
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -20.0, 20.0);
    glEnable(GL_DEPTH_TEST);
}

// Funcao para desenhar triangulo
void drawTriangle(GLfloat *f1, GLfloat *f2, GLfloat *f3){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); 
    glShadeModel(GL_SMOOTH); 
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    glVertex2fv(f1);
    glColor3f(1,1,1);
    glVertex2fv(f2);
    glColor3f(1,1,1);
    glVertex2fv(f3);
    glEnd();
}

// Funcao para calcular os triangulos recursivamente
void recursiveTriangle(GLfloat *f1, GLfloat *f2, GLfloat *f3, int deep){
    GLfloat midpoint[3][2];
     int nvertex;
     if (deep > 0) {

        //1. Calculando os pontos medios de cada aresta
        for (nvertex = 0; nvertex < 2; nvertex++) {
            midpoint[0][nvertex] = (f1[nvertex] + f2[nvertex]) / 2;
        }
        for (nvertex = 0; nvertex < 2; nvertex++) {
            midpoint[1][nvertex] = (f1[nvertex] + f3[nvertex]) / 2;
        }
        for (nvertex = 0; nvertex < 2; nvertex++) {
            midpoint[2][nvertex] = (f2[nvertex] + f3[nvertex]) / 2;
        }

        //2. Calculando recursivamente novos vertices
        recursiveTriangle(f1, midpoint[0], midpoint[1], deep-1);
        recursiveTriangle(midpoint[0], f2, midpoint[2], deep-1);
        recursiveTriangle(midpoint[1], midpoint[2], f3, deep-1);
    }
    else{
        drawTriangle(f1, f2, f3);
    }
}

// Funcao para desenhar piramide
void drawPyramid(GLfloat *f1, GLfloat *f2, GLfloat *f3, GLfloat *f4){
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);   
    glShadeModel(GL_SMOOTH);
    
    glBegin(GL_TRIANGLES);
        glColor3f(1,1,1);
        glVertex3fv(f1);
        glColor3f(1,1,1);
        glVertex3fv(f2);
        glColor3f(1,1,1);
        glVertex3fv(f3);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(1,1,1);
        glVertex3fv(f1);
        glColor3f(1,1,1);
        glVertex3fv(f2);
        glColor3f(1,1,1);
        glVertex3fv(f4);
    glEnd();

   glBegin(GL_TRIANGLES);
        glColor3f(1,1,1);
        glVertex3fv(f1);
        glColor3f(1,1,1);
        glVertex3fv(f3);
        glColor3f(1,1,1);
        glVertex3fv(f4);
    glEnd();

    glBegin(GL_TRIANGLES);
        glColor3f(1,1,1);
        glVertex3fv(f2);
        glColor3f(1,1,1);
        glVertex3fv(f3);
        glColor3f(1,1,1);
        glVertex3fv(f4);
    glEnd();

}

// Funcao de modelagem do fractal
void fractal(GLfloat *f1, GLfloat *f2, GLfloat *f3, GLfloat *f4, int deep){
    GLfloat midpoint[6][3];
     int nvertex;
     if (deep > 0) {

        //1. Calcular pontos médios de cada aresta
        for (nvertex = 0; nvertex < 3; nvertex++) {
            midpoint[0][nvertex] = (f1[nvertex] + f2[nvertex]) / 2;
        }
        for (nvertex = 0; nvertex < 3; nvertex++) {
            midpoint[1][nvertex] = (f1[nvertex] + f3[nvertex]) / 2;
        }
        for (nvertex = 0; nvertex < 3; nvertex++) {
            midpoint[2][nvertex] = (f2[nvertex] + f3[nvertex]) / 2;
        }
        for (nvertex = 0; nvertex < 3; nvertex++) {
            midpoint[3][nvertex] = (f1[nvertex] + f4[nvertex]) / 2;
        }
        for (nvertex = 0; nvertex < 3; nvertex++) {
            midpoint[4][nvertex] = (f2[nvertex] + f4[nvertex]) / 2;
        }
        for (nvertex = 0; nvertex < 3; nvertex++) {
            midpoint[5][nvertex] = (f3[nvertex] + f4[nvertex]) / 2;
        }

        //2. Calcular recursivamente novos vértices
        fractal(f1, midpoint[0], midpoint[1], midpoint[3], deep-1);
        fractal(midpoint[0], f2, midpoint[2], midpoint[4], deep-1);
        fractal(midpoint[1], midpoint[2], f3, midpoint[5], deep-1);
        fractal(midpoint[3], midpoint[4], midpoint[5], f4, deep-1);
        recursiveTriangle(midpoint[0], midpoint[1], midpoint[2], deep-1);
    }
    else{
        drawPyramid(f1, f2, f3, f4);
    }
}

// Função utizada na função de callback temporizada
void timer(int value) {
    angle += increment;
    display();
    glutTimerFunc(30, timer, 0);
}

// Funcao de Display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(angle, 0.1, 0.1,0.1);
    gluLookAt(0,0,0.5,0,0,0,0,1,0);
    fractal(pyramid[0], pyramid[1], pyramid[2], pyramid[3], deep);
    glPopMatrix();
    glFlush();
    glutPostRedisplay();
}

// Funcao pricipal
int main(int argc, char **argv){
	//1. Inicializando o GLUT
    glutInit(&argc, argv);
    glutInitWindowSize(winw, winh);
    glutCreateWindow("Fractal 3D");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyPressEvent);
    timer(0);
    glutMainLoop();

    //2. Isso eh tudo pessoal :) ...
    return 0;
}