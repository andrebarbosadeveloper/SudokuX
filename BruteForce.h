//
// Created by Jorge  Lopes on 01/01/2020.
//

#ifndef UNTITLED1_BRUTEFORCE_H
#define UNTITLED1_BRUTEFORCE_H
#define UNASSIGNED 0
#include <math.h>
#include <stdio.h>
#include "main.h"
double main_bruteforce(BOARD *board);
int FindUnassignedLocation(CEL *first_cel, CEL **empty_cel);
int SolveSudoku_BruteForce(BOARD *board, CEL *first_cel, int sizeN, double *cost);
int isSafe(CEL *cel, CEL *first_cel, int num, int sizeN);
int UsedInBox(CEL *cel, CEL *first_cel, int num, int sizeN);
int UsedInRow(CEL *cel,int num);
int UsedInCol(CEL *cel,int num);
int MainDiagonal(CEL *cel, int num);
int SecondaryDiagonal(CEL *cel,int num, int sizeN);

#endif //UNTITLED1_BRUTEFORCE_H
