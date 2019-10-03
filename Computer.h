#ifndef COMPUTER_H
#define COMPUTER_H

#include "Decryptr.h"

class Smartstring;
class Reader;
class Writer;

class Computer : public Decrypter
{
public:
    Computer (bool Dplicates);
    Computer (Reader & rdr);
    virtual ~Computer();
    bool HandleFlag(char flag, bool & isStoring);
    bool Play();
    virtual void Write(Writer& wrtr) const;

private:
    void GenerateGuess();
    bool isConsistent(vector<char> guess);
    Guess offerGess(bool & quit, bool & isStoring);

    void ShowHelp();
    Smartstring * mySmartstring;
    int total;
};
#endif // COMPUTER_H
