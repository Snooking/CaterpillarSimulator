#include "Map.h"

//Base Constructor
Map::Map(int width, int height, int length) {
	SetWidth(width);
	SetHeight(height);
	CreateMap();
	Edek = new Caterpillar(length);
}

Map::~Map() {
	delete Edek;
for (int i=0; i<Height; i++) { delete map[i];}
	delete map;
}

//Getter of Height
int Map::GetHeight() {
	return Height;
}

//Getter of Width
int Map::GetWidth() {
	return Width;
}

//Setter of Height
void Map::SetHeight(int height) {
	Height = height;
}

//Setter of Width
void Map::SetWidth(int width) {
	Width = width;
}

//Get current positions sign
char Map::GetCurrentPosition(int currentHeight, int currentWidth) {
	if (currentHeight < 0 || currentHeight >= Height || currentWidth < 0 || currentWidth >= Width)
		return '.';
	return map[currentHeight][currentWidth];
}

//Set current positions sign
void Map::SetCurrentPosition(int currentHeight, int currentWidth, char sign) {
	map[currentHeight][currentWidth] = sign;
}

//Constructor of map
void Map::CreateMap() {
	map = new char*[Height];
	for (int i = 0; i < Height; i++) {
		map[i] = new char[Width];
	}
}

//Scanner of the map
void Map::ScanMap() {
	char currentSign;
	int currentPosition = 0;
	int howMany = 0;
	while (currentPosition < Height*Width) {
		scanf("%c", &currentSign);
		if (currentSign == ' ' || currentSign == '\n') continue;
		else if (currentSign >= '0' && currentSign <= '9')
			howMany = howMany * 10 + CharToInt(currentSign);
		else if (howMany > 0) {
			for (int i = 0; i < howMany; i++) {
				SetCurrentPosition(currentPosition / Width, currentPosition % Width, currentSign);
				currentPosition++;
			}
			howMany = 0;
		}
		else {
			SetCurrentPosition(currentPosition / Width, currentPosition%Width, currentSign);
			currentPosition++;
		}
	}
}

void Map::ScanCommands() {
	char currentDirection;
	int howMany = 0;
	while ((currentDirection=getchar()) != EOF && CheckIfEdekIsAlive()) {
		if (currentDirection == ' ' || currentDirection == '\n') continue;
		else if (currentDirection >= '0' && currentDirection <= '9')
			howMany = howMany * 10 + CharToInt(currentDirection);
		else if (howMany > 0) {
			MoveCaterpillar(currentDirection, howMany);
			howMany = 0;
		}
		else {
			MoveCaterpillar(currentDirection, 1);
		}
	}
}

//Converter from char to short
int Map::CharToInt(char currentSign) {
	int howMany = 0;
	switch (currentSign)
	{
	case '0':
		break;
	case '1':
		howMany = 1;
		break;
	case '2':
		howMany = 2;
		break;
	case '3':
		howMany = 3;
		break;
	case '4':
		howMany = 4;
		break;
	case '5':
		howMany = 5;
		break;
	case '6':
		howMany = 6;
		break;
	case '7':
		howMany = 7;
		break;
	case '8':
		howMany = 8;
		break;
	case '9':
		howMany = 9;
		break;
	default:
		break;
	}
	return howMany;
}

//Moves Caterpillar around
void Map::MoveCaterpillar(char direction, int howMany) {
	int CurrentPosition = Edek->GetCurrentPosition();
	switch (direction)
	{
	case 'p':
		if (CurrentPosition % Width + howMany >= Width)
			CurrentPosition = CheckForObstaclesRight(Width - (CurrentPosition % Width) - 1, CurrentPosition);
		else
			CurrentPosition = CheckForObstaclesRight(howMany, CurrentPosition);
		break;
	case 'l':
		if (CurrentPosition % Width - howMany < 0)
			CurrentPosition = CheckForObstaclesLeft(CurrentPosition % Width, CurrentPosition);
		else
			CurrentPosition = CheckForObstaclesLeft(howMany, CurrentPosition);
		break;
	case 'd':
		if (CurrentPosition + howMany * Width >= Height * Width)
			CurrentPosition = CheckForObstaclesDown(Height - (CurrentPosition / Width) - 1, CurrentPosition);
		else
			CurrentPosition = CheckForObstaclesDown(howMany, CurrentPosition);
		break;
	case 'g':
		if (CurrentPosition - howMany * Width < 0)
			CurrentPosition = CheckForObstaclesUp(CurrentPosition / Width, CurrentPosition);
		else
			CurrentPosition = CheckForObstaclesUp(howMany, CurrentPosition);
		break;
	default:
		break;
	}
	Edek->SetCurrentPosition(CurrentPosition);
}

//Check if there's obstacle on right side of us
int Map::CheckForObstaclesRight(int howMany, int currentPosition) {
	for (int i = 0; i < howMany; i++) {
		currentPosition = ReactToObstacle(currentPosition + 1, currentPosition);
	}
	return currentPosition;
}

//Check if there's obstacle on left side of us
int Map::CheckForObstaclesLeft(int howMany, int currentPosition) {
	for (int i = 0; i < howMany; i++) {
		currentPosition = ReactToObstacle(currentPosition - 1, currentPosition);
	}
	return currentPosition;
}

//Check if there's obstacle on our bottom
int Map::CheckForObstaclesDown(int howMany, int currentPosition) {
	for (int i = 0; i < howMany; i++) {
		currentPosition = ReactToObstacle(currentPosition + Width, currentPosition);
	}
	return currentPosition;
}

//Check if there's obstacle on top of us
int Map::CheckForObstaclesUp(int howMany, int currentPosition) {
	for (int i = 0; i < howMany; i++) {
		currentPosition = ReactToObstacle(currentPosition - Width, currentPosition);
	}
	return currentPosition;
}

//Check what obstacle we're hitting and what to do with it
int Map::ReactToObstacle(int positionToGo, int currentPosition) {
	if (positionToGo >= Width*Height) return positionToGo;
	if (map[positionToGo / Width][positionToGo % Width] == 'G') {
		Edek->SetLength(Edek->GetLength() + 1);
		map[positionToGo / Width][positionToGo % Width] = '.';
		Edek->Color->Push(NULL);
	}

	else if (map[positionToGo / Width][positionToGo % Width] == 'K') {
		Edek->Color->Pop();
		Edek->SetLength(Edek->GetLength() - 1);
		if (Edek->GetLength() <= 0) return currentPosition;
	}

	else if (map[positionToGo / Width][positionToGo % Width] >= 'a' && map[positionToGo / Width][positionToGo%Width] <= 'z') {
		Edek->Color->SetNextValue(map[positionToGo / Width][positionToGo%Width]);
	}

	else if (map[positionToGo / Width][positionToGo%Width] == '.' && Edek->Color->GetNextValue() != NULL) {
		map[positionToGo / Width][positionToGo%Width] = Edek->Color->GetNextValue();
	}

	if (map[positionToGo / Width][positionToGo%Width] == 'T') return currentPosition;

	else {
		Edek->Color->Go();
		return positionToGo;
	}
}

bool Map::CheckIfEdekIsAlive() {
	return Edek->Alive() ? true : false;
}

//Printer of the map
void Map::PrintMap() {
	Edek->Death(Width);
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}
