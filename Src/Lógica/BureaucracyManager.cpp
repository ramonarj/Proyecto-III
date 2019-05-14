#include "BureaucracyManager.h"
#include "Edificio.h"
#include <PARKEngine/PARKEngine.h>
#include <PARKEngine/TextBox.h>
#include <PARKEngine/FrameWindowBox.h>
#include "NPC.h"
#include <ctime>
#include <cmath>
#include <cstdio>


BureauCrazyManager::BureauCrazyManager() : startedToCount_(false), bankruptcy_(false)
, ruptcyStartTime_(0), textDinero_(nullptr), infoNPC_(nullptr), selectedNPC_(nullptr),ingTime_(0)
, infoImpuestos_(nullptr)
{

	start = std::clock();
}

BureauCrazyManager::~BureauCrazyManager()
{

}

void BureauCrazyManager::updateMoneyText()
{
	textDinero_->setText(std::to_string((int)actualMoney_) + " $");
	infoDinero_->setText("Dinero actual: " + std::to_string((int)actualMoney_) + " $");
}

void BureauCrazyManager::checkBankRuptcy()
{
	
	if (!startedToCount_ && actualMoney_ < floorRuptcyMoney_) {
		ruptcyStartTime_ = clock(); //Empieza a contar
		startedToCount_ = true;
	}
	
	if (startedToCount_ && (((clock() - ruptcyStartTime_) / CLOCKS_PER_SEC ) >= ruptcyMaxTime_)) //Ha superado el tiempo maximo que se puede estar en negativo
	{
		bankruptcy_ = true;

	}
	if (actualMoney_ > floorRuptcyMoney_) { //Si vuelvo a estar en positivo dejo de contar
		startedToCount_ = false;
	}
}

void BureauCrazyManager::taxCollect(TaxType taxType)
{
	actualMoney_ -= bills_[taxType].amount_;

	updateMoneyText();


}

void BureauCrazyManager::taxCollectALL()
{
	for (TaxBill t : bills_) {
		actualMoney_ -= t.amount_;
	}

	updateMoneyText();

}

void BureauCrazyManager::addAmountToTax(TaxType type, float amount)
{
	bills_[type].amount_ += amount;
}

void BureauCrazyManager::changeTaxAmount(TaxType type, float amount)
{
	bills_[type].amount_ = amount;
}

void BureauCrazyManager::timer()
{
	ingTime_ = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	seconds = ingTime_;
	minutes = seconds / 60;
	hours = minutes / 60;

}

void BureauCrazyManager::cobradorImpuestos()
{

	if (electricidadCobrado != minutes && minutes != 0  && minutes % 2 == 0  )
	{
		electricidadCobrado = minutes;
		taxCollect(TaxType::ELECTRIC_TAX);
		nextTax_->setText("Sig. Impuesto: " + to_string(-(int)bills_[TaxType::MAINTENANCE_TAX].amount_) + " $");
	}
	if (mantenimientoCobrado != minutes && minutes % 2 != 0) {
		mantenimientoCobrado = minutes;
		taxCollect(TaxType::MAINTENANCE_TAX);
		nextTax_->setText("Sig. Impuesto: " + to_string(- (int)bills_[TaxType::ELECTRIC_TAX].amount_) + " $");
	}

	
}



bool BureauCrazyManager::bankruptcy()
{
	return bankruptcy_;
}

void BureauCrazyManager::load(json file)
{
	for (json taxes : file["Taxes"])
	{
		TaxBill bill = { TaxType(taxes["Id"]), taxes["Amount"] };
		bills_.push_back(bill);
	}

	ruptcyMaxTime_ = file["BankRuptcy"]["ruptcyMaxTime"] ;
	floorRuptcyMoney_ = file["BankRuptcy"]["floorRuptcyMoney"];
	Time2Tax_ = file["BankRuptcy"]["InitialTime2Tax"];
	actualMoney_ = file["BankRuptcy"]["ActualMoney"];
	visitors_ = file["BankRuptcy"]["InitVisitors"];
}


void BureauCrazyManager::update(unsigned int time)
{

	timer();

	cobradorImpuestos();

	checkBankRuptcy();

	if (bankruptcy())
	{
		send(&Message(BANKRUPTCY));
		
	}

	//TODO ESTO DEBERÍA IR EN EL START/POR MENSAJES (mejor lo segundo)
	if (textDinero_ == nullptr) {
		textDinero_ = SceneManager::instance()->currentState()->getEntity("TextDinero")->getComponent<TextBox>();
		textDinero_->setText(std::to_string((int)actualMoney_) + " $");
	}
	if (infoDinero_ == nullptr) {
		infoDinero_ = SceneManager::instance()->currentState()->getEntity("InfoDinero")->getComponent<TextBox>();
		infoDinero_->setText("Dinero actual: " + std::to_string((int)actualMoney_) + " $");
	}

	if (infoNPC_ == nullptr)
	{
		infoNPC_ = SceneManager::instance()->currentState()->getEntity("NPCInfoPanel")->getComponent<FrameWindowBox>();
		infoNPC_->getWindow()->hide();
	}
	if (infoImpuestos_ == nullptr) {
		infoImpuestos_ = SceneManager::instance()->currentState()->getEntity("TextTimer")->getComponent<TextBox>();
		infoImpuestos_->setText(to_string(hours) + " : " + to_string(minutes) + " : " + to_string(seconds%60));
	}
	if(selectedNPC_ != nullptr)
		showNPCInfoBars(selectedNPC_);

	if (nextTax_ == nullptr) {
		nextTax_ = SceneManager::instance()->currentState()->getEntity("TextNextTax")->getComponent<TextBox>();
		nextTax_->setText("Sig. Impuesto: -15 $");
	}

	infoImpuestos_->setText(to_string(hours) + " : " + to_string(minutes) + " : " + to_string(seconds % 60));

}


