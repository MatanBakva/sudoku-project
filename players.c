//name: Matan bakva ID: 212856694
//name: Yehonatan shiran ID: 315536888
#include "players.h"

PlayerList* CreatePlayers(int num) 
{
	int size = num;
	char* name;
	PlayerList* lst;
	Player player;
	lst = (PlayerList*)malloc(sizeof(PlayerList));
	allocationCheck(lst);
	createEmptyList(lst);
	for (int i = 0; i < size; i++)
	{
		printf("enter the name of player %d: ", i + 1);
		if (i == 0)
			getchar();
		fgets(player.name, 100, stdin);
		player.name[strlen(player.name) - 1] = '\0';
		player.status = NOT_FINISH;
		insertDataToEnd(&player, lst);
		printf("good luck %s!\n", player.name);
	}
	return lst;
}

void createEmptyList(PlayerList* lst) 
{
	lst->head = lst->tail = NULL;
	lst->size = 0;
}

PlayerListNode* createPlayerListNode(Player* data, PlayerListNode* prev, PlayerListNode* next) 
{
	PlayerListNode* new;
	new = (PlayerListNode*)malloc(sizeof(PlayerListNode));
	allocationCheck(new);
	new->player = data;
	new->next = prev;
	new->prev = next;
	return new;
}

void insertDataToEnd(Player* data, PlayerList* lst) 
{
	Player* myplayer = (Player*)malloc(sizeof(Player));
	allocationCheck(myplayer);
	strcpy(myplayer->name, data->name);
	myplayer->status = data->status;
	myplayer->board = MakeRandomBoard();
	PlayerListNode* node = createPlayerListNode(myplayer, NULL, NULL);

	insertNodeToEndList(node, lst);
}

void insertNodeToEndList(PlayerListNode* node, PlayerList* lst) 
{
	if (isEmptyList(lst))
	{
		lst->head = lst->tail = node;
	}
	else {
		node->prev = lst->tail;
		lst->tail->next = node;
		lst->tail = node;
	}
	lst->size++;
}

bool isEmptyList(PlayerList* lst) 
{
	return lst->head == NULL;
}

Player** createPlayerArr(PlayerList* lst) 
{
	int size = lst->size;
	Player** players = (Player**)malloc(sizeof(Player*) * size);
	allocationCheck(players);
	PlayerListNode* node = lst->head;
	for (int i = 0; i < size; i++)
	{
		if (node != NULL) {
			players[i] = node->player;
			node = node->next;
		}
	}
	mergeSort(players, size);
	return players;
}

void mergeSort(Player** players, int size) 
{
	Player** myNew;
	if (size == 1)
		return;

	mergeSort(players, size / 2);
	mergeSort(players + size / 2, size - (size / 2));
	myNew = merge(players, size / 2, players + size / 2, size - (size / 2));
	for (int i = 0; i < size; i++)
	{
		players[i] = myNew[i];
	}
	free(myNew);
}

Player** merge(Player** players1, int size1, Player** players2, int size2) 
{
	int i = 0, j = 0, count = 0, filled1, filled2, strcom;
	Player** myNew = (Player**)malloc(sizeof(Player*) * (size1 + size2));
	allocationCheck(myNew);
	while (i < size1 && j < size2) {
		filled1 = checkHowMuchCellsFilled(players1[i]->board);
		filled2 = checkHowMuchCellsFilled(players2[j]->board);
		if (filled1 > filled2) {
			myNew[count] = players1[i];
			i++;
			count++;
		}
		else if (filled1 < filled2) {
			myNew[count] = players2[j];
			j++;
			count++;
		}
		else {
			strcom = strcmp(players2[j]->name, players1[i]->name);
			if (strcom > 0) {
				myNew[count] = players1[i];
				i++;
				count++;
			}
			else if (strcom < 0) {
				myNew[count] = players2[j];
				j++;
				count++;
			}
			else {
				myNew[count] = players1[i];
				i++;
				count++;
			}
		}
	}
	for (i; i < size1; i++, count++)
	{
		myNew[count] = players1[i];
	}
	for (j; j < size2; j++, count++)
	{
		myNew[count] = players2[j];
	}
	return myNew;
}

void insertDataToWinnerEnd(Player* data, PlayerList* winners) 
{
	PlayerListNode* node = createPlayerListNode(data, NULL, NULL);

	insertNodeToEndList(node, winners);
}

void MoveToWinner(Player* winner, PlayerList* winners, PlayerList* players) 
{
	insertDataToWinnerEnd(winner, winners);
	deleteFromPlayersList(winner, players);
}

void deleteFromPlayersList(Player* winner, PlayerList* players) 
{
	PlayerListNode* myplayer = players->head;
	while (myplayer != NULL) {
		if (winner == myplayer->player) {
			removeNodeFromList(myplayer, players);
			return;
		}
		myplayer = myplayer->next;
	}
}

