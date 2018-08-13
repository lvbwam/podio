#ifndef ExampleWithArraymeOBJ_H
#define ExampleWithArraymeOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "ExampleWithArraymeData.h"



// forward declarations
class ExampleWithArrayme;
class ConstExampleWithArrayme;



class ExampleWithArraymeObj : public podio::ObjBase {
public:
  /// constructor
  ExampleWithArraymeObj();
  /// copy constructor (does a deep-copy of relation containers)
  ExampleWithArraymeObj(const ExampleWithArraymeObj&);
  /// constructor from ObjectID and ExampleWithArraymeData
  /// does not initialize the internal relation containers
  ExampleWithArraymeObj(const podio::ObjectID id, ExampleWithArraymeData data);
  virtual ~ExampleWithArraymeObj();

public:
  ExampleWithArraymeData data;


};



#endif
