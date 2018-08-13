#ifndef SimpleStruct_H
#define SimpleStruct_H


#include <iostream>


class SimpleStruct {
public:
  int x;
  int y;

 SimpleStruct() : x(0),y(0) {} SimpleStruct( const int* v) : x(v[0]),y(v[1]) {} 
};

inline std::ostream& operator<<( std::ostream& o,const SimpleStruct& value ){ 
  o << value.x << " " ;
  o << value.y << " " ;
  return o ;
}




#endif
