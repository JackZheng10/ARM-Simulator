#pragma once
#include <string>
#include <cstdint> 

using namespace std;

class Instruction {
	string type;
	string disassembled;
	int32_t	srcOne;
	int32_t	srcTwo;
	int32_t	offset;
	int32_t	dest;
	int32_t	immediateValue;
	int32_t	srcdst;

public:
	Instruction(string binary);
	Instruction();
	string getType();
	string getDisassembled();
	void setDisassembled(string disassembled);
	int32_t	getSrcOne();
	int32_t	getSrcTwo();
	int32_t	getOffset();
	int32_t	getDest();
	int32_t	getImmediateValue();
	int32_t	getSrcDst();
};

