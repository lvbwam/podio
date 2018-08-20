// Data model
#include "EventInfoCollection.h"
#include "ExampleWithArraymeCollection.h"
#include "ExampleWithStructCollection.h"

// STL
#include <iostream>
#include <vector>

// podio specific includes
#include "podio/EventStore.h"
#include "podio/ASCIIWriter.h"

int main(int argc, char *argv[]){
    
    if ( argc != 2 ) {// argc should be 2 for correct execution
        // We print argv[0] assuming it is the program name
        std::cout<<"usage: "<< argv[0] <<" <filename>\n";
    }

  std::cout<<"start processing"<<std::endl;
    
    
  int nevents= atoi(argv[1]);

  auto store = podio::EventStore();
  auto writer = podio::ASCIIWriter("example.txt", &store, nevents);

  auto& info       = store.create<EventInfoCollection>("info");
  //auto& arrays     = store.create<ExampleWithArraymeCollection>("arrays");
  auto& structs     = store.create<ExampleWithStructCollection>("structs");
  writer.registerForWrite<EventInfoCollection>("info");
  //writer.registerForWrite<ExampleWithArraymeCollection>("arrays");
  writer.registerForWrite<ExampleWithStructCollection>("structs");

  

  for(int i=0; i<nevents; ++i) {
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
      
      NotSoSimpleStruct b[100];
      b[0].data.x = (i)/3.0;
      b[0].data.y = (i+1)/3.0;
      structs.push_back(b[0]);
      
      for (int j = 1; j<100; j++) {
          b[j].data.x = (i+j)/3.0;
          b[j].data.y = (i+j+1)/3.0;
          structs.push_back(b[j]);
      }
      
    writer.writeEvent();
    store.clearCollections();
  }

  writer.finish();
}
