#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <map>
#include <set>
#include <algorithm>

using namespace std;


/***************************************************************/
/*********************** OUTPUT FORMATTING *********************/
/***************************************************************/
string bold(string str) {
    return "\033[1m" + str + "\033[0m";
}

string underline(string str) {
    return "\033[4m" + str + "\033[0m";
}

string red(string str) {
    return "\033[31m" + str + "\033[0m";
}

string green(string str) {
    return "\033[32m" + str + "\033[0m";
}

string cyan(string str) {
    return "\033[36m" + str + "\033[0m";
}

/*****************************************************************/
/************************ HELPER FUNCTIONS ***********************/
/*****************************************************************/
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

/*****************************************************************/
/************************ INPUT FUNCTIONS ************************/
/*****************************************************************/
int take_valid_int_input(string prompt, int min_val = 1, int max_val = INT_MAX) {
    int num;
    string input;
    while(true) {
        cout << prompt;
        cin >> input;
        if (input.size() == 0) {}
        else if (input.find_first_not_of("0123456789") != string::npos) {}
        else if ((num = stoi(input)) >= min_val && num <= max_val) {
            return num;
        }
        cout << red("Error: Invalid input.") << endl;
    }
}

char take_valid_char_input(string prompt) {
    char c;
    string input;
    while(true) {
        cout << prompt;
        cin >> input;
        if (input.size() == 1) {
            return input[0];
        }
        cout << red("Error: Invalid input.") << endl;
    }
}

string take_valid_string_input(string prompt) {
    string input;
    while(true) {
        cout << prompt;
        cin >> input;
        if (input.size() > 0) {
            return input;
        }
        cout << red("Error: Invalid input.") << endl;
    }
}

/*****************************************************************/
/************************ TURING MACHINE *************************/
/*****************************************************************/
class TuringMachine {

    private:
        /***************** Turing Machine specifications *****************/
        set<string> states;
        string initial_state;
        set<char> input_symbols, tape_symbols;
        map<tuple<string, char>, tuple<string, char, char>> transitions;
        set<char> valid_actions = {'L', 'R', 'Y', 'N'};

        /***************** Functions to check validity of TM specs input *****************/
        bool check_valid_state(string state) {
            bool is_valid_string = (state.size() > 0);
            bool is_not_duplicate = (this->states.find(state) == this->states.end());
            return is_valid_string && is_not_duplicate;
        }

        bool check_valid_symbol(char symbol, set<char> symbol_set) {
            bool is_not_duplicate = (symbol_set.find(symbol) == symbol_set.end());
            return is_not_duplicate;
        }

        bool check_valid_tape_symbol_set() {
            for (char input_symbol : input_symbols) {
                if (this->tape_symbols.find(input_symbol) == this->tape_symbols.end()) {
                    return false;
                }
            }
            return true;
        }

        bool check_valid_transition(string transition) {
            string temp_trans = "" + transition;
            
            size_t comma1 = temp_trans.find(',');
            size_t comma2 = temp_trans.find(',', comma1 + 1);
            size_t openParen = temp_trans.find('(');
            size_t closeParen = temp_trans.find(')');

            if (comma1 == string::npos || comma2 == string::npos || openParen == string::npos || closeParen == string::npos) {
                return false;
            }

            string state = trim_copy(temp_trans.substr(openParen + 1, comma1 - openParen - 1));
            char write_symbol = trim_copy(temp_trans.substr(comma1 + 1, comma2 - comma1 - 1))[0];
            char action = toupper(trim_copy(temp_trans.substr(comma2 + 1, closeParen - comma2 - 1))[0]);

            bool is_valid_action = (this->valid_actions.find(action) != this->valid_actions.end());
            bool is_valid_write_symbol = (this->tape_symbols.find(write_symbol) != this->tape_symbols.end());
            bool is_valid_state = (this->states.find(state) != this->states.end());

            return is_valid_action && is_valid_write_symbol && is_valid_state;
        }

