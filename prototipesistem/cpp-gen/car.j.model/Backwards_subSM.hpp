#ifndef __BACKWARDS_SUBSM_HPP__
#define __BACKWARDS_SUBSM_HPP__

#include "Gearbox.hpp"
#include "EventStructures.hpp"
namespace Model {

}
namespace Model {
class Backwards_subSM: public SubStateMachine {

public:
	static void initTransitionTable();
	bool process_event(ES::EventRef);
	void setInitialState();
	void initialize(ES::EventRef);
	void finalize(ES::EventRef);
	Backwards_subSM(Gearbox*);
	enum States
		: int {BInit_ST, B1_ST, B2_ST
	};

protected:
	typedef std::function<void(Backwards_subSM&, ES::EventRef)> ActionFuncType;
	typedef std::function<bool(Backwards_subSM&, ES::EventRef)> GuardFuncType;
	typedef std::pair<GuardFuncType, ActionFuncType> GuardAction;
	static std::unordered_multimap<EventState, Backwards_subSM::GuardAction> _mM;

private:
//Simple Machine Parts
	void initStateMachine();

	void setState(int s_);
	void entry(ES::EventRef e_);
	void exit(ES::EventRef e_);

	int _cS;
	Gearbox* _pSm;
	void B1_entry(ES::EventRef);
	void B2_entry(ES::EventRef);
	void B1_exit(ES::EventRef);
	void B2_exit(ES::EventRef);

	void BInit_B1(ES::EventRef);
	void B1_B2(ES::EventRef);
	void B2_B1(ES::EventRef);

};

}

#endif //__BACKWARDS_SUBSM_HPP_

