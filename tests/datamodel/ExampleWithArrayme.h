#ifndef ExampleWithArrayme_H
#define ExampleWithArrayme_H
#include "SimpleStruct.h"

#include <array>
#include "NotSoSimpleStruct.h"
#include "ExampleWithArraymeData.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include "podio/ObjectID.h"

//forward declarations


#include "ExampleWithArraymeConst.h"
#include "ExampleWithArraymeObj.h"



class ExampleWithArraymeCollection;
class ExampleWithArraymeCollectionIterator;
class ConstExampleWithArrayme;

/** @class ExampleWithArrayme
 *  Datatype with an array member
 *  @author: Ali Fatemi
 */
class ExampleWithArrayme {

  friend ExampleWithArraymeCollection;
  friend ExampleWithArraymeCollectionIterator;
  friend ConstExampleWithArrayme;

public:

  /// default constructor
  ExampleWithArrayme();
  ExampleWithArrayme(NotSoSimpleStruct arrayStruct,std::array<int, 4> myArray,std::array<SimpleStruct, 4> structArray);

  /// constructor from existing ExampleWithArraymeObj
  ExampleWithArrayme(ExampleWithArraymeObj* obj);
  /// copy constructor
  ExampleWithArrayme(const ExampleWithArrayme& other);
  /// copy-assignment operator
  ExampleWithArrayme& operator=(const ExampleWithArrayme& other);
  /// support cloning (deep-copy)
  ExampleWithArrayme clone() const;
  /// destructor
  ~ExampleWithArrayme();

  /// conversion to const object
  operator ConstExampleWithArrayme () const;

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

  /// Get reference to the  component that contains an array
  NotSoSimpleStruct& arrayStruct();
  /// Set the  component that contains an array
  void arrayStruct(class NotSoSimpleStruct value);
  /// Get reference to the member of  component that contains an array
  SimpleStruct& data();
  /// Set the  member of  component that contains an array
  void data(class SimpleStruct value);
  /// Set the array-member without space to test regex
  void myArray(std::array<int, 4> value);

  /// Set item i in array-member without space to test regex
  void myArray(size_t i, int value);

  /// Set the an array containing structs
  void structArray(std::array<SimpleStruct, 4> value);

  /// Set item i in an array containing structs
  void structArray(size_t i, SimpleStruct value);




  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ExampleWithArraymeObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ExampleWithArrayme& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstExampleWithArrayme& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ExampleWithArrayme& p1,
//       const ExampleWithArrayme& p2 );
  bool operator<(const ExampleWithArrayme& other) const { return m_obj < other.m_obj  ; }


  unsigned int id() const { return getObjectID().collectionID * 10000000 + getObjectID().index  ;  } 

  const podio::ObjectID getObjectID() const;

private:
  ExampleWithArraymeObj* m_obj;

};

std::ostream& operator<<( std::ostream& o,const ConstExampleWithArrayme& value );




#endif
