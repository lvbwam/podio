In this branch an ASCIIReader is provided which can only read ExampleWithStruct datatypes. As an example in read_asciicopy.cpp file:

    auto& structs = store.get<ExampleWithStructCollection>("structs");
    if (structs.isValid() && structs.size() != 0) {
        auto structure = structs[0];
        if (structure.mystruct().data.x != eventNum) {
            throw std::runtime_error("structs not properly set.");
        }
        if (structure.mystruct().data.y != eventNum + 1) {
            throw std::runtime_error("structs not properly set.");
        }

The address of example.txt file must be passed to the executable file:
    
    cd build/tests/ASCIItest
    ./ASCIIReader ../example.txt
