#include "../include/CFG.hpp"

CFG::CFG(std::ifstream &fs) {
    if (!fs.is_open()) throw "Please open file before creating CFG";
    std::string line;
    bool initStart = true;
    while (std::getline(fs>>std::ws,line)) {
        char variable{line[0]};

        // Catch Start Symbol
        if (initStart) {
            Start = variable;
            Variables.insert(variable);
            initStart = false;
        }
        // Captures productions separated by spaces
        std::string production{};
        // Iterate across file, non-terminals are always capital letters
        for(std::string::iterator it = line.begin()+1; it != line.end(); ++it)
        {
            if (*it >= 'A' && *it <= 'Z') Variables.insert((*it));
            // Advances past "->" indicating start of productions
            else if (*it == '-' && (it+1 != line.end() && *(it+1) == '>')) {
                it++;
                continue;
            }
            // Indicates multiple productions from one non-terminal
            else if (*it == '|') {
                rules.emplace(variable,production);
                production.clear();
                continue;
            }
            // Everything else between ASCII 33 and 126 are considered terminals
            else if (*it >= '!' && *it <= '~') 
                Sigma.insert(*it);
            else continue;
            production += *it;
        }
        // Assumed every line has a production
        rules.emplace(variable,production);
    }
    // Calculate First and Follow Sets
    First();
    Follow();
}

/*  LeadsToEpsilon(#) = True
    LeadsToEpsilon(Terminal) = False
    LeadsToEpislon(NonTerminal) = any(LeadsToEpsilon(Productions))
*/
bool CFG::LeadsToEpsilon(char a) {
    if (auto b = Sigma.find(a); b != Sigma.end()) {
        return *b == '#';
    }
    auto range = rules.equal_range(a);
    for (auto it = range.first; it != range.second; it++) {
        if (LeadsToEpsilon(it->second[0])) return true;
    }
    return false;
}

/*  FirstHelper("",acc) = acc
    FirstHelper(x,acc) = acc.insert(x)
    FirstHelper(A,acc) = acc.merge(FirstHelper(Productions(A),acc))
    FirstHelper(AB,acc) = acc.merge(FirstHelper(Productions(B),acc)), 
                            if LeadsToEpsilon(A)
*/
Set CFG::First_Helper(std::string rule, Set &acc) {
    if (rule == "") return acc;
    char c = rule[0];
    // If rule[0] is in Sigma, add it to acc and return
    if (Sigma.find(c) != Sigma.end()) {
        acc.insert(c);
        return acc;
    }
    // Grab all productions of non-terminal stored in char c
    //      Since grammars are non-recursive, this will always terminate
    auto range = rules.equal_range(c);
    for (auto it = range.first; it != range.second; it++)
        acc = First_Helper(it->second,acc);
    if (LeadsToEpsilon(c)) {
        if (Variables.find(*(rule.begin()+1)) != Variables.end())
            acc = First_Helper(rule.substr(1),acc);
    }
    return acc;
}

// Iterate through Rules of type multimap<char,string>, AKA multimap<Rule>
void CFG::First() {
    for (Rule r : rules) {
        Set fSet{};
        fSet = First_Helper(r.second, fSet);
        firstSet[r.first].insert(fSet.begin(),fSet.end());
    }
}

/*  Follow_Helper(A -> xBC) = followSet[B] += {First_Helper(C)}
    Follow_Helper(A -> xB)  = followSet[B] += {Follow_Helper(A)}
    Follow_Helper(A -> xBC) 
        = followSet[B] += {Follow_Helper(A)} U {First_Helper(C)},
        if LeadsToEpsilon(C) == true
*/
void CFG::Follow_Helper(char var) {
    for (auto it = rules.begin(); it != rules.end(); it++) {
        for (auto sit = it->second.begin(); sit != it->second.end(); sit++) {
            if (*sit == var) {
                if (sit+1 != it->second.end()) {
                    Set first{};
                    first = First_Helper(std::string{*(sit+1)},first);
                    first.erase('#');
                    followSet[*sit].insert(first.begin(), first.end());
                }
                if ( (sit+1 == it->second.end() && var != it->first) ||
                     (sit+1 != it->second.end() && LeadsToEpsilon(*(sit+1))) ){
                    Follow_Helper(it->first);
                    followSet[*sit].insert(followSet[it->first].begin(), 
                                            followSet[it->first].end());
                }
            }
        }
    }
}

// Iterate through non terminals to inspect within the rules
// O(|V|*|R|), V are Variables, R are Rules
void CFG::Follow() {
    followSet[Start].insert('$');
    for (char A : Variables) {
        Follow_Helper(A);
    }
}

void CFG::Print() {
    std::cout << "Reading Terminals\n";
    for (auto x : Sigma) std::cout << x << ' ';
    std::cout << "\nReading NonTerminals\n";
    for (auto x : Variables) std::cout << x << ' ';
    std::cout << "\nReading Rules\n";
    for (auto x : rules) std::cout << x.first << "->" << x.second << '\n';
}

// We don't like printing unordered set >:(
void DisplayParseSet(char c, Set const &x) {
    std::cout << c << " = { ";
    std::string output;
    for (auto it = x.begin(); it != x.end(); ++it) {
        output += *it;
        output += ", ";
    }
    output.erase(output.end()-2);
    std::cout << output << "}\n";
}

void CFG::DisplayFollow() {
    std::cout << "********** Follow Set **********\n";
    for (auto x : followSet) DisplayParseSet(x.first, x.second);
}

void CFG::DisplayFirst() {
    std::cout << "********** First Set **********\n";
    for (auto x : firstSet) DisplayParseSet(x.first, x.second);
}