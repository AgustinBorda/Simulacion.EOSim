#ifndef RANDOMEVENT_HPP
#define RANDOMEVENT_HPP

#include <eosim/core/bevent.hpp>
#include <eosim/core/entity.hpp>
#include <string>

// identificador del evento fijo RandomEvent
const std::string evento = "EventoAleatorio";

class RandomEvent: public eosim::core::BEvent {

protected:
    int flag = 0;

public:
	// constructor
	RandomEvent(eosim::core::Model& model);
	// destructor
	~RandomEvent();
	// rutina del evento fijo
	void eventRoutine(eosim::core::Entity* who);
};

#endif
