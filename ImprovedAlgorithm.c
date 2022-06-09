//
// Created by Jorge  Lopes on 08/01/2020.
//

#include "ImprovedAlgorithm.h"

/*!
 * \brief Função Principal do Algoritmo-Improved
 * \details A função recebe um tabuleiro que se pretende resolver.
 * @param board Tabuleiro
 * @return
 */
double main_ImprovedAlgorithm(BOARD *board) {
    double cost_improved = 0;
    Solve_ImprovedAlgorithm(board, board->first_cel, board->size, &cost_improved);
    printf("Cost_ImprovedAlgorithm=%.0f\n", cost_improved);

    return cost_improved;
}

/*!
 * \brief Resolve o SudokuX (Improved Algorithm)
 * \details Recebe um tabuleiro parcialmente preenchido e tenta resolver o tabuleiro com numeros de 1 a Size em
 * todos os locais ainda não preencidos (0) de forma a cumprir as regras para a solução do SudokuX (sem duplicação em
 * linhas, colunas, quadrados internos (box's), diagonais principal e secundária). Se este algoritmo melhorado não
 * conseguir resolver totalmente o tabuleiro, voltamos a chamar o brute-force para terminar a sua resolução.
 * @param first_cel Primeira célula do tabuleiro
 * @param size Dimensão do tabuleiro
 * @return
 */
void Solve_ImprovedAlgorithm(BOARD *board, CEL *first_cel, int size, double *cost_improved) {
    int encontrado = 1;
    while (encontrado) {
        *cost_improved = *cost_improved + 1;
        NakedSingles(first_cel, size);
        /*printf("NakedSingles: \n");
        Print_Struct(first_cel); //     <<<<<<<<<-------------------*/
        encontrado = 0;
        CEL *cel_atual = first_cel;
        CEL *linha_atual = first_cel;
        while (linha_atual != NULL) {
            while (cel_atual != NULL) {
                for (int i = 0; i < size; ++i) {
                    if (*(cel_atual->possibilities + i) != 0) {
                        if (HiddenSingles(first_cel, cel_atual, size, i)) {
                            *cost_improved = *cost_improved + 1;
                            encontrado = 1;
                        }
                    }
                }
                cel_atual = cel_atual->pe;
            }
            linha_atual = linha_atual->ps;
            cel_atual = linha_atual;
        }
        /*printf("HiddenSigles: \n");
        Print_Struct(first_cel); //     <<<<<<<<<-------------------*/
        NakedPairs(first_cel, size);
        findPossibilities(first_cel, size);
        /*printf("NakedPairs: \n");
        Print_Struct(first_cel); //     <<<<<<<<<-------------------*/
    }
    //printf("END: \n");
    Print_Struct(first_cel); //     <<<<<<<<<-------------------
    solutions_txt(board, "solutions.txt");
    solutions_bin(board, "solutions_bin");
}

/*!
 * \brief Rule: Naked Singles
 * \details Esta função é responsável por verificar se nas possibilidades de cada célula. Se nessa célula existir apenas
 * uma possibilidade é porque essa possibilidade é o número que tem que ficar colocado nessa célula.
 * @param first_cel Primeira célula do tabuleiro
 * @param size Dimensão do tabuleiro
 * @return
 */
int NakedSingles(CEL *first_cel, int size) { //Encontra números sozinhos - que só tem aquela possibilidade
    CEL *cel_atual = first_cel;
    CEL *linha_atual = first_cel;
    while (linha_atual != NULL) {
        while (cel_atual != NULL) {
            int count = 0, aux = 0;
            if (cel_atual->info == 0) {
                for (int i = 0; i < size; i++) {
                    if (*(cel_atual->possibilities + i) != 0) {
                        aux = *(cel_atual->possibilities + i);
                        count++;
                    }
                }
                if (count == 1 && aux != 0) {
                    cel_atual->info = aux;
                    findPossibilities(first_cel, size);
                    //printf("aux:%d\n",aux);
                    return 1;
                }
            }
            cel_atual = cel_atual->pe;
        }
        linha_atual = linha_atual->ps;
        cel_atual = linha_atual;
    }
    return 0;
}

