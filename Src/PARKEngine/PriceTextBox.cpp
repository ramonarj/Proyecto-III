#include "PriceTextBox.h"
#include "SceneManager.h"
#include <L�gica/DatosEdificio.h>

PriceTextBox::PriceTextBox()
{
}

PriceTextBox::~PriceTextBox()
{
}

void PriceTextBox::load(json file)
{
	TextBox::load(file);

	addParameter(buildName_, file["bName"]);
}

void PriceTextBox::update(unsigned int time)
{
	if (datosEdificio_ == nullptr) {
		datosEdificio_ = SceneManager::instance()->currentState()->getEntity("DatosEdificios")->getComponent<DatosEdificio>();
		datos_ = SceneManager::instance()->currentState()->getEntity("DatosEdificios")->getComponent<DatosEdificio>()->findData(buildName_);
	}

	if (bureauCrazyManager_ == nullptr)
		bureauCrazyManager_ = SceneManager::instance()->currentState()->getEntity("BureauCrazyManager")->getComponent<BureauCrazyManager>();
	else{
		changeTextPrice();
		if (bureauCrazyManager_->getActualMoney() < datosEdificio_->getPrice(buildName_))
			setColorText("FFFF0000", "FFFF0000", "FFFF0000", "FFFF0000");
	}
}

void PriceTextBox::changeTextPrice()
{
	if (datos_->Locked_) {
		window->setText(to_string(datos_->LockedPrice_) + " $");
		setColorText("FF00C5FF", "FF00C5FF", "FF00C5FF", "FF00C5FF");
	}
	else {
		window->setText(to_string(datos_->price_) + " $");
		setColorText("FF00FF00", "FF00FF00", "FF00FF00", "FF00FF00");
	}
}
