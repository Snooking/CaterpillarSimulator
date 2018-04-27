#ifndef LIST
#define LIST

#define NULL 0

class List {
private:
	struct Elem {
		char Value;
		Elem* Next;
	};
	Elem* Current;
public:
	char GetCurrentValue();
	void SetCurrentValue(char);
	void Push(char);
	void Go();
	void Pop();
	void SetNextValue(char value);
	char GetNextValue();
};

#endif