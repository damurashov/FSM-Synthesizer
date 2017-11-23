#ifndef MACHINE_MATRIX_H
#define MACHINE_MATRIX_H

#include "positions_map.h"

using namespace std;

class Machine_Matrix {
private: public:
    struct Cell;

    Positions_Map m_posmap;
    list<Int_Set> m_states;
    list<char>    m_symbols;
    list<Cell>    m_cells;

    void markup_base_indexes();
    void markup_inside_brackets( const Positions_Map::Iterator& iter_left_bracket );
    void form_table();
    void register_state( const Int_Set& state );
    Positions_Map::Iterator seek_right_bracket( const Positions_Map::Iterator& iter_left_bracket );
    bool is_inside_nested_brackets( const Positions_Map::Iterator& iter_left_outer_bracket,
        const Positions_Map::Iterator& iter_position );
    Int_Set& at_cell( const char& symbol, const Int_Set& header );
    Machine_Matrix();
public:
    Machine_Matrix( const Machine_Matrix& machine_matrix );
    Machine_Matrix( const Positions_Map& positions_map );
    const Machine_Matrix operator=( const Machine_Matrix& machine_matrix );
    const Int_Set& get_cell( const char& symbol, const Int_Set& state_from ) const;
    const list<Int_Set>& get_states() const;
    const list<char>& get_symbols() const;
};

// ----- Inner Classifiers -----
#include "cell.h"

#endif /* end of include guard: MACHINE_MATRIX_H */
