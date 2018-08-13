#ifndef ConstExampleWithArrayme_H
#define ConstExampleWithArrayme_H
#include "SimpleStruct.h"

#include <array>
#include "NotSoSimpleStruct.h"
#include "ExampleWithArraymeData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "ExampleWithArraymeObj.h"



class ExampleWithArraymeObj;
class ExampleWithArrayme;
class ExampleWithArraymeCollection;
class ExampleWithArraymeCollectionIterator;

/** @class ConstExampleWithArrayme
 *  Datatype with an array member
 *  @author: Ali Fatemi
 */

class ConstExampleWithArrayme {

  friend ExampleWithArrayme;
  friend ExampleWithArraymeCollection;
  friend ExampleWithArraymeCollectionIterator;

public:

  /// default constructor
  ConstExampleWithArrayme();
  ConstExampleWithArrayme(NotSoSimpleStruct arrayStruct,std::array<int, 4> myArray,std::array<SimpleStruct, 4> structArray);

  /// constructor from existing ExampleWithArraymeObj
  ConstExampleWithArrayme(ExampleWithArraymeObj* obj);
  /// copy constructor
  ConstExampleWithArrayme(const ConstExampleWithArrayme& other);
  /// copy-assignment operator
  ConstExampleWithArrayme& operator=(const ConstExampleWithArrayme& other);
  /// support cloning (deep-copy)
  ConstExampleWithArrayme clone() const;
  /// destructor
  ~ConstExampleWithArrayme();


public:

  /// Access the  component that contains an array
  const NotSoSimpleStruct& arrayStruct() const;
  /// Access the member of  component that contains an array
  const SimpleStruct& data() const;
  /// Access the array-member without space to test regex
  const std::array<int, 4>& myArray() const;
  /// Access item i in the array-member without space to test regex
  const int& myArray(size_t i) const;
  /// Access the an array containing structs
  const std::array<SimpleStruct, 4>& structArray() const;
  /// Access item i in the an array containing structs
  const SimpleStruct& structArray(size_t i) const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ExampleWithArraymeObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstExampleWithArrayme& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ExampleWithArrayme& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ExampleWithArrayme& p1,
//       const ExampleWithArrayme& p2 );
  bool operator<(const ConstExampleWithArrayme& other) const { return m_obj < other.m_obj  ; }

  unsigned int id() const { return getObjectID().collectionID * 10000000 + getObjectID().index  ;  } 

  const podio::ObjectID getObjectID() const;

private:
  ExampleWithArraymeObj* m_obj;

};


#endif
