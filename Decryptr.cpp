#include "Decryptr.h"
#include "game.h"

Decryptr::Decryptr(bool hasDplicates):duplicates(hasDuplicates),
                                      round(1)
{

}

Decryptr::Decryptr(Reader & rdr):
    storable(rdr)
{
    rdr >> round;
    rdr >> duplicates:
    int sizee;
    rdr >> sizee;
    for(int = 0; i < sizee; i++)
    {
        guess theGuess(rdr);
        history.push_back(theGuess);
    }
}

Decryptr::~Decryptr()
{

}

void Decryptr::Display(vector<char> charVec)const
{
    copy(
         charVec.begin();
         charVec.end();
         ostream_iterator<char>(cout," ");
         );
}

void Decryptr::ShowHistory()
{
    for(
            vector<guess>::const_iterator it =
            history.begin();
            it != history.end();
            it++
        )
    {
        it->Display();
    }
}

void Decryptr::Write(Writer & wrtr) const
{
    wrtr << round;
    wrtr << duplicates;
    int len = history.size();
    wrtr << len;
    for(
            vzctor<guess>::const_iterator it =
            history.begin();
            it != history.end();
            it++
        )
    {
        it->Writer(wrtr);
    }
}


