#ifndef MAP
#define MAP

#include <stdio.h>
#include "Caterpillar.h"

class Map {
private:
	int Width;
	int Height;
	char** map;
	Caterpillar* Edek;

	void MoveCaterpillar(char direction, int howMany);
	int CheckForObstaclesRight(int howMany, int currentPosition);
	int CheckForObstaclesLeft(int howMany, int currentPosition);
	int CheckForObstaclesDown(int howMany, int currentPosition);
	int CheckForObstaclesUp(int howMany, int currentPosition);
	int ReactToObstacle(int positionToGo, int currentPosition);

	void CreateMap();
	int CharToInt(char);

public:
	Map(int, int, int);
	~Map();

	int GetWidth();
	int GetHeight();
	void SetWidth(int);
	void SetHeight(int);

	char GetCurrentPosition(int, int);
	void SetCurrentPosition(int, int, char);

	void ScanMap();
	void ScanCommands();
	bool CheckIfEdekIsAlive();
	void PrintMap();
};

#endif