        bool check_valid_tape(string tape) {
            for (int i = 0; i < tape.size(); i++) {
                if (this->tape_symbols.find(tape[i]) == this->tape_symbols.end()) {
                    return false;
                }
            }
            return true;
        }

    public:
        /************************* Getters *************************/
        set<string> get_states() {
            return states;
        }

        string get_initial_state() {
            return initial_state;
        }

        set<char> get_input_symbols() {
            return input_symbols;
        }

        set<char> get_tape_symbols() {
            return tape_symbols;
        }

        map<tuple<string, char>, tuple<string, char, char>> get_transitions() {
            return transitions;
        }

        // This function takes Turing Machine specifications as input from the user
        void get_TM_specs_from_user() {
            // Read states
            int n_states = take_valid_int_input(bold("Enter number of states: "));
            for (int i = 0; i < n_states; i++) {
                string prompt = "Enter state " + to_string(i + 1) + "/" + to_string(n_states) + ": ";
                string state = take_valid_string_input(prompt);
                if (check_valid_state(state)) {
                    this->states.insert(state);
                } else {
                    cout << red("Error: Invalid state.") << endl;
                    i--;
                }
            }
            
            // Read input symbols
            cout << "==================================\n";
            int n_ipsymbols = take_valid_int_input(bold("Enter number of input symbols: "));
            for (int i = 0; i < n_ipsymbols; i++) {
                char input_symbol = take_valid_char_input("Enter input symbol " + to_string(i + 1) + "/" + to_string(n_ipsymbols) + ": ");
                if (check_valid_symbol(input_symbol, input_symbols)) {
                    input_symbols.insert(input_symbol);
                } else {
                    cout << red("Error: Invalid input symbol.") << endl;
                    i--;
                }
            }
            
            // Read tape symbols
            cout << "==================================\n" << cyan("Note: Tape symbols must include input symbols.") << endl;
            int n_tsymbols = take_valid_int_input(bold("Enter number of tape symbols: "), n_ipsymbols, INT_MAX);
            while(true) {
                for (int i = 0; i < n_tsymbols; i++) {
                    char tape_symbol = take_valid_char_input("Enter tape symbol " + to_string(i + 1) + "/" + to_string(n_tsymbols) + ": ");
                    if (check_valid_symbol(tape_symbol, this->tape_symbols)) {
                        this->tape_symbols.insert(tape_symbol);
                    } else {
                        cout << red("Error: Invalid tape symbol.") << endl;
                        i--;
                    }
                }
                if (check_valid_tape_symbol_set())
                    break;
                cout << red("Error: Input symbols must be a subset of tape symbols.") << endl;
                this->tape_symbols.clear();
            }
            
            char left_mark;
            while(true) {
                left_mark = take_valid_char_input("Add transition for left mark \'<\'? (y/n): ");
                if (left_mark == 'y') {
                    this->tape_symbols.insert('<');
                    n_tsymbols++;
                    break;
                } else if (left_mark == 'n') {
                    break;
                }
                cout << red("Error: Invalid input.") << endl;
            }

            // Read initial state
            cout << "==================================\n";
            while(true) {
                initial_state = take_valid_string_input(bold("Enter initial state: "));
                if (this->states.find(initial_state) != this->states.end()) {
                    break;
                }
                cout << red("Error: Unrecognized state.") << endl;
            }
            
            
            // Read transitions
            cout << "==================================\n" << cyan("Note: Transitions must be in the format (state,tapeSymbol) -> (nextState,writeSymbol,move) without spaces") << endl;
            int n_transitions = n_states * n_tsymbols;
            vector<char> tape_symbols_vec(this->tape_symbols.begin(), this->tape_symbols.end());
            cout << bold(underline("State transitions:")) << endl;
            for (string state : this->states) {
                for (int i = 0; i < n_tsymbols; i++) {
                    char tape_symbol = tape_symbols_vec[i];
                    string prompt = "(" + state + "," + tape_symbol + ") -> ";
                    string transition = take_valid_string_input(prompt);
                    if (check_valid_transition(transition)) {
                        size_t comma1 = transition.find(',');
                        size_t comma2 = transition.find(',', comma1 + 1);
                        size_t openParen = transition.find('(');
                        size_t closeParen = transition.find(')');

                        string next_state = trim_copy(transition.substr(openParen + 1, comma1 - openParen - 1));
                        char write_symbol = trim_copy(transition.substr(comma1 + 1, comma2 - comma1 - 1))[0];
                        char action = toupper(trim_copy(transition.substr(comma2 + 1, closeParen - comma2 - 1))[0]);

                        transitions[make_tuple(state, tape_symbol)] = make_tuple(next_state, write_symbol, action);
                    } else {
                        cout << red("Error: Invalid transition.") << endl;
                        i--;
                    }
                }
            }
        }

