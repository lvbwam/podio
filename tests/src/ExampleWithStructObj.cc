#include "ExampleWithStructObj.h"



ExampleWithStructObj::ExampleWithStructObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data()
{ }

ExampleWithStructObj::ExampleWithStructObj(const podio::ObjectID id, ExampleWithStructData data) :
    ObjBase{id,0}, data(data)
{ }

ExampleWithStructObj::ExampleWithStructObj(const ExampleWithStructObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{

}

ExampleWithStructObj::~ExampleWithStructObj() {
  if (id.index == podio::ObjectID::untracked) {

  }

}

