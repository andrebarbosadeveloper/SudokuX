#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "BruteForce.h"
#include "ImprovedAlgorithm.h"

int main() {
    //Algumas das funções "client" têm comentários que podem justificar o código presente nessas funções.

     client_R9();
    // client_R10();
    // client_R11();
    // client_R12(); // <- Brute-Force (Backtracking)
    // client_R13(); // <- Improved Algorithm
    // client_R14();
    // client_R15();

    /*
    BOARD *boards = load_from_file("client.txt");
    BOARD *aux = boards;
    //Print_Diagonals(aux->first_cel);
    while (aux != NULL) { // Imprime todos os tabuleiros do ficheiro
        Print_Struct(aux->first_cel);
        aux = aux->board_next;
    }
    findPossibilities(boards->first_cel, boards->size);
    //main_bruteforce(boards);
    //main_ImprovedAlgorithm(boards);
     */
    return 0;
}

/*!
 * \brief Requisito 9
 * \details Permitir a construção e inicialização de um ou mais tabuleiros.
 * i) Leitura dos tabuleiros a partir de um ficheiro de texto.
 */
void client_R9(){
    BOARD *boards=load_from_file("sudokux.txt");
    /*
     * load_from_file() -> Leitura dos tabuleiros a partir de um ficheiro de texto.
     * OBS: A função descrita a baixo é chamada dentro da função descrita a cima.
     * lista_ligada_create_connect() -> Costrução e inicialização de um ou mais tabuleiros.
     *
     */
    // Imprimir todos os tabuleiros do ficheiro carregado:
    BOARD *aux = boards;
    while (aux != NULL) {
        Print_Struct(aux->first_cel);
        aux = aux->board_next;
    }
}

/*!
 * \brief Requisito 10
 * \details Permitir guardar os tabuleiros previamente carregados.
 * i) Deve usar uma estrutura de dados do tipo “fila”.
 */
void client_R10(){
    BOARD *boards=load_from_file("sudokux.txt");
    /*
     * Quando faço o carregamento/leitura dos tabuleiros para a memória utilizo uma estrutura do tipo "fila", podemos
     * confirmar isso quando peço para imprimir o primeiro tabuleiro, de seguida o segundo (etc) e estes são impressos
     * na consola pela ordem que se encontram no ficheiro de texto.
     *
     * load_from_file() -> Permitir guardar os tabuleiros previamente carregados.
     * OBS: A função descrita a baixo é chamada dentro da função descrita a cima.
     * lista_ligada_create_connect() -> Costrução e inicialização de um ou mais tabuleiros.
     *
     *
     */
    // Imprimir todos os tabuleiros do ficheiro carregado:
    BOARD *aux = boards;
    while (aux != NULL) {
        Print_Struct(aux->first_cel);
        aux = aux->board_next;
    }
}

/*!
 * \brief Requisito 11
 * \details Permitir resolver tabuleiros 9x9 (Sudoku X); 16x16 (Sudoku X), 25x25 (Sudoku), 36x36 (Sudoku).
 */
void client_R11(){
    BOARD *boards = load_from_file("client.txt");
    findPossibilities(boards->first_cel, boards->size);
    main_bruteforce(boards);
    //main_ImprovedAlgorithm(boards);
}

/*!
 * \brief Requisito 12
 * \details Permitir resolver o problema com abordagens brute-force, encontrando as soluções possíveis para os tabuleiros.
 */
void client_R12(){
    BOARD *boards = load_from_file("client.txt");
    findPossibilities(boards->first_cel, boards->size);
    main_bruteforce(boards);
}

/*!
 * \brief Requisito 13
 * \details Melhorar o algoritmo desenvolvido em R4 b) (algoritmo melhorado), utilizando estruturas ligadas, implementando estratégias que
 * melhorem a eficiência na pesquisa de uma solução possível.
 */
void client_R13(){
    BOARD *boards = load_from_file("client.txt");
    findPossibilities(boards->first_cel, boards->size);
    main_ImprovedAlgorithm(boards);
}

