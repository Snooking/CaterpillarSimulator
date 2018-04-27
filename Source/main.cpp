#include "Map.h"

int main() {
	//Initializing variables
	int width, height, length;
	//Scanning values of variables
	scanf("%d %d %d\n", &width, &height, &length);

	//Creating map which we'll work on
	Map* Mapa = new Map(width, height, length);

	//Map actions
	Mapa->ScanMap();
	Mapa->ScanCommands();
	Mapa->PrintMap();


	delete Mapa;

	return 0;
}