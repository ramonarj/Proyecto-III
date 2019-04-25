#pragma once
#include "Widget.h"

class Button : public Widget
{
private:
	std::string callback;
	std::string callbackParam;

public:
	Button();
	~Button();

	void load(json file);

	//M�todos principales
	virtual void render(unsigned int time) {}
	virtual void update(unsigned int time) {}
	virtual bool handleEvent(unsigned int time);

	virtual bool onClick(const CEGUI::EventArgs& e);

	virtual void receive(Message* msg) {};
};

REGISTER_TYPE(Button)