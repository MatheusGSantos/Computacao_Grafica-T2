#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h>

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



void setScale_M(int tx, int ty, int tz)
{
	glm::vec4 v0 = glm::vec4();
	glm::vec4 v0 = glm::vec4();
	glm::vec4 v0 = glm::vec4();
	glm::vec4 v0 = glm::vec4();
}
void setTranslation_M(){}
void setRotation_M(){}

void DrawPipeline(glm::vec3 const &p)
{
	glm::vec4 pix = glm::vec4(p.x,p.y,p.z,1);
	pix = ModelViewProjection*pix;
	pix = pix / pix[4];



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

