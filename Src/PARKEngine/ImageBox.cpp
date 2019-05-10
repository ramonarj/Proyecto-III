#include "ImageBox.h"

ImageBox::ImageBox()
{
	type = "TaharezLook/StaticImage";
}

ImageBox::~ImageBox()
{
}

void ImageBox::load(json file)
{
	Widget::load(file);
	staticImage_ = static_cast<CEGUI::Window*>(window);

	std::string nombre;
	nombre = file["imageName"].get<std::string>();

	if (!CEGUI::ImageManager::getSingleton().isDefined(nombre)){
		CEGUI::ImageManager::getSingleton().addFromImageFile(nombre, nombre);
	}
		
	staticImage_->setProperty("Image", nombre);
	setBackgroundVisible("False");
}

void ImageBox::setBackgroundVisible(string boolean)
{
	window->setProperty("BackgroundEnabled", boolean);
	window->setProperty("FrameEnabled", boolean);
}
