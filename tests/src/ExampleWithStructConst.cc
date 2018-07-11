// datamodel specific includes
#include "ExampleWithStruct.h"
#include "ExampleWithStructConst.h"
#include "ExampleWithStructObj.h"
#include "ExampleWithStructData.h"
#include "ExampleWithStructCollection.h"
#include <iostream>




ConstExampleWithStruct::ConstExampleWithStruct() : m_obj(new ExampleWithStructObj()) {
 m_obj->acquire();
}

ConstExampleWithStruct::ConstExampleWithStruct(NotSoSimpleStruct mystruct) : m_obj(new ExampleWithStructObj()){
 m_obj->acquire();
   m_obj->data.mystruct = mystruct;
}


ConstExampleWithStruct::ConstExampleWithStruct(const ConstExampleWithStruct& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstExampleWithStruct& ConstExampleWithStruct::operator=(const ConstExampleWithStruct& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstExampleWithStruct::ConstExampleWithStruct(ExampleWithStructObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstExampleWithStruct ConstExampleWithStruct::clone() const {
  return {new ExampleWithStructObj(*m_obj)};
}

ConstExampleWithStruct::~ConstExampleWithStruct(){
  if ( m_obj != nullptr) m_obj->release();
}

  const SimpleStruct& ConstExampleWithStruct::data() const { return m_obj->data.mystruct.data; }
  /// Access the  component that contains an struct
  const NotSoSimpleStruct& ConstExampleWithStruct::mystruct() const { return m_obj->data.mystruct; }



bool  ConstExampleWithStruct::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstExampleWithStruct::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstExampleWithStruct::operator==(const ExampleWithStruct& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const ExampleWithStruct& p1, const ExampleWithStruct& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


