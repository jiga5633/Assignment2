#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCode.h"

#include <cctype>
#include <iostream>

using namespace std;

LexicalAnalyzer::LexicalAnalyzer(ifstream *inputFile)
{
    sourceCodeFile = inputFile;
    currentChar = ' ';
    currentLineNumber = 1;
    currentLine = "";           // initialize currentLine to empty string
    currentCharIndex = 0;       // initialize currentCharIndex to 0

}
LexicalAnalyzer::~LexicalAnalyzer()
{
    sourceCodeFile->close();
}
Token *LexicalAnalyzer::getNextToken() {
    while (isspace(currentChar)) {
        getNextChar();
    }

    Token *t;
    string lexeme;

    switch (currentChar) {
        case '+':
            t = new Token(PLUS, "+");
            getNextChar();
            break;
        case '-':
            t = new Token(MINUS, "-");
            getNextChar();
            break;
        case '*':
            t = new Token(TIMES, "*");
            getNextChar();
            break;
        case '/':
            getNextChar();
            if (currentChar == '/') {
                readNextLine();
                return getNextToken();
            } else {
                t = new Token(SLASH, "/");
            }
            break;
        case '%':
            t = new Token(MOD, "%");
            getNextChar();
            break;
        case '(':
            t = new Token(LPAREN, "(");
            getNextChar();
            break;
        case ')':
            t = new Token(RPAREN, ")");
            getNextChar();
            break;
        case '{':
            t = new Token(LBRACE, "{");
            getNextChar();
            break;
        case '}':
            t = new Token(RBRACE, "}");
            getNextChar();
            break;
        case ';':
            t = new Token(SEMICOLON, ";");
            getNextChar();
            break;
        case ',':
            t = new Token(COMMA, ",");
            getNextChar();
            break;
        case '<':
            getNextChar();
            if (currentChar == '=') {
                t = new Token(LEQ, "<=");
                getNextChar();
            } else {
                t = new Token(LSS, "<");
            }
            break;
        case '>':
            getNextChar();
            if (currentChar == '=') {
                t = new Token(GEQ, ">=");
                getNextChar();
            } else {
                t = new Token(GTR, ">");
            }
            break;
        case '=':
            getNextChar();
            if (currentChar == '=') {
                t = new Token(EQL, "==");
                getNextChar();
            } else {
                t = new Token(ASSIGN, "=");
            }
            break;
        case '!':
            getNextChar();
            if (currentChar == '=') {
                t = new Token(NEQ, "!=");
                getNextChar();
            } else {
                t = new Token(NOT, "!");
            }
            break;
        case '|':
            getNextChar();
            if (currentChar == '|') {
                t = new Token(OR, "||");
                getNextChar();
            } else {
                t = new Token(NAL, "|");
            }
            break;
        case '&':
            getNextChar();
            if (currentChar == '&') {
                t = new Token(AND, "&&");
                getNextChar();
            } else {
                t = new Token(NAL, "&");
            }
            break;
        case EOF:
            t = new Token(EOI, "");
            break;
        default:
            if (isalpha(currentChar)) {
                while (isalnum(currentChar)) {
                    lexeme += currentChar;
                    getNextChar();
                }
                if (lexeme == "int") {
                    t = new Token(INTSYM, lexeme);
                } else if (lexeme == "float") {
                    t = new Token(FLOATSYM, lexeme);
                } else if (lexeme == "bool") {
                    t = new Token(BOOLSYM, lexeme);
                } else if (lexeme == "if") {
                    t = new Token(IFSYM, lexeme);
                } else if (lexeme == "else") {
                    t = new Token(ELSESYM, lexeme);
                } else if (lexeme == "for") {
                    t = new Token(FORSYM, lexeme);
                } else if (lexeme == "while") {
                    t = new Token(WHILESYM, lexeme);
                } else if (lexeme == "true") {
                    t = new Token(TRUESYM, lexeme);
                } else if (lexeme == "false") {
                    t = new Token(FALSESYM, lexeme);
                } else if (lexeme == "return") {
                    t = new Token(RETURNSYM, lexeme);
                } else if (lexeme == "scanf") {
                    t = new Token(SCANFSYM, lexeme);
                } else if (lexeme == "printf") {
                    t = new Token(PRINTFSYM, lexeme);
                } else if (lexeme == "void") {
                    t = new Token(VOIDSYM, lexeme);
                } else {
                    t = new Token(IDENT, lexeme);
                }
                return t;
            } else if (isdigit(currentChar)) {
                string lexeme = "";
                while (isdigit(currentChar)) {
                    lexeme += currentChar;
                    getNextChar();
                }
                if (currentChar == '.') {
                    lexeme += currentChar;
                    getNextChar();
                    while (isdigit(currentChar)) {
                        lexeme += currentChar;
                        getNextChar();
                    }
                    t = new Token(NUMLIT, lexeme);
                } else {
                    t = new Token(NUMLIT, lexeme);
                }
                return t;
            } else if (currentChar == '/') {
                getNextChar();
                if (currentChar == '/') {
                    readNextLine();
                    getNextChar();
                    return getNextToken();
                } else {
                    t = new Token(DIV, "/");
                    return t;
                }
            } else if (currentChar == '<') {
                getNextChar();
                if (currentChar == '=') {
                    t = new Token(LEQ, "<=");
                    getNextChar();
                } else {
                    t = new Token(LSS, "<");
                }
                return t;
            } else if (currentChar == '>') {
                getNextChar();
                if (currentChar == '=') {
                    t = new Token(GEQ, ">=");
                    getNextChar();
                } else {
                    t = new Token(GTR, ">");
                }
                return t;
            } else if (currentChar == '=') {
                getNextChar();
                if (currentChar == '=') {
                    t = new Token(EQL, "==");
                    getNextChar();
                } else {
                    t = new Token(ASSIGN, "=");
                }
                return t;
            } else if (currentChar == '!') {
                getNextChar();
                if (currentChar == '=') {
                    t = new Token(NEQ, "!=");
                    getNextChar();
                } else {
                    t = new Token(NOT, "!");
                }
                return t;
            } else if (currentChar == '(') {
                t = new Token(LPAREN, "(");
                getNextChar();
                return t;
            }
    }
}

[[maybe_unused]] bool LexicalAnalyzer::isEOI() {
    return false;
}

void LexicalAnalyzer::readNextLine() {
    currentLineNumber++; // increase line number
    getline(*sourceCodeFile, currentLine); // read the next line from file
    currentCharIndex = 0; // reset character index to the beginning of the line
}

void LexicalAnalyzer::getNextChar() {
    if (currentCharIndex >= currentLine.length()) { // end of line
        readNextLine();
        currentChar = ' '; // reset currentChar
        currentCharIndex = 0; // reset currentCharIndex to the beginning of the new line
    } else {
        currentChar = currentLine[currentCharIndex++];
    }
}

