#include <stdio.h>
#include <stdlib.h>

typedef struct {

    int topo;
    char *vetor;
    char *ptrtopo;
} pile;

void criaPilha(int tamanho, pile *pilha) {

    pilha->topo = 0;
    pilha->vetor = malloc(tamanho*sizeof(char));
    pilha->ptrtopo = &pilha->vetor[0];
}

void colocaPrimeiro(char n, pile *pilha) {

    pilha->vetor[pilha->topo] = n;
    pilha->topo++;
    pilha->ptrtopo++;
}

char tiraPrimeiro (pile *pilha) {

    char f;
    f = pilha->vetor[pilha->topo];
    if (pilha->topo > 0)    
        pilha->topo--;
    
    pilha->ptrtopo--;
    return f;
}

int pilhaVazia (pile *pilha) {

    if (pilha->ptrtopo < &pilha->vetor[0])
        return 1;
    else
        return 0;
}

void destroiPilha (pile *pilha) {

    free(pilha->vetor);
    pilha->vetor = NULL;
    free(pilha);
    pilha = NULL;
}

char veTopo (pile *pilha) {
    return (pilha->vetor[pilha->topo]);
}



int prioridade(char c) {
    
    if (c == '+' || c=='-') return 1;
    if (c == '*' || c=='/') return 2;
}



int main () {

    int tamanho, i, j;
    char *palavra, fora;
    
    scanf("%d", &tamanho);
    j = 0;
    palavra = malloc(tamanho*sizeof(char));
    
    pile *pilha;
    pilha = malloc(sizeof(pile));
    criaPilha(tamanho,pilha);

    for(i = 0; i <= tamanho + 1 ; i++) {
        scanf("%c", &palavra[i]);
    }

    for(i = 0; i <= tamanho + 1 ; i++) {
        printf("%c", palavra[i]);
    }    

    while (palavra[j] != '\0') {
        
        if (palavra[j] >= 'A' && palavra[j] <= 'Z' ) {
            printf("%c", palavra[j]);
            j++;
        }

        else if (palavra[j] == '(') {
 
            while (palavra[j] != ')' ) {
                
                if (palavra[j] >= 'A' && palavra[j] <= 'Z' ) {
                    printf("%c", palavra[j]);
                    j++;
                }
                else {
                    colocaPrimeiro(palavra[j], pilha);
                    j++;
                }           
            }
            
            j++;
            
            pilha->topo--;
            while (veTopo(pilha) != '(' )
                printf("%c", tiraPrimeiro(pilha));
                
            fora = tiraPrimeiro(pilha);
        }

        else {

            if (pilhaVazia(pilha) == 1)
                colocaPrimeiro(palavra[j], pilha);

            else if (prioridade(veTopo(pilha)) > prioridade(palavra[j]))
                
                printf("%c", tiraPrimeiro(pilha));
            
            else {
                printf("%c", tiraPrimeiro(pilha));
                printf("%c", palavra[j]);
            }
            
            j++; 
            
        }        
    }


    while (pilhaVazia(pilha) == 0);
        printf("%c",tiraPrimeiro(pilha) );

    printf("\n");



    return 0;
}