#include "Game.h"
#include "Tempo.h"
#include "pFlag.h"
#include <random>
#include <Siv3D.hpp>
#define BEAT 4

Game::Game()
{
}


Game::~Game()
{
}

void Game::run(char _mode) {
	mode=_mode;
	init();
	const Font font(40);
	int prev=-1;double score=0;
	pFlag player,answer;
	switch(mode){
	case 'e':
		bpm=tempo_easy;break;
	case 'n':
		bpm=tempo_normal;break;
	case 'd':
		bpm=tempo_difficult;break;
	case 'l':
		bpm=120;break;
	default:
		bpm=120;
		break;
	}
	metronome.set_tempo(bpm,BEAT);
	const Sound sound_intro(L"intro.mp3");
	const Sound sound_loop(L"loop.mp3");
	const Sound sound_correct(L"correct.mp3");
	const Sound sound_wrong(L"wrong.mp3");
	sound_intro.setSpeed((double)bpm/120);
	metronome.start();
	sound_intro.play();
	while(System::Update()) {
		current=metronome.get_current();
		int ber_current = metronome.get_ber_current();
		if(ber_current==2)break;
		else if(current<3 || ber_current==0){
			int x=3 - ((int)current/2 + ber_current*2);
			font(x).drawCenter(320,240);
		}
		else {
			command.color='s';
			draw(&player,&answer);
		}
	}
	answer.quiz(&command);quiz_count=1;prev=0;
	sound_loop.setSpeed((double)bpm/120);
	sound_loop.setLoop(true);
	sound_loop.play();
	while(System::Update() && game_continue) {						//ループ開始点
		current=metronome.get_current();
		switch((int)current) {
		case 0:
			if(quiz_count > score_n + 3) {
				game_continue=false;
				sound_loop.stop();
				continue;
			}
			if(prev == 3) {
				if(player == answer) {
					bpm += del_tempo_endless;
					if(mode=='l') metronome.set_tempo(bpm,BEAT);
					sound_loop.setSpeed((double)bpm / 120);
				}
				else player=answer;
				answer.quiz(&command);quiz_count++;
				sound_loop.setPosSec(0.0);
			}
		default:
			if(update(&player))
				score=(double)BEAT-current;
			break;
		case 3:
			if(prev != (int)current) {
				if(answer == player) {
					score_total+=score;
					score_n++;
					command.color='c';
					sound_correct.setSpeed((double)bpm / 120);
					sound_correct.play();
				}
				else{
					command.color='n';
					sound_wrong.setSpeed((double)bpm / 120);
					sound_wrong.play();
				}
			}
			break;
		}
		draw(&player,&answer);
		prev=(int)current;
	}												//ループ終了点
}

bool Game::update(pFlag *_player) {
	bool flg_change=false;
	if(Input::KeyA.clicked && _player->white==false) {
		_player->white=true;
		flg_change=true;
	}
	else if(Input::KeyZ.clicked && _player->white==true) {
		_player->white=false;
		flg_change = true;
	}
	if(Input::KeyK.clicked && _player->red==false) {
		_player->red=true;
		flg_change = true;
	}
	else if(Input::KeyM.clicked && _player->red==true) {
		_player->red=false;
		flg_change = true;
	}
	return flg_change;
}

void Game::init() {
	score_total=0;
	score_n=0;quiz_count=-1;
	current=0;
	game_continue=true;
}

void Game::draw(const pFlag *_player,const pFlag *_answer) {
	static const Font font(30);
	String str;
	str.clear();
	switch(command.color) {
	case 'c':
		str=L"正解";break; 
	case 'n':
		str=L"不正解";break;
	case 'r':
	case 'w':
		if(command.color=='r')
			str=L"赤";
		else if(command.color=='w')
			str=L"白";
		if(command.up == true)
			str+=L"上げ";
		else
			str+=L"下げ";
		if(command.tf==true)
			str+=L"て";
		else
			str+=L"ないで";
		break;
	case 's':
		str=L"Start!";break;
	}
	font(str).drawCenter(200);
	if(_player->red)
		font(L"赤").drawCenter(440,400,Palette::Red);
	else font(L"赤").drawCenter(430, 440, Palette::Red);
	if(_player->white)
		font(L"白").drawCenter(200, 400, Palette::White);
	else font(L"白").drawCenter(210, 440, Palette::White);
	font(L"score: ",Pad(score_n,{3,L'0'})).draw(400,20);
	font(Pad(quiz_count,{3,L' '}),L"問目").draw(400,60);
	if(current-(int)current<=0.3)
		if((int)current==0)Circle(40, 40, 30).draw(Palette::Orangered);
		else Circle(40,40,18).draw(Palette::Lightyellow);
}

double Game::getscore(char count_or_total) {
	switch(count_or_total) {
	case 'c':return score_n;
	case 't':return score_total;
	case 'q':return quiz_count;
	default:return score_n;
	}
}