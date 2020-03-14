//Emulator.cpp for HW4
//Isaiah Kiefer

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
	
	int i;
	char* in, * out;
	in = NULL;
	out = NULL;
	
	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--in") == 0)
		{
			if ((i + 1) < argc)
			{
				in = argv[i+1];
				i++;
			}
			else {
				cerr << "Error: --in missing file name\n";
				exit(1);
			}
		}
		else if (strcmp(argv[i], "--out") == 0)
		{
			if ((i + 1) < argc)
			{
				out = argv[i+1];
				i++;
			}
			else {
				cerr << "Error: --out missing file name\n";
				exit(1);
			}
		}
		else {
			cerr << "Error: invalid paramter >%s<\n", argv[i];
			exit(1);
		}
	}
	if (in == NULL)
	{
		cerr << "Error: missing --in <fn> parameter\n";
		exit(1);
	}
	if (out == NULL)
	{
		cerr << "Error: missing --out <fn> parameter\n";
		exit(1);
	}
	
	string inFile;
	int numFile;
	int num;
	ifstream file;
	string test;
	file.open(in);
	vector<int> mem;
	while (!file.eof())
	{
		file >> inFile;
		if (inFile.empty() || inFile[0] == '#')
		{

		}
		else {
			numFile = stoi(inFile, nullptr, 16);
			mem.push_back(numFile);
		}
	}
	
	int mbr = 0;
	int ac = 0;
	int mar = 0;
	int pc = 0;
	int input = 0;
	int output = 0;
	ofstream outFile;
	outFile.open(out);
	outFile << "Instruction	" << "PC" << endl;
	while (pc<5000 && ((mem[pc] & 0xF000) != 0x7000))
	{
		int instr=(mem[pc] & 0xF000);
		int hand = (mem[pc] & 0x0FFF);
		outFile << hex << instr << "		" << pc << endl;
		pc++;
		switch (instr)
		{
		case 0x1000://Load
			mar = hand;
			mbr = mem[mar];
			ac = mbr;
			break;
		case 0x2000://Store
			mbr = ac;
			mar = hand;
			mem[mar] = mbr;
			break;
		case 0x3000: //Add
			mar = hand;
			mbr = mem[mar];
			ac = ac + mbr;
			break;
		case 0x4000: //Subt
			mar = hand;
			mbr = mem[mar];
			ac = ac - mbr;
			break;
		case 0x5000://Input
			cout << "Input value" << endl;
			cin >> input;
			ac = input;
			break;
		case 0x6000://Output
			output = ac;
			cout<< output;
			outFile << "Output: " << dec << output<<endl;
			break;
	
		case 0x8000://skipcond
			 if ((hand & 0xF00) == 0x400)
			{
				if (ac == 0)
				{
					pc = pc + 1;
				}
			}
			else if ((hand & 0xF00) == 0x800)
			{
				if (ac > 0)
				{
					pc = pc + 1;
				}
			}
			else {
				 if (ac < 0)
				 {
					 pc = pc + 1;
				 }
			 }
			break;
		case 0x9000://Jump
			pc = hand;
			break;
		case 0x0000://JnS
			mbr = pc;
			mar = hand;
			mem[mar] = mbr;
			mbr = hand;
			ac = 1;
			ac = ac + mbr;
			pc = ac;
			break;
		case 0xa000://Clear
			ac = 0;
			break;
		case 0xb000://AddI
			mar = hand;
			mbr = mem[mar];
			mar = mbr;
			mbr = mem[mar];
			ac = ac + mbr;
			break;
		case 0xc000://JumpI
			mar = hand;
			mbr = mem[mar];
			pc = mbr;
			break;
		case 0xd000://Load I
			mar = hand;
			mbr = mem[mar];
			mar = mbr;
			mbr = mem[mar];
			ac = mbr;
			break;
		case 0xe000: //StoreI
			mar = hand;
			mbr = mem[mar];
			mar = mbr;
			mbr = ac;
			mem[mar] = mbr;
			break;
		}
		
	}
	if (pc > 5000)
	{
		cout << "ERROR: Too many instructions!";
	}
	else {
		outFile << hex << 28672 << "		" << pc << endl;
	}
    
	outFile.close();
    return 0;
	
}