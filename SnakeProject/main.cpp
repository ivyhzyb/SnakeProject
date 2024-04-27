#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int highestScore = 0;

class SnakeGame {
private:
    bool gameOver;
    const int width = 50;
    const int height = 20;
    int x, y, fruitX, fruitY, score;
    int tailX[100], tailY[100];
    int nTail;
    enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
    eDirection dir;

public:
    SnakeGame() {
        gameOver = false;
        dir = STOP;
        x = width / 2;
        y = height / 2;
        fruitX = rand() % width;
        fruitY = rand() % height;
        score = 0;
        nTail = 0;
    }

	void Draw() {
		//system("cls"); // clear the console window
		// Hide the cursor
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(consoleHandle, &cursorInfo);
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(consoleHandle, &cursorInfo);

		COORD cursorPosition;
		cursorPosition.X = 0;
		cursorPosition.Y = 0;
		SetConsoleCursorPosition(consoleHandle, cursorPosition);

		cout << "Welcome to the Snake Game!" << endl;
		cout << "Press any key of W -- UP, S -- DOWN, A -- LEFT and D -- RIGHT to start" << endl;
		cout << "Press X to end the game." << endl;

		for (int i = 0; i < width + 1; i++)
			cout << "#";
		cout << endl;

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++)
			{
				if (j == 0 || j == width - 1)
					cout << "#";
				if (i == y && j == x)
				{
					if(gameOver)
						cout << "X";
					else
						cout << "O";
				}
					
				else if (i == fruitY && j == fruitX)
					cout << "F";
				else
				{
					bool print = false;
					for (int k = 0; k < nTail;k++)
					{
						// print tail if tail's location is current location
						if (tailX[k] == j && tailY[k] == i)
						{
							if (gameOver)
								cout << "x";
							else
								cout << "o";
							print = true;
						}
					}
					if (!print)
						cout << " ";

				}

			}
			cout << endl;

			
		}

		for (int i = 0; i < width + 1; i++)
			cout << "#";
		cout << endl;
		cout << "Score: " << score << endl;
		cout << "Highest Score: " << highestScore << endl;

		if (gameOver)
		{
			cout << "Game Over!" << endl;
			if (score == highestScore)
				cout << "Congratulation! You break the highest score!" << endl;
		}

		// Show the cursor
		cursorInfo.bVisible = true;
		SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	}

	void Input()
	{
		// if any keyborad is pressed 
		if (_kbhit())
		{
			switch (_getch()) {
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				gameOver = true;
				break;
			}
		}

	}

	void Logic() {
		int prevX = tailX[0];
		int prevY = tailY[0];
		int prev2X, prev2Y;
		tailX[0] = x;
		tailY[0] = y;
		for (int i = 1; i < nTail; i++)
		{
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}

		switch (dir)
		{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
		}

		// terminate the game if going out of the board
		//if (x > width-1 || x < 0 || y > height -1 || y<0)
		//	gameOver = true;

		// Snake can go through the wall
		if (x >= width) x = 0;
		else if (x < 0) x = width - 1;
		if (y >= height) y = 0;
		else if (y < 0) y = height - 1;

		// check if the head hits the tail

		for (int i = 0;i < nTail; i++)
		{
			if (tailX[i] == x && tailY[i] == y)
			{
				gameOver = true;
				if (score > highestScore)
					highestScore = score;
			}
		}

		if (x == fruitX && y == fruitY)
		{
			score += 10;
			fruitX = rand() % width;
			fruitY = rand() % height;
			// tail
			nTail++;

		}

	}

    void Run() {
		system("cls");
        while (!gameOver) {
            Draw();
            Input();
            Logic();
			//increase the speed when score getting high
			if (score <= 30)
				Sleep(150);
			else if (score <= 60)
				Sleep(100);
			else
				Sleep(80);
        }
		Draw();
    }
};

int main() {
	char play = 'Y';
	while (play == 'Y')
	{
		SnakeGame game;
		game.Run();
		cout << "Play again? (Y/N):";
		cin >> play;
	}
    return 0;
}