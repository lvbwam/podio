include_directories(
	${CMAKE_SOURCE_DIR}/include
${CMAKE_SOURCE_DIR}/datamodels/datamodel
  ${CMAKE_CURRENT_SOURCE_DIR}/datamodel
)

file(GLOB sources src/*.cc)
file(GLOB headers datamodel/*.h)

add_library(ASCIIDataModel SHARED ${sources} ${headers})
install(TARGETS ASCIIDataModel DESTINATION datamodels)

REFLEX_GENERATE_DICTIONARY(ASCIIDataModel ${headers} SELECTION src/selection.xml)
add_library(ASCIIDataModelDict SHARED ASCIIDataModel.cxx)
add_dependencies(ASCIIDataModelDict ASCIIDataModel-dictgen)
install(TARGETS ASCIIDataModelDict DESTINATION tests)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ASCIIDataModelDict.rootmap DESTINATION tests)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ASCIIDataModel_rdict.pcm DESTINATION tests)