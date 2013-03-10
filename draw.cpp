/**
 * Draws line on various algorithms.
 * Drawing windows size: 640x640. Window should not be resized - algorithmic line do not recalculate.
 * 
 * To draw lines simply mouse-click on drawing window where to start and end the lines.
 * 
 * Function calls and algorithms they use:
 *      - lineNO(): Not optimized line; iterates x and calculate y on pure math. Uses Math.round().
 *      - lineO1(): Standard Bresenham's algorithm with floats.
 *      - lineO2(): Optimized Bresenham's algorithm with integers and steep.
 *      - LineSO(): Simplified Bresenham's algorithm. Works slow.
 */
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#include <time.h>


using namespace std;

#define zP 0 // Pointed line Z-coord
#define zL 1 // OpenGL line Z-coord

static int point = 0;
static int x00, x10, y00, y10 = 0;

void init2D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);  
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D(0.0, 640.0, 0.0, 640.0);
        glDisable(GL_POINT_SMOOTH);
}

void lineNO(float x0, float y0, float x1, float y1)
{
    if((y1-y0) != 0) {
        int y;
        for (int x=x0;x<=x1;x++)
        {
            y = (int)(((y1-y0)/(x1-x0))*(x-x0)+y0+0.5);
            glVertex3i(x, y, zP);
        }
    }
}

void lineO1(int x0, int y0, int x1, int y1)
{
    float dx = x1-x0;
    float dy = y1-y0;
    float error = 0.0;
    float derr = abs(dy/dx);
    int y = y0;
    
    for(int x=x0;x<=x1;x++) 
    {
        glVertex3i(x, y, zP);
        
        error += derr;
        if(error >= 0.5)
        {
            y++;
            error--;
        }
    }
}

void lineO2(int x0, int y0, int x1, int y1)
{
    bool steep = abs(y1-y0) > abs(x1-x0);
    if(steep)
    {
        swap(x0,y0);
        swap(x1,y1);
    }
    if (x0 > x1) 
    {
        swap(x0,x1);
        swap(y0,y1);
    }
    int deltax = x1-x0;
    int deltay = abs(y1 - y0);
    int error = (int)(deltax/2);
    int ystep;
    int y = y0;
    
    if (y0<y1)
    {
        ystep = 1;
    } else {
        ystep = -1;
    }
    
    for (int x = x0;x <= x1; x++)
    {
        if(steep)
        {
            glVertex3i(y, x, zP);
        } else {
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


void lineSO(float x0, float y0, float x1, float y1)
{
    int sx, sy, err, err2;
    int dx = abs(x1-x0);
    int dy = abs(y1-y0); 
    
    if (x0 < x1) { sx = 1; } else { sx = -1; }
    if (y0 < y1) { sy = 1; } else { sy = -1; }
    err = dx-dy;
    glVertex3i(x0, y0, zP);
    while (x0 != x1 && y0 != y1) 
    {
        err2 = 2*err;
        if (err2 > -1*dy) 
        {
            err -= dy;
            x0 += sx;
        };
        if (err2 < dx) 
        {
            err += dx;
            y0 += sy;
        };
        glVertex3i(x0, y0, zP);
    }
    
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
        if(x00 > 0) 
        {
            // Red
            glColor3f(1.0, 0.0, 0.0);
            // Draw a GL line
            glBegin(GL_LINES);
                glVertex3i(x00,y00, zL);
                glVertex3i(x10,y10, zL);
            glEnd();
        
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
        glFlush();
}

void mouse(int bin, int state , int x , int y) {
    
    if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
    {
        
        y = 640-y;
        switch(point) {
            case 0: 
                cout << x << " " << y << endl;
                x00 = x;
                y00 = y;
                point++;
                break;
            case 1:
                cout << x << " " << y << endl;
                x10 = x;
                y10 = y;
                point++;
                display();
                break;
            default:
                break;
        }
    }
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (640, 640);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Line");
    glutMouseFunc(mouse);
    init2D(0.0,0.0,0.0);
    glEnable (GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutMainLoop();
    
    return(0);
}