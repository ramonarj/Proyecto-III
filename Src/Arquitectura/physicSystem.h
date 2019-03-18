#pragma once
#include "btBulletDynamicsCommon.h"
#include <OgreRoot.h>
#include <memory>
#include <vector>

//Tipo enumerado para los tipos de formas de los RigidBody
enum Shape{ EmptyShape, BoxShape, SphereShape, CapsuleShape, PlaneShape, CylinderShape, ConeShape};
const btVector3 DEFAULT_GRAVITY = { 0, -10, 0 };
using Vector3 = Ogre::Vector3;
using Quaternion = Ogre::Quaternion;

//Clase physXSytem: Singleton para gestionar el sistema de f�sicas
class physicSystem
{
public:

	//Devuelve la instancia
	static physicSystem* instance();

	//Inicializa el sistema de f�sicas
	void initPhysics();

	//Actualiza el sistema
	void stepSimulation(unsigned int time);

	//Limpia la basura
	void clenanupPhysics();

	//Crea un rigidbody con una forma, posici�n, masa y dimensiones dadas
	static btRigidBody* createRigidBody(Shape forma, Vector3 dimensions, btScalar mass);

	//A�de una forma al vector 
	void addShape(btCollisionShape* shape) { shapes.push_back(shape); };

	//A�ade un rigidbody al mundo f�sico
	void addRigidBody(btRigidBody* rigid){ dynamicsWorld->addRigidBody(rigid); }



	//Destructora
	~physicSystem();
private:
	//Constructora privada
	physicSystem();
	//Instancia
	static std::unique_ptr<physicSystem> instance_;

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