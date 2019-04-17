#include "main.h"

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


//Declaration

/*
//0° to 45°, 1st octant
Pixel pxl1 = Pixel(250,250,green);
Pixel pxl2 = Pixel(500,350,green);


//45° to 90°, 2nd octant
Pixel pxl3 = Pixel(250,250,red);
Pixel pxl4 = Pixel(325,500,red);


//90° to 135°, 3rd octant
Pixel pxl5 = Pixel(250,250,orange);
Pixel pxl6 = Pixel(200,500,orange);


//135° to 180°, 4th octant
Pixel pxl7 = Pixel(250,250,yellow);
Pixel pxl8 = Pixel(0,300,yellow);

//180° to 225°, 5th octant
Pixel pxl9 = Pixel(250,250,pink);
Pixel pxl10 = Pixel(0,200,pink);


//225° to 270°, 6th octant
Pixel pxl11 = Pixel(250,250,purple);
Pixel pxl12 = Pixel(200,0,purple);


//270° to 315°, 7th octant
Pixel pxl13 = Pixel(250,250,violet);
Pixel pxl14 = Pixel(300,0,violet);

//315° to 360°, 8th octant
Pixel pxl15 = Pixel(250,250,gray);
Pixel pxl16 = Pixel(500,230,gray);


//Diagonals and axis
Pixel PixelD = Pixel(250,250,white);
Pixel PixelNW = Pixel(0,0,white);
Pixel PixelNE = Pixel(IMAGE_WIDTH-1,0,white);
Pixel PixelSE = Pixel(IMAGE_WIDTH-1,IMAGE_HEIGHT-1,white);
Pixel PixelSW = Pixel(0,IMAGE_HEIGHT-1,white);
Pixel PixelX0 = Pixel(0,250,white);
Pixel PixelX1 = Pixel(IMAGE_WIDTH-1,250,white);
Pixel PixelY0 = Pixel(250,0,white);
Pixel PixelY1 = Pixel(250,IMAGE_HEIGHT-1,white);


Linha line1 = Linha(pxl1, pxl2);
Linha line2 = Linha(pxl3, pxl4);
Linha line3 = Linha(pxl5, pxl6);
Linha line4 = Linha(pxl7, pxl8);
Linha line5 = Linha(pxl9, pxl10);
Linha line6 = Linha(pxl11, pxl12);
Linha line7 = Linha(pxl13, pxl14);
Linha line8 = Linha(pxl15, pxl16);


Linha lineD1 = Linha(PixelD, PixelNW);
Linha lineD2 = Linha(PixelD, PixelNE);
Linha lineD3 = Linha(PixelD, PixelSW);
Linha lineD4 = Linha(PixelD, PixelSE);
Linha lineX = Linha(PixelX0, PixelX1);
Linha lineY = Linha(PixelY0, PixelY1);



void Sandbox()
{
	DrawLine(line1.pInicial,line1.pFinal);
	DrawLine(line2.pInicial, line2.pFinal);
	DrawLine(line3.pInicial, line3.pFinal);
	DrawLine(line4.pInicial, line4.pFinal);
	DrawLine(line5.pInicial, line5.pFinal);
	DrawLine(line6.pInicial, line6.pFinal);
	DrawLine(line7.pInicial, line7.pFinal);
	DrawLine(line8.pInicial, line8.pFinal);
	DrawLine(lineD1.pInicial, lineD1.pFinal);
	DrawLine(lineD2.pInicial, lineD2.pFinal);
	DrawLine(lineD3.pInicial, lineD3.pFinal);
	DrawLine(lineD4.pInicial, lineD4.pFinal);
	DrawLine(lineX.pInicial, lineX.pFinal);
	DrawLine(lineY.pInicial, lineY.pFinal);
}
*/


Pixel vertice1 = Pixel(125,300, red);
Pixel vertice2 = Pixel(375,300, blue);
Pixel vertice3 = Pixel(250,83, green);

Triangulo tr = Triangulo(vertice1,vertice2,vertice3);


//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	tr.DrawTriangle();
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

