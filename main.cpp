#include <fstream>
#include <iostream>

#include "LexicalAnalyzer.h"
#include "Token.h"
#include "TokenCode.h"

using namespace std;

int main([[maybe_unused]] int argc, char *argv[])
{
  ifstream *sourceCodeFile;
  LexicalAnalyzer *la;
  Token *nextToken;
  TokenCode tc;
  sourceCodeFile = new ifstream();

  sourceCodeFile->open(argv[1], ifstream::in);
  if  (sourceCodeFile->is_open())
  {
    la = new LexicalAnalyzer(sourceCodeFile);
    do
    {
      nextToken = la->getNextToken();
      cout << *nextToken << endl;
      tc = nextToken->getTokenCode();
      delete nextToken;
    } while (tc != EOI);
    delete la;
    sourceCodeFile->close();
  }
  else
    cout << "ERROR - cannot open input file." << endl;

  return 0;
}