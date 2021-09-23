//name: Matan bakva ID: 212856694
//name: Yehonatan shiran ID: 315536888
#include "sudokuGeneral.h"
#include "players.h"
#include "possabilities.h"

void main() {
	srand(12345);
	//srand(time(NULL));
	PlayerTree* PT;
	int count = 0;
	PlayerListNode* playerNode;
	int NumOfPlayers;
	printf("enter how much players are playing: ");
	scanf("%d", &NumOfPlayers);
	printf("\n");
	PlayerList* players = CreatePlayers(NumOfPlayers);
	PlayerList* winners = (PlayerList*)malloc(sizeof(PlayerList));
	allocationCheck(winners);
	createEmptyList(winners);
	Player** sortedPlayers = createPlayerArr(players);
	PT = BuildTreeFromArray(sortedPlayers, NumOfPlayers);
	ActivateOneStage(PT, players, winners);
	playerNode = winners->head;
	while (playerNode != NULL) {
		printf("winner number %d is %s\n", count + 1, playerNode->player->name);
		printf("%s's board is\n", playerNode->player->name);
		sudokoPrintBoard(playerNode->player->board->board);
		printf("\n");
		playerNode = playerNode->next;
		count++;
	}
	freeList(winners);
	freeArr(sortedPlayers, NumOfPlayers);
	freeTree(PT);
 }