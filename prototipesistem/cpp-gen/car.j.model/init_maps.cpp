#include "init_maps.hpp"
#include "Backwards_subSM.hpp"
#include "Lamp.hpp"
#include "Gearbox.hpp"
#include "Engine.hpp"
#include "Forwards_subSM.hpp"
namespace Model {
void initTransitionTables() {
	Backwards_subSM::initTransitionTable();
	Lamp::initTransitionTable();
	Gearbox::initTransitionTable();
	Engine::initTransitionTable();
	Forwards_subSM::initTransitionTable();

	return;
}
}

