#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    int lin, col;
    int elemento;
    
    printf("MATRIZ COM VALORES DE 0 A 9\n\n");
    printf("DIGITE A QUANTIDADE DE LINHAS E COLUNAS DA MATRIZ SEPARADAS POR ESPAÇO: ");
    scanf("%d", &lin);
    scanf("%d", &col);
    
    int *matriz = malloc(lin * col * sizeof(int));
    
    for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col; j++) {
            printf("Elemento [%d][%d]: ", j, i);
            
            while (true) {
                scanf("%d", &elemento);
    
                if (elemento < 10 && elemento >= 0) {
                    break;
                } else {
                    printf("DIGITE UM NÚMERO VÁLIDO: ");
                }
            }
            matriz[i * col + j] = elemento;
        }
    }
    
    printf("\n === MATRIZ ===\n");
    
    for (int z = 0; z < lin; z++) {
        if (z == 0) {
            printf(" \033[36m  %d\033[m", z);
        } else {
            printf(" \033[36m %d\033[m", z);
        }
        if (z == lin - 1) {
            printf("\n");
        }
    }
    
    for (int i = 0; i < lin; i++) {
        printf(" \033[36m%d\033[m", i);
        for (int j = 0; j < col; j++) {
            printf(" %d ", matriz[i * col + j]);
            
            if (j == col - 1) {
                printf("\n");
            }
        }
    }
    
    if (matriz != NULL) {
        free(matriz);
    }
    
    return 0;
}
