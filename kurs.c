#define _USE_MATH_DEFINES
#include <GL/glut.h>
#include<math.h>
#include <time.h>
#include <stdlib.h>

int sec, min, hour, min_in_sec, hour_in_sec;

void DrawTickMarks(float x, float y, float r, float amount)
{
    float angle, rx, ry, i;

    glBegin(GL_POINTS);
        for (i = 0.0; i < amount; i++)
        {
            angle = 2.0 * M_PI * i / amount;
            rx = r * cos(angle);
            ry = r * sin(angle);
            glColor3f(0.0, 0.0, 0.0);
            glVertex2f(x + rx, y + ry);
        }
    glEnd();
}

void DrawCircle(float x, float y, float r, float amount)
{
    float angle, rx, ry, i;

    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
        for (i = 0.0; i < amount; i++)
        {
            angle = 2.0 * M_PI * i / amount;
            rx = r * cos(angle);
            ry = r * sin(angle);
            glColor3f(0.0, 0.0, 0.0);
            glVertex2f(x + rx, y + ry);
        }
    glEnd();
}

void DrawClockHands()
{
    float sec_x, sec_y, min_x, min_y, hour_x, hour_y, angle;

    angle = (90 - sec * 6) * M_PI / 180;
    sec_x = 130 * cos(angle);
    sec_y = 130 * sin(angle);

    glLineWidth(1);
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(sec_x, sec_y);
    glEnd();

    angle = (90 - min_in_sec * 6/60) * M_PI / 180;
    min_x = 130 * cos(angle);
    min_y = 130 * sin(angle);

    glLineWidth(2);
    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(min_x, min_y);
    glEnd();

    angle = (90 - hour_in_sec * 30/60/60) * M_PI / 180;
    hour_x = 90 * cos(angle);
    hour_y = 90 * sin(angle);

    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 0.0);
        glVertex2f(0.0, 0.0);
        glVertex2f(hour_x, hour_y);
    glEnd();

    sec++;
    min_in_sec++;
    hour_in_sec++;
}

void Drawing()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    DrawCircle(0, 0, 150, 50);
    glPointSize(6);
    DrawTickMarks(0, 0, 140, 12);
    glPointSize(2);
    DrawTickMarks(0, 0, 140, 60);
    DrawClockHands();

    glutSwapBuffers();
}

void Timer()
{
    glutPostRedisplay();
    glutTimerFunc(1000, Timer, 0);
}

void RotateKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case(GLUT_KEY_UP):
            glTranslatef(0, 10, 0);
            break;
        case(GLUT_KEY_DOWN):
            glTranslatef(0, -10, 0);
            break;
        case(GLUT_KEY_LEFT):
            glTranslatef(-10, 0, 0);
            break;
        case(GLUT_KEY_RIGHT):
            glTranslatef(10, 0, 0);
            break;
    }
}

void ScaleKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case('='):
            glScalef(1.1, 1.1, 1);
            break;
        case('-'):
            glScalef(0.9, 0.9, 1);
            break;
        case(' '):
            exit(EXIT_SUCCESS);
            break;
    }
}

int main(int argc, char** argv)
{
    time_t t = time(NULL);
    struct tm* now = localtime(&t);

    int h = now->tm_hour;
    min = now->tm_min;
    sec = now->tm_sec;
    if (h > 11) hour = h - 12; 
    else hour = h;
    min_in_sec = min * 60 + sec;
    hour_in_sec = hour * 60 * 60 + min * 60 + sec;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(500, 200);
    glutCreateWindow("Часы");

    glutDisplayFunc(Drawing);
    glutTimerFunc(1000, Timer, 0);
    glutSpecialFunc(RotateKeyboard);
    glutKeyboardFunc(ScaleKeyboard);

    glOrtho(-200.0, 200.0, -200.0, 200.0, -5.0, 5.0);
    glutMainLoop();

    return 0;
}