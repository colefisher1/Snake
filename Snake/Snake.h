#pragma once
#include <string>
#include <vector>
#include "Tile.h"
using namespace std;

class Snake
{
public:
	struct Head
	{
		int xPos = rand() % 30 + 2;
		int yPos = rand() % 20 + 2;
		string direction = "STILL";
	};
	struct TailSegment
	{
		int xPos;
		int yPos;
	};
	struct Apple
	{
		int xPos;
		int yPos;
	};

	Head snakeHead;
	vector <TailSegment> tail;
	Apple theApple;
	unsigned int tailSize;

	bool win;
	bool lose;
	bool reset = true;

	void resetSnake()
	{
		Head myNewHead;
		snakeHead = myNewHead;
		tail.clear();
		tailSize = 0;
		win = false;
		lose = false;
	}

	void addTail(Tile(&board)[35][25])
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			TailSegment tailBlock;
			if (tailSize == 0)
			{
				tailBlock.xPos = snakeHead.xPos;
				tailBlock.yPos = snakeHead.yPos;
			}
			else
			{
				tailBlock.xPos = tail.back().xPos;
				tailBlock.yPos = tail.back().yPos;
			}
			tail.push_back(tailBlock);
			tailSize++;
			if (tailSize == 250)
			{
				win = true;
			}
		}
	}
	
	void spawnApple(Tile(&board)[35][25])
	{
		bool success = false;
		while (success == false)
		{
			theApple.xPos = rand() % 30 + 2;
			theApple.yPos = rand() % 20 + 2;
			if (board[theApple.xPos][theApple.yPos].getStatus() != 1)
			{
				board[theApple.xPos][theApple.yPos].setStatus(2);
				success = true;
			}
		}
		
	}

	void move( Tile (&board)[35][25])
	{
		if (lose != true && win != true)
		{
			/* ----- Moves Head ----- */
			board[snakeHead.xPos][snakeHead.yPos].setStatus(0);
			int headXpos = snakeHead.xPos;
			int headYpos = snakeHead.yPos;
			if (snakeHead.direction == "UP")
			{
				snakeHead.yPos--;
			}
			else if (snakeHead.direction == "DOWN")
			{
				snakeHead.yPos++;
			}
			else if (snakeHead.direction == "RIGHT")
			{
				snakeHead.xPos++;
			}
			else if (snakeHead.direction == "LEFT")
			{
				snakeHead.xPos--;
			}


			if (board[snakeHead.xPos][snakeHead.yPos].getStatus() == 2)
			{
				addTail(board);
				spawnApple(board);
			}
			else if (board[snakeHead.xPos][snakeHead.yPos].getStatus() == 1 || board[snakeHead.xPos][snakeHead.yPos].getStatus() == 3)
			{
				lose = true;
				board[snakeHead.xPos][snakeHead.yPos].setStatus(4);
			}
			else
			{
				board[snakeHead.xPos][snakeHead.yPos].setStatus(1);
			}
		
		
				/* ----- Moves Tail ----- */
				int tailXpos, tailYpos, x, y;
				if (tail.size() > 0)
				{
					for (int i = 0; i < tailSize; i++)
					{
						board[tail[i].xPos][tail[i].yPos].setStatus(0);

						if (i == 0)
						{
							tailXpos = tail[i].xPos;
							tailYpos = tail[i].yPos;

							tail[i].xPos = headXpos;
							tail[i].yPos = headYpos;
						}
						else
						{
							x = tailXpos;
							y = tailYpos;

							tailXpos = tail[i].xPos;
							tailYpos = tail[i].yPos;

							tail[i].xPos = x;
							tail[i].yPos = y;
						}
						board[tail[i].xPos][tail[i].yPos].setStatus(1);
					}
				}
				if (lose == true)
				{
					board[snakeHead.xPos][snakeHead.yPos].setStatus(4);
				}
		}
	}
};

