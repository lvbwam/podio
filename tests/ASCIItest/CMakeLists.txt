
add_executable(ASCIIReader read_asciicopy.cpp ASCIIReader.cc)
target_include_directories(ASCIIReader PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests/datamodel)

target_link_libraries(ASCIIReader TestDataModelDict TestDataModel podio)
install(TARGETS ASCIIReader DESTINATION tests)

#[[set(executable read_asciicopy.cpp)
string( REPLACE ".cpp" "" name ${executable} )
add_executable( ${name} ${executable} )
target_link_libraries( ${name} TestDataModelDict )
install(TARGETS ${name} DESTINATION tests)]]

add_test(NAME read_asciicopy COMMAND ASCIIReader /Users/alifatemi/Documents/GitHub/podio/build/tests/example.txt)
set_property(TEST read_asciicopy PROPERTY ENVIRONMENT LD_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib:${CMAKE_INSTALL_PREFIX}/tests:$ENV{LD_LIBRARY_PATH})
set_property(TEST read_asciicopy PROPERTY DEPENDS write_asciicopy )