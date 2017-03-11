#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
//void inserePonto();
//void insereFace();
//void lerPonto();
//void lerFace();
void lerArquivo();
//fim dos protótipos

/**Funções para manipular as listas*/
//Função para iniciar os valores da lista da face
void criarListaFace(tListaFace *listaF){
    listaF->inicioFace = NULL;
    listaF->tamanhoFace = 0;
}

//Função para iniciar os valores da lista do ponto
void criarListaPonto(tListaPonto *listaP){
    listaP->inicioPonto = NULL;
    listaP->tamanhoPonto = 0;
}

//Função para verificar se a lista de face está vazia
int listaFaceVazia(tListaFace listaF){
    if(listaF.tamanhoFace == 0){
        return 1;
    }
    return 0;
}

//Função para verificar se a lista de ponto está vazia
int listaPontoVazia(tListaPonto listaP){
    if(listaP.tamanhoPonto == 0){
        return 1;
    }
    return 0;
}

//Função para inserir um elemento na lista da face, sempre no final. Função vai ser int para saber se foi inserido corretamente
int inserirFace(tListaFace *listaF, int f1, int f2, int f3){
    tFace *noFace, *fimFace;
    fimFace = listaF->inicioFace;//esse ponteiro vai percorrer toda lista para inserir no fim
    //int cont = 1;
    noFace = malloc(sizeof(tFace));
    if(noFace == NULL){//if que verifica se um novo nó foi alocado
        return 0;
    }
    noFace->pt[0] = f1;
    noFace->pt[1] = f2;
    noFace->pt[2] = f3;
    if(listaFaceVazia(*listaF)){
        noFace->proxFace = NULL;
        listaF->inicioFace = noFace;
        listaF->tamanhoFace++;
    }else{
        while(fimFace->proxFace!=NULL){//percorre até o último índice da lista
            fimFace = fimFace->proxFace;
        }
        noFace->proxFace = NULL;
        fimFace->proxFace = noFace;
        listaF->tamanhoFace++;
    }
    return 1;
}

//Função para inserir um elemento na lista do ponto, sempre no final. Função vai ser int para saber se foi inserido corretamente
int inserirPonto(tListaPonto *listaP, float xp, float yp, float zp){
    tPonto *noPonto, *fimPonto;
    fimPonto = listaP->inicioPonto;
    noPonto = malloc(sizeof(tPonto));
    if(noPonto == NULL){
        return 0;
    }
    noPonto->x = xp;
    noPonto->y = yp;
    noPonto->z = zp;
    if(listaPontoVazia(*listaP)){
        noPonto->proxPonto = NULL;
        listaP->inicioPonto = noPonto;
        listaP->tamanhoPonto++;
    }else{
        while(fimPonto->proxPonto!=NULL){
            fimPonto = fimPonto->proxPonto;
        }
        noPonto->proxPonto = NULL;
        fimPonto->proxPonto = noPonto;
        listaP->tamanhoPonto++;
    }
    return 1;
}

void mostrarFace(tListaFace listaF){
    tFace *face;
    int n = 1;
    face = listaF.inicioFace;
    while((n<=listaF.tamanhoFace)&&(face!=NULL)){
        printf("Face %d: %d, %d, %d\n", n, face->pt[0], face->pt[1], face->pt[2]);
        face = face->proxFace;
        n++;
    }
}
/**Fim da funções para manipular as listas */


