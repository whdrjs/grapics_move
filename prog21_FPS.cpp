#include<glut.h>
#include<math.h>
#include<stdio.h>
#include<windows.h>
#define WIDTH 500
#define HEIGHT 500
#define PI  3.1415926
#define TURN 1
/*
* @author :김종건 201433676
*/
int theta = 0;
int delay = 10;
float eye[3], fo[3], up[3];// eye point , focus point  , up vector
float mX, mZ;
float vX=0, vZ=0;
void init()
{
	//initial camera point
	eye[0] = 0.0; eye[1] = 0.0, eye[2] = 2.0;
	fo[0] = 0; fo[1] = 0; fo[2] = 0;
	up[0] = 0; up[1] = 1; up[2] = 0;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();// load an identity matrix	

	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20.0);											//최적의 비율 에 근사하다고 생각

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);		//restore to model view
	glLoadIdentity();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();// load an identity matrix	

	gluLookAt(eye[0], eye[1], eye[2], fo[0], fo[1], fo[2], up[0], up[1], up[2]);
//start
{
		glPushMatrix();
		glColor3f(0.3, 0.7, 0.2);
		glTranslatef(0.2, 0.0, -0.4);
		glutWireCube(1.2);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.3, 0.4, 0.8);
		glutWireTeapot(0.3);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.8, 0.5, 0.6);
		glTranslatef(0.5, 0.5, -2.0);
		glutWireSphere(0.2, 10, 10);	//translatef가 wire 앞으로
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.0, 0.0, 0.5);
		glTranslatef(2.3, -0.3, 0.3);
		glutWireTeapot(0.3);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.3, 0.4, 0.5);
		glTranslatef(-0.7, -0.3, 0.6);
		glutWireCube(0.4);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.7, 0.0, 0.9);
		glTranslatef(0.0, 1.0, -25.0);
		glutWireSphere(1, 7.0, 7.0);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.0, 0.8, 1.0);
		glTranslatef(0.0, 1.0, 10.5);
		glutWireOctahedron();
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.8, 0.1, 0.0);
		glTranslatef(-30.0, -1.0, 13.5);
		glutWireIcosahedron();
		glPopMatrix();
}
Sleep(20);
glutSwapBuffers();
}

void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);//continuos
}

/*
* it doesn't need to point, it just chage to user(camera) position
*
*/
void keyboard_handler(unsigned char key, int x, int y)
{
	//front
	if (key == 'w')
	{
		fo[2] -= 0.1;
		eye[2] -= 0.1;
		//fo[0] += mX;
		//eye[0] += mX;
	}
	//back
	if (key == 's')
	{
		fo[2] += 0.1;
		eye[2] += 0.1;
		//fo[0] -= mX;
		//eye[0] -= mX;
	}
	//left
	if (key == 'a')
	{
		fo[0] -= 0.1;
		eye[0] -= 0.1;
		//fo[0] -= mX;
		//eye[0] -= mX;
	}
	//right
	if (key == 'd')
	{
		fo[0] += 0.1;
		eye[0] += 0.1;
		//fo[0] += mX;
		//eye[0] += mX;
	}
}

void mouse_handler(int x, int y) {
	vX = fo[0] - eye[0];
	vZ = fo[2] - eye[2];

	if (x - WIDTH > 0)
	{
		fo[0] = (eye[0]+ cos(TURN)*vX - sin(TURN)*vZ);
		fo[2] = (eye[2] + sin(TURN)*vX + cos(TURN)*vZ);
	}
	else
	{
		fo[0] = (eye[0] + cos(-TURN)*vX - sin(-TURN)*vZ);
		fo[2] = (eye[2] + sin(-TURN)*vX + cos(-TURN)*vZ);
	}

	mX = (float)x/5000.0;
	
	fo[1] += (250 - (float)y) / 5000.0;
	printf("%d %d\n", x, y);
	printf("%f %f\n", fo[0], fo[2]);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH,HEIGHT);
	glutInitWindowPosition(500, 50);
	glutCreateWindow("Prog21 : CAD");
	
	glutKeyboardFunc(keyboard_handler);

	glutDisplayFunc(display);
	glutMotionFunc(mouse_handler);	//Use glutMotionFunc to change whenever the mouse moves.

	glutTimerFunc(delay, timer, 0);//continuous change glutTimerFunc

	init();
	glutMainLoop();

	return 0;
}