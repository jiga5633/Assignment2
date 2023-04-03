//
// Created by User_Jiang on 2023/3/28.
//

#ifndef ASSIGNMENT2_TOKEN_H
#define ASSIGNMENT2_TOKEN_H

#include <iostream>
#include <string>

#include "TokenCode.h"

using namespace std;

class Token
{
private:
    string lexemeString;
    TokenCode tokenCode;

public:
    Token();
    Token(TokenCode, string);

    [[maybe_unused]] string getLexemeString();
    void setLexemeString(string);
    TokenCode getTokenCode();
    void setTokenCode(TokenCode);
    friend ostream& operator<<(ostream& os, const Token& t);
};

#endif //ASSIGNMENT2_TOKEN_H
