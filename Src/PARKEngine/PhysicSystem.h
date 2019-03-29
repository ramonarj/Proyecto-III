#pragma once
#include "Utils.h"

//Tipo enumerado para los tipos de formas de los RigidBody
enum Shape{ EmptyShape, BoxShape, SphereShape, CapsuleShape, PlaneShape, CylinderShape, ConeShape};
const Vector3 DEFAULT_GRAVITY = { 0, -10, 0 };

//Forward-declarations
class btRigidBody;
class btCollisionShape;

class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

//Clase physXSytem: Singleton para gestionar el sistema de f�sicas
class PhysicSystem
{
public:

	//Devuelve la instancia
	static PhysicSystem* instance();

	//Inicializa el sistema de f�sicas
	void initPhysics();

	//Actualiza el sistema
	void stepSimulation(unsigned int time);

	//Crea un rigidbody con una forma, posici�n, masa y dimensiones dadas
	static btRigidBody* createRigidBody(Shape forma, Vector3 dimensions, float mass);

	//A�de una forma al vector 
	void addShape(btCollisionShape* shape);

	//A�ade un rigidbody al mundo f�sico
	void addRigidBody(btRigidBody* rigid);



	//Destructora
	~PhysicSystem();
private:
	//Constructora privada
	PhysicSystem();
	//Limpia la basura
	void cleanupPhysics();
	//Instancia
	static std::unique_ptr<PhysicSystem> instance_;

	//Atributos
	//Config. de colisiones
	btDefaultCollisionConfiguration * collisionConfiguration;
	//Dispatcher 
	btCollisionDispatcher * dispatcher;
	//OverlappingPairCache
	btBroadphaseInterface * overlappingPairCache;
	//Solver
	btSequentialImpulseConstraintSolver * solver;
	//Mundo f�sico
	static btDiscreteDynamicsWorld * dynamicsWorld;

	//Formas
	static std::vector<btCollisionShape*> shapes;
};