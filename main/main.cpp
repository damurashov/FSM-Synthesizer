#include "machine_matrix.h"
#include <fstream>
#include <iostream>

using namespace std;

const string& get_input() {
    std::ifstream input_file("INPUT", std::ios::in);
    static std::string line;
    std::getline(input_file, line);
    input_file.close();
    return line;
}

void print_intro() {
    cout << "Finite State Machine Synthesizer" << endl;
    cout << "St. Petersburg, SUAI, 2017" << endl << endl;
}

void print_state(const Int_Set& state) {
    const list<int>& listint = state.get_integers();
    for (auto it = listint.begin(); it != listint.end(); ++it)
        cout << *it;
}

int main() {
    Positions_Map posmap(get_input());
    Machine_Matrix matrix(posmap);
    const list<Int_Set>& states = matrix.get_states();
    const list<char>& symbols = matrix.get_symbols();

    print_intro();
    cout << '\t';
    // Headers
    for (auto it = states.begin(); it != states.end(); ++it) {
        print_state(*it);
        cout << '\t';
    }
    cout << endl;
    // Table content
    for (auto it = symbols.begin(); it != symbols.end(); ++it) {
        cout << *it << '\t';
        for (auto init = states.begin(); init != states.end(); ++init) {
            print_state(matrix.get_cell(*it,*init));
            cout << '\t';
        }
        cout << endl;
    }
}
