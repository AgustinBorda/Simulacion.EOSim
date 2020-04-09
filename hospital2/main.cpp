#include <eosim/dist/mt19937.hpp>
#include <eosim/core/experiment.hpp>
#include "hospitalsimple.hpp"
#include "constantes.hpp"

#include <iostream>
#include <fstream>

const unsigned int repeticiones = 4;

int main () {
	std::string s;
    using namespace eosim::core;
    unsigned int cantCamas;
    int nuevoEvento;
    //repito el experimento una cierta cantidad de veces
    for (int i = 0; i < repeticiones; i++) {
        std::cout << "Ingrese el numero de camas \n";
        std::cin >> cantCamas;
        std::cout << "Desea cargar el evento extra?(0 o 1)\n";
        std::cin >> nuevoEvento;
        HospitalSimple m(cantCamas, tasaArribos, tiempoEstadia, mediaDistNormal, varianzaDistNormal, nuevoEvento);
        Experiment e;
        std::cout << "Arranco ...\n";
        m.connectToExp(&e);
        e.setSeed((unsigned long) i + 129);
        e.run(1200.0);
        std::cout << "Termine ...\n\n\n";
		m.lCola.print(0);
		std::cout << '\n';
		m.tEspera.print(0);
		std::cout << '\n';
		m.ocupacionCamas.print(0);
		std :: cout << "Factor de utilizacion de camas: " << m.ocupacionCamas.getMean() / m.camas.getMax() << std :: endl;
		std::cin >> s;
    }
}

