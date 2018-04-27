#include "List.h"

//Gets current value
char List::GetCurrentValue() {
	return Current->Value;
}

//Sets value of this element
void List::SetCurrentValue(char value) {
	Current->Value = value;
}

//Pushes new element after current one
void List::Push(char value) {
	if (Current == NULL) {
		Current = new Elem();
		Current->Value = value;
		Current->Next = Current;
	}
	else {
		Elem* elem = new Elem();
		elem->Value = value;
		elem->Next = Current->Next;
		Current->Next = elem;
	}
}

void List::Go() {
	Current = Current->Next;
}

void List::Pop() {
	if (Current == NULL) return;
	if (Current->Next == Current) {
		return;
	}
	Elem* tmp;
	tmp = Current->Next;
	Current->Next = tmp->Next;
	delete tmp;
}

void List::SetNextValue(char value) {
	Current->Next->Value = value;
}

char List::GetNextValue() {
	return Current->Next->Value;
}
