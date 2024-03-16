#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "soundlib.h"


#define refreshRate 100		//not really a refresh rate, but rather pause between refreshing
#define W 1500			//basic window width (I don't recommend changing it, rendering will break)
#define H 1000			//basic window height - " -


int lastTime = 0;		//lastRefresh it is needed for timer (refresh rate aka fps)
int mandelbrotMap[W][H];
int durations[W];

void renderScene(void);		//practically rendering
void idleFunction();		//refreshing
void generateMandelbrotSet(int[W][H]);
void genDur(int[W], int[W][H]);


struct complexNumber {
	double r;
	double i;
};



void resize(int width, int height) {
    // we ignore the params and do:
    glutReshapeWindow( W, H);	//always resizes window to the right state. Espesially needed on dwm, which I use. I use arch btw
}

int main(int argc, char** argv){
	//soundGen(200);
	generateMandelbrotSet(mandelbrotMap);
	genDur(durations, mandelbrotMap);
	glutInit(&argc, argv);						//guess
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);	//I have also no idea
	glutInitWindowPosition(100,100);
	glutInitWindowSize(W,H);
	glutCreateWindow("project");
	glutDisplayFunc(renderScene);	
	glutIdleFunc(idleFunction);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 1;
}

void 
generateMandelbrotSet(int map[W][H]){
	for (int x = 0; x < W; x++){
		for (int y = 0; y < H; y++){
		struct complexNumber num;
		num.r = (double)x / (double)W * 3 -2;
		num.i = (double)y / (double)H * 2 -1;
		//printf("%f %f\n", num.r, num.i);
		struct complexNumber z;
		z.r = 0;
		z.i = 0;
		for (int i = 1; i < 1000; i++){

			//printf("%f, %f \n",z.r, z.i);
			if (abs(z.i) + abs(z.r) > 2.5) {map[x][y] = i;break;}
			double im = z.i;
			//printf("%f\n", z.i);
			double re = z.r;
			z.r = -im*im + re*re + num.r;
			z.i = im*re + im*re + num.i;
		}
		//printf("%f %f\n", z.i-num.i, z.r-num.r);
		if (abs(z.i) + abs(z.r) <=2.5){
			map[x][y] = 0;
		}
	}}
}


void 
renderScene(void){
	//printf("change");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	float firstR = (float)rand()/2147483647.0f;
	float secondR = (float)rand()/2147483647.0f;
	float thirdR = (float)rand()/2147483647.0f;
	//printf("%f\n", firstR);
	for (int x = 0; x < W; x++){
		for (int y = 0; y < H; y++){		
			glBegin(GL_POINTS);
				if (mandelbrotMap[x][y] == 0){
					glColor3f(0.0f,0.0f,0.0f);
				} else {
					//printf("%d\n",mandelbrotMap[i][j]);
					glColor3f(0.5f,(float)mandelbrotMap[x][y]/20,(float)mandelbrotMap[x][y]/10);
				}
				//glColor3f((double)i/(double)W, (double)j/(double)H, 0.5f);
				glVertex2f((float)x/(float)W*2.0f-1,(float)y/(float)H*2.0f-1);
			glEnd();
		}
	}
	glutSwapBuffers(); 
}

void 
idleFunction(){
	int time = glutGet(GLUT_ELAPSED_TIME);
	int diff = time- lastTime;
	if (diff > refreshRate){
		glutPostRedisplay();
		lastTime = glutGet(GLUT_ELAPSED_TIME);
	}
	for (int x = 0; x < W; x += 10) for (int y = 0; y< H; y+= 10){
		if (!mandelbrotMap[x][y]){
			soundGen(30, durations[x]*5);
		}else{
			soundGen(mandelbrotMap[x][y]*100, durations[x]);
		}
	}
}


void 
genDur(int dst[W], int src[W][H])
{
	for (int x = 0; x < W; x++) {
		int counter = 0;
		for (int y = 0; y < H; y++){
			if (src[x][y] == 0){
				counter++;
			}
		}
		dst[x] = counter/H;
	}
}
