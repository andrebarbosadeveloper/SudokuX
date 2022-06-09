//
// Created by Jorge  Lopes on 01/01/2020.
//

#include "BruteForce.h"

/*!
 * \brief Função Principal do Algoritmo Brute-force (Back Tracking Search)
 * \details A função recebe um tabuleiro que se pretende resolver e o respetivo tamanho do mesmo.
 * @param board Tabuleiro
 * @return
 */
double main_bruteforce(BOARD *board) {
    double cost = 0;
    SolveSudoku_BruteForce(board,board->first_cel, board->size, &cost);
    printf("Cost_BruteForce=%.0f\n", cost);

    return cost;
}

/*!
 * \brief Resolve o SudokuX (Brute-force (Back Tracking Search))
 * \details Recebe um tabuleiro parcialmente preenchido e tenta resolver o tabuleiro com numeros de 1 a Size em
 * todos os locais ainda não preencidos (0) de forma a cumprir as regras para a solução do SudokuX
 * (sem duplicação em linhas, colunas, regiões (box's), diagonais principal e secundária).
 * @param board Tabuleiro
 * @param first_cel Primeira célula do tabuleiro
 * @param sizeN Dimensão do tabuleiro
 * @param cost Cost - Número de iterações
 * @return
 */
int SolveSudoku_BruteForce(BOARD *board, CEL *first_cel, int sizeN, double *cost) {
    CEL *current_cel = NULL;
    // num_solutions passado como parametro
    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(first_cel, &current_cel)) {
        /* A utility function to print grid */
        Print_Struct(first_cel); // Se quiser imprimir para a consola
        solutions_txt(board,"solutions.txt");
        solutions_bin(board,"solutions_bin");
        return 1; // success!  Se return 1 quer dizer que nao existe mais nenhum espaco em branco (0)
    }
    // consider digits 1 to N
    for (int num = 1; num <= sizeN; num++) {
        *cost = *cost + 1;
        // if looks promising
        if (isSafe(current_cel, first_cel,num, sizeN)) {
            // make tentative assignment
            current_cel->info = num;
            //printf("%d\n",current_cel->info);
            if (SolveSudoku_BruteForce(board,first_cel, sizeN, cost)) {
                return 1; // return, if success, yay!
            }
            // failure, unmake & try again
            current_cel->info = UNASSIGNED;
        }
    }
    return 0; // this triggers backtracking
}


/*!
 * \brief Procura posição não preenchida (0)
 * \details A função percorre o tabuleiro passado (linhas e colunas) à procura de células não preenchidas (0).
 * Se for encontrada uma célula por preencher ( a "0"), a função retorna 1 (True), se a célula estiver
 * preenchida (num de 1 a Size), a função retorna 0 (False).
 * @param first_cel Primeira célula do tabuleiro
 * @param empty_cel Célula vazia
 * @return
 */
int FindUnassignedLocation(CEL *first_cel, CEL **empty_cel) {
    CEL *aux_first_cel;
    aux_first_cel = first_cel;
    while (aux_first_cel != NULL) {
        while (aux_first_cel != NULL) {
            *empty_cel = aux_first_cel;
            if ((*empty_cel)->info == UNASSIGNED)
                return 1;
            aux_first_cel = aux_first_cel->pe; //Mudança de linha
        }
        first_cel=first_cel->ps;
        aux_first_cel=first_cel;
    }
    return 0;
}

/*!
 * \brief Verifica se o numero é usado na linha
 * \details A função percorre as colunas da linha em que se encontra a célula passada e se o número passado for encontrado
 * nessa mesma linha,a função retorna 1 (True), caso contrário (o número não foi encontrado), retorna 0 (False).
 * @param cel Célula atual
 * @param num Número
 * @return
 */
int UsedInRow(CEL *cel,int num) {
    CEL *aux_cel=NULL;
    aux_cel=cel;
    while (aux_cel != NULL) {  //Used In Line
        if (aux_cel->info == num) {
            return 1;
        }
        aux_cel= aux_cel->pe;
    }
    aux_cel=cel;
    while (aux_cel != NULL) {  //Used In Line
        if (aux_cel->info == num) {
            return 1;
        }
        aux_cel = aux_cel->po;
    }
    return 0;
}

/*!
 * \brief Verifica se o numero é usado na coluna
 * \details A função percorre as linhas da coluna em que se encontra a célula passada e se o número passado for encontrado
 * nessa mesma linha,a função retorna 1 (True), caso contrário (o número não foi encontrado), retorna 0 (False).
 * @param cel Célula atual
 * @param num Número
 * @return
 */
int UsedInCol(CEL *cel,int num) {
    CEL *aux_cel=NULL;
    aux_cel=cel;
    while (aux_cel != NULL) {  //Used In Column
        if (aux_cel->info == num) {
            return 1;
        }
        aux_cel = aux_cel->ps;
    }
    aux_cel=cel;
    while (aux_cel != NULL) {  //Used In Column
        if (aux_cel->info == num) {
            return 1;
        }
        aux_cel = aux_cel->pn;
    }
    return 0;
}

