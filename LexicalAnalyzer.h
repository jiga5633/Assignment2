//
// Created by User_Jiang on 2023/3/28.
//

#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <fstream>

#include "Token.h"
#include "TokenCode.h"

using namespace std;

class LexicalAnalyzer
{
public:
    explicit LexicalAnalyzer(ifstream *inputFile);
    ~LexicalAnalyzer(); // declare destructor

    Token *getNextToken();

private:
    ifstream *sourceCodeFile;
    string currentLine;         // current line of source code being analyzed
    int currentCharIndex;       // current character index within current line
    char currentChar;           // current character being analyzed
    int currentLineNumber;      // current line number
    // other member functions

    [[maybe_unused]] bool isEOI();
    void readNextLine();
    void getNextChar();


};

#endif
