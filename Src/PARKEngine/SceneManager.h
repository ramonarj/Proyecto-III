#pragma once
#include <map>
#include <memory>
#include "GameState.h"

class SceneManager
{
public:
	SceneManager(bool* ex);
	virtual ~SceneManager();

	static void initInstance(bool* ex);
	static SceneManager* instance();

	void exitGame() {
		*exit = true;
	}

	// �> Devuelve el estado activo actualmente
	GameState* currentState();

	// �> Crea y a�ade un nuevo estado al SceneManager
	GameState* addState(std::string stateID);

	// �> Cambia de estado por el indicado por par�metro. En caso de no existir, lo crea
	void changeState(std::string stateID);

	// -> Remove state
	bool removeState(std::string stateID);

private:
	static std::unique_ptr<SceneManager> instance_; // Singleton

	std::map <std::string, GameState*> states; // Estados del juego

	GameState* currentState_; // Estado activo

	bool* exit;

	void disableOtherStatesNodes();
};