/*!
 * \brief Verifica se o numero é usado na diagonal principal.
 * \details Se a posição da linha for igual à posição da coluna (ex: 0,0 / 5,5), a função percorre a diagonal principal
 * e, se o número passado for encontrado nessa diagonal, a função retorna 1 (True), caso contrário (o número não foi
 * encontrado), retorna 0 (False).
 * @param cel Célula atual
 * @param num Número
 * @return
 */
int MainDiagonal(CEL *cel, int num) {
    CEL *aux_cel = NULL;
    aux_cel = cel;
    if (aux_cel->l == aux_cel->c) {
        while (aux_cel != NULL) {  //Used In Diagonal Principal
            if (aux_cel->info == num) {
                return 1;
            }
            aux_cel = aux_cel->pse;
        }
        aux_cel = cel;
        while (aux_cel != NULL) {  //Used In Diagonal Principal
            if (aux_cel->info == num) {
                return 1;
            }
            aux_cel = aux_cel->pno;
        }
    }
    return 0;
}

/*!
 * \brief Verifica se o numero é usado na diagonal secundária.
 * \details Se a soma das posições das linhas com as colunas for igual ao tamanho do tabuleiro menos 1, a função
 * percorre a diagonal secundária e, se o número passado for encontrado nessa diagonal, a função retorna 1 (True),
 * caso contrário (o número não foi encontrado), retorna 0 (False).
 * @param cel Célula atual
 * @param num Número
 * @param sizeN Dimensão do tabuleiro
 * @return
 */
int SecondaryDiagonal(CEL *cel,int num, int sizeN) {
    CEL *aux_cel=NULL;
    aux_cel=cel;
    if (cel->l + cel->c == sizeN - 1) {
        while (aux_cel != NULL) {  //Used In Diagonal Secundária
            if (aux_cel->info == num) {
                return 1;
            }
            aux_cel = aux_cel->pso;
        }
        aux_cel=cel;
        while (aux_cel != NULL) {  //Used In Diagonal Secundária
            if (aux_cel->info == num) {
                return 1;
            }
            aux_cel = aux_cel->pne;
        }
    }
    return 0;
}
/*!
 * \brief Verifica se o numero é usado nas Regiões (Box's)
 * \details Esta função começa por calcular os índices (linha e coluna do tabuleiro) da célula que é passada.
 * Após descobertos os índices, a primeira célula do tabuleiro é iterada até chegar à primeira célula da box/região onde
 * se encontra a célula que é passada (cel). De seguida, a primeira célula da box/região é iterada ao longo dessa mesma
 * box/região e, se o número passado for encontrado nessa box/região, a função retorna 1 (True), caso contrário (o número
 * não foi encontrado), retorna 0 (False).
 * @param cel Célula atual
 * @param first_cel Primeira célula do tabuleiro
 * @param num Número
 * @param sizeN Dimensão do tabuleiro
 * @return
 */
int UsedInBox(CEL *cel, CEL *first_cel, int num, int sizeN) {
    CEL *aux_cel=first_cel;
    int squareN = sqrt(sizeN);
    int RowIndex= cel->l - cel->l % squareN;
    int ColIndex= cel->c - cel->c % squareN;

    for (int i = 0; i < RowIndex; ++i){
        aux_cel=aux_cel->ps;
    }
    for (int j = 0 ; j < ColIndex ; ++j){
        aux_cel=aux_cel->pe;
    }
    // Após estes 2 ciclos - Descubro a posição do canto superior esquerdo da box/região
    CEL *box_first_cel= aux_cel;
    for (int k = 0; k < squareN; ++k) {
        for (int i = 0; i < squareN ; ++i) {
            if(aux_cel->info==num){
                //printf("used in box: %d %d %d\n", cel->l,cel->c,num);
                return 1;
            }
            aux_cel=aux_cel->pe;

        }
        aux_cel= box_first_cel->ps;
        box_first_cel=box_first_cel->ps;
    }
    return 0;
}
/*!
 * \brief Verifica se é seguro colocar o número
 * \details Com base nas funções de teste das regras do SudokuX, a função indica se será possível colocar o número célula
 * que é passada.
 * @param cel Célula atual
 * @param first_cel Primeira célula do tabuleiro
 * @param num Número
 * @param sizeN Dimensão do tabuleiro
 * @return
 */
int isSafe(CEL *cel, CEL *first_cel, int num, int sizeN) {
    return !UsedInRow(cel, num) &&
           !UsedInCol(cel,num) &&
           !UsedInBox(cel, first_cel, num, sizeN) &&
           !MainDiagonal(cel, num) &&
           !SecondaryDiagonal(cel, num, sizeN) &&
           cel->info == UNASSIGNED;
}