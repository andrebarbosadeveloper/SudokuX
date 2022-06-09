//
// Created by Jorge  Lopes on 01/01/2020.
//

#ifndef UNTITLED1_MAIN_H
#define UNTITLED1_MAIN_H
/*!
 * \brief Estrutura CEL
 * \details Contém informações como o número presente em cada célula (info), as cordenadas (l,c) e possibilidades (1 a size)
 * de resolução para essa mesma célula. Incluim ainda os apontadores para as células vizinhas.
 */
typedef struct cel {
    int info;
    int l,c;
    int *possibilities;
    struct cel *pn,*ps,*po,*pe,
            *pno,*pne,*pso,*pse;
} CEL;

/*!
 * \brief Estrutura BOARD
 * \details Contém informações como o tamanho do tabuleiro, a primeira célula do mesmo e ainda um apontador para o tabuleiro
 * seguinte.
 */
typedef struct board {
    int size;
    CEL *first_cel;
    struct board *board_next;
}BOARD;

void client_R9();
void client_R10();
void client_R11();
void client_R12();
void client_R13();
void client_R14();
void client_R15();

CEL *lista_ligada_create_connect(int size);
BOARD *load_from_file(char *file_name);
void Print_Struct(CEL *first_cel);
void Print_Diagonals(CEL *first_cel);
void findPossibilities(CEL *first_cel, int size);
void solutions_txt(BOARD *board, char fn[]);
void solutions_bin(BOARD *board, char fn[]);

#endif //UNTITLED1_MAIN_H
