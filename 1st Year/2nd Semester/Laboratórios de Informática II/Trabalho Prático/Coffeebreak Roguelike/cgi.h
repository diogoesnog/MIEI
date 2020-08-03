#ifndef ___CGI_H___
#define ___CGI_H___

/**
@file cgi.h
@brief Macros úteis para gerar CGIs.
*/

#include <stdio.h>

/**
\brief Caminho para as imagens.
*/
#define IMAGE_PATH							"http://localhost/images/"

/**
\brief Macro para começar o html.
*/
#define COMECAR_HTML						printf("Content-Type: text/html\n\n")

/**
\brief Macro para abrir um svg.
@param tamx O comprimento do svg.
@param tamy A altura do svg.
*/
#define ABRIR_SVG(tamx, tamy)				printf("<svg align =\"center\" width=%d height=%d>\n", tamx, tamy)

/**
\brief Macro para fechar um svg.
*/
#define FECHAR_SVG							printf("</svg>\n")

/**
\brief Macro para criar uma imagem.
@param X A coordenada X do canto superior esquerdo.
@param Y A coordenada Y do canto superior esquerdo.
@param ESCALA A escala da imagem.
@param FICHEIRO O caminho para o link do ficheiro.
*/
#define IMAGEM(X, Y, ESCALA, FICHEIRO)					printf("<image x=%d y=%d width=%d height=%d xlink:href=%s/%s />\n", \
															ESCALA * X, ESCALA * Y, ESCALA, ESCALA, IMAGE_PATH, FICHEIRO)

/**
\brief Macro para criar uma imagem que irá fazer reload da página/jogo.
@param X A coordenada X do canto superior esquerdo.
@param Y A coordenada Y do canto superior esquerdo.
@param ESCALA A escala da imagem.
@param FICHEIRO O caminho para o link do ficheiro.
*/		
#define IMAGEMR(X, Y, ESCALA, FICHEIRO)					printf("<a href=\"http://localhost/cgi-bin/jogo\"><image x=%d y=%d width=%d height=%d xlink:href=%s/%s /></a>\n", \
															X, Y, ESCALA, ESCALA, IMAGE_PATH, FICHEIRO)

/**
\brief Macro para criar o logótipo do jogo.
@param X A coordenada X do canto superior esquerdo.
@param Y A coordenada Y do canto superior esquerdo.
@param ESCALA A escala da imagem.
@param FICHEIRO O caminho para o link do ficheiro.
*/		
#define IMAGEML(X, Y, ESCALA, FICHEIRO)					printf("<image x=%d y=%d width=%d height=%d xlink:href=%s/%s />\n", \
															X, Y, ESCALA, ESCALA, IMAGE_PATH, FICHEIRO)

/**
\brief Macro para criar uma imagem de GAMEOVER.
@param X A coordenada X do canto superior esquerdo.
@param Y A coordenada Y do canto superior esquerdo.
@param ESCALA A escala da imagem.
@param FICHEIRO O caminho para o link do ficheiro.
*/		
#define IMAGEMFJ(X, Y, ESCALA, FICHEIRO)				printf("<a href=\"http://localhost/cgi-bin/jogo\"><image x=%d y=%d width=%d height=%d xlink:href=%s/%s /></a>\n", \
															X, Y, ESCALA, ESCALA, IMAGE_PATH, FICHEIRO)

/**
\brief Macro para criar um texto dos pontos.
@param X A coordenada X do canto superior esquerdo.
@param Y A coordenada Y do canto superior esquerdo.
@param ESCALA A escala da imagem.
@param TXT Os pontos em si.
*/		
#define TEXTOP(X, Y, ESCALA, TXT)						printf("<text x=%d y=%d style=\"font-family: Ubuntu; font-weight: Bold; font-size:20px;\">\n%s\n</text>\n", \
															ESCALA * X, ESCALA * Y, TXT)

/**
\brief Macro para criar um titulo do Score.
@param X A coordenada X do canto superior esquerdo.
@param Y A coordenada Y do canto superior esquerdo.
@param ESCALA A escala da imagem.
@param TXT O titulo em si.
*/		
#define TEXTOS(X, Y, ESCALA, TXT)						printf("<text x=%d y=%d style=\"font-family: Ubuntu; font-weight: Bold; fill:#CC9305; font-size:20px;\">\n%s\n</text>\n", \
															ESCALA * X, ESCALA * Y, TXT)

/**
\brief Macro para criar um titulo do BestScore.
@param X A coordenada X do canto superior esquerdo.
@param Y A coordenada Y do canto superior esquerdo.
@param ESCALA A escala da imagem.
@param TXT O titulo em si.
*/	
#define TEXTOBS(X, Y, ESCALA, TXT)						printf("<text x=%d y=%d style=\"font-family: Ubuntu; font-weight: Bold; fill:#7C8B8A; font-size:20px;\">\n%s\n</text>\n", \
															ESCALA * X, ESCALA * Y, TXT)
																													
/**
\brief Macro para criar um quadrado.
@param X A coordenada X do canto superior esquerdo.
@param Y A coordenada Y do canto superior esquerdo.
@param ESCALA A escala do quadrado.
@param COR A cor de preenchimento do quadrado.
*/
#define QUADRADO(X, Y, ESCALA, COR)						printf("<rect x=%d y=%d width=%d height=%d fill=%s />\n", \
															ESCALA * X, ESCALA * Y, ESCALA, ESCALA, COR)

/**
\brief Macro para criar um quadrado transparente
@param X A coordenada X do canto superior esquerdo.
@param Y A coordenada Y do canto superior esquerdo.
@param ESCALA A escala do quadrado.
*/
#define QUADRADO_TRANSPARENTE(X, Y, ESCALA)				printf("<rect x=%d y=%d width=%d height=%d opacity=0 />\n", \
															ESCALA * X, ESCALA * Y, ESCALA, ESCALA)

/**
\brief Macro para abrir um link.
@param link O caminho para o link.
*/
#define ABRIR_LINK(link)								printf("<a xlink:href=%s>\n", link)

/**
\brief Macro para fechar o link.
*/
#define FECHAR_LINK							printf("</a>\n")

#endif