/*!
 * \brief Rule: Hidden Singles
 * \details Esta função é responsável por procurar uma célula que não esteja resolvida e que seja a única célula onde
 * o número passado possa ser colocado relativamente à linha, coluna, diagonal principal/secundária ou box/região.
 * @param first_cel Primeira célula do tabuleiro
 * @param cel_atual Célula atual
 * @param size Dimensão do tabuleiro
 * @param num Número
 * @return
 */
int HiddenSingles(CEL *first_cel, CEL *cel_atual, int size, int num) {
    CEL *cel_aux;
    // ------------------------------------------- LINHAS ------------------------------------------- //
    int encontrado = 1;
    cel_aux = cel_atual->pe;
    while (cel_aux != NULL) {
        //percorre este e ve as possibilidades, se encontrar 1 é pq ha varias
        if (*(cel_aux->possibilities + num) != 0) {
            encontrado = 0;
            break;
        }
        cel_aux = cel_aux->pe;
    }
    cel_aux = cel_atual->po;
    while (cel_aux != NULL) {
        //percorre este e ve as possibilidades, se encontrar 1 é pq ha varias
        if (*(cel_aux->possibilities + num) != 0) {
            encontrado = 0;
            break;
        }
        cel_aux = cel_aux->po;
    }
    if (encontrado) { //se tiver encontrado single, adicionar ao tabuleiro
        cel_atual->info = num + 1;
        findPossibilities(first_cel, size);
        return 1;
    }

    // ------------------------------------------- COLUNAS ------------------------------------------- //
    encontrado = 1;
    cel_aux = cel_atual->ps;
    while (cel_aux != NULL) {
        //percorre este e ve as possibilidades, se encontrar 1 é pq ha varias
        if (*(cel_aux->possibilities + num) != 0) {
            encontrado = 0;
            break;
        }
        cel_aux = cel_aux->ps;
    }
    cel_aux = cel_atual->pn;
    while (cel_aux != NULL) {
        //percorre este e ve as possibilidades, se encontrar 1 é pq ha varias
        if (*(cel_aux->possibilities + num) != 0) {
            encontrado = 0;
            break;
        }
        cel_aux = cel_aux->pn;
    }
    if (encontrado) { //se tiver encontrado single, adicionar ao tabuleiro
        cel_atual->info = num + 1;
        findPossibilities(first_cel, size);
        return 1;
    }
    // ------------------------------------------- DIAGONAL PRINCIPAL ------------------------------------------- //
    if (cel_atual->l == cel_atual->c) {
        encontrado = 1;
        cel_aux = cel_atual->pno;
        while (cel_aux != NULL) {
            //percorre este e ve as possibilidades, se encontrar 1 é pq ha varias
            if (*(cel_aux->possibilities + num) != 0) {
                encontrado = 0;
                break;
            }
            cel_aux = cel_aux->pno;
        }
        cel_aux = cel_atual->pse;
        while (cel_aux != NULL) {
            //percorre este e ve as possibilidades, se encontrar 1 é pq ha varias
            if (*(cel_aux->possibilities + num) != 0) {
                encontrado = 0;
                break;
            }
            cel_aux = cel_aux->pse;
        }
        if (encontrado) { //se tiver encontrado single, adicionar ao tabuleiro
            cel_atual->info = num + 1;
            findPossibilities(first_cel, size);
            return 1;
        }
    }
    // ------------------------------------------- DIAGONAL SECUNDÁRIA ------------------------------------------- //
    if (cel_atual->l + cel_atual->c == size - 1) {
        encontrado = 1;
        cel_aux = cel_atual->pso;
        while (cel_aux != NULL) {
            //percorre este e ve as possibilidades, se encontrar 1 é pq ha varias
            if (*(cel_aux->possibilities + num) != 0) {
                encontrado = 0;
                break;
            }
            cel_aux = cel_aux->pso;
        }
        cel_aux = cel_atual->pne;
        while (cel_aux != NULL) {
            //percorre este e ve as possibilidades, se encontrar 1 é pq ha varias
            if (*(cel_aux->possibilities + num) != 0) {
                encontrado = 0;
                break;
            }
            cel_aux = cel_aux->pne;
        }
        if (encontrado) { //se tiver encontrado single, adicionar ao tabuleiro
            cel_atual->info = num + 1;
            findPossibilities(first_cel, size);
            return 1;
        }
    }


    // ------------------------------------------- BOX's / REGIÕES ------------------------------------------- //
    encontrado = 1;
    cel_aux = first_cel;
    int squareN = sqrt(size);
    int RowIndex = cel_atual->l - cel_atual->l % squareN;
    int ColIndex = cel_atual->c - cel_atual->c % squareN;
    for (int i = 0; i < RowIndex; ++i) {
        cel_aux = cel_aux->ps;
    }
    for (int j = 0; j < ColIndex; ++j) {
        cel_aux = cel_aux->pe;
    }
    // Após estes 2 ciclos - Descubro a posição do canto superior esquerdo do quadrado interno
    CEL *box_first_cel = cel_aux;
    for (int k = 0; k < squareN; ++k) {
        for (int i = 0; i < squareN; ++i) {        // Porque nao queremos testar a cel atual
            if (*(cel_aux->possibilities + num) != 0 && !(k == RowIndex && i == ColIndex)) {
                encontrado = 0;
            }
            cel_aux = cel_aux->pe;
        }
        cel_aux = box_first_cel->ps;
        box_first_cel = box_first_cel->ps;
    }
    if (encontrado) { //se tiver encontrado single, adicionar ao tabuleiro
        cel_atual->info = num + 1;
        findPossibilities(first_cel, size);
        return 1;
    }

    return 0;
}