/*!
 * \brief Requisito 14
 * \details Permitir gerar um ficheiro de texto com os tabuleiros de números.
 */
void client_R14(){
    BOARD *boards = load_from_file("client.txt");
    findPossibilities(boards->first_cel, boards->size);
    main_bruteforce(boards);
    /*
     * solutions_txt() -> Guarda a solução do tabuleiro pretendido num ficheiro texto.
     * Esta função é chamada na função SolveSudoku_BruteForce() ao mesmo tempo que imprime essa solução para a consola.
     */
}

/*!
 * \brief Requisito 15
 * \details Permitir gerar um ficheiro binário com todos os tabuleiros de números resolvidos.
 */
void client_R15(){
    BOARD *boards = load_from_file("client.txt");
    findPossibilities(boards->first_cel, boards->size);
    main_bruteforce(boards);
    /*
     * solutions_bin() -> Guarda a solução do tabuleiro pretendido num ficheiro binário.
     * Esta função é chamada na função SolveSudoku_BruteForce() ao mesmo tempo que imprime essa solução para a consola.
     */
}

/*!
 * \brief Criar/Ligar - Listas Ligadas
 * \details Função responsável por, a partir de um ficheiro de texto, carregar para a memória os tabuleiros a resolver.
 * Neste processo, é alocada memória para cada célula sequencialmente. O tabuleiro é criado e ligado linha a linha, ou seja,
 * cria sequencialmente as células da primeira linha e de seguida avança para a segunda, criando as células dessa linha,
 * e assim sucessivamente. Após este processo inicial, obtemos o "tabuleiro" ligado horizontalmente e verticalmente. Deste modo,
 * ficam a faltar as ligações das diagonais, principal e secundária, que são feitas de seguida. Em suma, concordamos que
 * este processo escolhido irá ter um custo maior e que seria certamente possível fazê-lo num menor número de iterações, ou seja,
 * quando alocamos memoria para a célula verificar se esta se encontra na diagonal principal ou secundária, se sim, faria-se
 * a ligação com a sua anterior e essa anterior com a atual, respetivamente.
 * @param size Dimensão do tabuleiro
 * @return
 */
CEL *lista_ligada_create_connect(int size) {
    CEL *cel = NULL;
    CEL *first_cel = NULL;
    CEL *pline = NULL; //inicio da linha atual
    CEL *pcolumn = NULL; // coluna anterior
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            CEL *celula = (CEL *) calloc(1, sizeof(CEL));   // ATUAL
            celula->l = i;
            celula->c = j;
            celula->possibilities = (int *) calloc(size, sizeof(int));
            if (i == 0 && j == 0) {
                first_cel = celula;
                pline = first_cel;
            } else if (i == 0) { // Primeira Linha
                pcolumn->pe = celula;
                celula->po = pcolumn;
            } else if (j == 0) { // Primeira Coluna
                celula->pn = pline;
                pline->ps = celula;
                pline = celula;
            } else {
                //Liga a linha horrizontalmente
                celula->po = pcolumn;
                pcolumn->pe = celula;
                //Liga a linha verticalmente
                celula->pn = pcolumn->pn->pe;
                celula->pn->ps = celula;
            }
            pcolumn = celula; //Valor da coluna anterior
        }
    }
    cel = first_cel;
    while (cel->ps != NULL) { // Diagonal Principal
        cel->pse = cel->ps->pe;
        cel->ps->pe->pno = cel;
        cel = cel->pse;
    }
    cel = first_cel;
    while (cel->pe != NULL) { // Ultima Celula da Primeira Linha
        cel = cel->pe;
    }
    // Da primeira celula da linha vamos para a ultima e damos o deslocamento para so (secundária)
    while (cel->ps != NULL) { // Diagonal Secundária
        cel->pso = cel->ps->po;
        cel->pso->pne = cel;
        cel = cel->pso;
    }

    return first_cel;
}

/*!
* \brief Quais as possibilidades para cada célula?
 * \details Esta função é responsável por verificar quais as possibilidades de números para cada uma das células; isto
 * com a utilização da função isSafe (regras base do SudokuX). No final desta função, cada célula terá a/as suas possibilidades
 * de resolução.
 * @param first_cel Primeira célula do tabuleiro
 * @param size Dimensão do tabuleiro
 * @return
 */
