#include "CFG.hpp"

CFG PrintCFG(std::string filename) {
    std::ifstream input{filename};
    CFG c(input);
    c.DisplayFirst();
    c.DisplayFollow();

    return c;
}


int main(int argc, char **argv) {
    CFG c = PrintCFG("test.txt");
    c.DisplayFirst();
    c.DisplayFollow();
    return 0;
}