        // This function prints the Turing Machine specifications to the console
        void print_TM_specs() {
            cout << "==================================\n";
            cout << bold(underline("Turing Machine specifications:")) << endl;
            // cout << bold("M = (K, Σ, Γ, δ, S)") << endl;
            // cout << bold("K = {");
            cout << bold("States = {");
            if (!this->states.empty()) {
                auto it = this->states.begin();
                cout << *it;
                ++it;
                for (; it != this->states.end(); ++it) {
                    cout << ", " << *it;
                }
            }
            cout << "}" << endl;

            // cout << bold("Σ = {");
            cout << bold("Input symbols = {");
            if (!this->input_symbols.empty()) {
                auto it = this->input_symbols.begin();
                cout << *it;
                ++it;
                for (; it != this->input_symbols.end(); ++it) {
                    cout << ", " << *it;
                }
            }
            cout << "}" << endl;

            // cout << bold("Γ = {");
            cout << bold("Tape symbols = {");
            if (!this->tape_symbols.empty()) {
                auto it = this->tape_symbols.begin();
                cout << *it;
                ++it;
                for (; it != this->tape_symbols.end(); ++it) {
                    cout << ", " << *it;
                }
            }
            cout << "}" << endl;

            // cout << bold("S = ") << this->initial_state << endl;
            cout << bold("Initial state = ") << this->initial_state << endl;

            // cout << bold("δ = (") << endl;
            cout << bold("Transitions = (") << endl;
            for (auto transition : this->transitions) {
                string state = get<0>(transition.first);
                char tape_symbol = get<1>(transition.first);
                string next_state = get<0>(transition.second);
                char write_symbol = get<1>(transition.second);
                char action = get<2>(transition.second);

                cout << "(" << state << "," << tape_symbol << ") , (" << next_state << "," << write_symbol << "," << action << ")" << endl;
            }
            cout << ")" << endl << endl;
        }

        // This function takes input tape and head position from the user
        pair<string, int> get_input_tape() {
            cout << cyan("Note: Enter tape without spaces.") << endl;
            string tape;
            while (true) {
                tape = take_valid_string_input(bold("Tape: ") + "<");
                if (check_valid_tape(tape)) {
                    break;
                }
                cout << red("Error: Invalid tape.") << endl;
            }
            tape = "<" + tape;

            cout << cyan("Note: Left mark is at position 0. Your string probably starts at position 1") << endl;
            int head_pos = take_valid_int_input(bold("Enter initial head position: "), 0);
            if (head_pos >= tape.size()) {
                tape += string(head_pos - tape.size() + 1, '#');
            }
            return make_pair(tape, head_pos);
        }

        // This function prints the tape with the head position
        void print_tape(string tape, int head_pos) {
            for (int i = 0; i < tape.size(); i++) {
                if (i == head_pos) {
                    cout << bold(underline(string(1, tape[i])));
                } else {
                    cout << tape[i];
                }
            }
            cout << "####...";
        }

