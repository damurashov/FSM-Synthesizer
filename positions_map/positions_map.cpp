#include "positions_map.h"

using namespace std;

// ----- Constructors, destructors -----

Positions_Map::Positions_Map() : SIZE(42) {}

Positions_Map::Positions_Map( const string& regexps ) : SIZE(regexps.size()-1) {
    m_positions = new Position*[SIZE];
    for (int i = 1; i < regexps.size(); i++)
        m_positions[i-1] = new Position(regexps[i-1], regexps[i]);
}

Positions_Map::Positions_Map( const Positions_Map& positions_map ) :
    SIZE(positions_map.SIZE) {
    /**/
    m_positions = new Position*[SIZE];
    for (int i = 0; i < SIZE; i++)
        m_positions[i] = new Position(*(positions_map.m_positions[i]));
}

Positions_Map::~Positions_Map() {
    for (int i = 0; i < SIZE; ++i)
        delete m_positions[i];
    delete [] m_positions;
}

// ----- Public methods -----

Positions_Map::Iterator Positions_Map::begin() const {
    return Positions_Map::Iterator(m_positions);
}

Positions_Map::Iterator Positions_Map::end() const {
    return Positions_Map::Iterator(&m_positions[SIZE-1]);
}

unsigned Positions_Map::size() const {
    return SIZE;
}

Position& Positions_Map::operator[]( const unsigned& index ) {
    return *(m_positions[index]);
}
