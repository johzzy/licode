cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)

#functions
function(test_lib LIB_NAME)
 if (${LIB_NAME} MATCHES "^.*-NOTFOUND")
  message(FATAL_ERROR "lib not found: " ${LIB_NAME} " check README")
  return()
 endif(${LIB_NAME} MATCHES "^.*-NOTFOUND")
endfunction(test_lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_THREAD_PROVIDES_FUTURE -DBOOST_THREAD_PROVIDES_FUTURE_CONTINUATION -DBOOST_THREAD_PROVIDES_FUTURE_WHEN_ALL_WHEN_ANY")


include_directories("${ERIZO_SOURCE_DIR}" "${THIRD_PARTY_INCLUDE}" "${NICER_INCLUDE}")

project (ERIZO_EXAMPLES)
file(GLOB_RECURSE ERIZO_EXAMPLES_SOURCES ${ERIZO_EXAMPLES_SOURCE_DIR}/*.cpp ${ERIZO_EXAMPLES_SOURCE_DIR}/*.h)
add_executable(hsam ${ERIZO_EXAMPLES_SOURCES})
include_directories(${ERIZO_EXAMPLES_SOURCE_DIR}/../erizo)
include_directories(${ERIZO_EXAMPLES_SOURCE_DIR}/../third_party/webrtc/src)
link_directories(${ERIZO_EXAMPLES_SOURCE_DIR}/../../build)

set (BOOST_LIBS thread regex system)
find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
target_link_libraries(hsam ${Boost_LIBRARIES})
target_link_libraries(hsam ${EXTRA_LIBS} erizo)
