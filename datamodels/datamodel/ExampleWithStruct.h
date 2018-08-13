#ifndef ExampleWithStruct_H
#define ExampleWithStruct_H
#include "NotSoSimpleStruct.h"
#include "ExampleWithStructData.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include "podio/ObjectID.h"

//forward declarations


#include "ExampleWithStructConst.h"
#include "ExampleWithStructObj.h"



class ExampleWithStructCollection;
class ExampleWithStructCollectionIterator;
class ConstExampleWithStruct;

/** @class ExampleWithStruct
 *  Datatype with a struct member
 *  @author: Ali Fatemi
 */
class ExampleWithStruct {

  friend ExampleWithStructCollection;
  friend ExampleWithStructCollectionIterator;
  friend ConstExampleWithStruct;

public:

  /// default constructor
  ExampleWithStruct();
  ExampleWithStruct(NotSoSimpleStruct mystruct);

  /// constructor from existing ExampleWithStructObj
  ExampleWithStruct(ExampleWithStructObj* obj);
  /// copy constructor
  ExampleWithStruct(const ExampleWithStruct& other);
  /// copy-assignment operator
  ExampleWithStruct& operator=(const ExampleWithStruct& other);
  /// support cloning (deep-copy)
  ExampleWithStruct clone() const;
  /// destructor
  ~ExampleWithStruct();

  /// conversion to const object
  operator ConstExampleWithStruct () const;

public:

  /// Access the  component that contains an struct
  const NotSoSimpleStruct& mystruct() const;
  /// Access the member of  component that contains an struct
  const SimpleStruct& data() const;

  /// Get reference to the  component that contains an struct
  NotSoSimpleStruct& mystruct();
  /// Set the  component that contains an struct
  void mystruct(class NotSoSimpleStruct value);
  /// Get reference to the member of  component that contains an struct
  SimpleStruct& data();
  /// Set the  member of  component that contains an struct
  void data(class SimpleStruct value);



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ExampleWithStructObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ExampleWithStruct& other) const {
    return (m_obj==other.m_obj);
  }

  bool operator==(const ConstExampleWithStruct& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ExampleWithStruct& p1,
//       const ExampleWithStruct& p2 );
  bool operator<(const ExampleWithStruct& other) const { return m_obj < other.m_obj  ; }


  unsigned int id() const { return getObjectID().collectionID * 10000000 + getObjectID().index  ;  } 

  const podio::ObjectID getObjectID() const;

private:
  ExampleWithStructObj* m_obj;

};

std::ostream& operator<<( std::ostream& o,const ConstExampleWithStruct& value );




#endif
