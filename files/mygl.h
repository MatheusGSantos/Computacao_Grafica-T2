#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
class Pixel
{
public:
    int x, y;
    int RGBA[4];
    Pixel(){};

    Pixel(int x, int y, int color[4])
    {
        this->x = x;
        this->y = y;
        RGBA[0] = color[0];
        RGBA[1] = color[1];
        RGBA[2] = color[2];
        RGBA[3] = color[3];
    }
    ~Pixel()
    {}

    void PutPixel()
    {
        FBptr[y*IMAGE_WIDTH*4 + 4*x+0] = RGBA[0];
        FBptr[y*IMAGE_WIDTH*4 + 4*x+1] = RGBA[1];
        FBptr[y*IMAGE_WIDTH*4 + 4*x+2] = RGBA[2];
        FBptr[y*IMAGE_WIDTH*4 + 4*x+3] = RGBA[3];
    }
};

void Interpol(Pixel start, Pixel finish, Pixel *current, float distT)
{
    int dx = finish.x - current->x;
    int dy = finish.y - current->y;
    float distP = sqrt(pow(dx,2) + pow(dy,2));
    float p = distP/distT;
    float scolor, fcolor;

    for(size_t i = 0; i < 4; i++)
    {
        scolor = start.RGBA[i] * p;
        fcolor = finish.RGBA[i] * (1-p);
        current->RGBA[i] = scolor + fcolor;
    }
    
}



void DrawLine(Pixel pInicial, Pixel pFinal)
{
    int dx = pFinal.x - pInicial.x;
    int dy = pFinal.y - pInicial.y;

    int incr_y = 1, incr_x = 1;
    float distTotal = sqrt(pow(dx,2) + pow(dy,2));

    Pixel currentPixel = pInicial;
    currentPixel.PutPixel();
    
    if (dx < 0) //3rd,4th,5th,6th octants
    {
        DrawLine(pFinal,pInicial);  //swap start and end
    }
    else 
    {
        if (dy < 0)
        {
            incr_y = -1; 
            dy = -dy;                   
        }
        
        if(abs(dy) == abs(dx))  //diagonal line
        {  
            while(currentPixel.x < pFinal.x){
                currentPixel.x += incr_x;
                currentPixel.y += incr_y;
                Interpol(pInicial,pFinal,&currentPixel,distTotal);
                currentPixel.PutPixel();
            }
        }
        else if (dy == 0)   //line in the x axis
        {
            while(currentPixel.x < pFinal.x){
                currentPixel.x += incr_x;
                Interpol(pInicial,pFinal,&currentPixel,distTotal);
                currentPixel.PutPixel();
            }
        }
        else if (dx == 0)   //line in the y axis
        {
            while(1)
            {
                if (currentPixel.y == pFinal.y) {
                    break;
                }
                currentPixel.y += incr_y;
                Interpol(pInicial,pFinal,&currentPixel,distTotal);
                currentPixel.PutPixel();
            }   
        }
        else if(abs(dx) > abs(dy))   //1st and 8th octants
        {
            int d = 2 * dy - dx;
            int incr_e = 2 * dy;
            int incr_ne = 2 * (dy - dx);

            while(currentPixel.x < pFinal.x)
            {
                if(d <= 0)
                {
                    d += incr_e;
                }
                else
                {
                    d += incr_ne;
                    currentPixel.y += incr_y;
                }
                currentPixel.x += incr_x;
                Interpol(pInicial,pFinal,&currentPixel,distTotal);
                currentPixel.PutPixel();
            }
        }
        else    //2nd and 7th octants
        {
            int d = 2 * dx - dy;
            int incr_e = 2 * dx;
            int incr_ne = 2 * (dx - dy);
            if ((pFinal.y - pInicial.y) < 0)     //7th octant
            {
                while(currentPixel.y > pFinal.y)
                {
                    if(d <= 0)
                    {
                        d += incr_e;
                    }
                    else
                    {
                        d += incr_ne;
                        currentPixel.x += incr_x;
                    }
                    currentPixel.y += incr_y;
                    Interpol(pInicial,pFinal,&currentPixel,distTotal);
                    currentPixel.PutPixel();
                }
            }
            else    //2nd octant
            {
                while(currentPixel.y < pFinal.y)
                {
                    if(d <= 0)
                    {
                        d += incr_e;
                    }
                    else
                    {
                        d += incr_ne;
                        currentPixel.x += incr_x;
                    }
                    currentPixel.y += incr_y;
                    Interpol(pInicial,pFinal,&currentPixel,distTotal);
                    currentPixel.PutPixel();
                }
            }
        }
    }
}


void M_init()
{
	scale = translation = rotation = Identity;
}


void setScale_M(int sx, int sy, int sz)
{
	scale[0][0]=sx;
	scale[1][1]=sy;
	scale[2][2]=sz;
}


void setTranslation_M(int tx, int ty, int tz)
{
	translation[3][0]=tx;
	translation[3][1]=ty;
	translation[3][2]=tz;
}


void setRotation_M(const char axis, const float theta)
{
	rotation = Identity;	
	switch(axis){
		case x:
			rotation[1][1]=cos(theta);
			rotation[1][2]=sen(theta);
			rotation[2][1]=-sen(theta);
			rotation[2][2]=cos(theta);
			break;
		case y:
			rotation[0][0]=cos(theta);
			rotation[0][2]=-sen(theta);
			rotation[2][0]=sen(theta);
			rotation[2][2]=cos(theta);
			break;
		case z:
			rotation[0][0]=cos(theta);
			rotation[0][1]=sen(theta);
			rotation[1][0]=-sen(theta);
			rotation[1][1]=cos(theta);
			break;
		default:
			std::cout << "Invalid axis value. Try again.\n";
			exit(-1);
	}
}


void buildViewPort(int w, int h)
{
	setScale_M(w/2,h/2,1);
	viewport = scale;
	setScale_M(1,-1,1);
	setTranslation_M(1,1,0);
	viewport *= translate*scale;
}


void DrawPipeline(glm::vec3 const &p)
{
	M_init();	
	glm::vec4 pix = glm::vec4(p.x,p.y,p.z,1);
	pix = ModelViewProjection*pix;
	pix = pix / pix[4];
	pix = viewport*pix;
}


class Triangulo
{
public:
    Pixel vertice1,vertice2,vertice3;
    Triangulo(Pixel v1,Pixel v2,Pixel v3):vertice1(v1), vertice2(v2), vertice3(v3)
    {}
    ~Triangulo(){}
    void DrawTriangle()
    {
        DrawLine(vertice1,vertice2);
        DrawLine(vertice2,vertice3);
        DrawLine(vertice3,vertice1);
    }
};


#endif // _MYGL_H_

