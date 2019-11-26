#include "Instruction.h"

Instruction::Instruction(string binary) {
	type = "DEFAULT";
	disassembled = "DEFAULT";
	srcOne = NAN;
	srcTwo = NAN;
	offset = NAN;
	dest = NAN;
	immediateValue = NAN;
	srcdst = NAN; 

	//determine type of instruction and set appropriate variables 
	if (binary == "10100000000000000000000000000000") {
		type = "DUMMY";
	}
	else {
		string firstThree = binary.substr(0, 3);

		//category 1 instructions
		if (firstThree == "001") {
			string opCode = binary.substr(3, 5);

			if (opCode == "10000") {
				type = "CBZ";

			}
			else if (opCode == "10001") {
				type = "CBNZ";
			}

			srcOne = stoi(binary.substr(8, 5), 0, 2);
			string offsetBinary = binary.substr(13, 19);

			if (offsetBinary.at(0) == '0') {
				offset = stoi(offsetBinary, 0, 2);
			}
			else {
				long offsetRaw = stol(offsetBinary, 0, 2);
				long offsetFlipped = offsetRaw ^ 524287;
				long offsetPos = offsetFlipped + 1;
				offset = 0 - offsetPos;
			}
		}

		//category 2 instructions
		if (firstThree == "010") {
			string opCode = binary.substr(3, 7);

			if (opCode == "1000000") {
				type = "ORRI";
			}
			else if (opCode == "1000001") {
				type = "EORI";
			}
			else if (opCode == "1000010") {
				type = "ADDI";
			}
			else if (opCode == "1000011") {
				type = "SUBI";
			}
			else if (opCode == "1000100") {
				type = "ANDI";
			}

			dest = stoi(binary.substr(10, 5), 0, 2);
			srcOne = stoi(binary.substr(15, 5), 0, 2);
			immediateValue = stol(binary.substr(20, 12), 0, 2);
		}

		//category 3 instructions
		if (firstThree == "011") {
			string opCode = binary.substr(3, 8);

			if (opCode == "10100000") {
				type = "EOR";
			}
			else if (opCode == "10100010") {
				type = "ADD";
			}
			else if (opCode == "10100011") {
				type = "SUB";
			}
			else if (opCode == "10100100") {
				type = "AND";
			}
			else if (opCode == "10100101") {
				type = "ORR";
			}
			else if (opCode == "10100110") {
				type = "LSR";
			}
			else if (opCode == "10100111") {
				type = "LSL";
			}

			dest = stoi(binary.substr(11, 5), 0, 2);
			srcOne = stoi(binary.substr(16, 5), 0, 2);
			srcTwo = stoi(binary.substr(21, 5), 0, 2);
		}

		//category 4 instructions 
		if (firstThree == "100") {
			string opCode = binary.substr(3, 8);

			if (opCode == "10101010") {
				type = "LDUR";
			}
			else if (opCode == "10101011") {
				type = "STUR";
			}

			srcdst = stoi(binary.substr(11, 5), 0, 2);
			srcOne = stoi(binary.substr(16, 5), 0, 2);

			string immediateBinary = binary.substr(21, 11);

			if (immediateBinary.at(0) == '0') {
				immediateValue = stoi(immediateBinary, 0, 2);
			}
			else {
				long immediateRaw = stol(immediateBinary, 0, 2);
				long immediateFlipped = immediateRaw ^ 2047;
				long immediatePos = immediateFlipped + 1;
				immediateValue = 0 - immediatePos;
			}
		}
	}
}

Instruction::Instruction() {
	type = "DEFAULT";
	disassembled = "DEFAULT";
	srcOne = NAN;
	srcTwo = NAN;
	offset = NAN;
	dest = NAN;
	immediateValue = NAN;
	srcdst = NAN;
}

string Instruction::getType() {
	return type;
}

string Instruction::getDisassembled() {
	return disassembled;
}

void Instruction::setDisassembled(string disassembled) {
	this->disassembled = disassembled;
}

int Instruction::getSrcOne() {
	return srcOne;
}

int Instruction::getSrcTwo() {
	return srcTwo;
}

int Instruction::getOffset() {
	return offset;
}

int Instruction::getDest() {
	return dest;
}

long Instruction::getImmediateValue() {
	return immediateValue;
}

int Instruction::getSrcDst() {
	return srcdst;
}
