#include "ExampleWithArraymeObj.h"



ExampleWithArraymeObj::ExampleWithArraymeObj() :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}, data()
{ }

ExampleWithArraymeObj::ExampleWithArraymeObj(const podio::ObjectID id, ExampleWithArraymeData data) :
    ObjBase{id,0}, data(data)
{ }

ExampleWithArraymeObj::ExampleWithArraymeObj(const ExampleWithArraymeObj& other) :
    ObjBase{{podio::ObjectID::untracked,podio::ObjectID::untracked},0}
    , data(other.data)
{

}

ExampleWithArraymeObj::~ExampleWithArraymeObj() {
  if (id.index == podio::ObjectID::untracked) {

  }

}

