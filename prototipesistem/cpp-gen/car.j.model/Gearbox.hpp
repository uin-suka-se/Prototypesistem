#ifndef __GEARBOX_HPP__
#define __GEARBOX_HPP__

#include "runtime/StateMachineOwner.hpp"
#include "runtime/ESRoot/Types.hpp"
#include "runtime/PortUtils.hpp"
#include "runtime/SubStateMachine.hpp"
#include "runtime/ESRoot/Elements.hpp"
namespace Model {
class Backwards_subSM;
class Lamp;
class Engine;
class Forwards_subSM;

}

namespace Model {
class Gearbox: public StateMachineOwner {

public:
	static void initTransitionTable();
	bool process_event(ES::EventRef);
	void setInitialState();
	void initialize(ES::EventRef);
	void finalize(ES::EventRef);
//RuntimeFunctions
	virtual void processEventVirtual(ES::EventRef);
	virtual void processInitTransition(ES::EventRef);

	void startEngineOp();
	Gearbox();
	void initGearbox();
	~Gearbox();
	void initPorts();
	enum States
		: int {Init_ST, Neutral_ST, Forwards_ST, Backwards_ST
	};

protected:
	typedef std::function<void(Gearbox&, ES::EventRef)> ActionFuncType;
	typedef std::function<bool(Gearbox&, ES::EventRef)> GuardFuncType;
	typedef std::pair<GuardFuncType, ActionFuncType> GuardAction;
	static std::unordered_multimap<EventState, Gearbox::GuardAction> _mM;

private:
//Simple Machine Parts
	void initStateMachine();

	void setState(int s_);
	void entry(ES::EventRef e_);
	void exit(ES::EventRef e_);

	int _cS;
//Hierarchical Machine Parts
	bool action_caller(ES::EventRef e_);
	SubStateMachine* _cM;
	std::unordered_map<int, ES::SharedPtr<SubStateMachine> > _compSates;
	friend class Backwards_subSM;
	friend class Forwards_subSM;

	void Init_Neutral(ES::EventRef);
	void Neutral_Forwards(ES::EventRef);
	void Neutral_Backwards(ES::EventRef);
	void Forwards_Neutral(ES::EventRef);
	void Backwards_Neutral(ES::EventRef);

	void Neutral_entry(ES::EventRef);
	void Forwards_entry(ES::EventRef);
	void Backwards_entry(ES::EventRef);
	void Neutral_exit(ES::EventRef);
	void Forwards_exit(ES::EventRef);
	void Backwards_exit(ES::EventRef);

};

}

#endif //__GEARBOX_HPP_

