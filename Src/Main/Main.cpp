#include "Game.h"

int main(int argc, char* argv[])
{
	Game* Juego = new Game("InitAplication.json");
	Juego->start();
	Juego->run();
	delete Juego;
	return 0;
}

