// Standard DFA simulation in C++
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class DFA {
private:
    int start_state;
    set<int> accept_states;
    map<pair<int, char>, int> transition;

public:
    DFA(int start) : start_state(start) {}

    void addTransition(int from, char input, int to) {
        transition[{from, input}] = to;
    }

    void addAcceptState(int state) {
        accept_states.insert(state);
    }

    bool simulate(const string& input) {
        int current_state = start_state;
        for (char c : input) {
            auto key = make_pair(current_state, c);
            if (transition.find(key) == transition.end()) {
                return false; // No valid transition
            }
            current_state = transition[key];
        }
        return accept_states.count(current_state) > 0;
    }
};

// Example usage
int main() {
    DFA dfa(0);
    dfa.addTransition(0, '0', 0);
    dfa.addTransition(0, '1', 1);
    dfa.addTransition(1, '0', 2);
    dfa.addTransition(1, '1', 1);
    dfa.addTransition(2, '0', 2);
    dfa.addTransition(2, '1', 1);
    dfa.addAcceptState(1);

    string input = "101";
    cout << (dfa.simulate(input) ? "Accepted" : "Rejected") << endl;
    return 0;
}