#include "Game.h"

int main(int argc, char* argv[])
{
	/*if (!IsDebuggerPresent())
	{
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
		_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	}*/

	Game* Juego = new Game("InitAplication.json");
	Juego->start();

	//delete Juego;
	system("pause");


	return 0;
}

