#include "Forwards_subSM.hpp"
#include "runtime/Action.hpp"
#ifndef NDEBUG
#include <iostream>
#endif
#include "runtime/ESRoot/StringUtils.hpp"
#include "runtime/ESRoot/CollectionUtils.hpp"
namespace Model {
std::unordered_multimap<EventState, Forwards_subSM::GuardAction> Forwards_subSM::_mM;
void Forwards_subSM::initTransitionTable() {
	Forwards_subSM::_mM.emplace(
			EventState(Events::Forward_EE, F1_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Forwards_subSM::defaultGuard),
					ActionFuncType(&Forwards_subSM::F1_F2)));
	Forwards_subSM::_mM.emplace(
			EventState(Events::Forward_EE, F2_ST, PortType::AnyPort),
			GuardAction(GuardFuncType(&Forwards_subSM::defaultGuard),
					ActionFuncType(&Forwards_subSM::F2_F1)));
}

Forwards_subSM::Forwards_subSM(Gearbox* pSm_) :
		_pSm(pSm_) {
	setInitialState();
}

bool Forwards_subSM::process_event(ES::EventRef e_) {
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
void Forwards_subSM::setState(int s_) {
	_cS = s_;
}

void Forwards_subSM::setInitialState() {
	setState (FInit_ST);
}
void Forwards_subSM::F1_entry(ES::EventRef) {
}

void Forwards_subSM::F2_entry(ES::EventRef) {
}

void Forwards_subSM::F1_exit(ES::EventRef) {
}

void Forwards_subSM::F2_exit(ES::EventRef) {
}

void Forwards_subSM::FInit_F1(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Forwards_subSM::FInit_F1\n";
#endif
	setState (F1_ST);
}

void Forwards_subSM::F1_F2(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Forwards_subSM::F1_F2\n";
#endif
	setState (F2_ST);
}

void Forwards_subSM::F2_F1(ES::EventRef) {
#ifndef NDEBUG
	std::cout << "Forwards_subSM::F2_F1\n";
#endif
	setState (F1_ST);
}

void Forwards_subSM::entry(ES::EventRef e_) {
	switch (_cS) {
	case (F1_ST): {
		F1_entry(e_);
		break;
	}
	case (F2_ST): {
		F2_entry(e_);
		break;
	}
	}
}

void Forwards_subSM::exit(ES::EventRef e_) {
	switch (_cS) {
	case (F1_ST): {
		F1_exit(e_);
		break;
	}
	case (F2_ST): {
		F2_exit(e_);
		break;
	}
	}
}

void Forwards_subSM::finalize(ES::EventRef e_) {
	exit(e_);
}

void Forwards_subSM::initialize(ES::EventRef e_) {
	FInit_F1(e_);
	entry(e_);
}

}

