#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int option;
    const char *description;
} MenuOption;

MenuOption menu[] = {
    {1, "ADICIONAR VALORES"},
    {2, "REMOVER VALORES"},
    {3, "REMOVER VALORES POR POSIÇÃO"},
    {4, "SUBSTITUIR VALORES"},
    {5, "SUBSTITUIR VALORES POR POSIÇÃO"},
    {6, "TAMANHO DO VETOR"},
    {7, "SOMATÓTIO DOS VALORES"},
    {8, "MÉDIA DOS VALORES"},
    {9, "ORDENAR VETOR EM ORDEM CRESCENTE"},
    {10, "ORDENAR VETOR EM ORDEM DECRESCENTE"},
    {11, "EMBARALHAR VETOR"},
    {12, "NÚMERO DE OCORRÊNCIAS DE UM VALOR"},
    {13, "MOSTRAR QUANTIDADE DE PARES E IMPARES"},
    {14, "MOSTRAR MENOR E MAIOR VALORES E SUAS POSIÇÕES"},
    {98, "SALVAR VALORES EM ARQUIVO"},
    {99, "DESFAZER A MODIFICAÇÃO ANTERIOR"}
};


void showMenu(MenuOption menu[], int size) {
    printf("\n\033[32m======== VECTOR PARTY ========\n");
    for (int i = 0; i < size; i++) {
        printf("\033[31m[ %d ] \033[34m%s\n", menu[i].option, menu[i].description);
    }
    printf("\033[36m[ 0 ] \033[36mSAIR\033[0m\n");
}


void saveFile(int *vector, int qtd, const char *nameFile) {
    FILE *file = fopen(nameFile, "w");

    if (file == NULL) {
        printf("\nERRO AO ABRIR O ARQUIVO\n");
        exit(1);
    }

    for (int i=0; i < qtd; i++) {
        fprintf(file, "%d ", vector[i]);
    }
    fclose(file);
}


int* createBackup(int *vector, int qtd) {
    int *backup = (int *)malloc(qtd * sizeof(int));
    if (backup == NULL) {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA PARA O BACKUP\n");
        exit(1);
    }

    for (int i=0; i < qtd; i++) {
        backup[i] = vector[i];
    }
    return backup;
}


void restoreFromBackup(int **vector, int *qtd, int *backup, int backupSize) {
    if (*vector != NULL) {
        free(*vector);
    }

    *vector = (int *)malloc(backupSize * sizeof(int));

    if (*vector == NULL) {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA PARA RESTAURAÇÃO\n");
        exit(1);
    }

    for (int i=0; i < backupSize; i++) {
        (*vector)[i] = backup[i];
    }
    *qtd = backupSize;
}


void performBackup(int **vector, int **backupVector, int *backupSize, int qtd) {
    if (*backupVector != NULL) {
        free(*backupVector);
    }
    *backupVector = createBackup(*vector, qtd);
    *backupSize = qtd;
}


void pauseExecution(void) {
    printf("\nPressione ENTER Para Continuar...");

    getchar();
    getchar();
}


void clearScreen(void) {
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}


void getBiggestAndSmallest(int *vector, int *biggest, int *smallest, int *positionBiggest, int *positionSmallest, int qtd) {
    *positionSmallest = 1;
    *positionBiggest = 1;

    *smallest = vector[0];
    *biggest = vector[0];

    for (int i=0; i < qtd; i++) {
        if (vector[i] > *biggest) {
            *biggest = vector[i];
            *positionBiggest = i + 1;
        }
        if (vector[i] < *smallest) {
            *smallest = vector[i];
            *positionSmallest = i + 1;
        }
    }
}


void getEvensAndOdds(int *vector, int qtd, int *evens, int *odds) {
    *evens = 0;
    *odds = 0;

    for (int i=0; i < qtd; i++) {
        if (vector[i] % 2 == 0) {
            (*evens)++;
        } else {
            (*odds)++;
        }
    }
}


void shuffleVector(int *vector, int qtd) {
    int temp = 0;
    srand(time(NULL));

    for (int i = qtd - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        temp = vector[i];
        vector[i] = vector[j];
        vector[j] = temp;
    }
}


int countOccurrences(int *vector, int qtd, int value) {
    int count = 0;

    for (int i=0; i < qtd; i++) {
        if (vector[i] == value) {
            count++;
        }
    }
    return count;
}


double averageVector(int *vector, int qtd) {
    long long sum = 0;

    for (int i=0; i < qtd; i++) {
        sum += vector[i];
    }
    return (double)sum / qtd;
}


int sumVector(int *vector, int qtd) {
    long long sum = 0;

    for (int i=0; i < qtd; i++) {
        sum += vector[i];
    }
    return sum;
}


void sortVector(int *vector, int qtd, int order) {
    int temp = 0;

    for (int i=0; i < qtd - 1; i++) {
        for (int j=0; j < qtd - i - 1; j++) {
            if ((order == 1 && vector[j] > vector[j + 1]) ||
                (order == 2 && vector[j] < vector[j + 1])) {
                temp = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = temp;
            }
        }
    }
}


