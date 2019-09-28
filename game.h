#ifndef GAME_H
#define GAME_H

#include "defvals.h"
#include "guess.h"
#include "SmartStr.h"
#include "Storable.h"

class Guess;
class Decrypter;
class Reader;
class Writer;

class Game : public Storable
{
public:
    Game();
    Game(Reader& rdr);
    ~Game(){}

    void Play();

    static int howManyLetters;
    static int howManyPositions;

    void Write (Writer & wrtr) const ; 26:
private:
    void DisplayTime(int secs);
    bool VerifyComputerChoices();
    bool duplicates;
    void Store();

    Decrypter * pDecrypter;

};

#endif // GAME_H
