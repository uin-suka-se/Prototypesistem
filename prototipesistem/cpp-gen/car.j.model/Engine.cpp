#include "Lamp.hpp"
#include "Gearbox.hpp"
#include "Engine.hpp"
#include "deployment.hpp"
#ifndef NDEBUG
#include <iostream>
#endif
#include "EventStructures.hpp"
#include "runtime/Action.hpp"
#include "runtime/ESRoot/StringUtils.hpp"
#include "runtime/ESRoot/CollectionUtils.hpp"

namespace Model {
std::unordered_multimap<EventState, Engine::GuardAction> Engine::_mM;
void Engine::initTransitionTable() {
	Engine::_mM.emplace(
			EventState(Events::EngineOff_EE, Working_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Engine::defaultGuard),
					ActionFuncType(&Engine::Working_Stopped)));
	Engine::_mM.emplace(
			EventState(Events::EngineOn_EE, Stopped_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Engine::defaultGuard),
					ActionFuncType(&Engine::Stopped_Working)));
}

void Engine::initStateMachine() {
	setPoolId(0);
	UsedRuntimeType::getRuntimeInstance()->setupObject(this);
	setInitialState();
}

bool Engine::process_event(ES::EventRef e_) {
	bool handled = false;
	auto range = _mM.equal_range(
			EventState(e_->getType(), _cS, e_->getPortType()));
	if (range.first == _mM.end() && e_->getPortType() != PortType::AnyPort) {
		range = _mM.equal_range(
				EventState(e_->getType(), _cS, PortType::AnyPort));
	}
	if (range.first != _mM.end()) {
		for (auto it = range.first; it != range.second; ++it) {
			if ((it->second).first(*this, e_)) //Guard call
					{
				exit(e_);
				(it->second).second(*this, e_); //Action Call
				entry(e_);
				handled = true;
				break;
			}
		}
	}
	return handled;
}
void Engine::processEventVirtual(ES::EventRef event_) {
	process_event(event_);
}

void Engine::processInitTransition(ES::EventRef event_) {
	initialize(event_);
}

void Engine::setState(int s_) {
	_cS = s_;
}

void Engine::setInitialState() {
	setState (Init_ST);
}
void Engine::Stopped_entry(ES::EventRef) {
}

void Engine::Working_entry(ES::EventRef) {
}

void Engine::Stopped_exit(ES::EventRef) {
}

void Engine::Working_exit(ES::EventRef) {
}

void Engine::Init_Stopped(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Engine::Init_Stopped\n";
#endif
	setState (Stopped_ST);
}

void Engine::Stopped_Working(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Engine::Stopped_Working\n";
#endif
	setState (Working_ST);
}

void Engine::Working_Stopped(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Engine::Working_Stopped\n";
#endif
	setState (Stopped_ST);
}

void Engine::entry(ES::EventRef e_) {
	switch (_cS) {
	case (Working_ST): {
		Working_entry(e_);
		break;
	}
	case (Stopped_ST): {
		Stopped_entry(e_);
		break;
	}
	}
}

void Engine::exit(ES::EventRef e_) {
	switch (_cS) {
	case (Working_ST): {
		Working_exit(e_);
		break;
	}
	case (Stopped_ST): {
		Stopped_exit(e_);
		break;
	}
	}
}

void Engine::finalize(ES::EventRef e_) {
	exit(e_);
}

void Engine::initialize(ES::EventRef e_) {
	Init_Stopped(e_);
	entry(e_);
}

Engine::Engine() {
	initEngine();
}
void Engine::initEngine() {
	initPorts();
	initStateMachine();

}
Engine::~Engine() {
	UsedRuntimeType::getRuntimeInstance()->removeObject(this);
}

void Engine::initPorts() {
}

}

