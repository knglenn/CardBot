/* CardBot by Kevin Glenn */

#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>
#include<ctype.h>

//swaps the elements of our array, used in shuffle function
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


//function that shuffles our suit(array) so players get different cards each game
void shuffle(int arr[], int n)
{
	
	srand(time(NULL));

	for (int i = n - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		swap(&arr[i], &arr[j]);
	}
}

/*this function finds the probability of being able to declare the game and win*/
bool probabilityFinder(int n) {
	if (n <= 3) {
		return false;
	}
	else {
		double probability = (double)n / 7;
		double result = (double)rand() / RAND_MAX;
		if (result <= probability) {
			return true;
		}
		else {
			return false;
		}
	}

}

//determine the probability of if player is bluffing and if computer should bluff
bool bluffProb(int n) {
	n -= randomNum2(4);
	if (n < 0) {
		n = randomNum(3);
	}
	double probability = (double)n / 7;
	double result = (double)rand() / RAND_MAX;
	if (result <= probability) {
		return true;
	}
	else {
		return false;
	}

}
//delay input and outputs
void delay() {
	for (int delay = 0; delay <= 500000000; delay++) {}
}

//generate a random number
int randomNum() {
	return rand() % 13 + 1;
}
//generate a random number with int n passed in, useful in situations such as above where determinign probabilities
int randomNum2(int n) {
	return rand() % n + 1;
}

//find if number exists in array
int findNumber(int arr[], int length, int value)
{
	int i;
	for (i = 0; i<length; i++)
	{
		if (arr[i] == value)
		{
			return(value);  
		}
	}
	return(-1);  
}

