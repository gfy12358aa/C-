#include"Star.h"
SolarSystem sys;
int timecc = 1;
void timeadd() { timecc++; }
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //背景黑色
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0); //画笔白色
	glLoadIdentity();  //加载单位矩阵
	gluLookAt(sys.viewX, sys.viewY, sys.viewZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	sys.onDisplay(timecc);
	glutSwapBuffers();
	timeadd();
	Sleep(50);
}
void KeyBoards(unsigned char key, int x, int y);
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void myidle(void);

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(KeyBoards);
	glutIdleFunc(myidle);//闲置调用
	glutMainLoop();
	return 0;
}

void myidle(void)
{
	glutPostRedisplay();//重画，相当于重新调用Display(),改编后的变量得以传给绘制函数
}
void KeyBoards(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		glFlush();

		break;
	}
} 
