// STL
#include <vector>
#include <iostream>
#include <exception>
#include <cassert>

// podio specific includes
#include "podio/EventStore.h"
#include "ASCIIReader.h"

// test data model

#include "ExampleWithArraymeCollection.h"
#include "ExampleWithStructCollection.h"

int glob = 0;

void processEvent(podio::EventStore& store, bool verboser, unsigned eventNum) {

  /*auto& arrays = store.get<ExampleWithArraymeCollection>("arrays");
  if (arrays.isValid() && arrays.size() != 0) {
    auto array = arrays[0];
    if (array.myArray(1) != eventNum) {
      throw std::runtime_error("Array not properly set.");
    }
    if (array.arrayStruct().data.x != eventNum) {
      throw std::runtime_error("Array not properly set.");
    }
    if (array.structArray(0).x != eventNum+2) {
      throw std::runtime_error("Array of struct not properly set.");
    }
  } else {
    throw std::runtime_error("Collection 'arrays' should be present");
  }*/
    
    auto& structs = store.get<ExampleWithStructCollection>("structs");
    if (structs.isValid() && structs.size() != 0) {
        auto structure = structs[0];
        if (structure.mystruct().data.x != eventNum) {
            throw std::runtime_error("structs not properly set.");
        }
        if (structure.mystruct().data.y != eventNum + 1) {
            throw std::runtime_error("structs not properly set.");
        }
    } else {
        throw std::runtime_error("Collection 'structss' should be present");
    }
}

int main(){
  auto reader = podio::ASCIIReader();
  auto store = podio::EventStore();
  reader.openFile("example.txt");
  store.setReader(&reader);

  bool verbose = true;

  unsigned nEvents = reader.getEntries();
  for(unsigned i=0; i<nEvents; ++i) {
    if(i%1000==0)
      std::cout<<"reading event "<<i<<std::endl;
    processEvent(store, true, i);
    store.clear();
    reader.endOfEvent();
  }
  return 0;
}
