#ifndef SMARTSTRING_H_INCLUDED
#define SMARTSTRING_H_INCLUDED

#include "defvals.h"
#include "smartChr.h"

class Guess;

class SmartString
{
public:
    SmartString(bool dupes);
    SmartString(Reader & rdr);
    virtual ~SmartString(){}

    bool CanEliminateCharacters(const Guess theGuess);
    bool GetNext();
    vector<char> GetString();
    bool RemoveCurrentCharacters();
    bool RemoveCurrentCharactersInEveryPosition();
    void Write(Writer & wrtr)const;

private:
    void ForceCharacters(const Guess & theGuess);
    int CountForcedInGues(const Guess & theGuess);
    int CountUniqueLettersInGuess(const Guess & theGuess);
    bool In(vector<char> vec, char target) const;

    vector<char> deadCharacters;
    bool duplicates;
    vector<char>forcedCharacters;
    vector<smartChar> myString;
};



#endif // SMARTSTRING_H_INCLUDED
