//
// Created by Jorge  Lopes on 08/01/2020.
//

#ifndef UNTITLED1_IMPROVEDALGORITHM_H
#define UNTITLED1_IMPROVEDALGORITHM_H
#include <stdio.h>
#include "main.h"
#include "BruteForce.h"
double main_ImprovedAlgorithm(BOARD *board);
void Solve_ImprovedAlgorithm(BOARD *board, CEL *first_cel, int size, double *cost_improved);
int NakedSingles(CEL *first_cel, int size);
int HiddenSingles(CEL *first_cel,CEL *cel_atual, int size, int num);
int NakedPairs(CEL *first_cel, int size);
int compare2Cels(CEL *cel_atual, CEL *cel_next, int size);
void removePossibilities(CEL *cel_atual, CEL *remove,int size);
int PointingPairs(CEL *first_cel, CEL *cel_atual, int size, int num);
#endif //UNTITLED1_IMPROVEDALGORITHM_H
