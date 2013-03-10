#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <time.h>


using namespace std;

#define LOOP_COUNT 100000

// No optimization at all. Calculated on pure Math.round()
void lineNO(float x0, float y0, float x1, float y1)
{
    if((y1-y0) != 0) {
        int y;
        // Should print here
        for (int x=x0;x<=x1;x++)
        {
            y = (int)(((y1-y0)/(x1-x0))*(x-x0)+y0+0.5);
            // Should print here
        }
    }
}

// Simple Bresenham's integers solution
void lineO1(int x0, int y0, int x1, int y1)
{
    float dx = x1-x0;
    float dy = y1-y0;
    float error = 0.0;
    float derr = abs(dy/dx);
    int y = y0;
    
    
    for(int x=x0;x<=x1;x++) 
    {
        // Should print here
        error += derr;
        if(error >= 0.5)
        {
            y++;
            error--;
        }
    }
    
}

// Integers optimized Bresenham's
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
        ystep = 1;
    } else {
        ystep = -1;
    }
    
    for (int x = x0;x <= x1; x++)
    {
        // Should print here
        error -= deltay;
        if(error < 0)
        {
            y += ystep;
            error += deltax;
        }
    }
    
}


// Simplified Bresenham's
void lineSO(float x0, float y0, float x1, float y1)
{
    int sx, sy, err, err2;
    int dx = abs(x1-x0);
    int dy = abs(y1-y0); 
    
    if (x0 < x1) { sx = 1; } else { sx = -1; }
    if (y0 < y1) { sy = 1; } else { sy = -1; }
    err = dx-dy;
    // Should print here
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
        // Should print here
    }
    
}


int main(int argc,char *argv[])
{

    long double time;
    clock_t t_start, t_end;

    cout << "Times functions called: " << LOOP_COUNT << endl;
    
    // Round() function time diff
    t_start = clock();
    for(int i = 0;i < LOOP_COUNT; i++) 
    {
        lineNO(10,10,500,21);
    }
    t_end = clock();

    time = ((long double) t_end - t_start) / CLOCKS_PER_SEC;
    cout << "calculation with Math.round() time diff: " << time << endl;
    
    
    // Optimized function time diff
    t_start = clock();
    for(int i = 0;i < LOOP_COUNT; i++) 
    {
        lineO2(10,10,500,21);
    }
    t_end = clock();

    time = ((long double) t_end - t_start) / CLOCKS_PER_SEC;
    cout << "calculation with integers time diff: " << time << endl;
    
    return(0);
}