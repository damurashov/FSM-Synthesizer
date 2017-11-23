
struct Positions_Map::Iterator {
    Position& operator*() const;
    Position* operator->() const;
    Iterator operator--();
    Iterator operator++();
    Iterator operator=( const Iterator& iterator );
    bool operator==( const Iterator& iterator ) const;
    bool operator!=( const Iterator& iterator ) const;
    Iterator();
    Iterator( const Iterator& iter );
    Iterator( Position** pos );
private:
    Position** m_ptr;
};