        // This function runs the Turing Machine on the input tape, prints the steps and the final tape
        void run_TM(string tape, int head_pos) {
            string state = this->initial_state;
            cout << "==================================\n";
            cout << bold("Running Turing Machine...") << endl;
            while (true) {
                char tape_symbol = tape[head_pos];
                if (this->transitions.find(make_tuple(state, tape_symbol)) == this->transitions.end()) {
                    cout << red("Error: No transition found for state " + state + " and symbol " + tape_symbol) << endl;
                    break;
                }

                cout << "--> (" << state << ", ";
                print_tape(tape, head_pos);
                cout << ")" << endl;

                tuple<string, char, char> transition = this->transitions[make_tuple(state, tape_symbol)];
                string next_state = get<0>(transition);
                char write_symbol = get<1>(transition);
                char action = get<2>(transition);

                tape[head_pos] = write_symbol;
                if (action == 'L') {
                    head_pos--;
                } else if (action == 'R' ) {
                    head_pos++;
                } else if (action == 'Y') {
                    cout << green("Accepted.") << endl;
                    break;
                } else if (action == 'N') {
                    cout << red("Rejected.") << endl;
                    break;
                }

                if (head_pos < 0) {
                    cout << red("Error: Head position out of bounds.") << endl;
                    break;
                } else if (head_pos >= tape.size()) {
                    tape.push_back('#');
                }

                state = next_state;
            }
            cout << "==================================\n";
            cout << bold("Final tape: ") << endl;
            print_tape(tape, head_pos);
            cout << endl;
        }

        /* This function translates the Turing Machine to machine code
        
            Machine code format:
            <state><tape_symbol><next_state><write_symbol><action>00<state><tape_symbol><next_state><write_symbol><action>00...

            The machine code is generated using unary encoding.
            Example:
            States: {q0, q1, q2} ==> Unary encoding: {1, 11, 111}
            Tape symbols: {#, 0, 1} ==> Unary encoding: {1, 11, 111}
            Actions: {L, R, Y, N} ==> Unary encoding: {1, 11, 111, 1111}
            Transition: (q0, 0) -> (q2, 1, R) ==> Unary encoding: 101101110111011
        */
        void translate_TM_to_machine_code() {
            string machine_code;
            auto it = this->transitions.begin();
            while (it != this->transitions.end()) {
                auto transition = *it;
                string state = get<0>(transition.first);
                char tape_symbol = get<1>(transition.first);
                string next_state = get<0>(transition.second);
                char write_symbol = get<1>(transition.second);
                char action = get<2>(transition.second);

                // Encode state
                for (int i = 0; i < this->states.size(); i++) {
                    if (state == *next(this->states.begin(), i)) {
                        machine_code += string(i + 1, '1');
                        break;
                    }
                }

                machine_code += '0';

                // Encode tape symbol
                for (int i = 0; i < this->tape_symbols.size(); i++) {
                    if (tape_symbol == *next(this->tape_symbols.begin(), i)) {
                        machine_code += string(i + 1, '1');
                        break;
                    }
                }

                machine_code += '0';

                // Encode next state
                for (int i = 0; i < this->states.size(); i++) {
                    if (next_state == *next(this->states.begin(), i)) {
                        machine_code += string(i + 1, '1');
                        break;
                    }
                }

                machine_code += '0';

                // Encode write symbol
                for (int i = 0; i < this->tape_symbols.size(); i++) {
                    if (write_symbol == *next(this->tape_symbols.begin(), i)) {
                        machine_code += string(i + 1, '1');
                        break;
                    }
                }

                machine_code += '0';

                // Encode action
                if (action == 'L') {
                    machine_code += "1";
                } else if (action == 'R') {
                    machine_code += "11";
                } else if (action == 'Y') {
                    machine_code += "111";
                } else if (action == 'N') {
                    machine_code += "1111";
                }

                it++;
                if (it != this->transitions.end()) {
                    machine_code += "00";
                }
            }

            cout << bold("Encoded TM string (machine code):") << endl << machine_code << endl;
            cout << "==================================\n";
        }

};

int main() {
    TuringMachine TM = TuringMachine();
    TM.get_TM_specs_from_user();
    TM.print_TM_specs();

    TM.translate_TM_to_machine_code();

    pair<string, int> tape = TM.get_input_tape();
    TM.run_TM(tape.first, tape.second);


    return 0;
}
