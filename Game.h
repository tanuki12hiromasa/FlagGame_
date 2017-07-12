#pragma once
#include"Tempo.h"
#include"pFlag.h"
class Game
{
public:
    Game();
    ~Game();
    void run(char _mode);
	double getscore(char count_or_total);
private:
    void init();
    bool update(pFlag *_player);//•Ô‚è’l‚Íƒ{ƒ^ƒ“‚ð‰Ÿ‚µ‚Ä‚¢‚½‚©‚Ç‚¤‚©
	void draw(const pFlag *_player,const pFlag *_answer);

    char mode;
	bool game_continue;
	fCommand command;
	Tempo metronome;
	int bpm;
	double current;
	double score_total;
	int score_n,quiz_count;

    const int tempo_easy = 90;
    const int tempo_normal = 120;
    const int tempo_difficult = 150;
	const int del_tempo_endless = 2;
};