void replaceNumbers(int *vector, int qtd, int numberToReplace, int newNumber){
     for (int i=0; i < qtd; i++) {
         if (vector[i] == numberToReplace) {
             vector[i] = newNumber;
        }
     }
}


void replaceNumbersByPosition(int *vector, int qtd, int positionNumberToReplace, int newNumber) {
    for (int i=0; i < qtd; i++) {
        if (i + 1 == positionNumberToReplace) {
            vector[i] = newNumber;
        }
    }
}


int *addNumbers(int *vector, int *qtd, int qtdNumerosToAdd) {
    vector = (int *)realloc(vector, (*qtd + qtdNumerosToAdd) * sizeof(int));

    if (vector == NULL) {
        printf("ERRO NA REALOCAÇÃO DE MEMÓRIA\n");
        exit(1);
    }
    *qtd += qtdNumerosToAdd;

    return vector;
}

void removeNumbersByPosition(int *vector, int *qtd, int positionToRemove) {
    if (positionToRemove < 1 || positionToRemove > *qtd) {
        printf("POSIÇÃO FORA DOS LIMITES\n");
        exit(1);
    }

    for (int i = positionToRemove - 1; i < positionToRemove; i++) {
        vector[i] = vector[i + 1];
    }

    (*qtd)--;
}

void removeNumbers(int *vector, int *qtd, int valueToRemove) {
    int found = 0;

    for (int i=0; i < *qtd;) {
        if (vector[i] == valueToRemove) {
            found = 1;
            for (int j = i; j < *qtd - 1; j++) {
                vector[j] = vector[j + 1];
            }
            (*qtd)--;

        } else {
            i++;
        }
    }

    if (!found) {
        printf("\nVALOR NÃO ENCONTRADO NO VETOR\n");
        exit(1);
    }
}


void showVector(int *vector, int qtd) {
    if (qtd == 0) {
        printf("\n\033[38;2;255;0;0mVETOR ATUAL -->\033[0m []\n");
        return;
    }

    printf("\n\033[38;2;255;0;0mVETOR ATUAL -->\033[0m ");
    printf("[");
    for (int i=0; i < qtd; i++) {
        if (i == qtd - 1) {
            printf("%d]", vector[i]);
        } else {
            printf("%d, ", vector[i]);
        }
    }
    printf("\n");
}


int *addVector(int qtd) {
    int *vector = (int *)malloc(qtd * sizeof(int));

    if (vector == NULL) {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA\n");
        exit(1);
    }
    return vector;
}


