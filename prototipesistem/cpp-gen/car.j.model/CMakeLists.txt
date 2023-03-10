cmake_minimum_required(VERSION 2.8.12)
project(car_j_model CXX C)
find_package(Threads)
include(CheckCXXCompilerFlag)
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  set(CMAKE_AR gcc-ar)
  set(CMAKE_RANLIB gcc-ranlib)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
  set(CMAKE_AR llvm-ar)
  set(CMAKE_RANLIB llvm-ranlib)
endif()
if(MSVC)
  add_compile_options(/W3 /WX)
  add_compile_options($<$<CONFIG:Debug>:/RTC>)
  add_compile_options($<$<CONFIG:Release>:/GL>)
else()
  add_compile_options(-std=c++14)
  add_compile_options(-Wall -pedantic -Wextra -Wconversion -Werror)
  add_compile_options(-Wno-error=unused-parameter)
  CHECK_CXX_COMPILER_FLAG(-Wno-error=unused-private-field WNOERROR_UNUSEDPRIVATEFIELD)
  if(WNOERROR_UNUSEDPRIVATEFIELD)
    add_compile_options(-Wno-error=unused-private-field)
  endif()
if(!WIN32)
  add_compile_options($<$<CONFIG:Debug>:-fsanitize=address>)
endif()
  add_compile_options($<$<CONFIG:Release>:-flto>)
endif()
include_directories(runtime)
add_library(libsmrt STATIC runtime/runtime.cpp runtime/StateMachineOwner.cpp runtime/NotStateMachineOwner.cpp runtime/threadpool.cpp runtime/threadcontainer.cpp runtime/timer.cpp runtime/itimer.cpp runtime/Action.cpp)
add_executable(main main.cpp deployment.cpp init_maps.cpp Env.cpp AssociationInstances.cpp Engine.cpp Lamp.cpp Backwards_subSM.cpp Forwards_subSM.cpp Gearbox.cpp)
target_link_libraries(main libsmrt)
if(MSVC)
  set_target_properties(main PROPERTIES LINK_FLAGS_RELEASE "/LTCG")
else()
if(!WIN32)
  set_target_properties(main PROPERTIES LINK_FLAGS_DEBUG "-fsanitize=address")
endif()
  set_target_properties(main PROPERTIES LINK_FLAGS_RELEASE "-flto")
endif()
if(Threads_FOUND)
  target_link_libraries(main "${CMAKE_THREAD_LIBS_INIT}")
endif()

