#include "randomevent.hpp"
#include "hospitalsimple.hpp"
#include <iostream>
using namespace eosim::core;

// en el constructor se utiliza el identificador definido en randomevent.hpp
RandomEvent::RandomEvent(Model& model): BEvent(evento, model) {}

RandomEvent::~RandomEvent() {}

void RandomEvent::eventRoutine(Entity* who, int flag){
    std::cout << "Evento nuevo en " << who->getClock() << "flag: " << flag << '\n';
    if (flag % 2 == 0 && h.camas.isAvailable(1))
		h.camas.acquire(1);
	else if (h.camas.getMax() - h.camas.getQuantity() > 0)
		h.camas.returnBin(1);
    h.schedule(20.0, new Entity(), evento);
    delete who;

}
