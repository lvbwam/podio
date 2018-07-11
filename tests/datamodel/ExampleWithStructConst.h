#ifndef ConstExampleWithStruct_H
#define ConstExampleWithStruct_H
#include "NotSoSimpleStruct.h"
#include "ExampleWithStructData.h"
#include <vector>
#include "podio/ObjectID.h"

//forward declarations


#include "ExampleWithStructObj.h"



class ExampleWithStructObj;
class ExampleWithStruct;
class ExampleWithStructCollection;
class ExampleWithStructCollectionIterator;

/** @class ConstExampleWithStruct
 *  Datatype with a struct member
 *  @author: Ali Fatemi
 */

class ConstExampleWithStruct {

  friend ExampleWithStruct;
  friend ExampleWithStructCollection;
  friend ExampleWithStructCollectionIterator;

public:

  /// default constructor
  ConstExampleWithStruct();
  ConstExampleWithStruct(NotSoSimpleStruct mystruct);

  /// constructor from existing ExampleWithStructObj
  ConstExampleWithStruct(ExampleWithStructObj* obj);
  /// copy constructor
  ConstExampleWithStruct(const ConstExampleWithStruct& other);
  /// copy-assignment operator
  ConstExampleWithStruct& operator=(const ConstExampleWithStruct& other);
  /// support cloning (deep-copy)
  ConstExampleWithStruct clone() const;
  /// destructor
  ~ConstExampleWithStruct();


public:

  /// Access the  component that contains an struct
  const NotSoSimpleStruct& mystruct() const;
  /// Access the member of  component that contains an struct
  const SimpleStruct& data() const;



  /// check whether the object is actually available
  bool isAvailable() const;
  /// disconnect from ExampleWithStructObj instance
  void unlink(){m_obj = nullptr;}

  bool operator==(const ConstExampleWithStruct& other) const {
       return (m_obj==other.m_obj);
  }

  bool operator==(const ExampleWithStruct& other) const;

// less comparison operator, so that objects can be e.g. stored in sets.
//  friend bool operator< (const ExampleWithStruct& p1,
//       const ExampleWithStruct& p2 );
  bool operator<(const ConstExampleWithStruct& other) const { return m_obj < other.m_obj  ; }

  unsigned int id() const { return getObjectID().collectionID * 10000000 + getObjectID().index  ;  } 

  const podio::ObjectID getObjectID() const;

private:
  ExampleWithStructObj* m_obj;

};


#endif
