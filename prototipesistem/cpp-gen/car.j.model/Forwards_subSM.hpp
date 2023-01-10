#ifndef __FORWARDS_SUBSM_HPP__
#define __FORWARDS_SUBSM_HPP__

#include "Gearbox.hpp"
#include "EventStructures.hpp"
namespace Model {

}
namespace Model {
class Forwards_subSM: public SubStateMachine {

public:
	static void initTransitionTable();
	bool process_event(ES::EventRef);
	void setInitialState();
	void initialize(ES::EventRef);
	void finalize(ES::EventRef);
	Forwards_subSM(Gearbox*);
	enum States
		: int {FInit_ST, F1_ST, F2_ST
	};

protected:
	typedef std::function<void(Forwards_subSM&, ES::EventRef)> ActionFuncType;
	typedef std::function<bool(Forwards_subSM&, ES::EventRef)> GuardFuncType;
	typedef std::pair<GuardFuncType, ActionFuncType> GuardAction;
	static std::unordered_multimap<EventState, Forwards_subSM::GuardAction> _mM;

private:
//Simple Machine Parts
	void initStateMachine();

	void setState(int s_);
	void entry(ES::EventRef e_);
	void exit(ES::EventRef e_);

	int _cS;
	Gearbox* _pSm;
	void F1_entry(ES::EventRef);
	void F2_entry(ES::EventRef);
	void F1_exit(ES::EventRef);
	void F2_exit(ES::EventRef);

	void FInit_F1(ES::EventRef);
	void F1_F2(ES::EventRef);
	void F2_F1(ES::EventRef);

};

}

#endif //__FORWARDS_SUBSM_HPP_

