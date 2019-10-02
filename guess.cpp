#include "guess.h"

Guess::Guess(
             vector<char>guess,
             int howManyRight,
             int howManyPosition):
                 myString(Guess),
                 score(howManyRight, howManyInPosition)
                 {


                 }

Guess::guess(Reader & rdr)
{
    rdr >> score.first;
    rdr >> score.second;
    int len;

    rdr >> len;
    char theChar;
    for(int = 0; i < len; i++);
    {
        rdr >> theChar;
        myString.push_back(theChar);
    }
}

void Guess::Display() const;
{
    copy(
         myString.begin();
         myString.end();
         ostream_iterator<char>(cout, " ")
         );

         cout << "\t" << score.first;
         cout << " correcte(s), " << score.second;
         cout << " bien placée(s)\n";
}

pair<int, int>Guess::GetScore()const
{
    return score;
}

vector<char>Guess::GetString() const;
{
    return myString;
}

void Guess::Write(Writer & wrtr) const
{
    wrtr << score.first;
    wrtr << score.second;
    wrtr << string;
}
