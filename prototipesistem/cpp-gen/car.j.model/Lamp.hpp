#ifndef __LAMP_HPP__
#define __LAMP_HPP__

#include "runtime/StateMachineOwner.hpp"
#include "runtime/ESRoot/Types.hpp"
#include "runtime/PortUtils.hpp"
#include "runtime/ESRoot/Elements.hpp"
namespace Model {
class Gearbox;
class Engine;

}

namespace Model {
class Lamp: public StateMachineOwner {

public:
	static void initTransitionTable();
	bool process_event(ES::EventRef);
	void setInitialState();
	void initialize(ES::EventRef);
	void finalize(ES::EventRef);
//RuntimeFunctions
	virtual void processEventVirtual(ES::EventRef);
	virtual void processInitTransition(ES::EventRef);

	Lamp();
	void initLamp();
	~Lamp();
	void initPorts();
	enum States
		: int {Init_ST, Dark_ST, Light_ST
	};

protected:
	typedef std::function<void(Lamp&, ES::EventRef)> ActionFuncType;
	typedef std::function<bool(Lamp&, ES::EventRef)> GuardFuncType;
	typedef std::pair<GuardFuncType, ActionFuncType> GuardAction;
	static std::unordered_multimap<EventState, Lamp::GuardAction> _mM;

private:
//Simple Machine Parts
	void initStateMachine();

	void setState(int s_);
	void entry(ES::EventRef e_);
	void exit(ES::EventRef e_);

	int _cS;

	void Init_Dark(ES::EventRef);
	void Dark_Light(ES::EventRef);
	void Light_Dark(ES::EventRef);
	void Light_Dark2(ES::EventRef);

	void Dark_entry(ES::EventRef);
	void Light_entry(ES::EventRef);
	void Dark_exit(ES::EventRef);
	void Light_exit(ES::EventRef);

};

}

#endif //__LAMP_HPP_

