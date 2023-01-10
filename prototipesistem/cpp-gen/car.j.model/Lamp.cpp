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
std::unordered_multimap<EventState, Lamp::GuardAction> Lamp::_mM;
void Lamp::initTransitionTable() {
	Lamp::_mM.emplace(
			EventState(Events::LightOff_EE, Light_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Lamp::defaultGuard),
					ActionFuncType(&Lamp::Light_Dark2)));
	Lamp::_mM.emplace(
			EventState(Events::SwitchLight_EE, Dark_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Lamp::defaultGuard),
					ActionFuncType(&Lamp::Dark_Light)));
	Lamp::_mM.emplace(
			EventState(Events::SwitchLight_EE, Light_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Lamp::defaultGuard),
					ActionFuncType(&Lamp::Light_Dark)));
}

void Lamp::initStateMachine() {
	setPoolId(0);
	UsedRuntimeType::getRuntimeInstance()->setupObject(this);
	setInitialState();
}

bool Lamp::process_event(ES::EventRef e_) {
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
void Lamp::processEventVirtual(ES::EventRef event_) {
	process_event(event_);
}

void Lamp::processInitTransition(ES::EventRef event_) {
	initialize(event_);
}

void Lamp::setState(int s_) {
	_cS = s_;
}

void Lamp::setInitialState() {
	setState (Init_ST);
}
void Lamp::Dark_entry(ES::EventRef) {
}

void Lamp::Light_entry(ES::EventRef) {
}

void Lamp::Dark_exit(ES::EventRef) {
}

void Lamp::Light_exit(ES::EventRef) {
}

void Lamp::Init_Dark(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Lamp::Init_Dark\n";
#endif
	setState (Dark_ST);
}

void Lamp::Dark_Light(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Lamp::Dark_Light\n";
#endif
	setState (Light_ST);
}

void Lamp::Light_Dark(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Lamp::Light_Dark\n";
#endif
	setState (Dark_ST);
}

void Lamp::Light_Dark2(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Lamp::Light_Dark2\n";
#endif
	setState (Dark_ST);
}

void Lamp::entry(ES::EventRef e_) {
	switch (_cS) {
	case (Dark_ST): {
		Dark_entry(e_);
		break;
	}
	case (Light_ST): {
		Light_entry(e_);
		break;
	}
	}
}

void Lamp::exit(ES::EventRef e_) {
	switch (_cS) {
	case (Dark_ST): {
		Dark_exit(e_);
		break;
	}
	case (Light_ST): {
		Light_exit(e_);
		break;
	}
	}
}

void Lamp::finalize(ES::EventRef e_) {
	exit(e_);
}

void Lamp::initialize(ES::EventRef e_) {
	Init_Dark(e_);
	entry(e_);
}

Lamp::Lamp() {
	initLamp();
}
void Lamp::initLamp() {
	initPorts();
	initStateMachine();

}
Lamp::~Lamp() {
	UsedRuntimeType::getRuntimeInstance()->removeObject(this);
}

void Lamp::initPorts() {
}

}

