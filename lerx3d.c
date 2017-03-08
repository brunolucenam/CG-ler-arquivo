#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*leitura de um arquivo de modelo*/
//tipos de dados
typedef struct face{
	int pt[3];
	struct face *proxFace;
}tFace;

typedef struct ponto{
	float x;
	float y;
	float z;
	struct ponto *proxPonto;
}tPonto;

//struct face *F=0;cabeça da lista
//struct ponto *P=0;//cabeça da lista
/**estruturas com um ponteiro para salvar o início ou cabeça das listas de ponto e face*/
typedef struct listaFace{
    struct face *inicioFace;
    int tamanhoFace;
}tListaFace;

typedef struct listaPonto{
    struct ponto *inicioPonto;
    int tamanhoPonto;
}tListaPonto;

//protótipos de função
void inserePonto();
void insereFace();
void lerPonto();
void lerFace();
void lerArquivo();
//fim dos protótipos

void lerArquivo(FILE *arquivo/*, tListaPonto *listaPonto, tListaFace *listaFace*/){
    char linha[400];
    int i;
    int qtdeentrou = 0, ent = 1;//serve de nada, só para numerar as faces

    //arquivo = fopen("quad.x3d", "r");
    while(!feof(arquivo)){
        fgets(linha, 400, arquivo);
        //printf("%s", linha);
        if(strstr(linha, "coordIndex=\"")!=NULL){
            printf("entrou\n");
            for(i = 0; i<strlen(linha); i++){
                if(linha[i]>='0' && linha[i]<='9'){
                    if(qtdeentrou == 0){
                        printf("#%d face: %c\n", ent, linha[i]);
                        ent++;//serve de nada, só para numerar as faces
                        qtdeentrou++;
                    }else if(qtdeentrou == 1){
                        printf("#%d face: %c\n", ent, linha[i]);
                        ent++;//serve de nada, só para numerar as faces
                        qtdeentrou++;
                    }else if(qtdeentrou == 2){
                        printf("#%d face: %c\n", ent, linha[i]);
                        ent++;//serve de nada, só para numerar as faces
                        qtdeentrou++;
                    }

                    if(qtdeentrou==3){
                        qtdeentrou = 0;
                        ent = 1;//serve de nada, só para numerar as faces
                    }
                }
                /**esse if é para verificar se foi lido as 3 faces e se foi, pular dois índices para não salvar o -1*/
                if(linha[i] == '-'){
                    //printf("entrou if\n");
                    i = i+2;
                }

            }
        }
    }
    //fclose(arquivo);
}

int main(){
    FILE *f;
    f = fopen("quad.x3d", "r");
    lerArquivo(f);
    fclose(f);
    return 0;
}
