//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef ExampleWithStructCollection_H
#define  ExampleWithStructCollection_H

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
#include "ExampleWithStructData.h"
#include "ExampleWithStruct.h"
#include "ExampleWithStructObj.h"


typedef std::vector<ExampleWithStructData> ExampleWithStructDataContainer;
typedef std::deque<ExampleWithStructObj*> ExampleWithStructObjPointerContainer;

class ExampleWithStructCollectionIterator {

  public:
    ExampleWithStructCollectionIterator(int index, const ExampleWithStructObjPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const ExampleWithStructCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const ExampleWithStruct operator*() const;
    const ExampleWithStruct* operator->() const;
    const ExampleWithStructCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable ExampleWithStruct m_object;
    const ExampleWithStructObjPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class ExampleWithStructCollection : public podio::CollectionBase {

public:
  typedef const ExampleWithStructCollectionIterator const_iterator;

  ExampleWithStructCollection();
//  ExampleWithStructCollection(const ExampleWithStructCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  ExampleWithStructCollection(ExampleWithStructVector* data, int collectionID);
  ~ExampleWithStructCollection();

  void clear() override final;

  /// operator to allow pointer like calling of members a la LCIO  \n     
  ExampleWithStructCollection* operator->() { return (ExampleWithStructCollection*) this ; }

  /// Append a new object to the collection, and return this object.
  ExampleWithStruct create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  ExampleWithStruct create(Args&&... args);
  int size() const;

  /// Returns the const object of given index
  const ExampleWithStruct operator[](unsigned int index) const;
  /// Returns the object of a given index
  ExampleWithStruct operator[](unsigned int index);
  /// Returns the const object of given index
  const ExampleWithStruct at(unsigned int index) const;
  /// Returns the object of given index
  ExampleWithStruct at(unsigned int index);


  /// Append object to the collection
  void push_back(ConstExampleWithStruct object);

  void prepareForWrite() override final;
  void prepareAfterRead() override final;
  void setBuffer(void* address) override final;
  bool setReferences(const podio::ICollectionProvider* collectionProvider) override final;

  podio::CollRefCollection* referenceCollections() override final { return &m_refCollections;};

  void setID(unsigned ID) override final {
    m_collectionID = ID;
    std::for_each(m_entries.begin(),m_entries.end(),
                 [ID](ExampleWithStructObj* obj){obj->id = {obj->id.index,static_cast<int>(ID)}; }
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
  std::vector<ExampleWithStructData>* _getBuffer() { return m_data;};

    template<size_t arraysize>
  const std::array<NotSoSimpleStruct,arraysize> mystruct() const;


private:
  bool m_isValid;
  int m_collectionID;
  ExampleWithStructObjPointerContainer m_entries;
  // members to handle 1-to-N-relations

  // members to handle streaming
  podio::CollRefCollection m_refCollections;
  ExampleWithStructDataContainer* m_data;
};

std::ostream& operator<<( std::ostream& o,const ExampleWithStructCollection& v);


template<typename... Args>
ExampleWithStruct  ExampleWithStructCollection::create(Args&&... args){
  int size = m_entries.size();
  auto obj = new ExampleWithStructObj({size,m_collectionID},{args...});
  m_entries.push_back(obj);
  return ExampleWithStruct(obj);
}

template<size_t arraysize>
const std::array<class NotSoSimpleStruct,arraysize> ExampleWithStructCollection::mystruct() const {
  std::array<class NotSoSimpleStruct,arraysize> tmp;
  auto valid_size = std::min(arraysize,m_entries.size());
  for (unsigned i = 0; i<valid_size; ++i){
    tmp[i] = m_entries[i]->data.mystruct;
 }
 return tmp;
}


#endif
