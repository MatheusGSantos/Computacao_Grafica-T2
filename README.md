# Computacao_Grafica-T2

## Implementação do Pipeline Gráfico em C/C++

Este projeto consiste na implementação do pipeline gráfico para transformar vértices do espaço do objeto até o espaço da tela.
As bibliotecas utilizadas foram do OpenGL, GLUT, Assimp e GLM. A aplicação é baseada em OpenGL, mas o pipeline tem cada passo montado através de operações e cálculos com vetores e matrizes.

## Desenvolvimento
Foram criadas as matrizes 4x4 a partir da GLM, para executar os passos do pipeline. As matrizes fundamentais (rotação, translação, escala) são matrizes globais, iniciadas como matriz identidade e modificadas com base na necessidade do uso em cada passo da transformação dos vértices. As outras matrizes (Model, View, ModelView, Projection, ModelViewProjection, ViewPort) foram calculadas por funções ao longo do pipeline gráfico. Essas matrizes são calculadas apenas uma vez por frame e multiplicam cada vértice do objeto a ser mostrado na tela.

### Espaço do Objeto -> Espaço do Universo
A matriz Model é responsável por essa transformação. Essa matriz é obtida através combinações (multiplicação das matrizes) de translação, rotação, escala e _shearing_. As matrizes fundamentais são modificadas através de funções set{nome da matriz}, com os parâmetros sendo os valores a serem _settados_ na matriz desejada. Ex.: setTranslate(1,1,0) muda o último vetor coluna da matriz de translação para (1,1,0,1). 

### Espaço do Universo -> Espaço da Câmera
A matriz View é responsável por essa transformação. Essa matriz é obtida através da multiplicação de uma matriz B transposta, formada por vetores ortonormais, calculados através das informações da câmera (vetor up, vetor look_at, vetor posição da camera), utilizando normalização e produto vetorial com a ajuda da biblioteca GLM, com uma matriz de translação onde o último vetor coluna tem x,y e z como -(posição da câmera). Tudo isso é calculado dentro de uma função, no fim montando a matriz View.

### Espaço da Câmera -> Espaço de Recorte
A partir da distância d (distância entre a câmera e o viewplane) é possível gerar a matriz projection, que transforma o w dos vértices num valor diferente de 1 e aplica distorção perpectiva (objetos mais distantes se tornam menores que objetos mais próximos). Também calculada dentro de uma função, no fim montando a matriz Projection.

### Espaço de Recorte -> Espaço Canônico
Todas as matrizes calculadas até esta etapa são multiplicadas, gerando a matriz ModelViewProjection.

## Referências
GLM - https://glm.g-truc.net/0.9.9/index.html

Material e Aulas do Professor Christian
