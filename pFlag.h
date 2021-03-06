#pragma once
#include<random>
struct fCommand {
	char color;//赤か白か
	bool up;//trueで上げて falseで下げて
	bool tf;//否定文か否か
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