void findPossibilities(CEL *first_cel, int size) {
    CEL *cel_atual = first_cel;
    CEL *linha_atual = first_cel;
    while (linha_atual != NULL) {
        while (cel_atual != NULL) {
            for (int i = 0; i < size; i++) {
                *(cel_atual->possibilities + i) = 0; // Coloca todas as possibilidades de cada célula = 0
                //printf("%d ",*(cel_atual->possibilities+i));  // Cada linha impressa é uma célula
                //Cada impressão 9x9 corresponde uma linha de células do tabuleiro
            }
            cel_atual = cel_atual->pe;
            //printf("\n");
        }
        //printf("\n");
        linha_atual = linha_atual->ps;
        cel_atual = linha_atual;
    }
    cel_atual = first_cel;
    linha_atual = first_cel;
    while (linha_atual != NULL) {
        while (cel_atual != NULL) {
            for (int i = 0; i < size; i++) {
                if (isSafe(cel_atual, first_cel, i + 1, size)) {
                    *(cel_atual->possibilities + i) = i + 1;
                } else {
                    *(cel_atual->possibilities + i) = 0;
                }
                //printf("%d ",*(cel_atual->possibilities+i));  // Cada linha impressa é uma célula
                //Cada impressão 9x9 corresponde uma linha de células do tabuleiro
            }
            cel_atual = cel_atual->pe;
            //printf("\n");
        }
        //printf("\n");
        linha_atual = linha_atual->ps;
        cel_atual = linha_atual;
    }
}

/*!
 * \brief Lê/Carrega o conteúdo de um ficheiro para a memória.
 * \details Função responsável por ler/carregar a partir de um ficheiro de texto determinada informação para a memória.
 * Neste caso, esta função carrega para a memória os tabuleiro presentes no ficheiro. Conforme são iterados os tabuleiros,
 * esta função chama também a função "lista_ligada_create_connect" para que enquanto carrega a informação do ficheiro vai,
 * de imediato, alocando memória e ligando cada uma das células às suas vizinhas.
 * @param file_name Nome do ficheiro que se pretende executar.
 * @return
 */
BOARD *load_from_file(char *file_name) { //Inserção à cauda
    BOARD *board = NULL;
    BOARD *first_board = NULL;
    BOARD *aux_board = NULL;
    CEL *cel_atual = NULL;
    CEL *linha = NULL;
    FILE *fp;
    int num_sudokux = 0;
    int size = 0;
    int i = 0;
    fp = fopen(file_name, "r");
    if (fp != NULL) {
        fscanf(fp, "%d\n", &num_sudokux);    // Numero de tabuleiros
        for (i = 0; i < num_sudokux; i++) {
            fscanf(fp, "%d\n", &size);      // 9
            board = (BOARD *) malloc(sizeof(BOARD));
            board->board_next = NULL;
            if (i != 0) {
                aux_board->board_next = board;
            } else {
                first_board = board;
            }
            aux_board = board;
            board->size = size;
            board->first_cel = lista_ligada_create_connect(size);
            cel_atual = board->first_cel;
            linha = board->first_cel;
            for (int j = 0; j < size; j++) { //LINHAS
                for (int k = 0; k < size; k++) { //COLUNAS
                    fscanf(fp, "%d ", &(cel_atual->info));
                    //printf("%d\n", cel_atual->info);
                    if (cel_atual->pe != NULL)
                        cel_atual = cel_atual->pe;
                }
                linha = linha->ps;
                cel_atual = linha;
            }
        }
    }
    fclose(fp);
    return first_board;
}

/*!
 * \brief Imprimir o tabuleiro
 * \details Esta função é responsável por imprimir para a consola o tabuleiro pretendido. Esta percorre célula a célula
 * tabuleiro imprimindo o número nela presente para a consola.
 * @param first_cel Primeira célula do tabuleiro
 * @return
 */
