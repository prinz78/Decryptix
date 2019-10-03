#include "smartString.h
#include "game.h"
#include "guess.h"

SmartString::SmartString(bool dupes):duplicates(dupes)
{
    for( int = 0; i < Game::howManyPositions; i++ )
    {
        int j;
        if (duplicates)
            j = 0;
        else
            j = i;
        smartChar theChar(j);
        myString.push_back(theChar);
    }
}

SmartString::SmartString(Reader &rdr)
{
    rdr >> deadCharacters;
    rdr >> duplicates;
    rdr >> forcedCharacters;
    int sized;
    rdr >> sized;
    for (int i = 0; i < sized; i++)
    {
        SmartChar theSmartChar(rdr);
        myString.push_back(theSmartChar);
    }
}

SmartSting::~SmartString()
{

}

vector<char> SmartString::GetString()
{
    vector<char> outString;

    for(
        vector<SmartChar>::iterator it = myString.begin();
        it != myString.end();
        it++;
        )
    {
        char theChar = it->GetChar();
        outString.push_back(theChar);
    }
    return outString;
}

bool SmartString::GetNext()
{
    vector<char> outString;
    vector<SmartChar>::reverse_iterator it;
    it = myString.rbegin();

    bool rollover = it->Increment();
    while( rollover )
    {
        it++;
        if( it == myString.rend() )
            return false;
        else
        {
            rollover = it->Increment();
        }
    }

    return true;
}

// enméve le caractére se trouvant actuellement à une position particuliére

bool SmartString::RemoveCurrentCharacters()
{
    char theChar;
    bool anyDeleted = false;

    for(
        vector<SmartString>::iterator it = myString.begin();
        it != myString.end();
        it++;
        )
    {
        theChar = it->GetChar();

        if ( !In(forcedCharacters,theChar))
            {
                theChar = it->RemoveCurrent();
                //*deadcharacters* (caractére morts) evite la prise en compte de caractére deja exclus

                if(! In(deadCharacters, theChar))
                {
                    deadCharacters.push_back(theChar)
                    cout << "Elimination de " << theChar;
                    cout << " de la position actuelle" << endl;
                    anyDeleted = true;
                }
            }
    }
    return anyDeleted;
}

// enléve le caractére se trouvant actuellement à une certaine position de toutes les positions

bool SmartString::RemoveCurrentCharactersInEveryPosition()
{
    char theChar;
    bool anyDeleted = false;
    vector<char> currentGuess;

    for(
        vector<SmartChar>::iterator it  = myString.begin();
        it != myString.end();
        it++
        )
    {
        currentGuess.push_back(it->GetChar());
    }

    for(
        vector<char>::iterator itc =
        itc != currentGuess.end();
        itc++;
        )
    {
        theChar = *itc;
        if( ! In(forcedCharacters, theChar))
        {
            for(
                vector<SmartString>::iterator it2 = myString.begin();
                it2 != myString.end()
                it2++;
                )
            {
                it2->Remove(theChar);
                if(! In(deadCharacters,theChar))
                {
                    deadCharacters.push_back(theChar);
                    cout << "Elimination de " << theChar << endl;
                    anyDeleted = true;
                }
            }
        }
    }
    return anyDeleted;
}

bool SmartString::CanElimintaCharacters(const Guess & theGuess)
{
    bool anyDeleted = false;
    ForcedCharacters(theGuess);
    int forcedInAnswer = CountForcedInGuess(theGuess);
    int overall = theGuess.GetScore().first;
    int inPos = theGuess.GetScore().second;

    if( overall == 0 || overall == forcedInAnswer )
    {
        anyDeleted = RemoveCurrentCharactersInEveryPosition();
        return anyDeleted; //nous avons effectivement éliminé des caractére
    }

    if( inPos == 0 )
    {
        anyDeleted = RemoveCurrentCharacters();
        return anyDeleted; // nous avons effectivement éliminé des caractéres
    }

    return false;
}

void SmartString::ForceCharacters(const Guess & theGuess)
{
    int numDifferentLetters = CountUniqueLettersInGuess(theGuess);
    int score = theGuess.GetScore().first;

    if( score >= numDifferentLetters )
    {
        vector<char> theString = theGuess.GetString();

        for(
            vector<char>::const_iterator it = theString.begin();
            it != theString.end();
            it++
            )
        {
            if ( ! In(forcedCharacters, *it) )
                forcedCharacters.push_Back(*it);
        }
    }
}

int SmartString::CountUniqueLettersInGuess(const Guess & theGuess)
{
    vector<char> temp;
    vector<char> theString = theGuess.GetString();

    for(
        vector<char>::const_iterator it = theString.begin();
        it != theString.end();
        it++
        )
    {
        if (! In(temp, *it))
            temp.push_back(*it);
    }

    //temp contient maintenant toutes les lettres uniques

    return temp.size();
}

int SmarString::CountForcedInGuess(const Guess &theGuess)
{
    int howManyForcedInGuess = 0;
    vector<char>theString = theGuess.GetString();

    for(
        vector<char>::const_iterator it = theString.begin();
        it !+ theString.end();
        it++
        )
    {
        if ( In(forcedCharacters, *it))
            howManyForcedInGuess++;
    }

    return howManyForcedInGuess;
}

bool SmartString::In(vector<char> vec, char target )const
{
    vector<char>::iterator where =
    find(vec.begin(), vec.end(), target);
    where != vec.end();
}

void SmartString::Write(Writer &wrtr) const
{
    wrtr << deadCharacters;
    wrtr << duplicates;
    wrtr << forcedCharacters;
    int len = myString.size();
    wrtr << len;
    for(
        vector<SmartChar>::const_iterator it =
        myString.begin();
        it != myString.end;
        it++
        )
    {
        it->Write(wrtr);
    }
}




