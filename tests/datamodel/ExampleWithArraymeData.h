#ifndef ExampleWithArraymeDATA_H
#define ExampleWithArraymeDATA_H

#include "SimpleStruct.h"

#include <array>
#include "NotSoSimpleStruct.h"


/** @class ExampleWithArraymeData
 *  Datatype with an array member
 *  @author: Ali Fatemi
 */

class ExampleWithArraymeData {
public:
  NotSoSimpleStruct arrayStruct;  ///< component that contains an array
  std::array<int, 4> myArray;  ///<array-member without space to test regex
  std::array<SimpleStruct, 4> structArray;  ///<an array containing structs
};


#endif
