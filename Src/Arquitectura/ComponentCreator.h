#pragma once
#include "EntityFactory.h"

// �> Macro para el registro de factor�as de componentes
/*
- #: Convierte el nombre del par�metro en un <String> -> Si Comp = Transform, entonces registerType("Transform", this)
- ##: Sirve para concatenar el nombre ->  Si Comp = Transform, entonces class TransformCreator, etc.

Usamos una variable 'static' porque la constructora de los objetos 'static' se llama antes de la llamada la main().
De esta manera, todas las factor�as de componentes quedan registradas autom�ticamente antes de la ejecuci�n del programa en s�.
*/
#define REGISTER_TYPE(Comp) \
    class Comp##Creator : public BaseCreator { \
    public: \
        Comp##Creator() \
        { \
            EntityFactory::registerType(#Comp, this); \
        } \
       virtual Component* createComponent() const { \
            return new Comp(); \
        } \
    }; \
    static Comp##Creator global_##Comp##Creator;