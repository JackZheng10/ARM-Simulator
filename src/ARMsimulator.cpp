#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "Instruction.h"

//begin implementation of main program 
int32_t	programCounter = 64;

//used for printing of memory contents - differentiates between memory and instruction addresses 
int32_t	memBegin;
int32_t	memEnd;

//used to evaluate an instruction and update appropriate fields in memory, registers, and/or program counter 
void evaluate(map<int32_t, Instruction>& instructions, map<int32_t, int32_t>& memory, vector<int32_t>& registers, int32_t& programCounter) {
	Instruction current = instructions[programCounter];

	if (current.getType() == "CBZ") {
		if (registers[current.getSrcOne()] == 0) {
			programCounter = (current.getOffset() << 2) + programCounter;
		}
		else {
			programCounter += 4;
		}
	}
	else if (current.getType() == "CBNZ") {
		if (registers[current.getSrcOne()] != 0) {
			programCounter = (current.getOffset() * 4) + programCounter;
		}
		else {
			programCounter += 4;
		}
	}
	else if (current.getType() == "ADDI") {
		registers[current.getDest()] = registers[current.getSrcOne()] + current.getImmediateValue();
		programCounter += 4;
	}
	else if (current.getType() == "SUBI") {
		registers[current.getDest()] = registers[current.getSrcOne()] - current.getImmediateValue();
		programCounter += 4;
	}
	else if (current.getType() == "ANDI") {
		registers[current.getDest()] = (uint32_t)registers[current.getSrcOne()] & (uint32_t)current.getImmediateValue();
		programCounter += 4;
	}
	else if (current.getType() == "ORRI") {
		registers[current.getDest()] = (uint32_t)registers[current.getSrcOne()] | (uint32_t)current.getImmediateValue();
		programCounter += 4;
	}
	else if (current.getType() == "EORI") {
		registers[current.getDest()] = (uint32_t)registers[current.getSrcOne()] ^ (uint32_t)current.getImmediateValue();
		programCounter += 4;
	}
	else if (current.getType() == "ADD") {
		registers[current.getDest()] = registers[current.getSrcOne()] + registers[current.getSrcTwo()];
		programCounter += 4;
	}
	else if (current.getType() == "SUB") {
		registers[current.getDest()] = registers[current.getSrcOne()] - registers[current.getSrcTwo()];
		programCounter += 4;
	}
	else if (current.getType() == "AND") {
		registers[current.getDest()] = (uint32_t)registers[current.getSrcOne()] & (uint32_t)registers[current.getSrcTwo()];
		programCounter += 4;
	}
	else if (current.getType() == "ORR") {
		registers[current.getDest()] = (uint32_t)registers[current.getSrcOne()] | (uint32_t)registers[current.getSrcTwo()];
		programCounter += 4;
	}
	else if (current.getType() == "EOR") {
		registers[current.getDest()] = (uint32_t)registers[current.getSrcOne()] ^ (uint32_t)registers[current.getSrcTwo()];
		programCounter += 4;
	}
	else if (current.getType() == "LSR") {
		uint32_t fiveLSB = registers[current.getSrcTwo()] & (uint32_t)31;
		registers[current.getDest()] = (uint32_t)registers[current.getSrcOne()] >> fiveLSB;
		programCounter += 4;
	}
	else if (current.getType() == "LSL") {
		uint32_t fiveLSB = registers[current.getSrcTwo()] & (uint32_t)31;
		registers[current.getDest()] = (uint32_t)registers[current.getSrcOne()] << fiveLSB;
		programCounter += 4;
	}
	else if (current.getType() == "LDUR") {
		registers[current.getSrcDst()] = memory[registers[current.getSrcOne()] + current.getImmediateValue()];
		programCounter += 4;
	}
	else if (current.getType() == "STUR") {

		memory[registers[current.getSrcOne()] + current.getImmediateValue()] = registers[current.getSrcDst()];
		programCounter += 4;
	}
}

