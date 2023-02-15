/* First(x)
    - The set of all terminals that may begin in RHS of any right sentinel form

    Rules for First(X):
    1) First(x), x is a terminal:
        First(x) = {x}
    2) First(X), X is a non-terminal and X -> e (epsilon):
        First(X) = {e}
    3) First(X), X is a non-terminal and X -> a | aY:
        First(X) = {a}
    4) First(X), X is a non-terminal and X -> AB:
        First(X) = First(A), if A !-*> e
        First(X) = First(A) U First(B), if A -*> e
    5) First(X), X is a non-terminal and X -> Y:
        First(X) = First(Y)
*/
/* Follow(X)
    - The set of all terminals that may follow to the right of X in any
        right sentinel form
    
    Rules for Follow(X):
    1) Follow(S) = {$}
    2) Follow(A) = Follow(S), S -> xA | xAB where x in E and B -*> e (epsilon)
    3) Follow(A) = First(B), S -> xAB where x in E and B !-*> e
    4) Follow(A) = Follow(S), S -> A
*/

#include <unordered_set>
#include <unordered_map>
#include <string>
#include <map>
#include <fstream>
#include <iostream>

using Rules = std::multimap<char,std::string>;
using Rule = std::pair<char,std::string>;
using Set = std::unordered_set<char>;
using ParseSet = std::unordered_map<char,Set>;
class CFG {
    ParseSet firstSet{};
    ParseSet followSet{};

    void First();
    void Follow();

    Set First_Helper(std::string rule, Set &acc);
    void Follow_Helper(char var);
    bool LeadsToEpsilon(char a);
public:
    // Throws unopened ifstream
    CFG(std::ifstream &fs) noexcept(false);

    Set Sigma;
    Set Variables;
    Rules rules;
    char Start;

    void Print();
    void DisplayFollow();
    void DisplayFirst();
};