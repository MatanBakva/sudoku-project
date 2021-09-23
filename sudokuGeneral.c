//name: Matan bakva ID: 212856694
//name: Yehonatan shiran ID: 315536888
#include "sudokuGeneral.h"
#include "possabilities.h"
void sudokoPrintBoard(short sudokuBoard[][9]) {
	printf("\n | 0 1 2| 3 4 5| 6 7 8\n");
	for (int i = 0; i < 9; i++)
	{
		if(i%3==0)
			printf("----------------------\n");
		printf("%d|", i);
		for (int j = 0; j < 9; j++)
		{
			if(j%3 == 2&&j!=8){
				if (sudokuBoard[i][j] == -1)
					printf("  |");
				else
					printf(" %d|", sudokuBoard[i][j]);
			}
			else
			{
				if (sudokuBoard[i][j] == -1)
					printf("  ");
				else
					printf(" %d", sudokuBoard[i][j]);
			}
		}
		printf("\n");
	}
	printf("----------------------\n");
}

bool isBoardFull(short sudokuBoard[][9]) //checks if board is full
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudokuBoard[i][j] == -1)
				return false;
		}
	}
	return true;
}

bool checkBoard(short sudokuBoard[][9], Array*** possibilities) {
	bool checks[9];
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (sudokuBoard[i][j] == -1)
			{
				if (possibilities[i][j] == NULL)
					return false;
				if (possibilities[i][j] != NULL && possibilities[i][j]->size == 0)
					return false;
			}
		}
	}

	for (int i = 0; i < 9; i++)//check row
	{
		if (!checkRow(sudokuBoard, i))
			return false;
	}

	for (int i = 0; i < 9; i++)//check column
	{
		if (!checkCol(sudokuBoard, i)) {
			return false;
		}
	}

	for (int i = 0; i < 9; i += 3)
	{
		for (int j = 0; j < 9; j += 3)
		{
			if (!checkGoodSquere(sudokuBoard, i, j))
				return false;
		}
	}
	return true;
}

bool checkRow(short sudokuBoard[][9], int i) 
{
	int* checks;
	checks = setBoolArrayToFalse();
	for (int j = 0; j < 9; j++)
	{
		if (sudokuBoard[i][j] != -1) {
			if (checks[sudokuBoard[i][j] - 1] == 1)
				return false;
			else
				checks[sudokuBoard[i][j] - 1] = 1;
		}
	}
	return true;
}

bool checkCol(short sudokuBoard[][9], int i) 
{
	int* checks;
	checks = setBoolArrayToFalse();
	for (int j = 0; j < 9; j++)
	{
		if (sudokuBoard[j][i] != -1) {
			if (checks[sudokuBoard[j][i] - 1] == 1)
				return false;
			else
				checks[sudokuBoard[j][i] - 1] = true;
		}
	}
	return true;
}

bool checkGoodSquere(short sudokuBoard[][9], int i, int j) 
{
	int* checks;
	checks = setBoolArrayToFalse();
	for (int k = i; k < i + 3; k++)
	{
		for (int s = j; s < j + 3; s++)
		{
			if (sudokuBoard[k][s] != -1) {
				if (checks[sudokuBoard[k][s] - 1] == 1)
					return false;
				else
					checks[sudokuBoard[k][s] - 1] = 1;
			}
		}
	}
	return true;
}

int* setBoolArrayToFalse()
{
	int k;
	int* Temp = (int*)malloc(sizeof(int) * 9);
	allocationCheck(Temp);
	//make false arr
	for (k = 0; k < 9; k++)
		Temp[k] = 0;
	return Temp;
}

