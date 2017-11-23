#include "position.h"


// ----- Static members -----
const char Position::MOCK = '_';
const char* Position::SPECIAL_CHARS = "_<>()|\t";

// ----- Constructors, destructors -----

Position::Position() : left(MOCK), right(MOCK) {}

Position::Position( const char& l, const char& r ) :
    left(l),
    right(r) {
    /**/
    f_before_left_bracket      = (right=='(' || right=='<')                         ? true : false;
    f_before_left_iter_bracket = (right == '<')                                     ? true : false;
    f_after_right_bracket      = (left == ')' || left == '>')                       ? true : false;
    f_after_right_iter_bracket = (left == '>')                                      ? true : false;
    f_before_term              = (is_special_char(left) && !is_special_char(right)) ? true : false;
    f_after_term               = (!is_special_char(left) && is_special_char(right)) ? true : false;
    f_prebase                  = (!is_special_char(right))                          ? true : false;
    f_base                     = (!is_special_char(left))                           ? true : false;
    f_start                    = (left == MOCK)                                     ? true : false;
    f_end                      = (right == MOCK)                                    ? true : false;
}

Position::Position( const Position& position ) :
    left(position.left),
    right(position.right) {
    /**/
    m_indexes                  = position.m_indexes;
    f_before_left_bracket      = position.f_before_left_bracket;
    f_before_left_iter_bracket = position.f_before_left_iter_bracket;
    f_after_right_bracket      = position.f_after_right_bracket;
    f_after_right_iter_bracket = position.f_after_right_iter_bracket;
    f_before_term              = position.f_before_term;
    f_after_term               = position.f_after_term;
    f_prebase                  = position.f_prebase;
    f_base                     = position.f_base;
    f_start                    = position.f_start;
    f_end                      = position.f_end;
}

// ----- Public mehods -----

void Position::add_index( const unsigned& index )  { m_indexes.push(index); }
void Position::add_indexes(const Int_Set& indexes) { m_indexes.append(indexes); }
const Int_Set& Position::get_indexes()       const { return m_indexes; }
bool Position::is_before_left_bracket()      const { return f_before_left_bracket; }
bool Position::is_before_left_iter_bracket() const { return f_before_left_iter_bracket; }
bool Position::is_after_right_bracket()      const { return f_after_right_bracket; }
bool Position::is_after_right_iter_bracket() const { return f_after_right_iter_bracket; }
bool Position::is_before_term()              const { return f_before_term; }
bool Position::is_after_term()               const { return f_after_term; }
bool Position::is_prebase()                  const { return f_prebase; }
bool Position::is_base()                     const { return f_base; }
bool Position::is_start()                    const { return f_start; }
bool Position::is_end()                      const { return f_end; }

bool Position::is_special_char( const char& symbol ) {
    for (auto it = &SPECIAL_CHARS[0]; *it != '\t'; ++it) {
        if (symbol == *it)
            return true;
    }
    return false;
}
