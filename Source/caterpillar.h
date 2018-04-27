#ifndef CATERPILLAR
#define CATERPILLAR

#include <stdio.h>
#include "List.h"

class Caterpillar {
private:
	int CurrentPosition;
	int Length;
public:
	List* Color;
	Caterpillar(int);
	~Caterpillar();

	int GetLength();
	void SetLength(int);
	int GetCurrentPosition();
	void SetCurrentPosition(int);
	bool Alive();

	void Death(int width);
};

#endif
