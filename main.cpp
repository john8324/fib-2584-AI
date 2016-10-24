#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "Fib2584/GameBoard.h"
#include "Fib2584/MoveDirection.h"
#include "Fib2584/Statistic.h"
#include "Fib2584Ai.h"

using namespace std;

void weightViewer()
{
	double *w = new double[1 << 22];
	FILE *fp = fopen("TD_w.bin", "r");
	if (fp) {
		fread(w, sizeof(double), 1 << 22, fp);
		fclose(fp);
	}
	while (1) {
		int n, a, b, c, d;
		n = a = b = c = d = -1;
		cout << "n a b c d:" << endl;
		cin >> n >> a >> b >> c >> d;
		if (n < 0 || a < 0 || b < 0 || c < 0 || d < 0) {
			break;
		}
		if (n >= 4 || a >= 32 || b >= 32 || c >= 32 || d >= 32) {
			break;
		}
		printf("%d %d %d %d %d\n%e\n", n, a, b, c, d, w[n<<20|a<<15|b<<10|c<<5|d]);
	}
	cout << *max_element(w, w + (1 << 22)) << endl;
	cout << *min_element(w, w + (1 << 22)) << endl;
	delete[] w;
}

int main(int argc, char* argv[])
{
	if(argc == 1) {
		cerr << "usage: play_game rounds [other arguments which your AI needs]" << endl;
		cout << "weightViewer >>>> " << endl;
		weightViewer();
		return 0;
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