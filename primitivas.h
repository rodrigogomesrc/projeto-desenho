#ifndef primitivas_h 
#define primitivas_h

void save(imagem *img, char nome_arquivo[]);

void line(imagem *img, int parametros[]);

void polygon(imagem *img, comando cmd);

void circle(imagem *img, int parametros[]);

void color(imagem *img, int parametros[]);

void clear(imagem *img, int parametros[]);

void rect(imagem *img, int parametros[]);

void open(imagem *img, char nome_arquivo[]);

void image(imagem *img, int parametros[]);

#endif