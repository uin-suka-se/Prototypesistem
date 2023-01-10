#ifndef __EVENTSTRUCTURES_HPP__
#define __EVENTSTRUCTURES_HPP__

#include "runtime/ievent.hpp"
namespace Model {

}
namespace Model {
enum Events {
	EngineOff_EE,
	Backward_EE,
	Forward_EE,
	LightOff_EE,
	SwitchLight_EE,
	EngineOn_EE
};
class EngineOff_EC: public EventBase {
public:
	EngineOff_EC() :
			EventBase(EngineOff_EE) {
	}
};

class Backward_EC: public EventBase {
public:
	Backward_EC() :
			EventBase(Backward_EE) {
	}
};

class Forward_EC: public EventBase {
public:
	Forward_EC() :
			EventBase(Forward_EE) {
	}
};

class LightOff_EC: public EventBase {
public:
	LightOff_EC() :
			EventBase(LightOff_EE) {
	}
};

class SwitchLight_EC: public EventBase {
public:
	SwitchLight_EC() :
			EventBase(SwitchLight_EE) {
	}
};

class EngineOn_EC: public EventBase {
public:
	EngineOn_EC() :
			EventBase(EngineOn_EE) {
	}
};

using EngineOffPtr = ES::SharedPtr<EngineOff_EC>;
using BackwardPtr = ES::SharedPtr<Backward_EC>;
using ForwardPtr = ES::SharedPtr<Forward_EC>;
using LightOffPtr = ES::SharedPtr<LightOff_EC>;
using SwitchLightPtr = ES::SharedPtr<SwitchLight_EC>;
using EngineOnPtr = ES::SharedPtr<EngineOn_EC>;

}

#endif //__EVENTSTRUCTURES_HPP_