void Print_Struct(CEL *first_cel) {
    CEL *cel_atual = first_cel;
    CEL *linha_atual = first_cel;
    while (linha_atual != NULL) {
        while (cel_atual != NULL) {
            if (cel_atual->info < 10) {
                printf("%d  ", cel_atual->info);
                cel_atual = cel_atual->pe;
            } else {
                printf("%d ", cel_atual->info);
                cel_atual = cel_atual->pe;
            }
        }
        printf("\n");
        linha_atual = linha_atual->ps;
        cel_atual = linha_atual;
    }
    printf("\n");
}

/*!
 * \brief Imprimir as Diagonais do tabuleiro
 * \details Esta função é responsável por imprimir para a consola as diagonais principal e secundária do tabuleiro que
 * se pretende.
 * @param first_cel Primeira célula do tabuleiro
 * @return
 */
void Print_Diagonals(CEL *first_cel) {
    CEL *aux_cel = first_cel;
    printf("DIAGONAL PRINCIPAL\n");
    while (aux_cel != NULL) { // Diagonal Principal
        printf("%d\n", aux_cel->info);
        aux_cel = aux_cel->pse;
    }

    printf("DIAGONAL SECUNDARIA\n");
    aux_cel = first_cel;
    while (aux_cel->pe != NULL) { // Ultima Celula da Primeira Linha
        aux_cel = aux_cel->pe;
    }
    while (aux_cel != NULL) { // Diagonal Secundária
        printf("%d\n", aux_cel->info);
        aux_cel = aux_cel->pso;
    }
}

/*!
 * \brief Guardar as soluções num ficheiro de texto
 * \details Esta função é responsável por guardar num ficheiro de texto o estado final do tabuleiro, ou seja, em caso de
 * uma resolução completa do tabuleiro é porque foi encontrada uma solução, logo utiliza-se esta função e guarda-se essa
 * mesma no ficheiro de texto.
 * @param board Tabuleiro
 * @param fn Nome do ficheiro
 * @return
 */
void solutions_txt(BOARD *board, char fn[]) {
    CEL *first_cel = board->first_cel;
    int sizeBoard = board->size;
    FILE *fp = fopen(fn, "a");
    if (fp == NULL) {
        fprintf(stdout, "...Erro Abrir Ficheiro: %s...\n", fn);
        return;
    }
    CEL *cel_atual = first_cel;
    CEL *linha_atual = first_cel;
    fprintf(fp, "%d\n", sizeBoard);
    while (linha_atual != NULL) {
        while (cel_atual != NULL) {
            fprintf(fp, "%d ", cel_atual->info);

            cel_atual = cel_atual->pe;
        }
        linha_atual = linha_atual->ps;
        cel_atual = linha_atual;
        fprintf(fp, "\n");
    }
    //fprintf(fp,"\n");
    fclose(fp);
}

/*!
 * \brief Guardar as soluções num ficheiro binário
 * \details Esta função é responsável por guardar num ficheiro binário o estado final do tabuleiro, ou seja, em caso de
 * uma resolução completa do tabuleiro é porque foi encontrada uma solução, logo utiliza-se esta função e guarda-se essa
 * mesma no ficheiro binário.
 * @param board Tabuleiro
 * @param fn Nome do ficheiro
 * @return
 */
void solutions_bin(BOARD *board, char fn[]) {
    CEL *first_cel = board->first_cel;
    int sizeBoard = board->size;
    FILE *fp = fopen(fn, "ab");
    if (fp == NULL) {
        fprintf(stdout, "...Erro Abrir Ficheiro: %s...\n", fn);
        return;
    }
    CEL *cel_atual = first_cel;
    CEL *linha_atual = first_cel;
    fwrite(&sizeBoard, sizeof(int),1,fp);   // Tamanho do tabuleiro
    while (linha_atual != NULL) {
        while (cel_atual != NULL) {
            fwrite(&(cel_atual->info), sizeof(int), 1, fp); // Número
            cel_atual = cel_atual->pe;
        }
        linha_atual = linha_atual->ps;
        cel_atual = linha_atual;
    }
    fclose(fp);
}

