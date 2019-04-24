# Computacao_Grafica-T2

## Implementação do Pipeline Gráfico em C/C++

Este projeto consiste na implementação do pipeline gráfico para transformar vértices do espaço do objeto até o espaço da tela.
As bibliotecas utilizadas foram do OpenGL, GLUT, Assimp e GLM. A aplicação é baseada em OpenGL, mas o pipeline tem cada passo montado através de operações e cálculos com vetores e matrizes.

## Desenvolvimento
Foram criadas as matrizes 4x4 a partir da GLM, para executar os passos do pipeline. As matrizes fundamentais (rotação, translação, escala) são matrizes globais, iniciadas como matriz identidade e modificadas com base na necessidade do uso em cada passo da transformação dos vértices. As outras matrizes (Model, View, ModelView, Projection, ModelViewProjection, ViewPort) foram calculadas por funções ao longo do pipeline gráfico.

###

## Referências
GLM - https://glm.g-truc.net/0.9.9/index.html

Material e Aulas do Professor Christian
