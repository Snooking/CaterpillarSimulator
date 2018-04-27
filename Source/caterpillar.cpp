#include "Caterpillar.h"

//Base constructor
Caterpillar::Caterpillar(int length) {
	Length = length;
	CurrentPosition = 0;
	Color = new List();
	for (int i = 0; i < Length; i++) {
		Color->Push(NULL);
	}
}

Caterpillar::~Caterpillar() {
	delete Color;
}

//Returns Length of the Caterpillar
int Caterpillar::GetLength() {
	return Length;
}

//Sets Length of the Caterpillar
void Caterpillar::SetLength(int length) {
	Length = length;
}

//Returns Current Position of the Caterpillar
int Caterpillar::GetCurrentPosition() {
	return CurrentPosition;
}

//Sets Current Position of the Caterpillar
void Caterpillar::SetCurrentPosition(int currentPosition) {
	CurrentPosition = currentPosition;
}

//Printing a word of goodbye from caterpillar
void Caterpillar::Death(int width) {
	if (!Alive())
		printf ("Zegnaj, okrutny swiecie!\n%hd %hd\n", CurrentPosition % width, CurrentPosition / width);
	else printf("%hd %hd\n", CurrentPosition % width, CurrentPosition / width);
}

bool Caterpillar::Alive() {
	return Length > 0 ? true : false;
}

