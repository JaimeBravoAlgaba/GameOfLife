#include <windows.h>
#include "..\libs\GLUT\include\GL\glut.h"
#include <new>
#include <stdlib.h>
#include <time.h>

#define XLIM 1280
#define YLIM 640
#define PIXEL 10
#define PROB 3
#define NX  (XLIM/PIXEL)
#define NY  (YLIM/PIXEL)

#define FRAMERATE 16

int **mat1, **mat2;

void inicio(){
	srand(time(NULL));
	int i, j;
	mat1 = new int*[NX];
	mat2 = new int*[NX];
	
	for(i=0; i<NX; ++i){
		mat1[i] = new int[NY];
		mat2[i] = new int[NY];
	}

	for(i=0; i<NX; ++i){
		for(j=0; j<NY; ++j){
			mat1[i][j] = PROB>(int)(rand()%10);
			mat2[i][j] = 0;
		}
	}

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, XLIM, 0, YLIM);           //Establece el sistema de coordenadas.
    glClearColor(0.0, 0.0, 0.0, 0.0);   //Establece el color RGB de fondo.
}

int sobrevive(int x, int y){
	int i, j;
	int aux = 0;
	if(!x || !y || (x==NX-1) || (y== NY-1)){
		return 0;
	}
	else{
		for(i=x-1; i<=x+1; ++i){
			for(j=y-1; j<=y+1; ++j){
				aux+=mat1[i][j];		
			}
		}
		aux-=mat1[x][y];
		aux = (mat1[x][y]) ? ((aux == 2)||(aux == 3)) :(aux == 3);
		return aux;
	}
}

void pantalla(){
	int i, j;
    glClear(GL_COLOR_BUFFER_BIT);

	for(i=0; i<NX; ++i){
		for(j=0; j<NY; ++j){			
			glPointSize(PIXEL);
			glColor3f(mat1[i][j], mat1[i][j], mat1[i][j]);
			glBegin(GL_POINTS);
				glVertex2f(i*PIXEL+PIXEL/2.0, j*PIXEL+PIXEL/2.0);
			glEnd();
		}
	}
	
	for(i=0; i<NX; ++i){
		for(j=0; j<NY; ++j){
			mat2[i][j] = sobrevive(i, j);		
		}
	}

    glutSwapBuffers();
}

void swap(){
	int **tmp;
	tmp  = mat1;
	mat1 = mat2;
	mat2 = tmp;
}

void timer(int){
	pantalla();
	swap();
	glutTimerFunc(FRAMERATE, timer, 0);
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(XLIM,YLIM);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("Game Of Life");    //Crea la ventana con su título.
    inicio();
    glutDisplayFunc(pantalla);
	timer(0);
    glutMainLoop();

    return EXIT_SUCCESS;
}
