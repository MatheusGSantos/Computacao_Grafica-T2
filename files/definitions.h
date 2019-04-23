#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define IMAGE_WIDTH  512 // número de colunas da imagem.
#define IMAGE_HEIGHT 512 // número de linhas da imagem.

#include <glm/glm.hpp>

unsigned char * FBptr;

//Canonical basis
glm::vec4 const canonic1 = glm::vec4(1,0,0,0);
glm::vec4 const canonic2 = glm::vec4(0,1,0,0);
glm::vec4 const canonic3 = glm::vec4(0,0,1,0);
glm::vec4 const canonic4 = glm::vec4(0,0,0,1);


//Identity Matrix
glm::mat4 Identity = glm::mat4(canonic1,canonic2, canonic3, canonic4);


//scale matrix
glm::mat4 scale;


//translation matrix
glm::mat4 translation;


//rotation matrix
glm::mat4 rotation;


//Model
glm::mat4 Model;


//View
glm::mat4 View;


//Camera
glm::vec3 camera_pos = glm::vec3(0,0,4);
glm::vec3 camera_lookat = glm::vec3(0,0,0);
glm::vec3 camera_up = glm::vec3(0,1,0);


//ModelView matrix
glm::mat4 ModelView;


//projection matrix
glm::mat4 Projection;


//ModelViewProjection matrix
glm::mat4 ModelViewProjection;


//viewport matrix
glm::mat4 viewport;


#endif // _DEFINITIONS_H_

