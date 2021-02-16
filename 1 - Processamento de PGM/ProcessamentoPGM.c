#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Para finalizar, a função que faz ambas as tarefas restantes
void limiarizacao(int l, int c, int matriz[l][c]){
int matrizlimiarizada[l][c], matriznegativa[l][c], i=0, j=0;
for(i=0; i < l; i++){
    for(j=0; j < c; j++){
        if(matriz[i][j] < 150){
            matrizlimiarizada[i][j] = 0;
        }else{
            matrizlimiarizada[i][j] = 255;
        }
            matriznegativa[i][j] = 255 - matriz[i][j];
    }
}
FILE *imagemLimiarizada;
imagemLimiarizada = fopen("imglimi.pgm", "wb");
fprintf(imagemLimiarizada, "P2\n");
fprintf(imagemLimiarizada, "%d %d\n", c, l);
fprintf(imagemLimiarizada, "255\n");
for(i=0; i < l; i++){
    for(j=0; j < c; j++){
        fprintf(imagemLimiarizada, "%d ", matrizlimiarizada[i][j]);
    }
    fprintf(imagemLimiarizada, "\n");
} fclose(imagemLimiarizada);

FILE *imagemNegativa;
imagemNegativa = fopen("imgNegativa.pgm", "wb");
fprintf(imagemNegativa, "P2\n");
fprintf(imagemNegativa, "%d %d\n", c, l);
fprintf(imagemNegativa, "255\n");
for(i=0; i < l; i++){
    for(j=0; j < c; j++){
        fprintf(imagemNegativa, "%d ", matriznegativa[i][j]);
    }
    fprintf(imagemNegativa, "\n");
} fclose(imagemNegativa);
}

//Enfim, a função que vai criar o histograma
void histograma(int l, int c, int matriz[l][c]){
FILE *histograma;
int contagem=0, numero=0, i=0, j=0;
histograma = fopen("histograma.txt", "w");
while(numero != 256){
for(i=0; i < l; i++){
    for(j=0; j < c; j++){
        if(matriz[i][j] == numero){
            contagem++;
        }
    }
}
fprintf(histograma, "Pixel: %d Quantidade: %d\n", numero, contagem);
contagem=0; numero++;
}
fclose(histograma);
limiarizacao(l, c, matriz);
}

// A função que vai encontrar os valores de cada pixel
void valoresmatriz(FILE *Imagem, int l, int c, char m[100]){
int matriz[l][c];
int i=0, j=0;
for(i=0; i < l; i++){
    fgets(m, 100, Imagem);
    char *p = m;
    for(j=0; j < c; j++){
        matriz[i][j] = strtol(p, &p, 10);
        p++;
    }
}
fclose(Imagem);
histograma(l, c, matriz);
}

// A função que vai encontrar a quantidade de linhas e de colunas dos pixels da imagem
void contalinhascolunas(FILE *Imagem){
int l=0, c=0, contagem=0;
char m[100];
while(fgets(m, 100, Imagem) != NULL){
contagem++;
if(contagem == 2){
sscanf(m, "%d %d", &c, &l);
fgets(m, 100, Imagem);
valoresmatriz(Imagem, l, c, m);
}}
}

// Basicamente uma função que pede o nome da img para encontra-la na pasta em que o arquivo está armazenado
void encontrarIMG(FILE *Imagem, char nomeimg[100]){
printf("Digite o nome do arquivo(Incluindo '.pgm'):");
scanf(" %[^\n]%*c", *&nomeimg);
Imagem = fopen(nomeimg, "rb");
if(Imagem == NULL){
printf("Nao foi possivel abrir o arquivo\n");
encontrarIMG(Imagem, nomeimg);
}else{
contalinhascolunas(Imagem);
}
}

int main(){
FILE *Imagem;
char nomeimg[100];
encontrarIMG(Imagem, nomeimg);
}

