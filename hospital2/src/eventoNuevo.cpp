#include "eventoNuevo.hpp"
#include "hospitalsimple.hpp"
#include <iostream>
using namespace eosim::core;

eventoNuevo::eventoNuevo(Model& model){}

eventoNuevo::~eventoNuevo(){}

void eventoNuevo :: eventRoutine(eosim::core::Entity* who) {
    std :: cout << "Soy un evento nuevo" << std :: endl;
}
