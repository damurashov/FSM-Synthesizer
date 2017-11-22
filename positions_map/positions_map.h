#ifndef POSITIONS_MAP_H
#define POSITIONS_MAP_H

using namespace std;

#ifndef STRING_H
#define STRING_H
#include <string>
#endif /* end of include guard: STRING_H */


#include "position.h"

class Positions_Map {
private: 
    const unsigned SIZE;
    Position** m_positions;
    Positions_Map();
public:
    typedef Position *const Iterator;

    Iterator begin() const;
    Iterator end() const;
    unsigned size() const;
    Position& operator[]( const unsigned& pos );
    Positions_Map( const string& regexps );
    Positions_Map( const Positions_Map& positions_map );
    ~Positions_Map();
};

#endif /* end of include guard: POSITIONS_MAP_H */
