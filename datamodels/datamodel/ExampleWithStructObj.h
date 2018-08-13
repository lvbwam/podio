#ifndef ExampleWithStructOBJ_H
#define ExampleWithStructOBJ_H

// std includes
#include <atomic>
#include <iostream>

// data model specific includes
#include "podio/ObjBase.h"
#include "ExampleWithStructData.h"



// forward declarations
class ExampleWithStruct;
class ConstExampleWithStruct;



class ExampleWithStructObj : public podio::ObjBase {
public:
  /// constructor
  ExampleWithStructObj();
  /// copy constructor (does a deep-copy of relation containers)
  ExampleWithStructObj(const ExampleWithStructObj&);
  /// constructor from ObjectID and ExampleWithStructData
  /// does not initialize the internal relation containers
  ExampleWithStructObj(const podio::ObjectID id, ExampleWithStructData data);
  virtual ~ExampleWithStructObj();

public:
  ExampleWithStructData data;


};



#endif
