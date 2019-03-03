#pragma once

//Clase physXSytem: Singleton para gestionar el sistema de f�sicas
class physicSystem
{
public:
	//Devuelve la instancia
	static physicSystem* instance();

	//Destructora
	~physicSystem();
private:
	//Constructora privada
	physicSystem();
	//Instancia
	static physicSystem* instance_;

};