//name: Matan bakva ID: 212856694
//name: Yehonatan shiran ID: 315536888
#include "possabilities.h"

void checkMinPossability(short sudokuBoard[][9], Array*** possibilities, short int* x, short int* y) 
{
	int xMin = 0, yMin = 0, len = 9;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudokuBoard[i][j] == -1 && possibilities[i][j] != NULL)
			{
				if (possibilities[i][j]->size < len) {
					len = possibilities[i][j]->size;
					xMin = i;
					yMin = j;
				}
			}
		}
	}
	*x = xMin;
	*y = yMin;
}

void checkRowCol(short sudokuBoard[][9], Array*** possibilities, int i, int j)
{
	int* exists;
	int k, x, y;
	exists = setBoolArrayToFalse();
	calcSqureIndex(i, j, x, y);
	int xsize = x * 3 + 3;
	int ysize = y * 3 + 3;//first element
	if (sudokuBoard[i][j] == -1) {
		if (possibilities[i][j] != NULL) {
			//check for row
			for (k = 0; k < 9; k++)
			{
				if (sudokuBoard[i][k] != -1)
					exists[sudokuBoard[i][k] - 1] = 1;
			}
			//check for col
			for (k = 0; k < 9; k++)
			{
				if (sudokuBoard[k][j] != -1)
					exists[sudokuBoard[k][j] - 1] = 1;
			}
			for (int k = x * 3; k < xsize; k++)//three spaces from first element
			{
				for (int s = y * 3; s < ysize; s++)
				{
					if (sudokuBoard[k][s] != -1)
						exists[sudokuBoard[k][s] - 1] = 1;//we found the number for the first time
				}
			}
			castTopossible(exists, possibilities, i, j);
		}
	}
	else {
		possibilities[i][j] = NULL;
	}

	free(exists);
}

void castTopossible(int Tocast[9], Array*** possibilities, int i, int j)
{
	int k, index = 0;
	short int size = 0;
	Array* Temp;
	for (k = 0; k < 9; k++)
	{
		if (Tocast[k] == 0)
			size++;
	}
	Temp = (Array*)malloc(sizeof(Array));
	allocationCheck(Temp);
	if (size > 0) {
		//alocating space in arr
		Temp->arr = (short*)malloc(sizeof(short) * size);
		Temp->size = size;
		//incerting data from bool to Temp Array
		for (k = 0; k < 9; k++)
		{
			if (Tocast[k] == 0)
			{
				Temp->arr[index] = k + 1;
				index++;
			}
		}
	}
	else {
		Temp = NULL;
	}


	possibilities[i][j] = Temp;
}

void updatePossabilities(short sudokuBoard[][9], Array*** possibilities, int i, int j)
{
	checkRowCol(sudokuBoard, possibilities, i, j);
}

Array*** PossibleDigits(short sudokuBoard[][9])
{
	Array*** possibilities;
	int i, k;
	possibilities = (Array***)malloc(sizeof(Array**) * 9);
	allocationCheck(possibilities);
	for (i = 0; i < 9; i++)
	{
		possibilities[i] = (Array**)malloc(sizeof(Array*) * 9);
		allocationCheck(possibilities[i]);
	}
	for (i = 0; i < 9; i++)
	{

		for (k = 0; k < 9; k++)
		{

			if (sudokuBoard[i][k] != -1)
			{
				possibilities[i][k] = NULL;
			}
			else {
				possibilities[i][k] = (Array*)malloc(sizeof(Array) * 9);
				allocationCheck(possibilities[i][k]);
				possibilities[i][k]->arr = (short int*)malloc(sizeof(short int) * 9);
				allocationCheck(possibilities[i][k]->arr);
			}
		}
	}
	for (i = 0; i < 9; i++)
	{
		for (k = 0; k < 9; k++)
		{
			updatePossabilities(sudokuBoard, possibilities, i, k);
		}
	}
	return possibilities;
}

Array*** setPossabilities(short board[][9], Array*** possabilities) 
{
	for (int k = 0; k < 9; k++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (possabilities[k][j] != NULL)
			{
				free(possabilities[k][j]->arr);

				free(possabilities[k][j]);
			}
		}
	}
	free(possabilities);
	return PossibleDigits(board);

}

Array*** OneStage(short sudokuBoard[][9], Array*** possibilities, short int* x, short int* y, int* value) 
{

	possibilities = setPossabilities(sudokuBoard, possibilities);

	bool hasFinished = false;
	int count = 0, minX = 0, minY = 0, minSize = 9;
	while (!hasFinished) {
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (possibilities[i][j] != NULL) {
					if (sudokuBoard[i][j] == -1) {
						if (possibilities[i][j]->size == 1) {
							sudokuBoard[i][j] = possibilities[i][j]->arr[0];
							possibilities = setPossabilities(sudokuBoard, possibilities);
							count++;
						}
					}
				}
			}
		}
		hasFinished = (count == 0);
		count = 0;
	}
	possibilities = setPossabilities(sudokuBoard, possibilities);
	checkMinPossability(sudokuBoard, possibilities, x, y);
	if (!checkBoard(sudokuBoard, possibilities)) {
		*value = FINISH_FAILURE;
	}
	else if (isBoardFull(sudokuBoard)) {
		*value = SUCCESS_FINISH;
	}
	else
		*value = NOT_FINISH;
	return possibilities;
}

void PrintPossibilitiesOfCell(Array* possibilitiesCell)
{
	int i;
	printf("options are:\n");
	for (i = 0; i < possibilitiesCell->size; i++)
	{
		printf("%d. %d\n", i + 1, possibilitiesCell->arr[i]);
	}
	printf("\n");
}