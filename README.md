# Si-Compiler-C++
This is a repository for the compiler and all of its related algorithms for the micro-language Si, based on C.

Please ensure you are compiling with at least the C++17 Standard! I like using If statements with initializers :)
The command I use (on my Raspberry Pi 4) is g++ -std=c++17 CFG-test.cpp CFG.cpp -o CFG.

I anticipate adding more files for LL(1) through SLR(1) parsers, as well as some more functionality for removing left recursion and ambiguousness in grammars,
so feel free to compile only the CFG class files and then link it later (perhaps in a Makefile? :O )
