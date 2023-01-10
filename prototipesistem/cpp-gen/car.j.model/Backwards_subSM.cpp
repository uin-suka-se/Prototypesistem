#include "Backwards_subSM.hpp"
#include "runtime/Action.hpp"
#ifndef NDEBUG
#include <iostream>
#endif
#include "runtime/ESRoot/StringUtils.hpp"
#include "runtime/ESRoot/CollectionUtils.hpp"
namespace Model {
std::unordered_multimap<EventState, Backwards_subSM::GuardAction> Backwards_subSM::_mM;
void Backwards_subSM::initTransitionTable() {
	Backwards_subSM::_mM.emplace(
			EventState(Events::Backward_EE, B2_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Backwards_subSM::defaultGuard),
					ActionFuncType(&Backwards_subSM::B2_B1)));
	Backwards_subSM::_mM.emplace(
			EventState(Events::Backward_EE, B1_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Backwards_subSM::defaultGuard),
					ActionFuncType(&Backwards_subSM::B1_B2)));
}

Backwards_subSM::Backwards_subSM(Gearbox* pSm_) :
		_pSm(pSm_) {
	setInitialState();
}

bool Backwards_subSM::process_event(ES::EventRef e_) {
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
void Backwards_subSM::setState(int s_) {
	_cS = s_;
}

void Backwards_subSM::setInitialState() {
	setState (BInit_ST);
}
void Backwards_subSM::B1_entry(ES::EventRef) {
}

void Backwards_subSM::B2_entry(ES::EventRef) {
}

void Backwards_subSM::B1_exit(ES::EventRef) {
}

void Backwards_subSM::B2_exit(ES::EventRef) {
}

void Backwards_subSM::BInit_B1(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Backwards_subSM::BInit_B1\n";
#endif
	setState (B1_ST);
}

void Backwards_subSM::B1_B2(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Backwards_subSM::B1_B2\n";
#endif
	setState (B2_ST);
}

void Backwards_subSM::B2_B1(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Backwards_subSM::B2_B1\n";
#endif
	setState (B1_ST);
}

void Backwards_subSM::entry(ES::EventRef e_) {
	switch (_cS) {
	case (B2_ST): {
		B2_entry(e_);
		break;
	}
	case (B1_ST): {
		B1_entry(e_);
		break;
	}
	}
}

void Backwards_subSM::exit(ES::EventRef e_) {
	switch (_cS) {
	case (B2_ST): {
		B2_exit(e_);
		break;
	}
	case (B1_ST): {
		B1_exit(e_);
		break;
	}
	}
}

void Backwards_subSM::finalize(ES::EventRef e_) {
	exit(e_);
}

void Backwards_subSM::initialize(ES::EventRef e_) {
	BInit_B1(e_);
	entry(e_);
}

}

