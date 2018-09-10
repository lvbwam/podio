Writers and readers now can write and read many instances of structs in one collection:

     NotSoSimpleStruct b[100];
      b[0].data.x = (i)/3.0;
      b[0].data.y = (i+1)/3.0;
      structs.push_back(b[0]);
      
     for (int j = 1; j<100; j++) {
      b[j].data.x = (i+j)/3.0;
      b[j].data.y = (i+j+1)/3.0;
      structs.push_back(b[j]);
     }
     
     
     
    auto& structs = store.get<ExampleWithStructCollection>("structs");
    if (structs.isValid() && structs.size() != 0) {
        for (int i = 0; i<100; i++) {
        auto structure = structs[i];
        if (structure.mystruct().data.x - (eventNum + i)/3.0 > 0.1 || structure.mystruct().data.x - (eventNum + i)/3.0 < -0.1 ) {
            throw std::runtime_error("structs not properly set.");
        }
        if (structure.mystruct().data.y - (eventNum + i + 1)/3.0 > 0.1 || structure.mystruct().data.y - (eventNum + i + 1)/3.0 < -0.1 ) {
            throw std::runtime_error("structs not properly set.");
        }
     
Number of events must be passed to the writers:
     
     cd build/tests
     ./writecopy 10000
     ./write_asciicopy 10000
