#include "paciente.hpp"
#include "hospitalsimple.hpp"
#include <iostream>
using namespace eosim::core;


// en el constructor se utiliza el identificador definido en paciente.hpp
// en el constructor se utiliza el identificador definido en pacientefeeder.hpp
PacienteFeeder::PacienteFeeder(Model& model): BEvent(pacienteF, model) {}

PacienteFeeder::~PacienteFeeder() {}

void PacienteFeeder::eventRoutine(Entity* who) {
	// se anuncia la llegada del paciente
	std::cout << "llego un paciente en " << who->getClock() << "\n";
	// se castea owner a un HospitalSimple
	HospitalSimple& h = dynamic_cast<HospitalSimple&>(owner);
	if (h.camas.isAvailable(1)) {
		std :: cout << "Cantidad Camas : " << h.camas.getQuantity() << std :: endl;
		h.camas.acquire(1);
        h.setAreaUtilizacionServer((h.getSimTime() - h.lastSimTime) * h.camas.getQuantity());
        h.ocupacionCamas.log(h.camas.getQuantity());
		std::cout << "un paciente fue aceptado en una cama " << h.getSimTime() << "\n";
		h.tEspera.log(h.getSimTime() - who->getClock());
		h.schedule(h.estadia.sample(), who, salidaP);
	}
	else {
        // se acumulan datos en los histogramas
        h.lCola.log(h.cola.size());
		// se pone al paciente recien llegado en la cola
		h.cola.push(who);
	}
	// Se actualiza el ultimo tiempo de simulacion con el tiempo actual
	h.lastSimTime = h.getSimTime();
    // se agenda el arribo del un nuevo paciente
	h.schedule(h.arribos.sample(), new Entity(), pacienteF);
}

// en el constructor se utiliza el identificador definido en paciente.hpp
SalidaPaciente::SalidaPaciente(Model& model): BEvent(salidaP, model) {}

SalidaPaciente::~SalidaPaciente() {}

void SalidaPaciente::eventRoutine(Entity* who) {
	// se informa la salida de un paciente
	std::cout << "un paciente se retira en " << who->getClock() << "\n";
	// se castea owner a un HospitalSimple
	HospitalSimple& h = dynamic_cast<HospitalSimple&>(owner);
	// se retorna la cama que el paciente ocupaba
	h.camas.returnBin(1);
    // Se actualiza area de utlizacion de las camas
    h.setAreaUtilizacionServer((h.getSimTime() - h.lastSimTime) * h.camas.getQuantity());
    h.ocupacionCamas.log(h.camas.getQuantity());
	if (!h.cola.empty()) {
		h.camas.acquire(1);
        h.ocupacionCamas.log(h.camas.getQuantity());
        h.setAreaUtilizacionServer((h.getSimTime() - h.lastSimTime) * h.camas.getQuantity());
		std::cout << "un paciente fue aceptado en una cama " << h.getSimTime() << "\n";
        h.lCola.log(h.cola.size());
		Entity* ent = h.cola.pop();
		h.tEspera.log(h.getSimTime() - ent->getClock());
		h.schedule(h.estadia.sample(), ent, salidaP);

	}
	// Se actualiza el ultimo tiempo de simulacion con el tiempo actual
	h.lastSimTime = h.getSimTime();
	// se elimina  al paciente del sistema
	delete who;
}
