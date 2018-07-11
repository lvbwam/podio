// datamodel specific includes
#include "ExampleWithArrayme.h"
#include "ExampleWithArraymeConst.h"
#include "ExampleWithArraymeObj.h"
#include "ExampleWithArraymeData.h"
#include "ExampleWithArraymeCollection.h"
#include <iostream>




ConstExampleWithArrayme::ConstExampleWithArrayme() : m_obj(new ExampleWithArraymeObj()) {
 m_obj->acquire();
}

ConstExampleWithArrayme::ConstExampleWithArrayme(NotSoSimpleStruct arrayStruct,std::array<int, 4> myArray,std::array<SimpleStruct, 4> structArray) : m_obj(new ExampleWithArraymeObj()){
 m_obj->acquire();
   m_obj->data.arrayStruct = arrayStruct;  m_obj->data.myArray = myArray;  m_obj->data.structArray = structArray;
}


ConstExampleWithArrayme::ConstExampleWithArrayme(const ConstExampleWithArrayme& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ConstExampleWithArrayme& ConstExampleWithArrayme::operator=(const ConstExampleWithArrayme& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ConstExampleWithArrayme::ConstExampleWithArrayme(ExampleWithArraymeObj* obj) : m_obj(obj) {
  if(m_obj != nullptr)
    m_obj->acquire();
}

ConstExampleWithArrayme ConstExampleWithArrayme::clone() const {
  return {new ExampleWithArraymeObj(*m_obj)};
}

ConstExampleWithArrayme::~ConstExampleWithArrayme(){
  if ( m_obj != nullptr) m_obj->release();
}

  const SimpleStruct& ConstExampleWithArrayme::data() const { return m_obj->data.arrayStruct.data; }
  /// Access the  component that contains an array
  const NotSoSimpleStruct& ConstExampleWithArrayme::arrayStruct() const { return m_obj->data.arrayStruct; }
  /// Access the array-member without space to test regex
  const int& ConstExampleWithArrayme::myArray(size_t i) const { return m_obj->data.myArray.at(i); }
  /// Access the array-member without space to test regex
  const std::array<int, 4>& ConstExampleWithArrayme::myArray() const { return m_obj->data.myArray; }
  /// Access the an array containing structs
  const SimpleStruct& ConstExampleWithArrayme::structArray(size_t i) const { return m_obj->data.structArray.at(i); }
  /// Access the an array containing structs
  const std::array<SimpleStruct, 4>& ConstExampleWithArrayme::structArray() const { return m_obj->data.structArray; }



bool  ConstExampleWithArrayme::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ConstExampleWithArrayme::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ConstExampleWithArrayme::operator==(const ExampleWithArrayme& other) const {
     return (m_obj==other.m_obj);
}

//bool operator< (const ExampleWithArrayme& p1, const ExampleWithArrayme& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


