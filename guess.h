#ifndef GUESS_H_INCLUDED
#define GUESS_H_INCLUDED

#include "defvals.h"
#include "Storable.h"


class Guess : public Strobale
{
public:
    Guess(vector<char>guess, int howManyRight, int howManyInPosition);
    Guess(Reader & rdr);
    virtual ~Guess() {}
    void Display() const;
    pair<int,int> GetScore()const;
    vector<char>GetString() const;
    virtual void Write(Writer & wrtr) const;

private:
    pair<int,int> score;
    vector<char> myString;

};



#endif // GUESS_H_INCLUDED
