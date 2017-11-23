#include "positions_map.h"

Positions_Map::Iterator::Iterator() {}
Positions_Map::Iterator::Iterator( Position** pos ) : m_ptr(pos) {}
Positions_Map::Iterator::Iterator( const Positions_Map::Iterator& iterator ) : m_ptr(iterator.m_ptr) {}

Position* Positions_Map::Iterator::operator->() const          { return *m_ptr; }
Position& Positions_Map::Iterator::operator*() const           { return **m_ptr; }
Positions_Map::Iterator Positions_Map::Iterator::operator--()  { m_ptr--; return *this; }
Positions_Map::Iterator Positions_Map::Iterator::operator++()  { m_ptr++; return *this; }

Positions_Map::Iterator Positions_Map::Iterator::operator=( const Positions_Map::Iterator& iterator ) {
    return m_ptr = iterator.m_ptr;
}

bool Positions_Map::Iterator::operator==( const Positions_Map::Iterator& iterator ) const {
    return m_ptr == iterator.m_ptr;
}

bool Positions_Map::Iterator::operator!=( const Positions_Map::Iterator& iterator ) const {
    return m_ptr != iterator.m_ptr;
}
