#ifndef SMARTCHAR_H_INCLUDED
#define SMARTCHAR_H_INCLUDED

#include "defvals.h"
#include "Storable.h"

class SmartChar : public Storable
{
public:
    SmartChar(int letter = 0);
    SmartChar(Reader &rdr);
    virtual ~SmartChar();

    char GetChar()const;
    bool Increment();
    char RemoveCurrent();
    bool Remove(char c);
    void Write(Writer & wrtr)const;

private:
    int myChar;
    vector<char> myCharacters;
};

#endif // SMARTCHAR_H_INCLUDED
