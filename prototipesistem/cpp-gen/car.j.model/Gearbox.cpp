#include "Backwards_subSM.hpp"
#include "Gearbox.hpp"
#include "Lamp.hpp"
#include "AssociationInstances.hpp"
#include "Engine.hpp"
#include "Forwards_subSM.hpp"
#include "deployment.hpp"
#ifndef NDEBUG
#include <iostream>
#endif
#include "EventStructures.hpp"
#include "runtime/Action.hpp"
#include "runtime/ESRoot/StringUtils.hpp"
#include "runtime/ESRoot/CollectionUtils.hpp"

namespace Model {
std::unordered_multimap<EventState, Gearbox::GuardAction> Gearbox::_mM;
void Gearbox::initTransitionTable() {
	Gearbox::_mM.emplace(
			EventState(Events::Backward_EE, Forwards_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Gearbox::defaultGuard),
					ActionFuncType(&Gearbox::Forwards_Neutral)));
	Gearbox::_mM.emplace(
			EventState(Events::Forward_EE, Backwards_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Gearbox::defaultGuard),
					ActionFuncType(&Gearbox::Backwards_Neutral)));
	Gearbox::_mM.emplace(
			EventState(Events::Forward_EE, Neutral_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Gearbox::defaultGuard),
					ActionFuncType(&Gearbox::Neutral_Forwards)));
	Gearbox::_mM.emplace(
			EventState(Events::Backward_EE, Neutral_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Gearbox::defaultGuard),
					ActionFuncType(&Gearbox::Neutral_Backwards)));
}

void Gearbox::initStateMachine() {
	_cM = nullptr;
	setPoolId(0);
	UsedRuntimeType::getRuntimeInstance()->setupObject(this);
	setInitialState();
	_compSates.emplace(Backwards_ST,
			ES::SharedPtr < SubStateMachine > (new Backwards_subSM(this)));
	_compSates.emplace(Forwards_ST,
			ES::SharedPtr < SubStateMachine > (new Forwards_subSM(this)));
}

bool Gearbox::process_event(ES::EventRef e_) {
	bool handled = false;
	if (_cM) {
		if (_cM->process_event(e_)) {
			handled = true;
		}
	}
	if (!handled) {
		handled = handled || action_caller(e_);
	}
//else unhandled event in this state
	return handled;
}

void Gearbox::processEventVirtual(ES::EventRef event_) {
	process_event(event_);
}

void Gearbox::processInitTransition(ES::EventRef event_) {
	initialize(event_);
}

