#ifndef __DEPLOYMENT_HPP__
#define __DEPLOYMENT_HPP__

#include "runtime/runtime.hpp"
#include "runtime/ESRoot/Types.hpp"

using UsedRuntimePtr = ES::RuntimePtr<Execution::ConfiguredThreadedRT<2>,2>;
using UsedRuntimeType = Execution::IRuntime<Execution::ConfiguredThreadedRT<2>,2>;

namespace deployment {
UsedRuntimePtr initRuntime();
}

#endif //__DEPLOYMENT_HPP_

