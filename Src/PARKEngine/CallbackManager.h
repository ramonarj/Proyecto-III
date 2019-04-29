#pragma once
#include <memory>
#include <map>
#include <functional>

class CallbackManager
{
private:
	static std::unique_ptr<CallbackManager> instance_;

	std::map <std::string, std::function<bool(std::string)>> callbacks;

	void initCallbacks();

	CallbackManager();

	bool onExit(std::string null);
	bool onChangeState(std::string state);
	bool EffectVolumeChange(std::string vol);
	bool MusicVolumeChange(std::string vol);

	//Callbacks para la construccion
	bool setConstructModeActive(std::string s);
	bool construct(std::string buildName);
public:
	static CallbackManager* instance();
	
	template<typename T>
	void addCallback(std::string keyName, bool(T::* cb)(std::string), T * obj);

	std::function<void(std::string)> getCallback(std::string name);

	~CallbackManager();
};
