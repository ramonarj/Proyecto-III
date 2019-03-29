#pragma once
#include <memory>
#include <Arquitectura/ResourceManager.h>
#include <ctime>

class BureauCrazyManager
{
	//Tipos de impuestos
	enum TaxType
	{
		ELECTRIC_TAX,MAINTENANCE_TAX,
	};

	struct TaxBill	//Recibos de los impuestos ( Cantidad + tipo )
	{
		TaxType taxType_;
		//Cantidad de dinero que resta este impuesto
		float amount_;
	};

public:
	~BureauCrazyManager();

	//Comprueba si esta en bancarrota
	bool bankruptcy(); 

	static BureauCrazyManager* instance(std::string jsonInit);

private:
	static std::unique_ptr<BureauCrazyManager> instance_;

	BureauCrazyManager(std::string jsonInit);

	//A partir de un valor definido de dinero actual comienza a tener en cuenta el proceso de bancarrota
	void checkBankRuptcy(); 

	//Resta la cantidad que haya definida actualmente de un impuesto
	void taxCollect(TaxType taxType);

	////Resta las cantidades definidas de todos los impuestos declarados
	void taxCollectALL();

	void addAmountToTax(TaxType type, float amount);
	void changeTaxAmount(TaxType type, float amount);

	float actualMoney_;
	int visitors_;

	std::vector<TaxBill> bills_;

	//Tiempo maximo que puede estar un jugador en negativo antes que se declare la bancarrota
	float ruptcyMaxTime_;

	//Tiempo en el que se empieza a contar para la bancarrota
	float ruptcyStartTime_;

	//Dinero a partir del cual se empieza a cronometrar la bancarrota del jugador
	float floorRuptcyMoney_;

	//Tiempo restante para cobrar los siguientes impuestos
	float Time2Tax_;

	//Informa si se ha empezado o no a contar para la bancarrota
	bool startedToCount_;

	bool bankruptcy_;

	//TODO: lista de atracciones desbloqueadas

};


