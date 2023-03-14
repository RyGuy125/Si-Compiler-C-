#include "LL1.hpp"

// Only parameterized constructor provided. Initializes ParseTable with CFG
LL1::LL1(CFG &cfg) : cfg{cfg}, stack{'$',cfg.Start} {
    for (char terminal : cfg.Variables) {
        for (char nonterminal : cfg.Sigma) {
            if (nonterminal == '#') continue;
            parseTable[terminal][nonterminal] = {'\0', "Error"};
        }
        parseTable[terminal]['$'] = {'\0', "Error"};
    }
    constructTable();
}

/*  extractFirst(c) = {c}, c in Sigma
    extractFirst(c) = First(c), c in Variables
    
    Character is always taken from a CFG Rule, so is either a terminal or
    non-terminal
*/
Set LL1::extractFirst(char c) {
    if (cfg.Sigma.find(c) != cfg.Sigma.end()) return Set{c};
    return cfg.firstSet.at(c);
}

/* constructTable() creates a 2D unordered_map object assigned to 
    member variable parseTable by iterating through the rules of a CFG and 
    grabbing the First Set of each starting symbol, or Follow Set if symbol is
    the empty string.

    Will throw if more than one rule is being added to a single index in the 
    parseTable, meaning the CFG is not LL(1)
*/
void LL1::constructTable() {
    for (std::pair<char,std::string> rule : cfg.rules) {
        Set range = extractFirst(rule.second[0]);
        for (char e : range) {
            if (e != '#' and parseTable[rule.first][e].second != "Error")
                throw "Grammar is not LL(1)";
            else if (e == '#') {
                for (auto follow : cfg.followSet[rule.first])
                    parseTable[rule.first][follow] = rule;
                continue;
            }
            parseTable[rule.first][e] = rule;
        }
    }
}

/*  parse(w) = true, if by the end of consuming a word, w, the stack is empty
                        save for a $, and our looking lookahead is $ as well.
                    -> top == lookAhead == '$'
    parse(w) = false, if word, w, is not consumed leaving $, the stack does not
                        match the lookahead symbol, and the parseTable does not
                        have a column for the lookahead symbol
                    -> top != lookAhead != '$', lookAhead not in parseTable[top]
*/
bool LL1::parse(std::string input) {
    input += '$';
    std::string::iterator la = input.begin();
    while (la != input.end()) {
        char top = stack.back();
        if (top == *la && *la == '$') return true;
        else if (top == *la) {
            stack.pop_back();
            la++;
        }
        else if (parseTable[top].find(*la) != parseTable[top].end()) {
            stack.pop_back();
            for (auto rit = parseTable[top][*la].second.rbegin(); 
                    rit != parseTable[top][*la].second.rend(); ++rit) 
                stack.push_back(*rit);
        }
        else return false;
    }
    return false;
}

/* Damn ugly display function that iterators over a (*blehg*) unordered_map
    because I needed it for debugging
*/
void LL1::display() {
    for (auto i : parseTable) {
        std::cout << "Row: " << i.first << '\n';
        for (auto j : i.second) 
            std::cout << "Column: " << j.first << ": " 
                      << j.second.first << " -> " << j.second.second << '\n';
    }
}