void removeNodeFromList(PlayerListNode* player, PlayerList* players) 
{

	if (player == players->head && player == players->tail)
	{
		players->head = players->tail = NULL;
	}
	else if (player == players->head) {
		players->head = player->next;
	}
	else if (player == players->tail) {
		players->tail = player->prev;
		players->tail->next = NULL;
	}
	else {
		player->next->prev = player->prev;
		player->prev->next = player->next;
	}
	free(player);
}

bool DelPlayerFromTree(PlayerTreeNode* root, Player* p) 
{
	if (root == NULL)
		return false;
	if (root->player == p) {
		root->player = NULL;
		return true;
	}
}

Player** PlayerTreeCreator(Player** sortedPlayers, int* size)
{
	int n = pow(2.0, (log2(*size + 1.0))) - 1;
	int i;
	int mySize = *size;
	*size += n;
 
	Player** Temp;
	Temp = (Player**)malloc(sizeof(Player*)* *size);
	allocationCheck(Temp);
	for (i = 0; i < mySize; i++)
	{
		Temp[i] = sortedPlayers[i];
	}
	for (i = mySize; i < *size; i++)
		Temp[i] = NULL;

	return Temp;

}

PlayerTree* BuildTreeFromArray(Player** arr, int size)
{
	PlayerTree* tr;
	Player** Temp;
	Temp = PlayerTreeCreator(arr, &size);
	tr = (PlayerTree*)malloc(sizeof(PlayerTree));
	allocationCheck(tr);
	
	tr->root = addmiddletoroot(Temp, size);
	free(Temp);
	return tr;

}
PlayerTreeNode* addmiddletoroot(Player** arr, int size)
{
	PlayerTreeNode* left, * right, * root;
	int center;
	if (size == 0)
		return NULL;
	root = TreeNodeAlloc();
	root->left = NULL;
	root->right = NULL;
	center = size / 2;
	root->left = addmiddletoroot(arr, center);
	if (arr[center] != NULL) {
		
		if (size == 1) {
			root->player = *arr;
			return root;
			*arr = NULL;
		}
		root->player = arr[center];
		arr[center] = NULL;
	}
	else
	{
		if (root->left == NULL)
			return root->right;
		return root->left;
	}
	root->right = addmiddletoroot(&arr[center + 1], size - center - 1);

	return root;

}

PlayerTreeNode* TreeNodeAlloc()
{
	PlayerTreeNode* trn;
	trn = (PlayerTreeNode*)malloc(sizeof(PlayerTreeNode));
	allocationCheck(trn);
	return trn;
}

void ActiveTreeInorder(PlayerTree* Pr, PlayerList* PL, PlayerList* winners)
{
	Tree_inOrder(Pr->root, PL, winners);
}


void Tree_inOrder(PlayerTreeNode* trn, PlayerList* PL, PlayerList* winners)
{
	char* name;
	int res;
	if (trn == NULL)
		return;
	if (trn->player == NULL) {
		Tree_inOrder(trn->left, PL, winners);
		Tree_inOrder(trn->right, PL, winners);
		return;
	}
	name = trn->player->name;
	Tree_inOrder(trn->left, PL, winners);

	printf("%s its your turn\n", name);

	res = FillBoard(trn->player->board->board, trn->player->board->possabilities);

	if (res == FINISH_FAILURE)
	{
		deleteFromPlayersList(trn->player, PL);
		DelPlayerFromTree(trn, trn->player);
		printf("it's game over for you %s\n", name);
		printf("Press Enter to continue...\n");
		getchar();
	}
	else
    {
		MoveToWinner(trn->player, winners, PL);
		DelPlayerFromTree(trn, trn->player);
		printf("you won %s\n", name);
		printf("Press Enter to continue...\n");
		getchar();
	}

	Tree_inOrder(trn->right, PL, winners);
}

void freeTree(PlayerTree* tr)
{
	freeTnode(tr->root);
	tr->root = NULL;
}

void freeTnode(PlayerTreeNode* trn)
{
	if (trn == NULL)
		return;
	else
	{
		freeTnode(trn->left);
		freeTnode(trn->right);
		free(trn);
	}

}

void ActivateOneStage(PlayerTree* Pt, PlayerList* PL, PlayerList* winners)
{
	while (!isEmptyList(PL))
	{
		ActiveTreeInorder(Pt, PL, winners);
	}
}

void freeList(PlayerList* players) 
{
	freeListHelper(players->head);
}
void freeListHelper(PlayerListNode* player) 
{
	PlayerListNode* temp;
	while (player != NULL) {
		temp = player;
		player = player->next;
		free(temp);
	}
}
void freeArr(Player** players,int size)
{
	for (int i = 0; i < size; i++)
	{
		free(players[i]);
	}
	free(players);
}