/*!
 * \brief Rule: Naked Pairs
 * \details Esta função proruca no tabuleiro (linhas, colunas, diagonais e box's/regiões) duas células que apenas tenham
 * 2 possibilidades de resolução. Quando encontra eliminamos essas mesmas possibilidades nas restantes células vizinhas
 * (linhas, colunas, diagonais e box's/regiões, respetivamente).
 * @param first_cel Primeira célula do tabuleiro
 * @param size Dimensão do tabuleiro
 * @return
 */
int NakedPairs(CEL *first_cel, int size) {
    CEL *board_first_cel_line;
    CEL *celA;
    CEL *celA_aux;
    CEL *celB;
    CEL *celB_aux;
    // ------------------------------------------- LINHAS ------------------------------------------- //
    board_first_cel_line = first_cel;
    celA = first_cel;
    while (board_first_cel_line != NULL) {
        while (celA != NULL) {
            if (celA->info == 0) {
                celB = celA->pe;
                while (celB != NULL) {
                    if (celB->info == 0) {
                        if (compare2Cels(celA, celB, size) == 2) { // Só existem 2 possibilidades
                            celA_aux = celA->pe;
                            while (celA_aux != celB) {
                                if (celA_aux->info == 0) {
                                    removePossibilities(celA, celA_aux, size);
                                }
                                celA_aux = celA_aux->pe;
                            }
                            celA_aux = celA->po;
                            while (celA_aux != NULL) {
                                if (celA_aux->info == 0) {
                                    removePossibilities(celA, celA_aux, size);
                                }
                                celA_aux = celA_aux->po;
                            }
                            celB_aux = celB->pe;
                            while (celB_aux != NULL) {
                                if (celB_aux->info == 0) {
                                    removePossibilities(celB, celB_aux, size);
                                }
                                celB_aux = celB_aux->pe;
                            }
                        }
                    }
                    celB = celB->pe;
                }
            }
            celA = celA->pe;
        }
        board_first_cel_line = board_first_cel_line->ps;
        celA = board_first_cel_line;
    }
    // ------------------------------------------- COLUNAS ------------------------------------------- //
    CEL *board_first_cel_col = first_cel;
    celA = first_cel;
    while (board_first_cel_col != NULL) {
        while (celA != NULL) {
            if (celA->info == 0) {
                celB = celA->ps;
                while (celB != NULL) {
                    if (celB->info == 0) {
                        if (compare2Cels(celA, celB, size) == 2) { // Só existem 2 possibilidades
                            celA_aux = celA->ps;
                            while (celA_aux != celB) {
                                if (celA_aux->info == 0) {
                                    removePossibilities(celA, celA_aux, size);
                                }
                                celA_aux = celA_aux->ps;
                            }
                            celA_aux = celA->pn;
                            while (celA_aux != NULL) {
                                if (celA_aux->info == 0) {
                                    removePossibilities(celA, celA_aux, size);
                                }
                                celA_aux = celA_aux->pn;
                            }
                            celB_aux = celB->ps;
                            while (celB_aux != NULL) {
                                if (celB_aux->info == 0) {
                                    removePossibilities(celB, celB_aux, size);
                                }
                                celB_aux = celB_aux->ps;
                            }
                        }
                    }
                    celB = celB->ps;
                }
            }
            celA = celA->ps;
        }
        board_first_cel_col = board_first_cel_col->pe;
        celA = board_first_cel_col;
    }
    // ------------------------------------------- DIAGONAL PRINCIPAL ------------------------------------------- //
    CEL *board_first_cel_diag = first_cel;
    celA = first_cel;
    while (board_first_cel_diag != NULL) {
        while (celA != NULL) {
            if (celA->info == 0) {
                celB = celA->pse;
                while (celB != NULL) {
                    if (celB->info == 0) {
                        if (compare2Cels(celA, celB, size) == 2) { // Só existem 2 possibilidades
                            celA_aux = celA->pse;
                            while (celA_aux != celB) {
                                if (celA_aux->info == 0) {
                                    removePossibilities(celA, celA_aux, size);
                                }
                                celA_aux = celA_aux->pse;
                            }
                            celA_aux = celA->pno;
                            while (celA_aux != NULL) {
                                if (celA_aux->info == 0) {
                                    removePossibilities(celA, celA_aux, size);
                                }
                                celA_aux = celA_aux->pno;
                            }
                            celB_aux = celB->pse;
                            while (celB_aux != NULL) {
                                if (celB_aux->info == 0) {
                                    removePossibilities(celB, celB_aux, size);
                                }
                                celB_aux = celB_aux->pse;
                            }
                        }
                    }
                    celB = celB->pse;
                }
            }
            celA = celA->pse;
        }
        board_first_cel_diag = board_first_cel_diag->pse;
        celA = board_first_cel_diag;
    }
    // ------------------------------------------- DIAGONAL SECUNDÁRIA ------------------------------------------- //
    CEL *board_first_cel_diag_sec = first_cel;
    celA = first_cel;
    while (board_first_cel_diag_sec != NULL) {
        while (celA != NULL) {
            if (celA->info == 0) {
                celB = celA->pso;
                while (celB != NULL) {
                    if (celB->info == 0) {
                        if (compare2Cels(celA, celB, size) == 2) { // Só existem 2 possibilidades
                            celA_aux = celA->pso;
                            while (celA_aux != celB) {
                                if (celA_aux->info == 0) {
                                    removePossibilities(celA, celA_aux, size);
                                }
                                celA_aux = celA_aux->pso;
                            }
                            celA_aux = celA->pne;
                            while (celA_aux != NULL) {
                                if (celA_aux->info == 0) {
                                    removePossibilities(celA, celA_aux, size);
                                }
                                celA_aux = celA_aux->pne;
                            }
                            celB_aux = celB->pso;
                            while (celB_aux != NULL) {
                                if (celB_aux->info == 0) {
                                    removePossibilities(celB, celB_aux, size);
                                }
                                celB_aux = celB_aux->pso;
                            }
                        }
                    }
                    celB = celB->pso;
                }
            }
            celA = celA->pso;
        }
        board_first_cel_diag_sec = board_first_cel_diag_sec->pso;
        celA = board_first_cel_diag_sec;
    }
    return 0;
}

