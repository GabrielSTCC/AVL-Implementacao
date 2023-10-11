#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int chave;
    struct no* esq;
    struct no* dir;
    int bal;
    int alt;
}NO;

NO* iniciarNo(NO* pt, int x){
    pt = (NO*)malloc(sizeof(NO));
    pt->chave = x;
    pt->esq = NULL;
    pt->dir = NULL;
    pt->bal = 0;
    pt->alt = 1;
    return pt;
}

int maior(int a, int b){
    return (a > b)? a: b;
}

int calcularAltura(NO* no){
    if(no == NULL){
        return 0;
    }
     
    return no->alt;
}

NO* rotatedir(NO* pt) {
    NO* novopt = pt->esq;
    NO* temp = novopt->dir;

    novopt->dir = pt;
    pt->esq = temp;

    pt->alt = maior(calcularAltura(pt->esq), calcularAltura(pt->dir)) + 1;
    novopt->alt = maior(calcularAltura(novopt->esq), calcularAltura(novopt->dir)) + 1;

    return novopt;
}

NO* rotateesq(NO* pt) {
    NO* novopt = pt->dir;
    NO* temp = novopt->esq;

    novopt->esq = pt;
    pt->dir = temp;

    pt->alt = maior(calcularAltura(pt->esq), calcularAltura(pt->dir)) + 1;
    novopt->alt = maior(calcularAltura(novopt->esq), calcularAltura(novopt->dir)) + 1;

    return novopt;
}

int getBalance(NO* pt) {
    if (pt == NULL) {
        return 0;
    }
    return calcularAltura(pt->esq) - calcularAltura(pt->dir);
}

NO* valorMinNo(NO* pt) {
    NO* atual = pt;
    while (atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

NO* InserirAVL(int x, NO* pt) {
    if (pt == NULL) {
        pt = iniciarNo(pt, x);
        pt->alt = 1; // Atualiza a altura para 1, pois é uma folha
    } else if (x == pt->chave) {
        //printf("Elemento ja existe.");
        return pt;
    } else if (x < pt->chave) {
        pt->esq = InserirAVL(x, pt->esq);
        pt->alt = 1 + maior(calcularAltura(pt->esq), calcularAltura(pt->dir));
    } else {
        pt->dir = InserirAVL(x, pt->dir);
        pt->alt = 1 + maior(calcularAltura(pt->esq), calcularAltura(pt->dir));
    }
    
    int balance = getBalance(pt);

    // Verifique e ajuste o balanceamento
    if (balance > 1) {
        if (x < pt->esq->chave) {
            return rotatedir(pt);
        }
        pt->esq = rotateesq(pt->esq);
        return rotatedir(pt);
    }
    if (balance < -1) {
        if (x > pt->dir->chave) {
            return rotateesq(pt);
        }
        pt->dir = rotatedir(pt->dir);
        return rotateesq(pt);
    }
    
    return pt;
}



int trocar(NO* a, NO* b) {
    a->chave = b->chave;
    return 0;
}

NO* RemoverAVL(int x, NO* pt) {
    if (pt == NULL) {
        //printf("Elemento nao existe\n");
        return pt;  // Adicione esta linha para retornar imediatamente
    } else {
        if (x < pt->chave) {
            pt->esq = RemoverAVL(x, pt->esq);
        } else if (x > pt->chave) {
            pt->dir = RemoverAVL(x, pt->dir);
        } else {
            if (pt->esq == NULL || pt->dir == NULL) {
                NO* temp = (pt->esq) ? pt->esq : pt->dir;

                if (temp == NULL) {
                    temp = pt;
                    pt = NULL;
                } else {
                    *pt = *temp;
                }

                free(temp);
            } else {
                NO* temp = valorMinNo(pt->dir);
                pt->chave = temp->chave;
                pt->dir = RemoverAVL(temp->chave, pt->dir);
            }
        }
    }

    // Após a remoção, atualize a altura e verifique o balanceamento
    if (pt == NULL) return pt;
    pt->alt = 1 + maior(calcularAltura(pt->esq), calcularAltura(pt->dir));
    int balance = getBalance(pt);

    // Verifique e ajuste o balanceamento
    if (balance > 1) {
        if (getBalance(pt->esq) >= 0) {
            return rotatedir(pt);
        } else {
            pt->esq = rotateesq(pt->esq);
            return rotatedir(pt);
        }
    }
    if (balance < -1) {
        if (getBalance(pt->dir) <= 0) {
            return rotateesq(pt);
        } else {
            pt->dir = rotatedir(pt->dir);
            return rotateesq(pt);
        }
    }
    
    return pt;
}


int verificarAVL(NO* pt){
   if (pt == NULL){
       return 1;
   }
   int esqAltura = calcularAltura(pt->esq);
   int dirAltura = calcularAltura(pt->dir);
   if(abs(esqAltura - dirAltura) <= 1 && verificarAVL(pt->esq) && verificarAVL(pt->dir)){
       return 1;
   }
   return 0;
}

int contarNos(NO* pt) {
    if (pt == NULL) {
        return 0;
    }
    return 1 + contarNos(pt->esq) + contarNos(pt->dir);
}

void testarAVL() {
    int i, j;
    int numArvores = 1000;
    int numNos = 10000;
    int chaveMaxima = 100000;

    for (i = 0; i < numArvores; i++) {
        NO* pt = NULL;
        for (j = 0; j < numNos; j++) {
            int chave = rand() % (chaveMaxima + 1);
            pt = InserirAVL(chave, pt);
        }
        int numNosNaArvore = contarNos(pt);
        printf("Arvore %d:\n", i + 1);
        printf("Numero de nos: %d\n", numNosNaArvore);
        printf("E AVL: %s\n", verificarAVL(pt) ? "Sim" : "Nao");

        for (j = 0; j < numNos / 10; j++) {
            int chave = rand() % (chaveMaxima + 1);
            pt = RemoverAVL(chave, pt);
        }
        numNosNaArvore = contarNos(pt);
        printf("Numero de nos apos exclusao: %d\n", numNosNaArvore);
        printf("E AVL apos exclusao: %s\n\n", verificarAVL(pt) ? "Sim" : "Nao");
    }
}

int main() {
    testarAVL();
    return 0;
}