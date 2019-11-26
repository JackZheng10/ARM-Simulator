#pragma once
#include <string>

using namespace std;

class Instruction {
	string type;
	string disassembled;
	int srcOne;
	int srcTwo;
	int offset;
	int dest;
	long immediateValue;
	int srcdst;

public:
	Instruction(string binary);
	Instruction();
	string getType();
	string getDisassembled();
	void setDisassembled(string disassembled);
	int getSrcOne();
	int getSrcTwo();
	int getOffset();
	int getDest();
	long getImmediateValue();
	int getSrcDst();
};

