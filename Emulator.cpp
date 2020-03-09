#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
/*
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
				in = argv[i];
				i++;
			}
			else {
				cerr<< "Error: --in missing file name\n";
				exit(1);
			}
		}
		else if (strcmp(argv[i], "--out") == 0)
		{
			if ((i + 1) < argc)
			{
				out = argv[i];
				i++;
			}
			else {
				cerr<< "Error: --out missing file name\n";
				exit(1);
			}
		}
		else {
			cerr<< "Error: invalid paramter >%s<\n", argv[i];
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
		cerr<< "Error: missing --out <fn> parameter\n";
		exit(1);
	}
	*/
int main()
{
	string inFile;
	int numFile;
	int num;
	ifstream file;
	file.open("test.txt");
	vector<int> mem;
	while (!file.eof())
	{
		file >> inFile;
		numFile = stoi(inFile, nullptr, 16);
		//cout<< hex << numFile<<endl;
		mem.push_back(numFile);
	}
	
	int mbr = 0;
	int ac = 0;
	int mar = 0;
	int pc = 0;
	int input = 0;
	int output = 0;
	while ((mem[pc] & 0xF000) != 0x7000)
	{
		int instr=(mem[pc] & 0xF000);
		int hand = (mem[pc] & 0x0FFF);
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
			cin >> input;
			ac = input;
			break;
		case 0x6000://Output
			output = ac;
			cout<< output;
			break;
		case 0x8000://skipcond
			if ((hand & 0xF00) == 0)//or is it mem[pc] & 0x0F00
			{
				if (ac < 0)
				{
					pc = pc + 1;
				}
			}
			else if ((hand & 0xF00) == 0x400)
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
			break;
		case 0x9000://Jump
			pc = hand;
			break;
		case 0x0000://JnS
			mbr = pc;
			cout << "mbr/pc "<<mbr << endl;
			mar = hand;
			cout << "mar " << mar << endl;
			mem[mar] = mbr;
			cout << "mem[mar] " << mem[mar] << endl;
			mbr = hand;
			cout << "mbr " << mbr << endl;
			ac = 1;
			cout << "ac initial " << ac << endl;
			ac = ac + mbr;
			cout << "ac " << ac << endl;
			pc = ac;
			cout << "pc final " << pc << endl;
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
	
}