void BureauCrazyManager::addUnlockedBuilding(const Edificio & building)
{
	unlockedBuildings_.push_back(building);
}

void BureauCrazyManager::receive(Message * msg)
{
	switch (msg->mType_)
	{
	case COLLECT_ALL_TAXES:
		taxCollectALL();
		break;
	case NEW_UNLOCKED_BUILDING:
		break;
	case IS_BUILDING_UNLOCKED:
	{
		IsBuildingUnlocked* unlMsg = static_cast<IsBuildingUnlocked*>(msg);
		if (isBuildingUnlocked(*unlMsg->edificio_))
			send(&BuildingUnlocked(BUILDING_UNLOCKED, unlMsg->edificio_));
		else 
			send(&BuildingNotUnlocked(BUILDING_NOT_UNLOCKED, unlMsg->edificio_));

		break;
	}
	case COLLEXT_ELECTRIX_TAX:
		taxCollect(ELECTRIC_TAX);
		break;
	case COLLEXT_MAINTEINANCE_TAX:
		taxCollect(MAINTENANCE_TAX);
		break;
	//Cambios de perspectiva en la cámara (esconde/muestra los paneles de gestión)
	case FIRST_PERSON_CAMERA: 
	{
		infoNPC_->getWindow()->hide();
		textDinero_->getWindow()->hide();
		SceneManager::instance()->currentState()->getEntity("ToolsPanel")->getComponent<FrameWindowBox>()->getWindow()->hide();
		SceneManager::instance()->currentState()->getEntity("ConstructButton")->getComponent<Button>()->getWindow()->hide();
		SceneManager::instance()->currentState()->getEntity("InfoButton")->getComponent<Button>()->getWindow()->hide();
		SceneManager::instance()->currentState()->getEntity("MainMenuButton")->getComponent<Button>()->getWindow()->hide();
		SceneManager::instance()->currentState()->getEntity("TextNextTax")->getComponent<TextBox>()->getWindow()->hide();
		SceneManager::instance()->currentState()->getEntity("TextTimer")->getComponent<TextBox>()->getWindow()->hide();
		//std::vector<Entity*> widgets = SceneManager::instance()->currentState()->getEntitiesWithComponent<Widget>();
		//for (Entity* e : widgets)
		//	e->getComponent<Widget>()->getWindow()->hide();
		break;
	}
	case THIRD_PERSON_CAMERA:
	{
		infoNPC_->getWindow()->show();
		textDinero_->getWindow()->show();
		SceneManager::instance()->currentState()->getEntity("ToolsPanel")->getComponent<FrameWindowBox>()->getWindow()->show();
		SceneManager::instance()->currentState()->getEntity("ConstructButton")->getComponent<Button>()->getWindow()->show();
		SceneManager::instance()->currentState()->getEntity("InfoButton")->getComponent<Button>()->getWindow()->show();
		SceneManager::instance()->currentState()->getEntity("MainMenuButton")->getComponent<Button>()->getWindow()->show();
		SceneManager::instance()->currentState()->getEntity("TextNextTax")->getComponent<TextBox>()->getWindow()->show();
		SceneManager::instance()->currentState()->getEntity("TextTimer")->getComponent<TextBox>()->getWindow()->show();
		break;
	}

	case NPC_SELECTED:
	{
		NPCSelected* npcSel = static_cast<NPCSelected*>(msg);
		setSelectedNPC(npcSel->selected_);
		break;
	}

	case NPC_IN:
		visitors_++;
		break;
	case NPC_OUT:
		visitors_--;
		break;
	default:
		break;
	}
}

bool BureauCrazyManager::isBuildingUnlocked(const Edificio & building)
{
	std::list<Edificio>::iterator findIter = std::find(unlockedBuildings_.begin(), unlockedBuildings_.end(),building);

	return findIter != unlockedBuildings_.end();
}

void BureauCrazyManager::setActualMoney(float f)
{
	actualMoney_ += f;
	
	updateMoneyText();
}

void BureauCrazyManager::showNPCInfoBars(NPC * npc)
{

	//Más comodidad
	Stat fun = npc->getFun();
	Stat hunger = npc->getHunger();
	Stat peepee = npc->getPeepee();

	infoNPC_->getWindow()->setProperty("Text", npc->getEntity()->getName());
	static_cast<CEGUI::ProgressBar*>(infoNPC_->getWindow()->getChildElement("FunBar"))->setProgress(fun.value_ / fun.MAX_VALUE);
	static_cast<CEGUI::ProgressBar*>(infoNPC_->getWindow()->getChildElement("HungerBar"))->setProgress((hunger.MAX_VALUE - hunger.value_) / hunger.MAX_VALUE);
	static_cast<CEGUI::ProgressBar*>(infoNPC_->getWindow()->getChildElement("PeePeeBar"))->setProgress((peepee.MAX_VALUE - peepee.value_) / peepee.MAX_VALUE);
}

void BureauCrazyManager::setSelectedNPC(NPC * npc)
{
	selectedNPC_ = npc;
	infoNPC_->getBrotherComponent<FrameWindowBox>()->getWindow()->show();
}



