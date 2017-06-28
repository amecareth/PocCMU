project(poccmu)

cmake_minimum_required(VERSION 2.6)
add_definitions(-Wall -Wextra -Wignored-qualifiers)

add_definitions(-g3)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.55.0 COMPONENTS system filesystem iostreams)


include_directories(${Boost_INCLUDE_DIRS})


#
# DOSSIERS DE HEADERS
#
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(HPP_FILES
    includes/Communication/Modes.hpp
    includes/Communication/Result.hpp
    includes/Communication/Requests.hpp
    includes/core/core.hpp
    includes/core/Factory.hpp
    includes/system/system.hpp
    includes/system/Service.hpp

    includes/SML/sml.hpp
    includes/CMU/cmu.hpp

    includes/json/json.h
    includes/json/json-forwards.h
)

set(CPP_FILES
    src/core/Core.cpp
    src/CMU/cmu.cpp
    src/SML/sml.cpp
    src/system/system.cpp
    src/system/Service.cpp
    src/core/Factory.cpp
    src/Extra/jsoncpp.cpp
    main.cpp
)

#
# CREATION DE L'EXECUTABLE
#
add_executable(poccmu ${HPP_FILES} ${CPP_FILES})

target_link_libraries(poccmu ${Boost_LIBRARIES}
			     pthread)