/**Função para ler as faces e colocar na lista de faces*/
void lerFace(char *str, tListaFace *listaF){
    int i, qtdeentrou = 0, ent = 1, cont_aspas = 0;
    int face[3];
    //("%s", str);
    if(strstr(str, "coordIndex=\"")!=NULL){

        for(i = 0; i<strlen(str); i++){

            if(str[i]>='0' && str[i]<='9'){
                if(qtdeentrou == 0){
                    face[qtdeentrou] = atoi(&str[i]);
                    printf("#%d face: %d\n", ent, face[qtdeentrou]);
                    ent++;//serve de nada, só para numerar as faces
                    qtdeentrou++;
                }else if(qtdeentrou == 1){
                    face[qtdeentrou] = atoi(&str[i]);
                    printf("#%d face: %d\n", ent, face[qtdeentrou]);
                    ent++;//serve de nada, só para numerar as faces
                    qtdeentrou++;
                }else if(qtdeentrou == 2){
                    face[qtdeentrou] = atoi(&str[i]);
                    printf("#%d face: %d\n", ent, face[qtdeentrou]);
                    ent++;//serve de nada, só para numerar as faces
                    qtdeentrou++;
                }

                if(qtdeentrou==3){
                    inserirFace(listaF, face[0], face[1], face[2]);
                    qtdeentrou = 0;
                    ent = 1;//serve de nada, só para numerar as faces
                }
            }

            /**esse if é para verificar se foi lido as 3 faces e se foi, pular dois índices para não salvar o -1*/
            if(str[i] == '-'){
                i++;
            }

            /**if para verificar se já foi encontrado as duas aspas */
            if(str[i] == '"'){
                cont_aspas++;
                if(cont_aspas == 2){
                    //printf("%d aspas\n", cont_aspas);
                    cont_aspas = 0;
                    break;
                }
            }

        }//fim do for que encontra as faces
    }//fim do if que procura as até achar o coordindex
}//fim da função que pega os pontos

/**Função para ler os pontos e colocar na lista de pontos */
void lerPonto(char *str, tListaPonto *listaP){
    int i, qtdeentrou = 0, ent = 1, cont_aspas = 0, indice = 0;
    float numero, ponto[3];
    char num[7];
    int numero_antes, numero_depois,flag_ponto = 1, cont=0, negativo = 0;;
    if(strstr(str, "point=\"")){
        for(i=0; i<strlen(str); i++){
                if((str[i]>='0'&&str[i]<='9')){
                    if(flag_ponto){
                        if(str[i-1] == '-'){
                            negativo = 1;
                            //numero_antes = atoi(&str[i]);
                            //numero_antes = -numero_antes;
                        }//else{
                            numero_antes = atoi(&str[i]);
                        //}
                    }else{
                        num[cont] = str[i];
                        //printf("%c\n", num[cont]);
                        cont++;
                        if(cont == 6){
                            numero_depois = atoi(num);
                            numero = numero_depois/1000000.0;
                            if(negativo){
                                numero = -(numero + numero_antes);
                                ponto[indice] = numero;
                                //indice++;
                                negativo = 0;
                            }else{
                                numero = numero + numero_antes;
                                ponto[indice] = numero;
                                //indice++;
                            }
                            if(indice == 2){
                                inserirPonto(listaP, ponto[0], ponto[1], ponto[2]);
                                indice = 0;
                            }
                            indice++;
                            printf("%f\n", numero);
                            cont = 0;
                            flag_ponto = 1;
                        }
                    }
                }
                if(str[i] == '.'){
                    flag_ponto = 0;
                }
                if(str[i] == '\"'){
                    cont_aspas++;
                    if(cont_aspas == 2){
                        cont_aspas = 0;
                        break;
                    }
                }
        }//fim do for
    }//fim do if que compara a string
}//fim da função de ler os pontos

void lerArquivo(FILE *arquivo, tListaPonto *listaPonto, tListaFace *listaFace){
    char linha[400];

    while(!feof(arquivo)){
        fgets(linha, 400, arquivo);
        //fscanf(arquivo, "%s", &linha);
        lerFace(linha, listaFace);
        lerPonto(linha, listaPonto);
    }//fim do arquivo
}//fim da função ler arquivo

int main(){
    tListaFace faceEnc;
    tListaPonto pontoEnc;
    criarListaFace(&faceEnc);
    criarListaPonto(&pontoEnc);
    FILE *f;
    f = fopen("quad.x3d", "r");
    lerArquivo(f, &pontoEnc, &faceEnc);
    fclose(f);
    mostrarFace(faceEnc);
    return 0;
}
