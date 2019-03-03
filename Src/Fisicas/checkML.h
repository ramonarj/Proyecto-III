/*	
	M�dulo para encontrar basura
		-> Solo funciona en modo Debug, y debe incluirse en todos los m�dulos en los que 
		se desee encontrar basura sin eliminar.
		-> Para activarlo, escribir la siguente l�nea al inicio de la funci�n main: 
		_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
*/
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif
