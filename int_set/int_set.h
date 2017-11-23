#ifndef INT_SET_H
#define INT_SET_H

#ifndef LIST_H
#define LIST_H
#include <list>
#endif /* end of include guard: LIST_H */

using namespace std;

class Int_Set {
private: public:
    list<int> m_integers;
public:
    bool is_empty() const;
    bool has_intersections( const Int_Set& intset ) const;
    bool has_item( const int& item ) const;
    bool operator==( const Int_Set& int_set ) const;
    void append( const Int_Set& int_set );
    void push( const int& in );
    const list<int>& get_integers() const;
    const Int_Set operator=( const Int_Set& int_set );
    Int_Set( const Int_Set& );
    Int_Set();
};

#endif /* end of include guard: INT_SET_H */
