#include "Instruction.h"

Instruction::Instruction(string binary) {
	type = "DEFAULT";
	disassembled = "DEFAULT";
	srcOne = 0;
	srcTwo = 0;
	offset = 0;
	dest = 0;
	immediateValue = 0;
	srcdst = 0; 

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
				int32_t	offsetRaw = stol(offsetBinary, 0, 2);
				int32_t	offsetFlipped = offsetRaw ^ 524287;
				int32_t	offsetPos = offsetFlipped + 1;
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
				int32_t	immediateRaw = stol(immediateBinary, 0, 2);
				int32_t	immediateFlipped = immediateRaw ^ 2047;
				int32_t	immediatePos = immediateFlipped + 1;
				immediateValue = 0 - immediatePos;
			}
		}
	}
}

Instruction::Instruction() {
	type = "DEFAULT";
	disassembled = "DEFAULT";
	srcOne = 0;
	srcTwo = 0;
	offset = 0;
	dest = 0;
	immediateValue = 0;
	srcdst = 0;
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

int32_t	Instruction::getSrcOne() {
	return srcOne;
}

int32_t	Instruction::getSrcTwo() {
	return srcTwo;
}

int32_t	Instruction::getOffset() {
	return offset;
}

int32_t	Instruction::getDest() {
	return dest;
}

int32_t	Instruction::getImmediateValue() {
	return immediateValue;
}

int32_t	Instruction::getSrcDst() {
	return srcdst;
}
