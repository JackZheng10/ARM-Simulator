## Available Instructions and Formatting

### Category 1:

**CBZ, CBNZ**

32-bit format:
001 + [Opcode (5 bits)] + [Src1 (5 bits)] + [Branch Offset (19 bits)]
<br/><br/>
Opcodes: <br/>
CBZ: 10000 <br/>
CBNZ: 10001 <br/>

### Category 2:

**ADDI, SUBI, ANDI, ORRI, EORI**

32-bit format:
001 + [Opcode (7 bits)] + [Dest (5 bits)] + [Src1 (5 bits)] + [Immediate Value (12 bits)]
<br/><br/>
Opcodes: <br/>
ORRI: 1000000 <br/>
EORI: 1000001 <br/>
ADDI: 1000010 <br/>
SUBI: 1000011 <br/>
ANDI: 1000100 <br/>

### Category 3:

**ADD, SUB, AND, ORR, EOR, LSR, LSL**

32-bit format:
001 + [Opcode (8 bits)] + [Dest (5 bits)] + [Src1 (5 bits)] + [Src2 (5 bits)] + 000000
<br/><br/>
Opcodes: <br/>
EOR: 10100000 <br/>
ADD: 10100010 <br/>
SUB: 10100011 <br/>
AND: 10100100 <br/>
ORR: 10100101 <br/>
LSR: 10100110 <br/>
LSL: 10100111 <br/>

### Category 4:

**LDUR, STUR**

32-bit format:
001 + [Opcode (8 bits)] + [SrcDst (5 bits)] + [Src1 (5 bits)] + [Immediate Value (11 bits)]
<br/><br/>
Opcodes: <br/>
LDUR: 10101010 <br/>
STUR: 10101011 <br/>

## Outputs

### `disassembly.txt`

Shows each 32-bit instruction word, its address, and its corresponding instruction or memory value.

### `simulation.txt`

Shows a simulation of the program run. Shows the cycle number, instruction ran and its address, and values in registers and memory.

## Notes

-Instructions are based on the Arm Instruction Set V1.0. <br/>
-File is taken in as a command line argument. <br/>
-Words are 4 bytes long. <br/>
-Instructions begin at address 64. <br/>
-LSL and LSR use the 5 least significant bits of Src2. <br/>
-There are 32 registers. <br/>
-There is a dummy instruction "10100000000000000000000000000000" which indicates the end of instructions and the beginning of 32-bit 2s-complement signed values in memory to be initialized. Memory addresses naturally begin right after this dummy instruction's address. <br/>
-For the newline character, Linux uses "/n" while Windows uses "\r\n". So, for example, you will get an error if you compile in a Linux environment using an input file generated in a Windows one.
