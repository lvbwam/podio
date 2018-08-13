
add_executable(ASCIIReader read_asciicopy.cpp ASCIIReader.cc)
target_include_directories(ASCIIReader PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tests/datamodel)

target_link_libraries(ASCIIReader TestDataModel podio)


install(TARGETS ASCIIReader DESTINATION tests)
