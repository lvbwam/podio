// standard includes
#include <stdexcept>


#include "ExampleWithArraymeCollection.h"



ExampleWithArraymeCollection::ExampleWithArraymeCollection() : m_isValid(false), m_collectionID(0), m_entries() ,m_data(new ExampleWithArraymeDataContainer() ) {
  
}

ExampleWithArraymeCollection::~ExampleWithArraymeCollection() {
  clear();
  if (m_data != nullptr) delete m_data;
  
}

const ExampleWithArrayme ExampleWithArraymeCollection::operator[](unsigned int index) const {
  return ExampleWithArrayme(m_entries[index]);
}

const ExampleWithArrayme ExampleWithArraymeCollection::at(unsigned int index) const {
  return ExampleWithArrayme(m_entries.at(index));
}

ExampleWithArrayme ExampleWithArraymeCollection::operator[](unsigned int index) {
  return ExampleWithArrayme(m_entries[index]);
}

ExampleWithArrayme ExampleWithArraymeCollection::at(unsigned int index) {
  return ExampleWithArrayme(m_entries.at(index));
}

int  ExampleWithArraymeCollection::size() const {
  return m_entries.size();
}

ExampleWithArrayme ExampleWithArraymeCollection::create(){
  auto obj = new ExampleWithArraymeObj();
  m_entries.emplace_back(obj);

  obj->id = {int(m_entries.size()-1),m_collectionID};
  return ExampleWithArrayme(obj);
}

void ExampleWithArraymeCollection::clear(){
  m_data->clear();

  for (auto& obj : m_entries) { delete obj; }
  m_entries.clear();
}

void ExampleWithArraymeCollection::prepareForWrite(){
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& obj : m_entries) {m_data->push_back(obj->data); }
  for (auto& pointer : m_refCollections) {pointer->clear(); } 

  for(int i=0, size = m_data->size(); i != size; ++i){

  }

}

void ExampleWithArraymeCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto obj = new ExampleWithArraymeObj({index,m_collectionID}, data);
    
    m_entries.emplace_back(obj);
    ++index;
  }
  m_isValid = true;
}

bool ExampleWithArraymeCollection::setReferences(const podio::ICollectionProvider* collectionProvider){


  return true; //TODO: check success
}

void ExampleWithArraymeCollection::push_back(ConstExampleWithArrayme object){
  int size = m_entries.size();
  auto obj = object.m_obj;
  if (obj->id.index == podio::ObjectID::untracked) {
      obj->id = {size,m_collectionID};
      m_entries.push_back(obj);
      
  } else {
    throw std::invalid_argument( "Object already in a collection. Cannot add it to a second collection " );
  }
}

void ExampleWithArraymeCollection::setBuffer(void* address){
  if (m_data != nullptr) delete m_data;
  m_data = static_cast<ExampleWithArraymeDataContainer*>(address);
}


const ExampleWithArrayme ExampleWithArraymeCollectionIterator::operator* () const {
  m_object.m_obj = (*m_collection)[m_index];
  return m_object;
}

const ExampleWithArrayme* ExampleWithArraymeCollectionIterator::operator-> () const {
  m_object.m_obj = (*m_collection)[m_index];
  return &m_object;
}

const ExampleWithArraymeCollectionIterator& ExampleWithArraymeCollectionIterator::operator++() const {
  ++m_index;
  return *this;
}

std::ostream& operator<<( std::ostream& o,const ExampleWithArraymeCollection& v){
  std::ios::fmtflags old_flags = o.flags() ; 
  o << "id:          arrayStruct [data,]:myArray:      structArray:  " << std::endl ;
   for(int i = 0; i < v.size(); i++){
     o << std::scientific << std::showpos  << std::setw(12)  << v[i].id() << " "  << std::setw(12) << v[i].arrayStruct() << " "  << std::endl;
  o.flags(old_flags) ; 
}
  return o ;
}



