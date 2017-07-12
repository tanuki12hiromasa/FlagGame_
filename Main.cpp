# include <Siv3D.hpp>
#include "Game.h"

void Main()
{
	const Font font(30);
	Game game;char mode='m';
	while (System::Update())
	{
		switch(mode){
		case 'm':
			font(L"<操作方法>\n白旗:A&Z\n赤旗:K&M\n\nPress Key'K' to Start").drawCenter(100);
			if(Input::KeyK.clicked)mode='g';
			break;
		case 'g':
			game.run('l');mode='e';break;
		case 'e':
			font(L"Game Over!!\nYour score:",(int)game.getscore('c'),L"\n\nもう一度:K  やめる:A").drawCenter(100);
			if(Input::KeyA.clicked)	System::Exit();
			if(Input::KeyK.clicked) mode='g';
			break;
		}
	}
}
