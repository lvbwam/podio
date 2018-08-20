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
        for (int i = 0; i<100; i++) {
        auto structure = structs[i];
        //std::cout << structure.mystruct().data.x << std::endl;
        if (structure.mystruct().data.x - (eventNum + i)/3.0 > 0.5 || structure.mystruct().data.x - (eventNum + i)/3.0 < -0.5 ) {
            throw std::runtime_error("structs not properly set.");
        }
            if (structure.mystruct().data.y - (eventNum + i + 1)/3.0 > 0.5 || structure.mystruct().data.y - (eventNum + i + 1)/3.0 < -0.5 ) {
                throw std::runtime_error("structs not properly set.");
            }
        /*if (abs(structure.mystruct().data.x - (eventNum + 1)/3.0) > 0.001) {
            throw std::runtime_error("structs not properly set.");
        }
        
        structure = structs[1];
        //std::cout << structure.mystruct().data.x << std::endl;
        if (structure.mystruct().data.x != eventNum + 2) {
            throw std::runtime_error("structs not properly set.");
        }
        if (structure.mystruct().data.y != eventNum + 3) {
            throw std::runtime_error("structs not properly set.");
        }*/
        }
    } else {
        throw std::runtime_error("Collection 'structss' should be present");
    }
}

int main(int argc, char *argv[]){
    if ( argc != 2 ) {// argc should be 2 for correct execution
        // We print argv[0] assuming it is the program name
        std::cout<<"usage: "<< argv[0] <<" <filename>\n";
        }
  auto reader = podio::ASCIIReader();
  auto store = podio::EventStore();
  reader.openFile( argv[1] );
  store.setReader(&reader);

  bool verbose = true;

  unsigned nEvents = reader.getEntries();
  for(unsigned i=0; i<nEvents; ++i) {
    //if(i%20==0)
      //std::cout<<"reading event "<<i<<std::endl;
    processEvent(store, true, i);
    store.clear();
    reader.endOfEvent();
  }
  return 0;
}
