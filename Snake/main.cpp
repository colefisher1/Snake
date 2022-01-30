#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include "Tile.h"
#include "Snake.h"


using namespace sf;
using namespace std;

//Prototypes
void printBoard(RenderWindow &window, Tile (&board)[35][25], map <string, Texture> &textures);
void resetBoard(Snake &mySnake, Tile(&board)[35][25]);

int main()
{
	//Load All Sprites
	map<string, Texture> gameTextures;
	Texture myTexture;
	myTexture.loadFromFile("Blue.jpg");
	gameTextures.emplace("Blue", myTexture);
	myTexture.loadFromFile("Green.png");
	gameTextures.emplace("Green", myTexture);
	myTexture.loadFromFile("Red.jpg");
	gameTextures.emplace("Red", myTexture);
	myTexture.loadFromFile("Black.jpg");
	gameTextures.emplace("Black", myTexture);
	myTexture.loadFromFile("Orange.jpg");
	gameTextures.emplace("Orange", myTexture);
	myTexture.loadFromFile("Reset.png");
	gameTextures.emplace("Reset", myTexture);

	//Initialize Window/Board and Clock
	RenderWindow window(VideoMode(735, 525), "Snake");
	Tile board[35][25];
	sf::Clock clock;
	Time time = seconds(0);
	
	Snake mySnake;
	
	while (window.isOpen())
	{
		//Make snake move
		time += milliseconds(50);
		if (time.asSeconds() > 0.5)
		{
			mySnake.move(board);
			time = seconds(0);
		}
		
		//Resets Board
		if (mySnake.reset == true)
		{
			resetBoard(mySnake, board);
			mySnake.reset = false;
		}
		
		//process events
		Event event;
		while (window.pollEvent(event))
		{
			string direction = mySnake.snakeHead.direction;
			
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::A && direction !="RIGHT") { mySnake.snakeHead.direction = "LEFT"; }
				if (event.key.code == Keyboard::D && direction != "LEFT") { mySnake.snakeHead.direction = "RIGHT"; }
				if (event.key.code == Keyboard::W && direction != "DOWN") { mySnake.snakeHead.direction = "UP"; }
				if (event.key.code == Keyboard::S && direction != "UP") { mySnake.snakeHead.direction = "DOWN"; }
				if (event.key.code == Keyboard::Space) { mySnake.reset = true; }
			}
			if (event.type == Event::MouseButtonPressed)
			{
				
			}
			
		}
		//Clear Screen
		window.clear(Color::White);

		//Draw Board
		printBoard(window, board, gameTextures);

		//Display to Screen
		window.display();
	}
	
	return 0;
}
void resetBoard(Snake &mySnake, Tile(&board)[35][25])
{
	mySnake.resetSnake();
	for (unsigned int i = 0; i < 35; i++)
	{
		for (unsigned int j = 0; j < 25; j++)
		{
			if (i < 2 || i > 32 || j < 2 || j > 22)
			{
				board[i][j].setStatus(3);
			}
			else
			{
				board[i][j].setStatus(0);
			}
		}
	}
	
	mySnake.spawnApple(board);
}

void printBoard(RenderWindow &window, Tile (&board)[35][25], map<string, Texture> &textures)
{
	Sprite sprite;
	int w = 21;

	for (unsigned int i = 0; i < 35; i++)
	{
		for (unsigned int j = 0; j < 25; j++)
		{
			if (board[i][j].getStatus() == 0)
			{
				sprite.setTexture(textures["Black"]);
				sprite.setPosition(i * w, j * w);
				window.draw(sprite);
			}
			else if (board[i][j].getStatus() == 1)
			{
				sprite.setTexture(textures["Green"]);
				sprite.setPosition(i * w, j * w);
				window.draw(sprite);
			}
			else if (board[i][j].getStatus() == 2)
			{
				sprite.setTexture(textures["Red"]);
				sprite.setPosition(i * w, j * w);
				window.draw(sprite);
			}
			else if (board[i][j].getStatus() == 3)
			{
				sprite.setTexture(textures["Blue"]);
				sprite.setPosition(i * w, j * w);
				window.draw(sprite);
			}
			else if (board[i][j].getStatus() == 4)
			{
				sprite.setTexture(textures["Orange"]);
				sprite.setPosition(i * w, j * w);
				window.draw(sprite);
			}
		}
	}

}

