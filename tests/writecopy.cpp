// Data model
#include "EventInfoCollection.h"
#include "ExampleWithArraymeCollection.h"
#include "ExampleWithStructCollection.h"
//#include "StructWithArray.h"

// STL
#include <iostream>
#include <vector>

// podio specific includes
#include "podio/EventStore.h"
#include "podio/ROOTWriter.h"

int main(int argc, char *argv[]){
    
    if ( argc != 2 ) {// argc should be 2 for correct execution
        // We print argv[0] assuming it is the program name
        std::cout<<"usage: "<< argv[0] <<" <filename>\n";
    }


  std::cout<<"start processing"<<std::endl;
    
  int nevents= atoi(argv[1]);

    

  auto store = podio::EventStore();
  auto writer = podio::ROOTWriter("example.root", &store);

  auto& info       = store.create<EventInfoCollection>("info");
  //auto& arrays     = store.create<ExampleWithArraymeCollection>("arrays");
  auto& structs     = store.create<ExampleWithStructCollection>("structs");
  writer.registerForWrite("info");
  //writer.registerForWrite("arrays");
  writer.registerForWrite("structs");



  for(unsigned i=0; i<nevents; ++i) {
    if(i % 1000 == 0) {
      std::cout << "processing event " << i << std::endl;
    }

    auto item1 = EventInfo();
    item1.Number(i);
    info.push_back(item1);
    
    //std::array<int, 4> arrayTest = {0, 0, 2, 3};
    //NotSoSimpleStruct a;
    //a.data.x = static_cast<int>(i);
    //a.data.y = static_cast<int>(i) + 1;
    //SimpleStruct nstruct;
    //nstruct.x = static_cast<int>(i) + 2;
    //nstruct.y = static_cast<int>(i) + 3;
    //std::array<SimpleStruct, 4> structArrayTest = {nstruct, nstruct, nstruct, nstruct};
    //auto array = ExampleWithArrayme(a, arrayTest, structArrayTest);
    //array.myArray(1, i);
    //array.arrayStruct(a);
    //arrays.push_back(array);

    NotSoSimpleStruct b;
    b.data.x = static_cast<int>(i);
    b.data.y = static_cast<int>(i) + 1;
    auto structure = ExampleWithStruct(b);
    structs.push_back(structure);
      
    NotSoSimpleStruct c;
    c.data.x = static_cast<int>(i) + 2;
    c.data.y = static_cast<int>(i) + 3;
    auto structure1 = ExampleWithStruct(c);
    structs.push_back(structure1);
    
    writer.writeEvent();
    store.clearCollections();
  }

  writer.finish();
}
