#include <iostream>
#include <cstdlib>
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/Statistic.h"
#include "Fib2584Ai.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc == 1) {
		cerr << "usage: play_game rounds [other arguments which your AI needs]" << endl;
		return 1;
	}
	int iPlayRounds = atoi(argv[1]);
	// create and initialize AI
	Fib2584Ai ai;
	ai.initialize(argc, argv);

	// initialize statistic data
	Statistic statistic;
	statistic.setStartTime();
	// play each round
	for(int i = 0;i < iPlayRounds;i++) {
		GameBoard gameBoard;
		gameBoard.initialize();
		int iScore = 0;
		int arrayBoard[4][4];
		while(!gameBoard.terminated()) {
			gameBoard.getArrayBoard(arrayBoard);
			MoveDirection moveDirection = ai.generateMove(arrayBoard);

			GameBoard originalBoard = gameBoard;
			iScore += gameBoard.move(moveDirection);
			if(originalBoard == gameBoard)
				continue;
			statistic.increaseOneMove();

			// check
			MyBoard ori(arrayBoard), bb;
			bb = ori;
			int ss;
			bb.move(moveDirection, ss);  // My
			int tmp[4][4];
			gameBoard.getArrayBoard(tmp);
			MyBoard tt(tmp); // TA
			if (0) {
				cout << "------------ori------------" << endl;
				cout << ori << endl;
				cout << "------------My-------------" << endl;
				cout << bb;
				cout << "------------TA-------------" << endl;
				cout << tt;
				cout << "---------------------------" << endl;
				cout << "dir = " << moveDirection << " WRONG MOVE!!!!!!!!!!!!!" << endl;
				cout << "------------xx-------------" << endl;
			}

			gameBoard.addRandomTile();
			//cout << "Now score = " << iScore << endl;
		}
		gameBoard.getArrayBoard(arrayBoard);
		ai.gameOver(arrayBoard, iScore);
		statistic.increaseOneGame();

		// update statistic data
		statistic.updateScore(iScore);
		statistic.updateMaxTile(gameBoard.getMaxTile());
	}
	statistic.setFinishTime();

	// output statistic data
	statistic.show();

	return 0;
}