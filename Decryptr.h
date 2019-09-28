#ifndef DECRYPTR_H_INCLUDED
#define DECRYPTR_H_INCLUDED

#include "defvals.h"
#include "guess.h"
#include "Storable.h"

class Decryptr
{
public:
    Decryptr (bool duplicates);
    Decryptr(Reader &rdr);
    virtual ~Decryptr();
    void Display(vector<char> charVec) const;
    virtual bool HandleFlag(char flag) = 0;
    virtual void Play() = 0;
    virtual void ShowHelp() = 0;
    void ShowHistory();
    void  Write(Writer & wrtr);

protected:
    bool duplicates;
    vector<Guess> history;
    int round;
    Reader storable;
};


#endif // DECRYPTR_H_INCLUDED
