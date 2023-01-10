#include "deployment.hpp"
namespace deployment {
UsedRuntimePtr initRuntime() {
	std::array<ES::SharedPtr<Execution::Configuration>, 2> conf;
	conf[0] = ES::SharedPtr < Execution::Configuration
			> (new Execution::Configuration(
					ES::SharedPtr < Execution::StateMachineThreadPool
							> (new Execution::StateMachineThreadPool),
					ES::SharedPtr < Execution::LinearFunction
							> (new Execution::LinearFunction(2, 0.0)), 5));
	conf[1] = ES::SharedPtr < Execution::Configuration
			> (new Execution::Configuration(
					ES::SharedPtr < Execution::StateMachineThreadPool
							> (new Execution::StateMachineThreadPool),
					ES::SharedPtr < Execution::LinearFunction
							> (new Execution::LinearFunction(1, 0.0)), 1));
	UsedRuntimePtr rt = UsedRuntimeType::getRuntimeInstance();
	rt->configure(conf);
	;

	return rt;
}
}

