//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef ExampleWithArraymeCollection_H
#define  ExampleWithArraymeCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>
#include <algorithm>
#include <iostream>
#include <iomanip>

// podio specific includes
#include "podio/ICollectionProvider.h"
#include "podio/CollectionBase.h"
#include "podio/CollectionIDTable.h"

// datamodel specific includes
#include "ExampleWithArraymeData.h"
#include "ExampleWithArrayme.h"
#include "ExampleWithArraymeObj.h"


typedef std::vector<ExampleWithArraymeData> ExampleWithArraymeDataContainer;
typedef std::deque<ExampleWithArraymeObj*> ExampleWithArraymeObjPointerContainer;

class ExampleWithArraymeCollectionIterator {

  public:
    ExampleWithArraymeCollectionIterator(int index, const ExampleWithArraymeObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const ExampleWithArraymeCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const ExampleWithArrayme operator*() const;
    const ExampleWithArrayme* operator->() const;
    const ExampleWithArraymeCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable ExampleWithArrayme m_object;
    const ExampleWithArraymeObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class ExampleWithArraymeCollection : public podio::CollectionBase {

public:
  typedef const ExampleWithArraymeCollectionIterator const_iterator;

  ExampleWithArraymeCollection();
//  ExampleWithArraymeCollection(const ExampleWithArraymeCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  ExampleWithArraymeCollection(ExampleWithArraymeVector* data, int collectionID);
  ~ExampleWithArraymeCollection();

  void clear() override final;

  /// operator to allow pointer like calling of members a la LCIO  \n     
  ExampleWithArraymeCollection* operator->() { return (ExampleWithArraymeCollection*) this ; }

  /// Append a new object to the collection, and return this object.
  ExampleWithArrayme create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  ExampleWithArrayme create(Args&&... args);
  int size() const;

  /// Returns the const object of given index
  const ExampleWithArrayme operator[](unsigned int index) const;
  /// Returns the object of a given index
  ExampleWithArrayme operator[](unsigned int index);
  /// Returns the const object of given index
  const ExampleWithArrayme at(unsigned int index) const;
  /// Returns the object of given index
  ExampleWithArrayme at(unsigned int index);


  /// Append object to the collection
  void push_back(ConstExampleWithArrayme object);

  void prepareForWrite() override final;
  void prepareAfterRead() override final;
  void setBuffer(void* address) override final;
  bool setReferences(const podio::ICollectionProvider* collectionProvider) override final;

  podio::CollRefCollection* referenceCollections() override final { return &m_refCollections;};

  void setID(unsigned ID) override final {
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](ExampleWithArraymeObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
    );
  };

  bool isValid() const override final {
    return m_isValid;
  }

  // support for the iterator protocol
  const const_iterator begin() const {
    return const_iterator(0, &m_entries);
  }
  const const_iterator end() const {
    return const_iterator(m_entries.size(), &m_entries);
  }

  /// returns the address of the pointer to the data buffer
  void* getBufferAddress() override final { return (void*)&m_data;};

  /// returns the pointer to the data buffer
  std::vector<ExampleWithArraymeData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<NotSoSimpleStruct,arraysize> arrayStruct() const;
  template<size_t arraysize>
  const std::array<std::array<int, 4>,arraysize> myArray() const;
  template<size_t arraysize>
  const std::array<std::array<SimpleStruct, 4>,arraysize> structArray() const;


private:
  bool m_isValid;
  int m_collectionID;
  ExampleWithArraymeObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  ExampleWithArraymeDataContainer* m_data;
};

std::ostream& operator<<( std::ostream& o,const ExampleWithArraymeCollection& v);


template<typename... Args>
ExampleWithArrayme  ExampleWithArraymeCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new ExampleWithArraymeObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return ExampleWithArrayme(obj);
}

template<size_t arraysize>
const std::array<class NotSoSimpleStruct,arraysize> ExampleWithArraymeCollection::arrayStruct() const {
  std::array<class NotSoSimpleStruct,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.arrayStruct;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<class std::array<int, 4>,arraysize> ExampleWithArraymeCollection::myArray() const {
  std::array<class std::array<int, 4>,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.myArray;
 }
 return tmp;
}
template<size_t arraysize>
const std::array<class std::array<SimpleStruct, 4>,arraysize> ExampleWithArraymeCollection::structArray() const {
  std::array<class std::array<SimpleStruct, 4>,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.structArray;
 }
 return tmp;
}


#endif
