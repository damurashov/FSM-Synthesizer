#include "machine_matrix.h"

// ----- Constructors, destructors -----

Machine_Matrix::Machine_Matrix() :
    m_posmap("Mock string") {}

Machine_Matrix::Machine_Matrix( const Positions_Map& posmap ) :
    m_posmap(posmap) {
    /**/
    // Fill symbols list
    for (auto it = m_posmap.begin(); it != m_posmap.end().next(); ++it) {
        if (!Position::is_special_char(it->right))
            register_symbol(it->right);
            //m_symbols.push_back(it->right);
    }
    // Markup all the key positions
    markup_base_indexes();
    // Markup all the directly following positions
    for (auto it = m_posmap.begin(); it != m_posmap.end().next(); ++it) {
        Position& pos = *it;
        if (!pos.is_end()
            && !pos.get_indexes().is_empty()
            && pos.is_before_left_bracket()) {
            /**/
            Position& next_pos = *(it.next());
            next_pos.add_indexes(pos.get_indexes());
        }
    }
    for (auto it = m_posmap.begin(); it != m_posmap.end().next(); ++it) {
        if (it->is_before_left_bracket())
            markup_inside_brackets(it);
    }
    // Prepare the table for using
    form_table();
}

Machine_Matrix::Machine_Matrix( const Machine_Matrix& machine_matrix ) :
    m_posmap( machine_matrix.m_posmap ),
    m_states( machine_matrix.m_states ),
    m_symbols( machine_matrix.m_symbols ),
    m_cells( machine_matrix.m_cells ) {
    /**/
    markup_base_indexes();
    // Markup all the directly following positions
    for (auto it = m_posmap.begin(); it != m_posmap.end().next(); ++it) {
        Position& pos = *it;
        if (!pos.is_end()
            && !pos.get_indexes().is_empty()
            && pos.is_before_left_bracket()) {
            /**/
            Position& next_pos = *(it.next());
            next_pos.add_indexes(pos.get_indexes());
        }
    }
    for (auto it = m_posmap.begin(); it != m_posmap.end().next(); ++it) {
        if (it->is_before_left_bracket())
            markup_inside_brackets(it);
    }
    form_table();
}

// ----- Public methods -----

const Int_Set& Machine_Matrix::get_cell( const char& symbol, const Int_Set& state_from ) const {
    for (auto it = m_cells.begin(); it != m_cells.end(); ++it)
        if (it->symbol == symbol && it->header == state_from)
            return it->target_state;
    return Int_Set::Int_Set();
}

const list<Int_Set>& Machine_Matrix::get_states() const {
    return m_states;
}

const list<char>& Machine_Matrix::get_symbols() const {
    return m_symbols;
}

// ----- Private methods -----

void Machine_Matrix::register_symbol( const char& symbol ) {
    bool f_already_registered = false;
    for (auto it = m_symbols.begin(); it != m_symbols.end(); ++it) {
        if (symbol == *it)
            f_already_registered = true;
    }
    if (!f_already_registered)
        m_symbols.push_back(symbol);
}

void Machine_Matrix::register_state( const Int_Set& state ) {
    bool f_already_registered = false;

    for (auto it = m_states.begin(); it != m_states.end(); ++it) {
        if (state == *it) {
            f_already_registered = true;
            break;
        }
    }
    if (!f_already_registered)
        m_states.push_back(state);
}

bool Machine_Matrix::is_inside_nested_brackets( const Positions_Map::Iterator& it_pos_lbr,
    const Positions_Map::Iterator& it_pos ) {
    /**/
    int nesting_level = 0;
    for (auto it = it_pos_lbr; it != it_pos.next(); ++it) {
        if (it->is_before_left_bracket() && (it != it_pos_lbr) && (it != it_pos))
            nesting_level++;
        if (it->is_after_right_bracket() && (it != it_pos_lbr))
            nesting_level--;
    }
    return (nesting_level > 0);
}

Positions_Map::Iterator Machine_Matrix::seek_right_bracket( const Positions_Map::Iterator& it_l ) {
    int rbr_to_skip = 0; // Is being used to handle nested brackets case
    auto it_r = it_l;

    // Look for the post-right-bracket position
    //it_r++;
    for (; it_r != m_posmap.end().next(); ++it_r) {
        Position& rpos = *it_r;
        if (rpos.is_after_right_bracket() && (it_r != it_l)) {
            rbr_to_skip--;
            if (rbr_to_skip == 0)
                break;
        }
        if (rpos.is_before_left_bracket()) {
            rbr_to_skip++;
        }
    }
    return it_r;

}

Int_Set& Machine_Matrix::at_cell( const char& symbol, const Int_Set& header ) {
    for (auto it = m_cells.begin(); it != m_cells.end(); ++it)
        if (it->symbol == symbol && it->header == header)
            return it->target_state;
    // When nothing was found:
    m_cells.push_back(Machine_Matrix::Cell(symbol, header));
    return m_cells.back().target_state;
}

void Machine_Matrix::markup_base_indexes() {
    int counter = 1;
    for (auto it = m_posmap.begin(); it != m_posmap.end().next(); ++it) {
        Position& pos = *it;
        if (pos.is_start())
            pos.add_index(0);
        else if (pos.is_base())
            pos.add_index(counter++);
    }
}

void Machine_Matrix::markup_inside_brackets( const Positions_Map::Iterator& it_l ) {
    Position& lpos = *it_l;
    auto it_r = seek_right_bracket(it_l);
    Position& rpos = *it_r;
    //Position& rpos = *(seek_right_bracket(it_l));

    // Pre-left-bracket to pre-term (post-right-iter-bracket)
    if (lpos.is_before_left_iter_bracket())
        rpos.add_indexes(lpos.get_indexes());
    for (auto it = it_l.next(); it != it_r.next(); ++it) {
        Position& pos = *it;
        if (!is_inside_nested_brackets(it_l, it) && pos.is_before_term())
            pos.add_indexes(lpos.get_indexes());
    }

    // Post-term to post-right-bracket
    for (auto it = it_l.next(); it != it_r.next(); ++it) {
        Position& pos = *it;
        if (!is_inside_nested_brackets(it_l, it) && pos.is_after_term())
            rpos.add_indexes(pos.get_indexes());
    }

    // Post-right-iter-bracket to pre-term
    if (rpos.is_after_right_iter_bracket()) {
        for (auto it = it_l.next(); it != it_r.next(); ++it) {
            Position& pos = *it;
            if (!is_inside_nested_brackets(it_l, it) && pos.is_before_term())
                pos.add_indexes(rpos.get_indexes());
        }
    }

}

void Machine_Matrix::form_table() {
    m_states.push_back(Int_Set::Int_Set());
    m_states.back().push(0);
    for (auto it_states = m_states.begin(); it_states != m_states.end(); ++it_states) {
        for (auto it_symbols = m_symbols.begin(); it_symbols != m_symbols.end(); ++it_symbols ) {
            for (auto it_prebase = m_posmap.begin(); it_prebase != m_posmap.end().next(); ++it_prebase) {
                if (it_prebase->right == *it_symbols) {
                    auto it_base = it_prebase;
                    it_base++;
                    if (it_prebase->get_indexes().has_intersections(*it_states))
                        at_cell(*it_symbols, *it_states).append(it_base->get_indexes());
                }
            }
            register_state(at_cell(*it_symbols, *it_states));
        }
    }

}
