#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define IMAGE_WIDTH  512 // número de colunas da imagem.
#define IMAGE_HEIGHT 512 // número de linhas da imagem.

unsigned char * FBptr;

//scale matrix
glm::mat4 scale;

//translation matrix
glm::mat4 translation;

//rotation matrix
glm::mat4 rotation;


#endif // _DEFINITIONS_H_