int main(void) {
    int size = sizeof(menu) / sizeof(menu[0]);
    int *vector = NULL, qtd, choice, *backupVector = NULL, backupSize = 0;

    printf("\n\033[32m===== BEM VINDO(A) À APLICAÇÃO VECTOR PARTY =====\033[0m\n");

    printf("\n--> Digite a Quantidade de Valores Inicial do Vetor: ");
    scanf("%d", &qtd);

    vector = addVector(qtd);

    printf("\n--> Digite os %d Valores Separados Por Espaço ou Linha: ", qtd);
    for (int i=0; i < qtd; i++) {
        scanf("%d", &vector[i]);
    }

    choice = 1;
    while (choice != 0) {
        clearScreen();
        showVector(vector, qtd);
        showMenu(menu,size);

        printf("\n\033[35mDigite sua Funcionalidade:\033[0m ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int qtdNumerosToAdd;
                performBackup(&vector, &backupVector, &backupSize, qtd);

                printf("\nDigite Quantos Valores Deseja Adicionar: ");
                scanf("%d", &qtdNumerosToAdd);

                vector = addNumbers(vector, &qtd, qtdNumerosToAdd);

                printf("\nDigite os Valores a Adicionar Separados Por Espaço ou Linha: ");
                for (int i = qtd - qtdNumerosToAdd; i < qtd; i++) {
                    scanf("%d", &vector[i]);
                }

                break;
            }

            case 2: {
                int qtdNumerosToRemove, valueToRemove;
                performBackup(&vector, &backupVector, &backupSize, qtd);

                printf("\nDigite Quantos Valores Deseja Remover: ");
                scanf("%d", &qtdNumerosToRemove);

                printf("\nDigite os Valores a Remover Separados Por Espaço ou Linha: ");
                for (int i=0; i < qtdNumerosToRemove; i++) {
                    scanf("%d", &valueToRemove);
                    removeNumbers(vector, &qtd, valueToRemove);
                }

                break;
            }

            case 3: {
                int qtdNumbersToReplace, positionToRemove, count = 1;
                performBackup(&vector, &backupVector, &backupSize, qtd);

                printf("\nDigite Quantos Valores Deseja Substituir: ");
                scanf("%d", &qtdNumbersToReplace);

                for (int i=0; i < qtdNumbersToReplace; i++) {
                    printf("\nDigite a Posição dp %dº Valor Que Deseja Remover: ", count);
                    scanf("%d", &positionToRemove);

                    removeNumbersByPosition(vector, &qtd, positionToRemove);
                }

                break;
            }

            case 4: {
                int qtdNumbersToReplace, numberToReplace, newNumber, count = 1;
                performBackup(&vector, &backupVector, &backupSize, qtd);

                printf("\nDigite Quantos Valores Deseja Substituir: ");
                scanf("%d", &qtdNumbersToReplace);

                for (int i=0; i < qtdNumbersToReplace; i++) {
                    printf("\nDigite o %dº Valor Que Deseja Substituir: ", count);
                    scanf("%d", &numberToReplace);

                    printf("\nDigite o Novo Valor: ");
                    scanf("%d", &newNumber);

                    replaceNumbers(vector, qtd, numberToReplace, newNumber);
                    count++;
                }

                break;
            }

            case 5: {
                int qtdNumbersToReplace, positionNumberToReplace, newNumber, count = 1;
                performBackup(&vector, &backupVector, &backupSize, qtd);

                printf("\nDigite Quantos Valores Deseja Substituir: ");
                scanf("%d", &qtdNumbersToReplace);

                for (int i=0; i < qtdNumbersToReplace; i++) {
                    printf("\nDigite a Posição do %dº Valor Que Deseja Substituir: ", count);
                    scanf("%d", &positionNumberToReplace);

                    printf("\nDigite o Novo Valor: ");
                    scanf("%d", &newNumber);

                    replaceNumbersByPosition(vector, qtd, positionNumberToReplace, newNumber);
                    count++;
                }

                break;
            }

            case 6: {
                printf("\n\033[92;47mO VETOR POSSUI %d VALORES\033[0m\n", qtd);
                pauseExecution();

                break;
            }

            case 7: {
                long long sum;

                sum = sumVector(vector, qtd);

                printf("\n\033[92;47mO SOMATÓRIO DOS VALORES É %lld\033[0m\n", sum);;
                pauseExecution();

                break;
            }

            case 8: {
                double average;

                average = averageVector(vector, qtd);

                printf("\n\033[92;47mA MÉDIA DOS VALORES É APROXIMADAMENTE %.2lf\033[0m\n", average);;
                pauseExecution();

                break;
            }

            case 9: {
                const int order = 1;
                performBackup(&vector, &backupVector, &backupSize, qtd);
                sortVector(vector, qtd, order);

                break;
            }

            case 10: {
                const int order = 2;
                performBackup(&vector, &backupVector, &backupSize, qtd);
                sortVector(vector, qtd, order);

                break;
            }

            case 11: {
                shuffleVector(vector, qtd);

                break;
            }

            case 12: {
                int value, occurrences;

                printf("\nDigite o Valor Que Deseja Verificar: ");
                scanf("%d", &value);

                occurrences = countOccurrences(vector, qtd, value);

                printf("\n\033[92;47mO VALOR %d APARECE %d VEZES NO VETOR\033[0m\n", value, occurrences);
                pauseExecution();

                break;
            }

            case 13: {
                int evens, odds;

                getEvensAndOdds(vector, qtd, &evens, &odds);

                printf("\n\033[93;42mEXISTEM %d NÚMEROS PARES NO VETOR\033[0m\n", evens);
                printf("\n\033[93;43mEXISTEM %d NÚMEROS ÍMPARES NO VETOR\033[0m\n", odds);
                pauseExecution();

                break;
            }

            case 14: {
                int positionBiggest, positionSmallest;
                int biggest, smallest;

                getBiggestAndSmallest(vector, &biggest, &smallest, &positionBiggest, &positionSmallest, qtd);

                printf("\n\033[93;42mMENOR --> %d\033[0m\n", smallest);
                printf("\n\033[93;42mPOSIÇÃO MENOR --> %d\033[0m\n\n", positionSmallest);
                printf("\n\033[93;43mMAIOR --> %d\033[0m\n", biggest);
                printf("\n\033[93;43mPOSIÇÃO MAIOR --> %d\033[0m\n", positionBiggest);
                pauseExecution();

                break;
            }

            case 15: {

            }

            case 0: {
                printf("Saindo...\n");

                break;
            }

            case 98:{
                int const MAXSIZE = 50;
                char *nameFile = (char *)malloc(MAXSIZE * sizeof(char));

                printf("\nDigite o Nome do Arquivo: ");
                scanf("%s", nameFile);

                saveFile(vector, qtd, nameFile);
                printf("\n\033[92mVETOR SALVO COM SUCESSO NO ARQUIVO '%s.txt'!\033[0m\n", nameFile);
                pauseExecution();

                free(nameFile);

                break;
            }


            case 99: {
                if (backupVector != NULL) {
                    restoreFromBackup(&vector, &qtd, backupVector, backupSize);
                    printf("\n\033[91;42mBACKUP RESTAURADO\033[0m\n");
                    pauseExecution();

                } else {
                    printf("\n\033[91;41mBACKUP INDISPONÍVEL\033[0m\n");
                    pauseExecution();
                }

                break;
            }

            default:

                break;
        }
    }
    if (vector != NULL) {}
    free(vector);

    if (backupVector != NULL) {
        free(backupVector);
    }
    return 0;
}
