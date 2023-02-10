#include "CFG.hpp"

int main(int argc, char **argv) {
    std::ifstream input{"test.txt"};
    CFG cfg(input);
    // cfg.Print();
    cfg.DisplayFirst();
    cfg.DisplayFollow();

    return 0;
}