#include "Matrix.h"

#include "Node.h"
#include "PARKEngine/PARKEngine.h"

Matrix::Matrix()
	: mSize_({ 0 ,0 }), nSize_({0, 0, 0})
{
}

Matrix::~Matrix()
{
}


void Matrix::load(json file)
{
	json nodeSize = file["nodeSize"];
	nSize_.x = nodeSize["x"];
	nSize_.y = nodeSize["y"];
	nSize_.z = nodeSize["z"];

	//Archivo que contiene la informaci�n de la matriz
	json matrixFile = ResourceManager::instance()->getJsonByKey(file["file"]);
	mSize_.x = matrixFile["rows"];
	mSize_.y = matrixFile["cols"];

	json data = matrixFile["data"];
	/*for (int i = 0; i < mSize_.x; i++)
	{
		for (int j = 0; j < mSize_.y; j++)
			std::cout << data[mSize_.y * i + j];
		std::cout << std::endl;
	}*/
	//Crea la matriz
	createMatrix();
}

void Matrix::start()
{
	for (int i = 0; i < matrix_.size(); i++) {
		for (int j = 0; j < matrix_[0].size(); j++) {
			SceneManager::instance()->currentState()->addEntity(matrix_[i][j]);
			for (Component* c : matrix_[i][j]->getComponents()) {
				if (c->isActive())
					c->start();
			}
		}
	}
}

void Matrix::createMatrix()// (json matrixInfo)
{
	Vector3 posIni = getPosIni();
	for (int i = 0; i < mSize_.x; i++) {
		matrix_.push_back(vector<Entity*>());
		for (int j = 0; j < mSize_.y; j++) {
			Entity* e = EntityFactory::Instance()->createEntityFromBlueprint("Node");
			e->getComponent<Transform>()->setPosition({ (Ogre::Real)(posIni.x + (j * nSize_.x)), (Ogre::Real)posIni.y, (Ogre::Real)(posIni.z + (i * nSize_.z)) });
			e->getComponent<Node>()->setMatrixPos(i, j);
			//SET NODE TYPE HERE READING FROM JSON
			matrix_[i].push_back(e);
		}
	}
}

Vector3 Matrix::getPosIni()
{
	Vector3 v;
	float midX = mSize_.x / 2;
	float midY = mSize_.y / 2;

	v = Vector3(-midX * nSize_.x, 0.0f, -midY * nSize_.z);
	return v;
}

vector<vector<Entity*>> Matrix::getMatrix()
{
	return matrix_;
}

Entity * Matrix::getEntityNode(int i, int j)
{
	return matrix_[i][j];
}

list<Entity*> Matrix::getAdj(Entity* e, int x, int y)
{
	list<Entity*> list;
	Vector2 nPos = e->getComponent<Node>()->getMatrixPos();
	for (int i = -x; i <= x; i++) {
		for (int j = -y; j <= y; j++) {
			if (limits(nPos.x + i, nPos.y + j)) {
				list.push_back(getEntityNode(nPos.x + i, nPos.y + j));
			}
		}
	}
	return list;
}

Entity * Matrix::getEntityNode(int index)
{
	int row = index / getSize(1);
	int col = index % getSize(1);
	return getEntityNode(row, col);
}

Ogre::Vector3 Matrix::getNodeSize()
{
	return nSize_;
}

bool Matrix::limits(int i, int j)
{
	return i >= 0 && j >= 0 && i < mSize_.x && j < mSize_.y;
}