/*!
 * \brief Comparar duas células
 * \details A função recebe duas células para serem comparadas relativamente ao número de possibilidades. Se ambas as
 * as células passadas tiverem apenas 2 possibilidades e sejam as mesmas, então retornamos essa informação para a função
 * onde é chamada uma vez que se não encontrar queremos avançar para as células seguintes.
 * @param cel_atual Célula A
 * @param cel_next Célula B
 * @param size Dimensão do tabuleiro
 * @return
 */
int compare2Cels(CEL *cel_atual, CEL *cel_next, int size) {
    int countPossibilities = 0;
    for (int i = 0; i < size; ++i) {
        if (*(cel_atual->possibilities + i) != *(cel_next->possibilities + i)) {
            return 0;
        }
        if (*(cel_atual->possibilities + i) != 0) {
            countPossibilities++;
        }
    }
    return countPossibilities == 2;
}

/*!
 * \brief Remover as possibilidades da célula
 * \details Esta função recebe uma célula A e uma célula B. Se a possibilidade na célula A for igual à possibilidade na
 * B podemos então remover (igualar a 0) essa possibilidade na célula B.
 * @param cel_atual Célula atual
 * @param celB Célula para remover
 * @param size Dimensão do tabuleiro
 */
void removePossibilities(CEL *cel_atual, CEL *celB, int size) {
    for (int i = 0; i < size; ++i) {
        if (*(cel_atual->possibilities + i) == *(celB->possibilities + i)) {
            *(celB->possibilities + i) = 0;
        }
    }
}

