#include "hospitalsimple.hpp"
#include <eosim/core/entity.hpp>
#include <eosim/dist/numbergenerator.hpp>
#include <iostream>

using namespace eosim::core;
using namespace eosim::dist;

using namespace std;

HospitalSimple::HospitalSimple(unsigned int cantCamas, double tasaArribos, double tiempoEstadia, double mediaDistNormal, double varianzaDistNormal):
// se contruyen los eventos B, los eventos C, las distribuciones, los recursos y los histogramas
								tasaArribos(tasaArribos),
								tiempoEstadia(tiempoEstadia),
								mediaDistNormal(mediaDistNormal),
								varianzaDistNormal(varianzaDistNormal),
								pF(*this),
								sP(*this),
								eA(*this),
								arribos(MT19937, tasaArribos),
								estadia(MT19937, tiempoEstadia),
								distribution(MT19937,mediaDistNormal,varianzaDistNormal),
								camas(cantCamas, cantCamas),
								tEspera("Tiempos de Espera"),
								lCola("Largos Medios de Colas", *this),
								ocupacionCamas("Ocupacion camas", *this) {}

HospitalSimple::~HospitalSimple() {}

void HospitalSimple::init() {
	// registro los eventos B
	registerBEvent(&pF);
	registerBEvent(&sP);
	registerBEvent(&eA);

	// registro las distribuciones
	registerDist(&arribos);
	registerDist(&estadia);
	registerDist(&distribution);
}

void HospitalSimple::doInitialSchedules() {
	// agendo el primer paciente
	std::cout <<camas.getQuantity()<< std::endl;
	schedule(0.0, new Entity(), pacienteF);
	schedule(distribution.sample(), new Entity(), evento);
}
