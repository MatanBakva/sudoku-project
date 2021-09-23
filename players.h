//name: Matan bakva ID: 212856694
//name: Yehonatan shiran ID: 315536888
#ifndef P__H
#define P__H
#include "sudokuGeneral.h"
#include "possabilities.h"
#include <math.h>

typedef struct Player
{
	char name[100];
	Board* board; //board contains possabilities
	int status;
}Player;
typedef struct PlayerListNode {
	Player* player;
	struct PlayerListNode* next;
	struct PlayerListNode* prev;
}PlayerListNode;

typedef struct PlayerList {
	int size;
	struct PlayerListNode* head;
	struct PlayerListNode* tail;
}PlayerList;

typedef struct PlayerTreeNode {
	Player* player;
	struct PlayerTreeNode* left;
	struct PlayerTreeNode* right;
}PlayerTreeNode;

typedef struct PlayerTree {
	struct PlayerTreeNode* root;
}PlayerTree;


PlayerListNode* createPlayerListNode(Player* data, PlayerListNode* prev, PlayerListNode* next);

PlayerTreeNode* addmiddletoroot(Player** arr, int size);

PlayerTreeNode* TreeNodeAlloc();

PlayerTree* BuildTreeFromArray(Player** arr, int  size);

PlayerList* CreatePlayers(int num);

Player** createPlayerArr(PlayerList* lst);

Player** merge(Player** players1, int size1, Player** players2, int size2);

Player** PlayerTreeCreator(Player** sortedPlayers, int *size);

bool DelPlayerFromTree(PlayerTreeNode* root, Player* p);

bool isEmptyList(PlayerList* lst);

void insertNodeToEndList(PlayerListNode* node, PlayerList* lst);

void createEmptyList(PlayerList* lst);

void insertDataToEnd(Player* data, PlayerList* lst);

void mergeSort(Player** players, int size);

void insertDataToWinnerEnd(Player* data, PlayerList* winners);

void MoveToWinner(Player* winner, PlayerList* winners, PlayerList* players);

void deleteFromPlayersList(Player* winner, PlayerList* players);

void removeNodeFromList(PlayerListNode* player, PlayerList* players);

void Tree_inOrder(PlayerTreeNode* trn, PlayerList* PL, PlayerList* winners);

void freeTree(PlayerTree* tr);

void freeTnode(PlayerTreeNode* trn);

void ActivateOneStage(PlayerTree* Pt, PlayerList* PL, PlayerList* winners);

void freeList(PlayerList* players);

void freeListHelper(PlayerListNode* player);

void freeArr(Player** players, int size);
#endif // !P__H