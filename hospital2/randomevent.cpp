#include "randomevent.hpp"
#include "hospitalsimple.hpp"
#include <iostream>
using namespace eosim::core;

// en el constructor se utiliza el identificador definido en randomevent.hpp
RandomEvent::RandomEvent(Model& model): BEvent(evento, model) {}

RandomEvent::~RandomEvent() {}

void RandomEvent::eventRoutine(Entity* who){
    std::cout << "Evento nuevo en " << who->getClock() << ", flag: " << flag << '\n';
    // se castea owner a un HospitalSimple
	HospitalSimple& h = dynamic_cast<HospitalSimple&>(owner);
    if (flag % 2 == 0 && h.camas.isAvailable(1)){
        std::cout << "Por adquirir una cama, cantidad de camas libres " << h.camas.getQuantity() << '\n';
        h.camas.acquire(1);
    std::cout << "cama adquirida, cantidad de camas libres " << h.camas.getQuantity() << '\n';
    }
	else if (h.camas.getMax() - h.camas.getQuantity() > 0){
	    std::cout << "Por devolver una cama, cantidad de camas libres " << h.camas.getQuantity() << '\n';
		h.camas.returnBin(1);
		std::cout << "cama devuelta, cantidad de camas libres " << h.camas.getQuantity() << '\n';
	}
    h.schedule(20.0, new Entity(), evento);
    flag++;
    delete who;
}
