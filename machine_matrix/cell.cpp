#include "machine_matrix.h"

// typedef Machine_Matrix::Cell Machine_Matrix::Cell;

Machine_Matrix::Cell::Cell() {}

Machine_Matrix::Cell::Cell( const Cell& cell ) :
    symbol( cell.symbol ),
    header( cell.header ),
    target_state( cell.target_state ) {}

Machine_Matrix::Cell::Cell( const char& smbl, const Int_Set& hdr ) :
    symbol(smbl),
    header(hdr) {}

const Machine_Matrix::Cell Machine_Matrix::Cell::operator=( const Cell& cell ) {
    symbol = cell.symbol;
    header = cell.header;
    target_state = cell.target_state;
    return *this;
}

bool Machine_Matrix::Cell::operator==( const Cell& cell ) {
    return ((symbol == cell.symbol) && (header == cell.header));
}
