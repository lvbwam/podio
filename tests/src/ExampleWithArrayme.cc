// datamodel specific includes
#include "ExampleWithArrayme.h"
#include "ExampleWithArraymeConst.h"
#include "ExampleWithArraymeObj.h"
#include "ExampleWithArraymeData.h"
#include "ExampleWithArraymeCollection.h"
#include <iostream>




ExampleWithArrayme::ExampleWithArrayme() : m_obj(new ExampleWithArraymeObj()){
 m_obj->acquire();
}

ExampleWithArrayme::ExampleWithArrayme(NotSoSimpleStruct arrayStruct,std::array<int, 4> myArray,std::array<SimpleStruct, 4> structArray) : m_obj(new ExampleWithArraymeObj()) {
  m_obj->acquire();
    m_obj->data.arrayStruct = arrayStruct;  m_obj->data.myArray = myArray;  m_obj->data.structArray = structArray;
}


ExampleWithArrayme::ExampleWithArrayme(const ExampleWithArrayme& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ExampleWithArrayme& ExampleWithArrayme::operator=(const ExampleWithArrayme& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ExampleWithArrayme::ExampleWithArrayme(ExampleWithArraymeObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ExampleWithArrayme ExampleWithArrayme::clone() const {
  return {new ExampleWithArraymeObj(*m_obj)};
}

ExampleWithArrayme::~ExampleWithArrayme(){
  if ( m_obj != nullptr) m_obj->release();
}

ExampleWithArrayme::operator ConstExampleWithArrayme() const {return ConstExampleWithArrayme(m_obj);}

  const NotSoSimpleStruct& ExampleWithArrayme::arrayStruct() const { return m_obj->data.arrayStruct; }
const SimpleStruct& ExampleWithArrayme::data() const { return m_obj->data.arrayStruct.data; }
  const std::array<int, 4>& ExampleWithArrayme::myArray() const { return m_obj->data.myArray; }
  const int& ExampleWithArrayme::myArray(size_t i) const { return m_obj->data.myArray.at(i); }
  const std::array<SimpleStruct, 4>& ExampleWithArrayme::structArray() const { return m_obj->data.structArray; }
  const SimpleStruct& ExampleWithArrayme::structArray(size_t i) const { return m_obj->data.structArray.at(i); }

  NotSoSimpleStruct& ExampleWithArrayme::arrayStruct() { return m_obj->data.arrayStruct; }
void ExampleWithArrayme::arrayStruct(class NotSoSimpleStruct value) { m_obj->data.arrayStruct = value; }
SimpleStruct& ExampleWithArrayme::data() { return m_obj->data.arrayStruct.data; }
void ExampleWithArrayme::data(class SimpleStruct value) { m_obj->data.arrayStruct.data = value; }
void ExampleWithArrayme::myArray(std::array<int, 4> value) { m_obj->data.myArray = value; }
void ExampleWithArrayme::myArray(size_t i, int value) { m_obj->data.myArray.at(i) = value; }
void ExampleWithArrayme::structArray(std::array<SimpleStruct, 4> value) { m_obj->data.structArray = value; }
void ExampleWithArrayme::structArray(size_t i, SimpleStruct value) { m_obj->data.structArray.at(i) = value; }



bool  ExampleWithArrayme::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ExampleWithArrayme::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ExampleWithArrayme::operator==(const ConstExampleWithArrayme& other) const {
  return (m_obj==other.m_obj);
}

std::ostream& operator<<( std::ostream& o,const ConstExampleWithArrayme& value ){
  o << " id : " << value.id() << std::endl ;
  o << " arrayStruct : " << value.arrayStruct() << std::endl ;
  o << " data : " << value.data() << std::endl ;
  return o ;
}


//bool operator< (const ExampleWithArrayme& p1, const ExampleWithArrayme& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


