# build project process:
# cmake -DCMAKE_BUILD_TYPE=Debug(Release) /mnt/c/Users/ksenia.nosulko/source/projects/test_ingenious_machine/machine"
# cmake --build . --target install

cmake_minimum_required(VERSION 3.0)

project(machine)

include_directories(${PROJECT_SOURCE_DIR}/..)
message(${PROJECT_SOURCE_DIR})


find_package(
    Boost 1.66 
        COMPONENTS unit_test_framework # system filesystem 
    REQUIRED
)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}  ${BOOST_LIBRARIES})

    message(${Boost_INCLUDE_DIRS})
    message(${Boost_LIBRARY_DIRS})
    message("using boost " 
        ${Boost_MAJOR_VERSION} "."
        ${Boost_MINOR_VERSION} "."
        ${Boost_SUBMINOR_VERSION}
        " version"
    )
endif()

set(SOURCES
    ${PROJECT_SOURCE_DIR}/sources/machine_call.cpp
)

set(TEST_SOURCES
    ${PROJECT_SOURCE_DIR}/test/test_call_dll.cpp
)

set(OUTPUT_PATH "${CMAKE_BINARY_DIR}/..")
set(CMAKE_INSTALL_RPATH "${CMAKE_BINARY_DIR}/..")
message("CMAKE_INSTALL_RPATH: " ${CMAKE_INSTALL_RPATH})

if(NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Release)
endif()
message("cmake_build_type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

if((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++17 -Wall -Wno-deprecated-declarations")
	if(CMAKE_BUILD_TYPE MATCHES "Debug")
		set(CMAKE_CXX_FLAGS_DEBUG "-g -D _DEBUG")
	endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DMACHINE_EXPORTS")

message("cmake_cxx_compiler_flags: " ${CMAKE_CXX_FLAGS})

set(TARGET_LIB_NAME machine)

add_library(
    ${TARGET_LIB_NAME} 
    SHARED 
    ${SOURCES}
)

target_link_libraries(${TARGET_LIB_NAME}) 

set(TARGET_EXE_NAME test_call_dll)

add_executable(${TARGET_EXE_NAME} 
    ${TEST_SOURCES}
)

set(TARGET_UNIT_TEST_NAME machine_unit_test)
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK) 
add_executable(${TARGET_UNIT_TEST_NAME} 
    ${PROJECT_SOURCE_DIR}/test/unit_test.cpp
)

if((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${TARGET_EXE_NAME} ${TARGET_LIB_NAME}) 
    target_link_libraries(${TARGET_UNIT_TEST_NAME} ${TARGET_LIB_NAME} boost_unit_test_framework)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_link_libraries(${TARGET_EXE_NAME} ${TARGET_LIB_NAME})
    target_link_libraries(${TARGET_UNIT_TEST_NAME} ${TARGET_LIB_NAME} boost_unit_test_framework)
endif()

enable_testing()
add_test(NAME ${TARGET_UNIT_TEST_NAME} COMMAND ${TARGET_UNIT_TEST_NAME})


install(
    TARGETS ${TARGET_EXE_NAME} ${TARGET_LIB_NAME}
    RUNTIME DESTINATION ${OUTPUT_PATH}
    LIBRARY DESTINATION ${OUTPUT_PATH}
    CONFIGURATIONS ${CMAKE_BUILD_TYPE}
)


# find_package(Catch2 REQUIRED)
# target_link_libraries(TARGET_UNIT_TEST_NAME Catch2::Catch2)
