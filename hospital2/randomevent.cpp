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
    if (flag % 2 == 0 && h.camas.isAvailable(1)) {
        h.ocupacionCamas.log(h.camas.getMax()-h.camas.getQuantity());
        h.camas.acquire(1);
        flag++;
    }
	else if (flag % 2 != 0 && h.camas.getQuantity() < h.camas.getMax()){
        h.ocupacionCamas.log(h.camas.getMax()-h.camas.getQuantity());
		h.camas.returnBin(1);
		if (!h.cola.empty()) {
            h.ocupacionCamas.log(h.camas.getMax()-h.camas.getQuantity());
            h.camas.acquire(1);
            std::cout << "un paciente fue aceptado en una cama " << h.getSimTime() << "\n";
            h.lCola.log(h.cola.size());
            Entity* ent = h.cola.pop();
            h.tEspera.log(h.getSimTime() - ent->getClock());
            h.schedule(h.estadia.sample(), ent, salidaP);
        }
		flag++;
	}
    h.schedule(20.0, new Entity(), evento);
    delete who;
}
