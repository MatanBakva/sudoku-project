//name: Matan bakva ID: 212856694
//name: Yehonatan shiran ID: 315536888
#ifndef POSSABILITIES__h

#define POSSABILITIES__h

#include "sudokuGeneral.h"


void checkMinPossability(short sudokuBoard[][9], Array*** possibilities, short int* x, short int* y);

void checkRowCol(short sudokuBoard[][9], Array*** possibilities, int i, int j);

void castTopossible(int Tocast[9], Array*** possibilities, int i, int j);

void updatePossabilities(short sudokuBoard[][9], Array*** possibilities, int i, int j);

void PrintPossibilitiesOfCell(Array* possibilities);

Array*** PossibleDigits(short sudokuBoard[][9]);

Array*** OneStage(short sudokuBoard[][9], Array*** possibilities, short int* x, short int* y, int* value);

Array*** setPossabilities(short board[][9], Array*** possabilities);

#endif
