#include <stdio.h>
#include <stdlib.h>


void showMenu(void) {
    printf("\n\033[32m======== VECTOR PARTY ========\033[0m\n");
    printf("\033[31m[ 1 ] \033[34mADICIONAR VALORES\033[0m\n");
    printf("\033[31m[ 2 ] \033[34mREMOVER VALORES\033[0m\n");
    printf("\033[31m[ 3xx ] \033[34mREMOVER VALORES POR POSIÇÃO\033[0m\n");
    printf("\033[31m[ 4 ] \033[34mSUBSTITUIR VALORES\033[0m\n");
    printf("\033[31m[ 5xx ] \033[34mSUBSTITUIR VALORES POR POSIÇÃO\033[0m\n");
    printf("\033[31m[ 6 ] \033[34mTAMANHO DO VETOR\033[0m\n");
    printf("\033[31m[ 7 ] \033[34mSOMATÓTIO DOS VALORES\033[0m\n");
    printf("\033[31m[ 8 ] \033[34mMÉDIA DOS VALORES\033[0m\n");
    printf("\033[31m[ 9 ] \033[34mORDENAR VETOR EM ORDEM CRESCENTE\033[0m\n");
    printf("\033[31m[ 10 ] \033[34mORDENAR VETOR EM ORDEM DECRESCENTE\033[0m\n");
    printf("\033[31m[ 11xx ] \033[34mEMBARALHAR VETOR\033[0m\n");
    printf("\033[31m[ 12 ] \033[34mNÚMERO DE OCORRÊNCIAS DE UM VALOR\033[0m\n");
    printf("\033[33m[ 98 ] \033[33mSALVAR VALORES EM ARQUIVO\033[0m\n");
    printf("\033[33m[ 99 ] \033[33mDESFAZER A MODIFICAÇÃO ANTERIOR\033[0m\n");
    printf("\033[31m[ 0 ] \033[34mSAIR\033[0m\n");
}


int* createBackup(int *vector, int qtd) {
    int *backup = (int *)malloc(qtd * sizeof(int));
    if (backup == NULL) {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA PARA O BACKUP\n");
        exit(1);
    }

    for (int i = 0; i < qtd; i++) {
        backup[i] = vector[i];
    }
    return backup;
}


void restoreFromBackup(int **vector, int *qtd, int *backup, int backupSize) {
    free(*vector);

    *vector = (int *)malloc(backupSize * sizeof(int));
    
    if (*vector == NULL) {
        printf("ERRO NA ALOCAÇÃO DE MEMÓRIA PARA RESTAURAÇÃO\n");
        exit(1);
    }

    for (int i = 0; i < backupSize; i++) {
        (*vector)[i] = backup[i];
    }
    *qtd = backupSize;
}


void performBackup(int **vector, int **backupVector, int *backupSize, int qtd) {
    if (backupVector != NULL) {
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


int countOccurrences(int *vector, int qtd, int value) {
    int count;

    count = 0;
    for (int i = 0; i < qtd; i++) {
        if (vector[i] == value) {
            count++;
        }
    }
    return count;
}


double averageVector(int *vector, int qtd) {
    long long sum;
    double average;

    sum = 0;
    for (int i = 0; i < qtd; i++) {
        sum += vector[i];
    }

    return (double)sum / qtd;
}


int sumVector(int *vector, int qtd) {
    long long sum;

    sum = 0;
    for (int i = 0; i < qtd; i++) {
        sum += vector[i];
    }
    return sum;
}


void sortVector(int *vector, int qtd, int order) {
    int temp;

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - i - 1; j++) {
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
     for (int index = 0; index < qtd; index++) {
         if (vector[index] == numberToReplace) {
             vector[index] = newNumber;
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


void removeNumber(int *vector, int *qtd, int valueToRemove) {
    int i, j;
    int found = 0;

    for (i = 0; i < *qtd; ) {
        if (vector[i] == valueToRemove) {
            found = 1;
            for (j = i; j < *qtd - 1; j++) {
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
    printf("\n\033[38;2;255;0;0mVETOR ATUAL -->\033[0m ");
    printf("[");
    for (int i = 0; i < qtd; i++) {
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
    int *vector, qtd, choice, *backupVector = NULL, backupSize = 0;

    printf("\n\033[32m===== BEM VINDO(A) À APLICAÇÃO VECTOR PARTY =====\033[0m\n");

    printf("\n--> Digite a Quantidade de Valores Inicial do Vetor: ");
    scanf("%d", &qtd);

    vector = addVector(qtd);

    printf("\n--> Digite os %d Valores Separados Por Espaço ou Linha: ", qtd);
    for (int i = 0; i < qtd; i++) {
        scanf("%d", &vector[i]);
    }

    choice = 1;
    while (choice != 0) {
        clearScreen();
        showVector(vector, qtd);
        showMenu();

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
                for (int i = 0; i < qtdNumerosToRemove; i++) {
                    scanf("%d", &valueToRemove);
                    removeNumber(vector, &qtd, valueToRemove);
                }

                break;
            }

            case 3: {

            }

            case 4: {
                int qtdNumbersToReplace, numberToReplace, newNumber, count = 1;
                performBackup(&vector, &backupVector, &backupSize, qtd);

                printf("\nDigite Quantos Valores Deseja Substituir: ");
                scanf("%d", &qtdNumbersToReplace);

                for (int i = 0; i < qtdNumbersToReplace; i++) {
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
                int order = 1;
                performBackup(&vector, &backupVector, &backupSize, qtd);
                sortVector(vector, qtd, order);

                break;
            }

            case 10: {
                int order = 2;
                performBackup(&vector, &backupVector, &backupSize, qtd);
                sortVector(vector, qtd, order);

                break;
            }

            case 11: {

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

            case 0:
                printf("Saindo...\n");

                break;

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
    free(vector);

    if (backupVector != NULL) {
        free(backupVector);
    }
    return 0;
}
