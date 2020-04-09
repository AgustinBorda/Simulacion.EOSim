#ifndef EVENTONUEVO_H
#define EVENTONUEVO_H
#include <eosim/core/bevent.hpp>
#include <eosim/core/entity.hpp>
#include <string>

class eventoNuevo : public eosim::core::BEvent
{
    public:
        eventoNuevo(eosim::core::Model& model);
        virtual ~eventoNuevo();
	void eventRoutine(eosim::core::Entity* who);
};

#endif // EVENTONUEVO_H
