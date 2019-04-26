#include "Widget.h"

Widget::Widget()
{
}

Widget::~Widget()
{
}

void Widget::load(json file)
{
	std::string name = getEntity()->getName();

	addParameter(type, file["type"]);

	float posX, posY, sizeX, sizeY, offsetX, offsetY;
	posX = posY = sizeX = sizeY = offsetX = offsetY = 0;

	addParameter(posX, file["posX"]);
	addParameter(posY, file["posY"]);
	addParameter(sizeX, file["sizeX"]);
	addParameter(sizeY, file["sizeY"]);
	addParameter(offsetX, file["offsetX"]);
	addParameter(offsetY, file["offsetY"]);

	window = HUDManager::instance()->createWidget(name, type, posX, posY, offsetX, offsetY, sizeX, sizeY);
}

bool Widget::handleEvent(unsigned int time)
{
	return false;
}