void allocationCheck(void* arr)
{
	if (!arr)
	{
		printf("allocation fail");
		exit(1);
	}
}
int FillBoard(short board[][9], Array*** possibilities)
{
	bool  boardchecker = checkBoard(board, possibilities);
	short int x, y;
	int value, num;
	value = NOT_FINISH;

	while (value == NOT_FINISH)
	{
		possibilities = OneStage(board, possibilities, &x, &y, &value);
		sudokoPrintBoard(board);

		if (value != NOT_FINISH)
			break;

		printf("choose input for [%d, %d]\n", x, y);
		PrintPossibilitiesOfCell(possibilities[x][y]);
		scanf("%d", &num);

		while (!checkInput(possibilities[x][y], num))
		{
			printf("incorrect input please choose a valid input!\n");
			scanf("%d", &num);
		}

		board[x][y] = num;
	}
	return value;
}
bool checkInput(Array* possability, int input) 
{
	for (int i = 0; i < possability->size; i++) {
		if (input == possability->arr[i]) {
			return true;
		}
	}
	return false;
}
int checkHowMuchCellsFilled(Board* board) 
{
	int count = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (board->board[i][j] != -1)
				count++;
		}
	}
	return count;
}

BoardList* MakeEmptylist()
{
	BoardList* newB = (BoardList*)malloc(sizeof(BoardList));
	allocationCheck(newB);
	newB->head = NULL;
	newB->tail = NULL;
	newB->size = 0;

	return newB;
}

Board* MakeEmptyBoard()
{
	Board* Bd;
	Bd = (Board*)malloc(sizeof(Board));
	allocationCheck(Bd);
	int i, j;
	for (i = 0; i < 9; i++)
		for (j = 0; j < 9; j++)
			Bd->board[i][j] = -1;
	Bd->possabilities = PossibleDigits(Bd->board);
	return Bd;
}

Board* MakeRandomBoard()
{
	Board* Bd;
	BoardList* Bl;
	BoardListNode* Temp;
	Cell* c;
	int numOfCelles, i, CellToDelet, Rnum, size;
	Bd = MakeEmptyBoard();
	Bl = MakeEmptylist();
	setCells(Bl);
	Temp = Bl->head;
	size = Bl->size;
	numOfCelles = randomGenerator(20);
	for (i = 0; i < numOfCelles; i++)
	{

		CellToDelet = randomGenerator(size);
		size--;
		c = DeleteFromList(CellToDelet, Bl);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				free(Bd->possabilities[i][j]);
			}
		}
		free(Bd->possabilities);
		Bd->possabilities = PossibleDigits(Bd->board);
		Rnum = GetRandomLegalNum(Bd->possabilities[c->i][c->j]->arr, Bd->possabilities[c->i][c->j]->size);
		Bd->board[c->i][c->j] = Rnum;
		Bl->size--;
		free(c);
	}

	return Bd;
}


void setCells(BoardList* Bl)
{
	BoardListNode* Temp, * TempHelper;

	int i, j;
	Bl->head = createBoardListNode(0, 0, NULL, NULL);
	Temp = Bl->head;
	Bl->size++;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (i == 0 && j == 0)
				continue;

			TempHelper = createBoardListNode(i, j, Temp, NULL);
			Temp->next = TempHelper;
			Temp = TempHelper;
			Bl->size++;
		}
	}
	Bl->tail = Temp;
}

int GetRandomLegalNum(short* arr, int size)
{
	int num;

	num = randomGenerator(size);
	num--;
	return arr[num];
}

Cell* DeleteFromList(int CellToDelet, BoardList* Bl)
{
	int i;
	BoardListNode* Temp = Bl->head;
	Cell* c;
	c = (Cell*)malloc(sizeof(Cell));
	allocationCheck(c);

	for (i = 0; i < CellToDelet - 1; i++)
		Temp = Temp->next;
	if (Temp->prev != NULL)
		Temp->prev->next = Temp->next;
	if (Temp->next != NULL)
		Temp->next->prev = Temp->prev;


	c->i = Temp->cel->i;
	c->j = Temp->cel->j;
	if (CellToDelet == 1)
		Bl->head = Bl->head->next;
	if (CellToDelet == Bl->size)
		Bl->tail = Bl->tail->prev;
	free(Temp);

	return c;
}

// Random generator
int randomGenerator(int num)
{
    return rand() % num + 1;
}

BoardListNode* createBoardListNode(int i, int j, BoardListNode* prev, BoardListNode* next)
{
	BoardListNode* new;
	new = (BoardListNode*)malloc(sizeof(BoardListNode));
	allocationCheck(new);
	new->cel = (Cell*)malloc(sizeof(Cell));
	new->cel->i = i;
	new->cel->j = j;
	new->prev = prev;
	new->next = next;
	return new;
}