//used to output a layout of instructions, their addresses, and memory values along with their addresses  
void disassemble(map<int32_t, Instruction>& instructions, map<int32_t, int32_t>& memory, vector<string>& instructionRead) {
	//outputs int32_t	o disassembly.txt 
	ofstream file("disassembly.txt");

	int32_t index = 0;
	int32_t	memIndex = 64;

	if (file.is_open()) {
		for (uint32_t	 x = index; x < instructions.size(); x++) {
			//prints out the raw binary, its address, and a built disassembled instruction in human-readable format
			file << instructionRead[x];
			file << "\t";
			file << memIndex;
			file << "\t";

			Instruction& current = instructions[memIndex];
			string instructionType = current.getType();

			if (instructionType == "CBZ" || instructionType == "CBNZ") {
				string disassemble = "";
				disassemble = disassemble + instructionType + " ";

				if (current.getSrcOne() == 31) {
					disassemble += "XZR, ";
				}
				else {
					disassemble = disassemble + "X" + to_string(current.getSrcOne()) + ", ";
				}

				disassemble = disassemble + "#" + to_string(current.getOffset());
				current.setDisassembled(disassemble);
				file << disassemble << endl;
			}
			else if (instructionType == "ADDI" || instructionType == "SUBI" || instructionType == "ANDI" || instructionType == "ORRI" || instructionType == "EORI") {
				string disassemble = "";
				disassemble = disassemble + instructionType + " ";

				if (current.getDest() == 31) {
					disassemble = disassemble + "XZR, ";
				}
				else {
					disassemble = disassemble + "X" + to_string(current.getDest()) + ", ";
				}

				if (current.getSrcOne() == 31) {
					disassemble = disassemble + "XZR, ";
				}
				else {
					disassemble = disassemble + "X" + to_string(current.getSrcOne()) + ", ";
				}

				disassemble = disassemble + "#" + to_string(current.getImmediateValue());
				current.setDisassembled(disassemble);
				file << disassemble << endl;
			}
			else if (instructionType == "ADD" || instructionType == "SUB" || instructionType == "AND" || instructionType == "ORR" || instructionType == "EOR" || instructionType == "LSR" || instructionType == "LSL") {
				string disassemble = "";
				disassemble = disassemble + instructionType + " ";

				if (current.getDest() == 31) {
					disassemble = disassemble + "XZR, ";
				}
				else {
					disassemble = disassemble + "X" + to_string(current.getDest()) + ", ";
				}

				if (current.getSrcOne() == 31) {
					disassemble = disassemble + "XZR, ";
				}
				else {
					disassemble = disassemble + "X" + to_string(current.getSrcOne()) + ", ";
				}

				if (current.getSrcTwo() == 31) {
					disassemble = disassemble + "XZR";
				}
				else {
					disassemble = disassemble + "X" + to_string(current.getSrcTwo());
				}

				current.setDisassembled(disassemble);
				file << disassemble << endl;
			}
			else if (instructionType == "LDUR" || instructionType == "STUR") {
				string disassemble = "";
				disassemble = disassemble + instructionType + " ";

				if (current.getSrcDst() == 31) {
					disassemble = disassemble + "XZR, ";
				}
				else {
					disassemble = disassemble + "X" + to_string(current.getSrcDst()) + ", ";
				}

				if (current.getSrcOne() == 31) {
					disassemble = disassemble + "[XZR, ";
				}
				else {
					disassemble = disassemble + "[X" + to_string(current.getSrcOne()) + ", ";
				}

				disassemble = disassemble + "#" + to_string(current.getImmediateValue()) + "]";
				current.setDisassembled(disassemble);
				file << disassemble << endl;
			}
			else if (instructionType == "DUMMY") {
				string disassemble = "DUMMY";
				current.setDisassembled(disassemble);
				file << disassemble << endl;
			}

			index++;
			memIndex += 4;
		}

		for (uint32_t x = index; x < memory.size() + instructions.size(); x++) {
			//prints out memory address and its initial value 
			file << instructionRead[x];
			file << "\t";
			file << memIndex;
			file << "\t";
			file << memory[memIndex] << endl;

			index++;
			memIndex += 4;
		}

		file.close();
	}
}