/*!
 * \brief Rule: Pointing Pairs
 * \details Esta função procura numa box/região a existência de duas possibilidades iguais em células vizinhas. Por exemplo,
 * se o par de possibilidades encontrado numa box/região se encontrar alinhado numa linha então, essas possibilidades podem
 * ser removidas nas células restantes dessa mesma linha. Por outro lado, se o par de possibilidades encontrado numa
 * box/região se encontrar alinhado numa coluna então, essas possibilidades podem ser removidas nas células restantes
 * dessa mesma coluna.
 * @param first_cel Primeira célula do tabuleiro
 * @param cel_atual célula atual
 * @param size Dimensão do tabuleiro
 * @param num Número
 * @return
 */
int PointingPairs(CEL *first_cel, CEL *cel_atual, int size, int num) {
    CEL *cel_aux;
    cel_aux = first_cel;
    int squareN = sqrt(size);
    int RowIndex = cel_atual->l - cel_atual->l % squareN;
    int ColIndex = cel_atual->c - cel_atual->c % squareN;
    for (int i = 0; i < RowIndex; ++i) {
        cel_aux = cel_aux->ps;
    }
    for (int j = 0; j < ColIndex; ++j) {
        cel_aux = cel_aux->pe;
    }
    // Após estes 2 ciclos - Descubro a posição do canto superior esquerdo do quadrado interno
    CEL *box_first_cel = cel_aux;
    CEL *next_cel;

    for (int i = 0; i < squareN; ++i) { //linhas
        for (int j = 0; j < squareN; ++j) { //colunas
            next_cel=cel_aux->pe;
            for (int k = j + 1; k < squareN; ++k) { //celula a seguir
                if (cel_aux->info == 0) {
                    if (compare2Cels(cel_aux,next_cel,size) == 2){
                        removePossibilities(cel_aux,next_cel,size);
                    }
                    next_cel=next_cel->pe;
                }
            }
            next_cel=cel_aux->ps;
            for (int k = j + 1; k < squareN; ++k) { //celula a seguir
                if (cel_aux->info == 0) {
                    if (compare2Cels(cel_aux,next_cel,size) == 2){
                        removePossibilities(cel_aux,next_cel,size);
                    }
                    next_cel=next_cel->ps;
                }
            }

            cel_aux = cel_aux->pe;
        }
        cel_aux = box_first_cel->ps;
        box_first_cel = box_first_cel->ps;
    }

    return 0;
}

