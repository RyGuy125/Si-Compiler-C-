#include <unordered_map>
#include <deque>
#include <string>
#include <exception>
#include "CFG.hpp"

using ParseTable = std::unordered_map<char, 
                                      std::unordered_map<char, 
                                                         std::pair<char, 
                                                                 std::string>>>;
class LL1 {
    ParseTable parseTable{{{}}};
    std::deque<char> stack;
    // Throws when provided CFG is not an LL(1) Grammar
    void constructTable() noexcept(false);
    // Helper Function to grab First set of first item in a rule
    Set extractFirst(char c);
    CFG cfg;
public:
    LL1(CFG &cfg);
    bool parse(std::string input);
    void display();
};