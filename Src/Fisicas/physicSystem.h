#pragma once
#include "btBulletDynamicsCommon.h"
#include <vector>

//Clase physXSytem: Singleton para gestionar el sistema de f�sicas
class physicSystem
{
public:
	//Devuelve la instancia
	static physicSystem* instance();

	//Inicializa el sistema de f�sicas
	void initPhysics();

	//Actualiza el sistema
	void stepSimulation();

	//Limpia la basura
	void clenaupPhysics();



	//Destructora
	~physicSystem();
private:
	//Constructora privada
	physicSystem();
	//Instancia
	static physicSystem* instance_;


	//Atributos
	//Config. de colisiones
	btDefaultCollisionConfiguration * collisionConfiguration;
	//Dispatcher ??
	btCollisionDispatcher * dispatcher;
	//
	btBroadphaseInterface * overlappingPairCache;
	//Solver
	btSequentialImpulseConstraintSolver * solver;
	//Mundo f�sico
	btDiscreteDynamicsWorld * dynamicsWorld;

	//RigidBodys
	std::vector<btCollisionShape*> shapes;
};