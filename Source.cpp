#pragma warning(disable:4996)

#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

typedef struct {
	wchar_t comm;
	wchar_t addr;
} VMCommand;

signed char regs[15] = { 0 };
//char prog_memIn[256];
VMCommand prog_mem[256];
char file_contents[10000];
bool die = false;
unsigned char iReg1, iReg2;
char* programFile = "decryptor.bin";
char* inputFile = "q1_encr.txt";

unsigned int jumper(VMCommand reg, int pc) {
	return (reg.addr + pc);
}

void main() {
	//std::char_traits<char>
		//std::char_traits<wchar_t>
	/* OPEN READ OF DECRYPTER */
	wifstream fp(programFile, ios::in | ios::binary);
	if (fp.is_open())
	{
		int i = 0;
		while (!fp.eof()) {
			fp.get(prog_mem[i].comm);
			fp.get(prog_mem[i].addr);
			// Outputs sum of 2 registers (reads just fine)
			//cout << hex << prog_mem[i].comm << "a" << prog_mem[i].addr << endl;
			i++;
		}
		fp.close();
	}
	else cout << "Unable to open program_mem file";

	/* CLOSE READ OF DECRYPTER */

	ifstream fp2(inputFile, ios::in | ios::binary);

	if (fp2.is_open())
	{
		int i = 0;
		while (!fp2.eof()) {
			fp2.get(file_contents[i]);
			//cout << file_contents[i];
			i++;
		}
		cout << endl;
		fp2.close();
	}
	else cout << "unable to open file";

	cout << "File read done." << endl;

	unsigned int pc = 0, i_r = 0;

	while (1) {
		iReg1 = prog_mem[pc].addr & 0x0F;
		iReg2 = (prog_mem[pc].addr & 0xF0) >> 4;
		/*if (iReg1 != 0) {
			cout << iReg1 << "as ireg" << endl;
		}*/

		cout << hex << prog_mem[pc].comm << " memoris" << endl;
		cout << hex << prog_mem[pc].addr << " addr" << endl;

		cout << "iregs:" << (int) iReg1 << " " << (int) iReg2 << endl;

		system("pause");


		switch (prog_mem[pc].comm)
		{
		case 0x01: {
			regs[iReg1]++;
			pc++;
			break;
		}
		case 0x02: {
			regs[iReg1]--;
			pc++;
			break;
		}
		case 0x03: {
			regs[1] = regs[2];
			pc++;
			break;
		}
		case 0x04: {
			regs[0] = prog_mem[pc].addr;
			pc++;
			//pc = prog_mem[pc].addr;
			break;
		}
		case 0x05: {
			regs[iReg1] = (unsigned char)(regs[iReg1] << 1);
			pc++;
			break;
		}
		case 0x06: {
			regs[iReg1] = (unsigned char)(regs[iReg1] >> 1);
			pc++;
			break;
		}
		case 0x07: {
			pc = prog_mem[pc].addr;
			break;
		}
		case 0x08: {
			cout << "die8";
			break;
		}
		case 0x09: {
			cout << "die9";
			break;
		}
		case 0x0A: {
			if (file_contents[i_r] = NULL) {
				cout << "luzo10";
				die = 1;
			}
			else {
				pc++;
			}
			break;
		}
		case 0x0B: {
			die = true;
			break;
		}
		case 0x0C: {
			regs[iReg1] += regs[iReg2];
			pc++;
			break;
		}
		case 0x0D: {
			regs[iReg1] -= regs[iReg2];
			pc++;
			break;
		}
		case 0x0E: {
			regs[iReg1] = regs[iReg1] ^ regs[iReg2];
			pc++;
			break;
		}
		case 0x0F: {
			regs[iReg1] = regs[iReg1] | regs[iReg2];
			pc++;
			break;
		}
		case 0x10: {
			if (file_contents[i_r] = NULL) cout << "luzo16";
			// pseudo skaitymas iš masyvo
			regs[iReg1] = file_contents[i_r];
			i_r++;
			pc++;
			//cout << endl << regs[iReg1] << "aaa";
			break;
		}
		case 0x11: {
			cout << regs[iReg1] << " ";
			pc++;
			break;
		}
		}
		if (die) {
			break;
		}
		//cout << endl;
	}

	cout << endl;

	system("pause");
}