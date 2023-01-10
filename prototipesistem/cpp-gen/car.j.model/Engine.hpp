#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include "runtime/StateMachineOwner.hpp"
#include "runtime/ESRoot/Types.hpp"
#include "runtime/PortUtils.hpp"
#include "runtime/ESRoot/Elements.hpp"
namespace Model {
class Lamp;
class Gearbox;

}

namespace Model {
class Engine: public StateMachineOwner {

public:
	static void initTransitionTable();
	bool process_event(ES::EventRef);
	void setInitialState();
	void initialize(ES::EventRef);
	void finalize(ES::EventRef);
//RuntimeFunctions
	virtual void processEventVirtual(ES::EventRef);
	virtual void processInitTransition(ES::EventRef);

	Engine();
	void initEngine();
	~Engine();
	void initPorts();
	enum States
		: int {Init_ST, Stopped_ST, Working_ST
	};

protected:
	typedef std::function<void(Engine&, ES::EventRef)> ActionFuncType;
	typedef std::function<bool(Engine&, ES::EventRef)> GuardFuncType;
	typedef std::pair<GuardFuncType, ActionFuncType> GuardAction;
	static std::unordered_multimap<EventState, Engine::GuardAction> _mM;

private:
//Simple Machine Parts
	void initStateMachine();

	void setState(int s_);
	void entry(ES::EventRef e_);
	void exit(ES::EventRef e_);

	int _cS;

	void Init_Stopped(ES::EventRef);
	void Stopped_Working(ES::EventRef);
	void Working_Stopped(ES::EventRef);

	void Stopped_entry(ES::EventRef);
	void Working_entry(ES::EventRef);
	void Stopped_exit(ES::EventRef);
	void Working_exit(ES::EventRef);

};

}

#endif //__ENGINE_HPP_

