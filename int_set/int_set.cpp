#include "int_set.h"

using namespace std;

// ----- Constructors, destructors -----

Int_Set::Int_Set() {}

Int_Set::Int_Set( const Int_Set& intset ) {
    for (auto it = intset.m_integers.begin(); it != intset.m_integers.end(); ++it)
        m_integers.push_back(*it);
}

// ----- Public methods -----

bool Int_Set::is_empty() const {
    return m_integers.empty();
}

bool Int_Set::has_intersections( const Int_Set& intset ) const {
    for (auto it = intset.m_integers.begin(); it != intset.m_integers.end(); ++it)
        if (has_item(*it))
            return true;
    return false;
}

bool Int_Set::has_item( const int& item ) const {
    for (auto it = m_integers.begin(); it != m_integers.end(); ++it)
        if (*it == item)
            return true;
    return false;
}

bool Int_Set::operator==( const Int_Set& intset ) const {
    // Lists' sizes and their contents must be agreed
    bool flag = true;
    if (!(m_integers.size() == intset.m_integers.size()))
        return false;
    for (auto it = intset.m_integers.begin(); it != intset.m_integers.end(); ++it)
        flag *= has_item(*it);
    return flag;
}

void Int_Set::append( const Int_Set& intset ) {
    for (auto it = intset.m_integers.begin(); it != intset.m_integers.end(); ++it)
        if (!has_item(*it))
            m_integers.push_back(*it);
}

void Int_Set::push( const int& item ) {
    if (!has_item(item))
        m_integers.push_back(item);
}

const list<int>& Int_Set::get_integers() const {
    return m_integers;
}

const Int_Set Int_Set::operator=( const Int_Set& intset ) {
    m_integers.assign(intset.m_integers.begin(), intset.m_integers.end());
    return *this;
}
