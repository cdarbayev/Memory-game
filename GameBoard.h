#pragma once
#include "Tile.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <windows.h>
#include <algorithm>


class GameBoard
{
private:
	sf::RenderWindow* window;
	std::vector <Tile*> tilesVec;
	std::vector <int> activeTilesVec;
	std::vector <int> selectionVec;
	float keyTime, keyTimeMax;
	sf::Vector2f mousePosView;
	float tileSize;
	bool exitGame;
	int tilesSelected;
	int nbOfActiveTiles;
	bool restarting;
	float displayTimer;
	int correct;
	int incorrect;
	clock_t startTime;
	clock_t endTime;
	bool timerStarted;

	void createBoard(const int board_width, const int board_height);
	void randomizeBoard();
	void displayOrder();
	const bool checkSelection();
	void updateKeyTime();
	void updateBoard();
	inline const bool checkKeyTime() const {
		return this->keyTime >= this->keyTimeMax;
	}
	inline void resetKeyTime() {
		this->keyTime = 0.f;
	}


public:
	GameBoard();
	GameBoard(sf::RenderWindow* window, float tile_size, int board_width, int board_height, int nr_active);
	~GameBoard();
	inline const bool checkExit() const {
		return this->exitGame;
	}

	void restart();
	void update(sf::RenderWindow& window);
	void render(sf::RenderTarget& target);

};

