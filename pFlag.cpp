#include "pFlag.h"
#include <random>
#include <stdlib.h>
void pFlag::quiz(fCommand *_command) {
	bool ud;
	if((*rand4)(*mt)<2){_command->color='r';ud=red;}
	else{ _command->color='w';ud=white;}
	if((*rand4)(*mt) <3 && ud==false) _command->up=true;
	else _command->up=false;
	if((*rand4)(*mt)<3) _command->tf=true;
	else _command->tf=false;
	if(_command->color=='r'){
		if(_command->up==_command->tf)
			red=true;
		else red=false;
	}
	else {
		if(_command->up == _command->tf)
			white=true;
		else white=false;
	}
}

pFlag::pFlag()
{
	std::random_device rd;
	static std::uniform_int_distribution<> _rand4(0, 3);
	static std::mt19937 _mt(rd());
	rand4 = &_rand4;mt = &_mt;
	red=false;white=false;
}

pFlag::~pFlag()
{
}
