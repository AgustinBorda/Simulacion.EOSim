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
    //repito el experimento una cierta cantidad de veces
    for (int i = 0; i < repeticiones; i++) {
        HospitalSimple m(cantCamas, tasaArribos, tiempoEstadia);
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
        std :: cout << "Utilizacion camas: " << m.ocupacionCamas.getMean()/ cantCamas << std :: endl;
		std::cout << "Area de utilizacion de las camas: " << m.getAreaUtilizacionServer() << '\n';
		std::cout << "Factor de utilizacion de las camas: " << m.getAreaUtilizacionServer() / (m.getSimTime() * cantCamas);
		std::cin >> s;
    }
}