int	main(int argc, char* argv[])
{
	//read the input file and store the raw binary in a vector

	//check for command line arg
	if (!argv[1]){
		cout << "Please specify a .txt file name." << endl;
		return 0;
	}

	ifstream fileRead(argv[1]);
	vector<string> instructionRead;

	if (fileRead.is_open()) {
		string instruction;

		while (getline(fileRead, instruction)) {
			instructionRead.push_back(instruction);
		}

		fileRead.close();
	} else {
		cout << "Could not open file. Please make sure it's a valid .txt file name." << endl;
		return 0;
	}

	//find the index of the dummy instruction 10100000000000000000000000000000, which has memory values following it
	auto myIterator = find(instructionRead.begin(), instructionRead.end(), "10100000000000000000000000000000");
	int32_t	 indexDummy = myIterator - instructionRead.begin();

	//each instruction has a unique address, starting from 64 (last instruction is the dummy)
	//translate the instruction into an instruction object 
	//map each instruction to its address using an ordered map
	map<int32_t, Instruction> instructions;
	int32_t	indexInstruction = 64;
	int32_t	indexVector = 0;
	for (int32_t x = indexVector; x < indexDummy + 1; x++) {
		instructions[indexInstruction] = Instruction(instructionRead[x]);
		indexInstruction += 4;
		indexVector++;
	}

	//load the values following last instruction into a map representing memory indexed by its address
	//4 byte word length
	//set initial and ending values for memory address to be used in printing
	map<int32_t	, int32_t> memory;
	memBegin = indexInstruction;

	for (uint32_t x = indexVector; x < instructionRead.size(); x++) {
		int32_t	value = 0;

		//push the correct value based on the sign 
		if (instructionRead[x].at(0) == '0') {
			value = stol(instructionRead[x], 0, 2);
		}
		else {
			int32_t	rawBinary = stoll(instructionRead[x], 0, 2);
			int32_t	flipped = rawBinary ^ 4294967295;
			int32_t	posRepresentation = flipped + 1;
			value = (int32_t)0 - posRepresentation;
		}

		memory[indexInstruction] = value;
		indexInstruction += 4;
	}

	memEnd = indexInstruction;

	//declare 32 registers, each with a default value of 0
	vector<int32_t> registers(32, 0);

	//outputs disassembly.txt using the disassemble method 
	disassemble(instructions, memory, instructionRead);

	//initialize variables used for simulation run 
	bool dummyReached = false;
	int32_t	cycle = 1;

	//instructions will run until the dummy instruction is reached
	//also outputs simulation.txt to show the run 
	ofstream fileWrite("simulation.txt");

	if (fileWrite.is_open()) {
		while (dummyReached != true) {
			//output the results of the current cycle 
			fileWrite << "--------------------" << endl;
			fileWrite << "Cycle " << cycle << ":" << "\t" << programCounter << "\t" << instructions[programCounter].getDisassembled() << endl;

			if (instructions[programCounter].getDisassembled() != "DUMMY") {
				evaluate(instructions, memory, registers, programCounter);
			}
			else {
				dummyReached = true;
			}

			fileWrite << endl;
			cycle++;

			//print contents of all registers 
			fileWrite << "Registers" << endl;
			fileWrite << "X00:";
			for (uint32_t x = 0; x < 8; x++) {
				fileWrite << "\t" << registers[x];
			}
			fileWrite << endl;

			fileWrite << "X08:";
			for (uint32_t x = 8; x < 16; x++) {
				fileWrite << "\t" << registers[x];
			}
			fileWrite << endl;

			fileWrite << "X16:";
			for (uint32_t x = 16; x < 24; x++) {
				fileWrite << "\t" << registers[x];
			}
			fileWrite << endl;

			fileWrite << "X24:";
			for (uint32_t x = 24; x < 32; x++) {
				fileWrite << "\t" << registers[x];
			}
			fileWrite << endl;

			fileWrite << endl;

			//print	contents of all memory addresses  
			fileWrite << "Data" << endl;
			int32_t	x = memBegin;
			int32_t	indexTemp = memBegin;

			for (x; x < memEnd; x += 32) {
				fileWrite << x << ":";

				for (int32_t y = 0; y < 8; y++) {
					if (indexTemp != memEnd) {
						fileWrite << "\t" << memory[indexTemp];
					}
					else {
						break;
					}
					indexTemp += 4;
				}

				fileWrite << endl;
			}

			fileWrite << endl;
		}
	}

	fileWrite.close();
}
