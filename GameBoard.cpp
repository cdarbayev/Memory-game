#include "GameBoard.h"
#include <ctime>

void GameBoard::createBoard(const int board_width, const int board_height)
{
	float x = 0.f;
	float y = 0.f;
	for (size_t i = 0; i < board_height; i++)
	{
		for (size_t k = 0; k < board_width; k++)
		{
			tilesVec.push_back(new Tile(sf::Vector2f(x, y), tileSize, false));
			x += tileSize;
		}
		y += tileSize;
		x = 0.f;
	}
}

void GameBoard::randomizeBoard()
{
	activeTilesVec.clear();
	for (size_t i = 0; i < tilesVec.size(); i++)
	{
		tilesVec[i]->setActive(false);
		tilesVec[i]->setColorInactive();
	} 

	std::vector<int> index_vector;
	for (size_t i = 0; i < tilesVec.size(); i++)
	{
		index_vector.push_back(i);
	}

	int tiles_added = 0;
	int index = -1;
	while (tiles_added != nbOfActiveTiles)
	{
		index = rand() % index_vector.size();
		tilesVec[index_vector[index]]->setActive(true);
		tilesVec[index_vector[index]]->setColorActive();
		activeTilesVec.push_back(index_vector[index]);
		index_vector.erase(index_vector.begin() + index);
		tiles_added++;
	}

}

void GameBoard::displayOrder()
{
	if (displayTimer < 50.f)
	{
		for (size_t i = 0; i < tilesVec.size(); i++)
		{
			tilesVec[i]->setColorInactive();
		}
	}
	else if(displayTimer >= 50.f && displayTimer < 100.f)
	{
		for (size_t i = 0; i < tilesVec.size(); i++)
		{
			if (tilesVec[i]->isActive())
				tilesVec[i]->setColorActive();
		}
	}
	else if (displayTimer >= 100.f && displayTimer < 150.f)
	{
		for (size_t i = 0; i < tilesVec.size(); i++)
		{
			tilesVec[i]->setColorInactive();
		}
	}
	else
	{
		restarting = false;
	}

	displayTimer += 1.f;
}

const bool GameBoard::checkSelection()
{
	std::sort(activeTilesVec.begin(), activeTilesVec.end());
	std::sort(selectionVec.begin(), selectionVec.end());

	return activeTilesVec == selectionVec;
}

void GameBoard::updateKeyTime()
{
	if (keyTime < keyTimeMax)
		keyTime += 1.f;
}

void GameBoard::updateBoard()
{
	if (restarting)
	{
		displayOrder();
	}
	else
	{
		if (tilesSelected < nbOfActiveTiles)
		{
			for (size_t i = 0; i < tilesVec.size(); i++)
			{
				tilesVec[i]->update(mousePosView, sf::Mouse::isButtonPressed(sf::Mouse::Left));

				if (tilesVec[i]->isPressed() && checkKeyTime())
				{
					if (!timerStarted && tilesSelected == 0) {
						startTime = clock();
						timerStarted = true;
					}
					selectionVec.push_back(i);
					tilesVec[i]->setColorActive();
					tilesSelected++;
					resetKeyTime();
				}
			}
		}
		else
		{
			if (checkSelection())
			{
				std::cout << "Correct" << "\n";
				correct++;
			}
			else
			{
				std::cout << "Incorrect" << "\n";
				incorrect++;
			}
			if (tilesSelected == nbOfActiveTiles) {
				endTime = clock();
				double timeToSolve = double(endTime - startTime) / 1000;

				std::cout << "Time from start: " << timeToSolve << " seconds\n";
			}
			std::cout << "Correct/Incorrect: " << correct << "/" << incorrect << "\n";
			restart();
		}
	}
}

GameBoard::GameBoard()
{
	window = nullptr;
	tileSize = 0.f;
	exitGame = false;
	keyTimeMax = 0.f;
	keyTime = 0.f;
	nbOfActiveTiles = 0;
	tilesSelected = 0;
	restarting = false;
	displayTimer = 0.f;
	correct = 0;
	incorrect = 0;
	timerStarted = false;
}

GameBoard::GameBoard(sf::RenderWindow* window, float tile_size, int board_width, int board_height, int nr_active)
	: window(window)
{
	tileSize = tile_size;
	exitGame = false;
	keyTimeMax = 10.f;
	keyTime = keyTimeMax;
	nbOfActiveTiles = nr_active;
	tilesSelected = 0;
	restarting = true;
	displayTimer = 0.f;
	correct = 0;
	incorrect = 0;
	timerStarted = false;

	createBoard(board_width, board_height);
	randomizeBoard();
}

GameBoard::~GameBoard()
{
	for (size_t i = 0; i < tilesVec.size(); i++)
	{
		delete tilesVec[i];
	}
}

void GameBoard::restart()
{
	tilesSelected = 0;
	restarting = true;
	displayTimer = 0.f;
	selectionVec.clear();
	randomizeBoard();
}

void GameBoard::update(sf::RenderWindow& window)
{
	mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	updateKeyTime();
	updateBoard();
}

void GameBoard::render(sf::RenderTarget& target)
{
	for (size_t i = 0; i < tilesVec.size(); i++)
	{
		tilesVec[i]->render(target);
	}
}
