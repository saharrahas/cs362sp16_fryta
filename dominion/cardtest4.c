#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>



int myAssert(int r, char* msg, int lineNum)
{
	static int failed = 0;
	if(r == 0)
	{
		printf("FAILED ASSERTION (line#%d): %s\n", lineNum, msg);
		failed = 1;
	}
	return failed;
}


//Testing mine and default deal
int main() {
	struct gameState g, orig;

	int k[10] = {smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,
			   outpost,baron,tribute};
	int i;
	int r = 0;
	//3 player game this time
	initializeGame(3, k, 1, &orig);
	//Trevor's suggestion, saving game state for testing purposes
	memcpy(&g, &orig, sizeof(struct gameState));	
	gainCard(mine, &orig, 2, 0);
	
	r = supplyCount(mine, &g);
	playCard(5, 1, 0, 0, &g);
	//Should gain coin
	r = buyCard(gold, &g);
	myAssert(r == 0, "Did not have 6 coins to buy gold", __LINE__);
	r = buyCard(estate, &g);
	myAssert(r == 0, "Should not have been able to buy estate", __LINE__);
	
	if(r == 0)
		printf("Tests completed successfully!\n");

	return 0;
}
	