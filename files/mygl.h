#ifndef _MYGL_H_
#define _MYGL_H_

#include "definitions.h"
#include <math.h>
#include <iostream>
#include <vector>


//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************


class Pixel
{
public:
    int x, y, z;
    int RGBA[4];
    Pixel(){};

    Pixel(int x, int y, int z, int color[4])
    {
        this->x = x;
        this->y = y;
        this->z = z;
        RGBA[0] = color[0];
        RGBA[1] = color[1];
        RGBA[2] = color[2];
        RGBA[3] = color[3];
    }
    ~Pixel()
    {}
};

void PutPixel(int x, int y, int RGBA[4])
{
    FBptr[y*IMAGE_WIDTH*4 + 4*x+0] = RGBA[0];
    FBptr[y*IMAGE_WIDTH*4 + 4*x+1] = RGBA[1];
    FBptr[y*IMAGE_WIDTH*4 + 4*x+2] = RGBA[2];
    FBptr[y*IMAGE_WIDTH*4 + 4*x+3] = RGBA[3];
}


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

    if(!dx && !dy)
    {
        PutPixel(pInicial.x,pInicial.y,pInicial.RGBA);
        return;
    }

    int incr_y = 1, incr_x = 1;
    float distTotal = sqrt(pow(dx,2) + pow(dy,2));

    Pixel currentPixel = pInicial;
    PutPixel(currentPixel.x, currentPixel.y, currentPixel.RGBA);
    
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
                PutPixel(currentPixel.x, currentPixel.y, currentPixel.RGBA);
            }
        }
        else if (dy == 0)   //line in the x axis
        {
            while(currentPixel.x < pFinal.x){
                currentPixel.x += incr_x;
                Interpol(pInicial,pFinal,&currentPixel,distTotal);
                PutPixel(currentPixel.x, currentPixel.y, currentPixel.RGBA);
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
                PutPixel(currentPixel.x, currentPixel.y, currentPixel.RGBA);
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
                PutPixel(currentPixel.x, currentPixel.y, currentPixel.RGBA);
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
                    PutPixel(currentPixel.x, currentPixel.y, currentPixel.RGBA);
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
                    PutPixel(currentPixel.x, currentPixel.y, currentPixel.RGBA);
                }
            }
        }
    }
}


void DrawTriangle(Pixel vertice1, Pixel vertice2, Pixel vertice3)
{
    DrawLine(vertice1,vertice2);
    DrawLine(vertice2,vertice3);
    DrawLine(vertice3,vertice1);
}


//set scale, translation and rotation to identity matrix
void M_init()
{
	scale = translation = rotation = Identity;
}


//set scale matrix
void setScale_M(int sx, int sy, int sz)
{
	scale[0][0]=sx;
	scale[1][1]=sy;
	scale[2][2]=sz;
}


//set translation matrix
void setTranslation_M(int tx, int ty, int tz)
{
	translation[3].x=tx;
	translation[3].y=ty;
	translation[3].z=tz;
}


//set rotation matrix
void setRotation_M(const char axis, const float theta)
{
	rotation = Identity;	
	switch(axis){
		case 'x':
			rotation[1][1]= glm::cos(theta);
			rotation[1][2]= glm::sin(theta);
			rotation[2][1]= -1 * glm::sin(theta);
			rotation[2][2]= glm::cos(theta);
			break;
		case 'y':
			rotation[0][0]= glm::cos(theta);
			rotation[0][2]= -1 * glm::sin(theta);
			rotation[2][0]= glm::sin(theta);
			rotation[2][2]= glm::cos(theta);
			break;
		case 'z':
			rotation[0][0]= glm::cos(theta);
			rotation[0][1]= glm::sin(theta);
			rotation[1][0]= -1 * glm::sin(theta);
			rotation[1][1]= glm::cos(theta);
			break;
		default:
			std::cout << "Invalid axis value. Try again.\n";
			exit(-1);
	}
}


//build view matrix
void buildView_M()
{
    //camera direction vector
    glm::vec3 camera_dir = camera_lookat - camera_pos;
	
    //camera coordinate vectors
    glm::vec3 z_camera = -glm::normalize(camera_dir);
    glm::vec3 x_camera = glm::normalize(glm::cross(camera_up, z_camera));
    glm::vec3 y_camera = glm::cross(z_camera, x_camera);

    //Bt matrix
    glm::mat4 Bt_M = glm::mat4( glm::vec4(x_camera[0], y_camera[0], z_camera[0], 0), 
                                glm::vec4(x_camera[1], y_camera[1], z_camera[1], 0), 
                                glm::vec4(x_camera[2], y_camera[2], z_camera[2], 0), 
                                canonic4
                              );

    //translation matrix
    setTranslation_M(-camera_pos[0],-camera_pos[1],-camera_pos[2]);

    View = Bt_M * translation;
}


//build projection matrix
void buildProjection_M()
{
    //viewplane distance
    double d = 1.9;

    Projection = glm::mat4( canonic1,
                            canonic2,
                            glm::vec4(0, 0, 1, -1.0/d),
                            glm::vec4(0, 0, d, 0)
                          );
}


//build viewport matrix
void buildViewPort(const int &w,const int &h)
{
    //scale with screen size
    setScale_M(w/2,h/2,1);
    //translate to screen
    setTranslation_M( (w-1)/2, (h-1)/2, 0);
    viewport = translation*scale;
    //invert image
    setScale_M(1,-1,1);
	viewport *= scale;
}


void PipeLine(glm::vec4 &p)
{
    setRotation_M('x',-0.09);
    Model = rotation*Identity;
    buildView_M();
    ModelView = View * Model;
    buildProjection_M();
    ModelViewProjection = Projection * ModelView;
    p = ModelViewProjection*p;
	p = p / p.w;
    buildViewPort(IMAGE_WIDTH, IMAGE_HEIGHT);
    p = viewport*p;
}

void DrawPipeLine(std::vector<glm::vec4> pixels, int color[4])
{
	//apply pipeline
	for (int i = 0; i < pixels.size(); i++)
    {
        PipeLine(pixels[i]);
    }

	//draw triangles
    for (int i = 0; i < pixels.size(); i += 3)
	{
		Pixel pixel1((int) pixels[i].x, (int) pixels[i].y, (int) pixels[i].z, color);
		Pixel pixel2((int) pixels[i + 1].x, (int) pixels[i + 1].y, (int) pixels[i + 1].z, color);
		Pixel pixel3((int) pixels[i + 2].x, (int) pixels[i + 2].y, (int) pixels[i + 2].z, color);
		DrawTriangle(pixel1, pixel2, pixel3);
	}
}


#endif // _MYGL_H_

