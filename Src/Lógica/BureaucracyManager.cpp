#include "BureaucracyManager.h"
#include "Edificio.h"
#include <PARKEngine/PARKEngine.h>
#include <PARKEngine/TextBox.h>
#include "NPC.h"
#include <ctime>
#include <cmath>

BureauCrazyManager::BureauCrazyManager() : startedToCount_(false), bankruptcy_(false)
, ruptcyStartTime_(0), textDinero_(nullptr)
{

}

BureauCrazyManager::~BureauCrazyManager()
{

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
}

void BureauCrazyManager::taxCollectALL()
{
	for (TaxBill t : bills_) {
		actualMoney_ -= t.amount_;
	}
}

void BureauCrazyManager::addAmountToTax(TaxType type, float amount)
{
	bills_[type].amount_ += amount;
}

void BureauCrazyManager::changeTaxAmount(TaxType type, float amount)
{
	bills_[type].amount_ = amount;
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

	checkBankRuptcy();

	if (bankruptcy())
	{
		//send(Message ESTAS EN BANCARROTA);
		//TODO: Gestionar que se termine la partida, mensajes de bancarrota etc..
	}

	if (textDinero_ == nullptr) {
		textDinero_ = SceneManager::instance()->currentState()->getEntity("TextDinero")->getComponent<TextBox>();
		textDinero_->setColorText("FFFF0000", "FFFF0000", "FFFF0000", "FFFF0000");
		textDinero_->setBackgroundVisible("False");
		textDinero_->setText(std::to_string((int)actualMoney_) + " $");
	}
}

bool BureauCrazyManager::handleEvent(unsigned int time)
{
	//Spawnea un NPC en la entrada del parque
	if (InputManager::getSingletonPtr()->isKeyDown("NPC"))
	{
		Entity* npc = EntityFactory::Instance()->createEntityFromBlueprint("NPC");
		SceneManager::instance()->currentState()->addEntity(npc);
		npc->start();
	}
	return false;
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
	textDinero_->setText(std::to_string((int)actualMoney_) + " $");
}



