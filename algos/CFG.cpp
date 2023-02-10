#include "CFG.hpp"
#include <sstream>
#include <algorithm>
#include <iterator>

CFG::CFG(std::ifstream &fs) {
    if (!fs.is_open()) throw "Please open file before creating CFG";
    std::string line;
    bool initStart = true;
    while (std::getline(fs>>std::ws,line)) {
        char variable{line[0]};
        if (initStart) {
            Start = variable;
            initStart = false;
        }
        std::string production{};
        for(std::string::iterator it = line.begin()+1; it != line.end(); ++it)
        {
            if (*it >= 'A' && *it <= 'Z') nonTerminals.insert((*it));
            else if (*it == '-' && (it+1 != line.end() && *(it+1) == '>')) {
                it++;
                continue;
            }
            else if (*it == '|') {
                rules.emplace(variable,production);
                production.clear();
                continue;
            }
            else if (*it >= '!' && *it <= '~') 
                terminals.insert(*it);
            else continue;
            production += *it;
        }
        rules.emplace(variable,production);
    }
    Sigma.insert(terminals.begin(), terminals.end());
    Sigma.insert(nonTerminals.begin(), nonTerminals.end());
    First();
    Follow();
}

/*  LeadsToEpsilon(#) = True
    LeadsToEpsilon(Terminal) = False
    LeadsToEpislon(NonTerminal) = any(LeadsToEpsilon(Productions))
*/
bool CFG::LeadsToEpsilon(char a) {
    if (auto b = terminals.find(a); b != terminals.end()) {
        return *b == '#';
    }
    std::pair range = rules.equal_range(a);
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
Set CFG::First_Helper(std::string rule, std::set<char> acc) {
    if (rule == "") return acc;
    char c = rule[0];
    if (*(terminals.find(c)) == *(rule.begin())) {
        acc.insert(c);
        return acc;
    }
    std::pair range = rules.equal_range(c);
    for (auto it = range.first; it != range.second; it++)
        acc.merge(First_Helper(it->second,acc));
    if (LeadsToEpsilon(c)) {
        if (nonTerminals.find(*(rule.begin()+1)) != nonTerminals.end())
            acc.merge(First_Helper(rule.substr(1),acc));
    }
    return acc;
}

void CFG::First() {
    for (Rule r : rules) {
        Set fSet = First_Helper(r.second, Set{});
        firstSet[r.first].insert(fSet.begin(),fSet.end());
        
    }
}


void CFG::Follow_Helper(char var) {
    for (auto it = rules.begin(); it != rules.end(); it++) {
        for (auto sit = it->second.begin(); sit != it->second.end(); sit++) {
            if (*sit == var) {
                if (sit+1 != it->second.end()) {
                    Set first = First_Helper(std::string{*(sit+1)},Set{});
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

void CFG::Follow() {
    followSet[Start].insert('$');
    for (char A : nonTerminals) {
        Follow_Helper(A);
    }
}

void CFG::Print() {
    std::cout << "Reading Terminals\n";
    for (auto x : terminals) std::cout << x << ' ';
    std::cout << "\nReading NonTerminals\n";
    for (auto x : nonTerminals) std::cout << x << ' ';
    std::cout << "\nReading Rules\n";
    for (auto x : rules) std::cout << x.first << "->" << x.second << '\n';
}

void ossDisplay(std::pair<char,Set> x) {
    std::ostringstream ss;
    std::copy(x.second.begin(), std::prev(x.second.end()), 
                std::ostream_iterator<char>(ss, ", "));
    ss << *(std::prev(x.second.end()));
    std::cout << x.first << " = {" << ss.str() << "}\n";
}

void CFG::DisplayFollow() {
    std::cout << "********** Follow Set **********\n";
    for (auto x : followSet) ossDisplay(x);
}

void CFG::DisplayFirst() {
    std::cout << "********** First Set **********\n";
    for (auto x : firstSet) ossDisplay(x);
}