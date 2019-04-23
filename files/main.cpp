#include "main.h"
#include "loader.h"

//colors
/*#1*/int green[4] = {0,255,0,255};
/*#2*/int red[4] = {255,0,0,255};
/*#3*/int blue[4] = {0,0,255,255};
/*#4*/int white[4] = {255,255,255,255};
/*#5*/int orange[4] = {255,128,0,255};
/*#6*/int pink[4] = {255,0,127,255};
/*#7*/int purple[4] = {102,0,102,255};
/*#8*/int yellow[4] = {255,255,0,255};
/*#9*/int ocean_blue[4] = {0,204,204,255};
/*#10*/int brown[4] = {51,0,0,255};
/*#11*/int gray[4] = {64,64,64,255};
/*#12*/int light_green[4] = {153,255,51,255};
/*#13*/int wine[4] = {102,0,0,255};
/*#14*/int violet[4] = {153,0,153,255};


std::vector<glm::vec4> vertex_v;



//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	DrawPipeLine(vertex_v, white);
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();
	M_init();

	//loads the object
	vertex_v = loadObject("monkey_model.obj");

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;
	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