bool Gearbox::action_caller(ES::EventRef e_) {
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

void Gearbox::setState(int s_) {
	auto it = _compSates.find(s_);
	if (it != _compSates.end()) {
		_cM = (it->second).get();
		_cM->setInitialState(); //restarting from initial state
	} else {
		_cM = nullptr;
	}
	_cS = s_;
}

void Gearbox::setInitialState() {
	setState (Init_ST);
}

void Gearbox::Neutral_entry(ES::EventRef) {
}

void Gearbox::Forwards_entry(ES::EventRef e_) {
	if (_cM) {
		_cM->initialize(e_);
	}
}

void Gearbox::Backwards_entry(ES::EventRef e_) {
	if (_cM) {
		_cM->initialize(e_);
	}
}

void Gearbox::Neutral_exit(ES::EventRef) {
}

void Gearbox::Forwards_exit(ES::EventRef e_) {
	if (_cM) {
		_cM->finalize(e_);
	}
}

void Gearbox::Backwards_exit(ES::EventRef e_) {
	if (_cM) {
		_cM->finalize(e_);
	}
}

void Gearbox::Init_Neutral(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Gearbox::Init_Neutral\n";
#endif
	setState (Neutral_ST);
}

void Gearbox::Neutral_Forwards(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Gearbox::Neutral_Forwards\n";
#endif
	this->startEngineOp();
	setState (Forwards_ST);
}

void Gearbox::Neutral_Backwards(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Gearbox::Neutral_Backwards\n";
#endif
	this->startEngineOp();
	setState (Backwards_ST);
}

void Gearbox::Forwards_Neutral(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Gearbox::Forwards_Neutral\n";
#endif
	MultipliedElement < Engine, 1, 1 > e_us0;
	MultipliedElement < Lamp, 1, 1 > l_us1;
	GEDescriptor::eEnd::CollectionType temp0 = this->assoc(GE.e);
	;
	typename EType<Engine, isPrimitive<Engine>::value>::Type temp1 =
			CollectionUtils::select(temp0);
	e_us0 = temp1;
	EngineOffPtr gen0;
	EngineOffPtr temp2;
	gen0 = temp2;
	gen0 = EngineOffPtr(new EngineOff_EC());
	Action::send(e_us0, gen0);
	GLDescriptor::lEnd::CollectionType temp3 = this->assoc(GL.l);
	;
	typename EType<Lamp, isPrimitive<Lamp>::value>::Type temp4 =
			CollectionUtils::select(temp3);
	l_us1 = temp4;
	LightOffPtr gen1;
	LightOffPtr temp5;
	gen1 = temp5;
	gen1 = LightOffPtr(new LightOff_EC());
	Action::send(l_us1, gen1);
	setState (Neutral_ST);
}

void Gearbox::Backwards_Neutral(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Gearbox::Backwards_Neutral\n";
#endif
	MultipliedElement < Engine, 1, 1 > e_us0;
	MultipliedElement < Lamp, 1, 1 > l_us1;
	GEDescriptor::eEnd::CollectionType temp0 = this->assoc(GE.e);
	;
	typename EType<Engine, isPrimitive<Engine>::value>::Type temp1 =
			CollectionUtils::select(temp0);
	e_us0 = temp1;
	EngineOffPtr gen0;
	EngineOffPtr temp2;
	gen0 = temp2;
	gen0 = EngineOffPtr(new EngineOff_EC());
	Action::send(e_us0, gen0);
	GLDescriptor::lEnd::CollectionType temp3 = this->assoc(GL.l);
	;
	typename EType<Lamp, isPrimitive<Lamp>::value>::Type temp4 =
			CollectionUtils::select(temp3);
	l_us1 = temp4;
	LightOffPtr gen1;
	LightOffPtr temp5;
	gen1 = temp5;
	gen1 = LightOffPtr(new LightOff_EC());
	Action::send(l_us1, gen1);
	setState (Neutral_ST);
}

void Gearbox::entry(ES::EventRef e_) {
	switch (_cS) {
	case (Backwards_ST): {
		Backwards_entry(e_);
		break;
	}
	case (Neutral_ST): {
		Neutral_entry(e_);
		break;
	}
	case (Forwards_ST): {
		Forwards_entry(e_);
		break;
	}
	}
}

void Gearbox::exit(ES::EventRef e_) {
	switch (_cS) {
	case (Backwards_ST): {
		Backwards_exit(e_);
		break;
	}
	case (Neutral_ST): {
		Neutral_exit(e_);
		break;
	}
	case (Forwards_ST): {
		Forwards_exit(e_);
		break;
	}
	}
}

void Gearbox::finalize(ES::EventRef e_) {
	exit(e_);
}

void Gearbox::initialize(ES::EventRef e_) {
	Init_Neutral(e_);
	entry(e_);
}

void Gearbox::startEngineOp() {
	MultipliedElement < Engine, 1, 1 > e_us0;
	GEDescriptor::eEnd::CollectionType temp0 = this->assoc(GE.e);
	;
	typename EType<Engine, isPrimitive<Engine>::value>::Type temp1 =
			CollectionUtils::select(temp0);
	e_us0 = temp1;
	EngineOnPtr gen0;
	EngineOnPtr temp2;
	gen0 = temp2;
	gen0 = EngineOnPtr(new EngineOn_EC());
	Action::send(e_us0, gen0);
}

Gearbox::Gearbox() {
	initGearbox();
}
void Gearbox::initGearbox() {
	initPorts();
	initStateMachine();

}
Gearbox::~Gearbox() {
	UsedRuntimeType::getRuntimeInstance()->removeObject(this);
}

void Gearbox::initPorts() {
}

}

