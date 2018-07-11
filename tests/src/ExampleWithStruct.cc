// datamodel specific includes
#include "ExampleWithStruct.h"
#include "ExampleWithStructConst.h"
#include "ExampleWithStructObj.h"
#include "ExampleWithStructData.h"
#include "ExampleWithStructCollection.h"
#include <iostream>




ExampleWithStruct::ExampleWithStruct() : m_obj(new ExampleWithStructObj()){
 m_obj->acquire();
}

ExampleWithStruct::ExampleWithStruct(NotSoSimpleStruct mystruct) : m_obj(new ExampleWithStructObj()) {
  m_obj->acquire();
    m_obj->data.mystruct = mystruct;
}


ExampleWithStruct::ExampleWithStruct(const ExampleWithStruct& other) : m_obj(other.m_obj) {
  m_obj->acquire();
}

ExampleWithStruct& ExampleWithStruct::operator=(const ExampleWithStruct& other) {
  if ( m_obj != nullptr) m_obj->release();
  m_obj = other.m_obj;
  return *this;
}

ExampleWithStruct::ExampleWithStruct(ExampleWithStructObj* obj) : m_obj(obj){
  if(m_obj != nullptr)
    m_obj->acquire();
}

ExampleWithStruct ExampleWithStruct::clone() const {
  return {new ExampleWithStructObj(*m_obj)};
}

ExampleWithStruct::~ExampleWithStruct(){
  if ( m_obj != nullptr) m_obj->release();
}

ExampleWithStruct::operator ConstExampleWithStruct() const {return ConstExampleWithStruct(m_obj);}

  const NotSoSimpleStruct& ExampleWithStruct::mystruct() const { return m_obj->data.mystruct; }
const SimpleStruct& ExampleWithStruct::data() const { return m_obj->data.mystruct.data; }

  NotSoSimpleStruct& ExampleWithStruct::mystruct() { return m_obj->data.mystruct; }
void ExampleWithStruct::mystruct(class NotSoSimpleStruct value) { m_obj->data.mystruct = value; }
SimpleStruct& ExampleWithStruct::data() { return m_obj->data.mystruct.data; }
void ExampleWithStruct::data(class SimpleStruct value) { m_obj->data.mystruct.data = value; }



bool  ExampleWithStruct::isAvailable() const {
  if (m_obj != nullptr) {
    return true;
  }
  return false;
}

const podio::ObjectID ExampleWithStruct::getObjectID() const {
  if (m_obj !=nullptr){
    return m_obj->id;
  }
  return podio::ObjectID{-2,-2};
}

bool ExampleWithStruct::operator==(const ConstExampleWithStruct& other) const {
  return (m_obj==other.m_obj);
}

std::ostream& operator<<( std::ostream& o,const ConstExampleWithStruct& value ){
  o << " id : " << value.id() << std::endl ;
  o << " mystruct : " << value.mystruct() << std::endl ;
  o << " data : " << value.data() << std::endl ;
  return o ;
}


//bool operator< (const ExampleWithStruct& p1, const ExampleWithStruct& p2 ) {
//  if( p1.m_containerID == p2.m_containerID ) {
//    return p1.m_index < p2.m_index;
//  } else {
//    return p1.m_containerID < p2.m_containerID;
//  }
//}


