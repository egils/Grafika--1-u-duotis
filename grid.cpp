/**
 * Draws Bresenham's line on 32x32 grid.
 * Drawing windows size: 640x640. Window might be resized - grid not resizing.
 * 
 * To draw a line simply mouse-click grid cells where to start and end the line.
 */
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>

using namespace std;

#define zP 0
#define zL 0

static int point = 0;
static int x00, x10, y00, y10 = 0;

static int window_width = 640, window_height = 640;

void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D(0.0, window_width, 0.0, window_height);
        glPointSize(20.0);
}

void lineO2(int x0, int y0, int x1, int y1)
{
    bool steep = abs(y1-y0) > abs(x1-x0);
    if(steep)
    {
        swap(x0, y0);
        swap(x1,y1);
    }
    if (x0 > x1) 
    {
        swap(x0,x1);
        swap(y0,y1);
    }
    int deltax = x1-x0;
    int deltay = abs(y1 - y0);
    int error = deltax/2;
    int ystep;
    int y = y0;
    
    if (y0<y1)
    {
        ystep = 20;
    } else {
        ystep = -20;
    }
    
    for (int x = x0;x <= x1; x=x+20)
    {
        if(steep)
        {
            cout << "printing (" << y << ", " << x << ")" << endl;
            glVertex3i(y, x, zP);
        } else {
            cout << "printing (" << x << ", " << y << ")" << endl;
            glVertex3i(x, y, zP);
        }
        error -= deltay;
        if(error <= 0)
        {
            y += ystep;
            error += deltax;
        }
    }
    
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); 
    
    if(x00>0) {
        // White
        glColor3f(1.0, 1.0, 1.0);
        // Draw a pointed line
        glBegin(GL_POINTS);
            if(x00 <= x10) 
            {
                lineO2(x00,y00,x10,y10);
            } else {
                lineO2(x10,y10,x00,y00);
            }
        glEnd();
    }
    
    // Red
    glColor3f(1.0, 0.0, 0.0);
    // Draw grid
    glBegin(GL_LINES);
    for(int i = 0; i <= 640; i += 20)
    {
        glVertex3f((float)i, 0.0f, 1.0f);
        glVertex3f((float)i, 640.0f, 1.0f);
        glVertex3f(0.0f, (float)i, 1.0f);
        glVertex3f(640.0f, (float)i, 1.0f);
    }
    glEnd();
    glFlush();
}


void mouse(int bin, int state , int x , int y) {
    
    if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        y = window_height-y;
        switch(point) {
            case 0: 
                x00 = (int)floor(x/20)*20+10;
                y00 = (int)floor(y/20)*20+10;
                cout << x00 << " " << y00 << endl;
                point++;
                break;
            case 1:
                x10 = (int)floor(x/20)*20+10;
                y10 = (int)floor(y/20)*20+10;
                cout << x10 << " " << y10 << endl;
                point++;
                display();
                break;
            default:
                break;
        }
    }
}

void reshape (int w, int h)
{
    window_width = w;
    window_height = h;
}

int main(int argc,char *argv[])
{

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (640, 640);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Single Line on Mouse-Click points");
    glutMouseFunc(mouse);
    init2D(0.0,0.0,0.0);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return(0);
}

