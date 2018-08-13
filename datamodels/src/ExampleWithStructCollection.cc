// standard includes
#include <stdexcept>


#include "ExampleWithStructCollection.h"



ExampleWithStructCollection::ExampleWithStructCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new ExampleWithStructDataContainer() ) {
  
}

ExampleWithStructCollection::~ExampleWithStructCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
}

const ExampleWithStruct ExampleWithStructCollection::operator[](unsigned int index) const {
  return ExampleWithStruct(m_entries[index]);
}

const ExampleWithStruct ExampleWithStructCollection::at(unsigned int index) const {
  return ExampleWithStruct(m_entries.at(index));
}

ExampleWithStruct ExampleWithStructCollection::operator[](unsigned int index) {
  return ExampleWithStruct(m_entries[index]);
}

ExampleWithStruct ExampleWithStructCollection::at(unsigned int index) {
  return ExampleWithStruct(m_entries.at(index));
}

int  ExampleWithStructCollection::size() const {
  return m_entries.size();
}

ExampleWithStruct ExampleWithStructCollection::create(){
  auto obj = new ExampleWithStructObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return ExampleWithStruct(obj);
}

void ExampleWithStructCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void ExampleWithStructCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void ExampleWithStructCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new ExampleWithStructObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;
}

bool ExampleWithStructCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void ExampleWithStructCollection::push_back(ConstExampleWithStruct object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void ExampleWithStructCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<ExampleWithStructDataContainer*>(address);
}


const ExampleWithStruct ExampleWithStructCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const ExampleWithStruct* ExampleWithStructCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const ExampleWithStructCollectionIterator& ExampleWithStructCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

std::ostream& operator<<( std::ostream& o,const ExampleWithStructCollection& v){
  std::ios::fmtflags old_flags = o.flags() ; 
  o << "id:          mystruct [data,]:" << std::endl ;
   for(int i = 0; i < v.size(); i++){
     o << std::scientific << std::showpos  << std::setw(12)  << v[i].id() << " "  << std::setw(12) << v[i].mystruct() << " "  << std::endl;
  o.flags(old_flags) ; 
}
  return o ;
}



