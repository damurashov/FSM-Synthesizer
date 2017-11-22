#ifndef CELL_H
#define CELL_H

struct Machine_Matrix::Cell {
    char symbol;
    Int_Set header;
    Int_Set target_state;

    bool operator==( const Cell& cell );
    const Cell operator=( const Cell& cell );
    Cell();
    Cell( const Cell& cell );
    Cell( const char& symbol, const Int_Set& header );
};

#endif /* end of include guard: CELL_H */
