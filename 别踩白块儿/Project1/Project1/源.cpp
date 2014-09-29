#include <GL/glut.h>
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")//去掉控制台
int day = 200;
void renderScene(void)  //渲染函数
{
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110, 1, 1, 40000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, -20000, 20000, 0, 0, 0, 0, 0, 1);

	// 绘制红色的“太阳”     
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidSphere(6960, 20, 20); // 绘制蓝色的“地球”     
	glColor3f(0.0f, 0.0f, 1.0f);
	
	glRotatef(day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(15000, 0.0f, 0.0f);
	glutSolidSphere(1594, 20, 20);// 绘制黄色的“月亮”     
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(3800, 0.0f, 0.0f);
	glutSolidSphere(434, 20, 20);
	
	glFlush();
	glutSwapBuffers();
}
void myIdle(void)
{
	++day;
	if (day >= 360)
		day = 0;
	renderScene();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("GLUT");
	glutDisplayFunc(renderScene);
	glutIdleFunc(myIdle);
	glutMainLoop();
	return 0;
}