main() {
	//implement seed for random number generator
	srand(time(NULL));

	bool game = true;
	bool playerChosen = false;
	bool roundStart = true;
    bool askValid = false;
	bool mysteryFound = false;

	char player;
	int playerTurn;
	int i = 0;
	int mysteryGuess;
	int player1Array[6];
	int player2Array[6];
	int mysteryCard[1];
	int cardsFlipped[6];
	int cardsFlippedCounter = 0;
	int askCard = 0;
	int probability;
	int myCardCounter = 6;
	int playerCardCounter = 0;
	int cardCounter = 1;
	int declaredValue = 0;
	int declareGuess = 0;
	int guessCounter = 5;
	int suit[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	int compCardsKnown[13];
	int playerCardsKnown[13];
	int n = sizeof(suit) / sizeof(suit[0]);
	int n2 = sizeof(player1Array) / sizeof(player1Array[0]);
	int n3 = sizeof(player2Array) / sizeof(player2Array[0]);

	shuffle(suit, n);

	//left in for debugging purposes
	/*for (int z = 0; z < n; z++) {
		printf("%d ", suit[z]);
	} 

	printf("\n\nYou are given the cards: "); */

	printf("\n\n--------------------------------------------------------------------------\n");
	printf("Your hand is: ");

	for (int j = 0; j < n2; j++) {
		player1Array[j] = suit[j];
		printf("%d ", player1Array[j]);
	}

	printf("\n--------------------------------------------------------------------------");
	printf("\n");

	//printf("\n\nComputer is given the cards: ");
	for (int k = 0; k < n3; k++) {
		player2Array[k] = suit[k + 6];
		compCardsKnown[k] = player2Array[k];
		//printf("%d ", player2Array[k]);
	}
	//printf("\n");
	mysteryCard[0] = suit[12];
	//printf("Mystery card : %d  ", mysteryCard[0]);
	//printf("\n"); 

	
	
	char response;
	char answer;
	char prompt;

//is the computer or player first?
	printf(">Is the computer or player first? Please enter 'c' for computer or 'p' for player.\n>(c/p)  ");
	while (!playerChosen) {
		scanf_s("%c", &player);

		if (player == 'p') {
			playerTurn = 0;
			playerChosen = true;
		}
		else if (player == 'c') {
			playerTurn = 1;
			playerChosen = true;
		}
		else {
			printf("Please enter either c or p.");
		}
}


	while (game) {


		/*for loop where each iteration represents a player -
		i = 0 = player 1, i = 1 = player 2
		Does not increment until certain conditions are met*/
		for (i = playerTurn; i < 2;) {
			roundStart = true;

			//deals with the computer playing the game
			if (i == 1) {
				printf("\n>It's the computer's turn!\n");
				delay();
				char guessResponse;
				int compGuess = randomNum();
				if (mysteryFound) {
					if (mysteryGuess == mysteryCard[0]) {
						printf(">Opponent has declared! They guessed the correct card of %d and won the game. You lose!\n", mysteryGuess);
						game = false;
						break;
					}
					else {
						mysteryFound = false;
					}
				}
				bool chance = probabilityFinder(cardCounter);
				if (chance) {
					while (findNumber(compCardsKnown, 13, compGuess) != -1) {
						declareGuess = randomNum();
					}
					if (declareGuess == mysteryCard[0]) {
						printf(">Opponent has declared! They guessed the correct card of %d and won the game. You lose!\n", declareGuess);
						game = false;
						break;

					}
					else {
						printf(">Opponent has declared! They guessed the incorrect card %d and lost the game. You win!\n", declareGuess);
						game = false;
						break;
					}

				}

				bool bluff = bluffProb(myCardCounter);
				if (!bluff) {
					while (findNumber(compCardsKnown, 13, compGuess) != -1) {
						compGuess = randomNum();
					}
				}
				else {
					while (findNumber(cardsFlipped, 6, compGuess) != -1) {
						compGuess = randomNum();
					}
				}
			
				int index = (findNumber(player1Array, 6, compGuess));
			

				if (index == -1) {

					printf(">Your opponent has incorrectly guessed one of your cards. Do you think they are bluffing?\n>(y/n) ");
					scanf_s(" %c", &guessResponse);
				
					delay();
					if (guessResponse == 'y') {
						if (bluff) {
							printf(">You called their bluff! Opponent has the card %d ", compGuess);
							playerCardsKnown[playerCardCounter] = compGuess;
							playerCardCounter++;
							printf("\n");
						}
						else {
							printf(">Opponent was not bluffing.\n");
						}
						i--;
						delay();
					}
					else if (guessResponse == 'n') {
						i--;
					}

				}
				else {
					printf(">Your opponent correctly guessed that you have card %d!\n", compGuess);
					guessCounter++;
					compCardsKnown[guessCounter] = compGuess;
				
					myCardCounter--;
					cardsFlipped[cardsFlippedCounter] = compGuess;
					cardsFlippedCounter++;

					i--;
				}
			

			}

			//deals with you(the player) playing the game
			else if (i == 0) {
				printf("\n\n--------------------------------------------------------------------------\n");
				printf("Your hand is: ");
				
				for (int x = 0; x < 6; x++) {
					printf("%d ", player1Array[x]);
				}
				

				if (playerCardCounter > 1) {
					printf("\nThe cards you know in opponent's hand are: ");
					for (int y = 0; y < playerCardCounter; y++) {
						printf("%d ", playerCardsKnown[y]);
					}
				}
				printf("\n--------------------------------------------------------------------------");
				printf("\n");

				printf(">It's your turn to play!\n");
				printf(">Would you like to declare or ask? Type a for ask, d for declare.\n (a/d) ");
				scanf_s(" %c", &response);

				if (response == 'a') {


					printf("\n>What card would you like to ask for? Please type a number between 1 and 13. ");
					while (!askValid) {
						scanf_s(" %d", &askCard);
						if (askCard <= 13 && askCard >= 1) {
							int index = findNumber(player2Array, 6, askCard);
							if (index == -1) {
								delay();
								bool bluff = bluffProb(myCardCounter);
								if (bluff) {
									if (findNumber(player1Array, 6, askCard) != -1) {
										printf(">The computer thinks you're bluffing, and has correctly called you on your bluff! Card %d has been turned.\n", askCard);

										guessCounter++;
										compCardsKnown[guessCounter] = askCard;

										myCardCounter--;
										cardsFlipped[cardsFlippedCounter] = askCard;
										cardsFlippedCounter++;

										i++;

									}
									else {
										printf(">The computer incorrectly assumed that you were bluffing.\n");
										mysteryGuess = askCard;
										mysteryFound = true;
										i++;
									}
								}
								
								else {
									printf(">The computer believes that you're telling the truth.");
								} 
								delay();
							} 
							else {

								printf(">Opponent has the card %d!\n", askCard);

								playerCardsKnown[playerCardCounter] = askCard;
								playerCardCounter++;
								cardCounter++;
								i++;

							}
							break;
						}
						else {
							printf(">Please enter a number between 1 and 13. ");
						}
					}

				}
			

				else if (response == 'd') {
					printf(">What card would you like to declare? Please enter a value between 1-13.\n Value:  ");
					scanf_s(" %d", &declaredValue);
					if (declaredValue == mysteryCard[0]) {
						printf(">You guessed the card correctly! You win the game!\n");
					}
					else {
						printf(">You guessed wrong! You lose!\n");

					}

					game = false;
					break;
				}
				
			}

				
		}


	}
	system("pause");

}











