#pragma once
#include<random>
struct fCommand {
	char color;//Ô‚©”’‚©
	bool up;//true‚Åã‚°‚Ä false‚Å‰º‚°‚Ä
	bool tf;//”Û’è•¶‚©”Û‚©
};
class pFlag
{
public:
	bool white,red;

	pFlag();
	~pFlag();
	void quiz(fCommand *_command);

	pFlag &operator=(const pFlag a) {
		white=a.white;red=a.red;
		return (*this);
	}
	bool operator==(const pFlag a) const {
		return (white==a.white)&&(red==a.red);
	}
private:
	std::uniform_int_distribution<> *rand4;
	std::mt19937 *mt;
};
