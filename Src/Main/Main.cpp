#include "Game.h"
#include <Windows.h>

int main(int argc, char* argv[])
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	Game* Juego = new Game("InitAplication.json");
	Juego->start();
	Juego->run();
	delete Juego;
	return 0;
}