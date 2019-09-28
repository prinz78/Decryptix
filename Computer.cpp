#include "Computer.h"
#include "SmartStr.h"
#include "Game.h"
#include <string>
#include <stdlib.h>

Computer::Computer(bool dupes): Decprypter(dupes),
total(0),
mySmartstring(0)
{

}

Computer::Computer(Reader & rdr):
Decrypter(rdr)
{
    mySmartstring = new SmartString(rdr);
    rdr >> total;
    cout << "Calculateur. \n";
}

Computer::~Computer()
{

}

void Computer::GenerateGuess()
{
    bool ok = true;
    int counter = 0;
    int start = time( NULL );

    do
    {
        counter++;
        total++;
        if (counter % 10000 == 0 )
            cout << ".";

        ok = mySmartstring->GetNext();

        if ( !ok )
        {
            cout << "Quelsue chose ne va pas !";
            cout << "Recommencez\n";
            round = 1;
            delete mySmartString;
            mySmartstring = new smartString(duplicates);
            ShowHistory();

            cout << "\n\n";
            history.clear();
            continue;
        }
    }while (! IsConsistant(mySmartString->geStrin()));

    int end = time (NULL);
    int seconds = end -start;
    cout << "(" << counter;
    cout << "chaines èliminées pour cet essai; ";
    cout << total << "total.)";
    if( seconds > 1 )
        cout << "[" << seconds << " seconds]";
    cout << "\n";

}

// Gestion des indicateurs de l'utilisateur (-?,-q, ect.)

bool Computer::HandleFlag(char flag, bool & isStoring)
{
    bool quit = false;
    isStoring = false;

    switch (flag)
    {
    case 's':
        ShowHistory();
        break;
    case '?':
        ShowHelp();
        break;
    case 'f':
        isStoring = true;
        quit = true;
        break;
    case 'q':
        quit = true;
        break;
    default:
        cout << "\nIndicateur inconnu, Ignoré.\n";
        break
    }
    return quit;
}

bool Computer::isConsistent(vector<char> the guess)
{
    if (! duplicates)
    {
        for(vector<char>::const_iterator it = theGuess.begin();
        it != theGuess.end();
        it++
        ){
            int howMany =
            count(theGuess.begin(), theGuess.end(),*it);
            if (howMany > 1)
                return false;
        }
    }

    bool isValide = true;

    int correct;
    int position

    for(
        vector<guess>::const_iterator it = history.begin();
        it != history.end();
        it++
        )
    {
        vector<char> temp = it->GetString();

        correct = 0;
        position = 0;

        for (int i = 0; i < Game::howManyLetters; i++)
        {
            int howManyInGuess =
                count(
                      theGuess.begin(),
                      theGuess.end(),
                      alpha[i]
                      );

            int howManyAnswer =
                count(temp.begin(), temp.end(), alpha[i]);
                correct += _MIN(howManyInGuess, howManyAnswer);
        }

        for( i = 0; i < Gmae::howManyPosition; i++)
        {
            if ( theGuess[i] == temp[i] )
                position++;
        }

        if(correct != it->GetScore().first ||
           position != it ->GetScore().second)
        {
            isValide =false;
            break;

            }
    }
    return isValide;
}

Guess Computer::offerGess(bool & quit, bool & isStoring)
{
    quit = false;
    isStoring = false;
    vector<char> theGuess =
    mySmartstring->GetString();
    char temp[80];
    for(;;)
    {
        cout << "\n";
        Display(theGuess);
        cout << "Essai " << round << ". ";
        cout << "Veuillez donner le score. \t";
        cout << "Combien sont correct ? ";
        cin >> temp;

        if ( temp[0] == '-') // c'est un indicateur
        {
            quit = HandleFlag(temp[1], isStoring);
            if( quit)
            {
                nomCorrect = 0;
                numInPosition = 0;
            }
            else
                continue;
        }

        else
        {
            numCorrect = atoi(temp);
            cout << "\t\t\tCombien sont bien placées ?: ";
            cin >> numInPosition;
            round++;
        }
        break;
    }
    Guess thisGuess(theGuess,numCorrect,numInPosition);
    return thisGuess;

}

bool Computer::Play()
{
    bool quit;
    bool isStoring = false;

    if( ! mySmartstring)
        mySmartstring = new SmartString(duplicates);
    vector<char> theGuess;

    bool deletedCharacters = false;

    for(;;)
    {
        Guess theGuess = offerGess(quit, isStoring);
        if(quit)
            break;

        history.push_back(theGuess);

        if ( theGuess.GetScore().second ==
            Game::howManyPositions)
                break;
        if(
           !mySmartstring->CanEliminateCharacters(theGuess) ||
           !isConsistent(mySmartstring->GetString())
           )
            generateAGuess();

    };

    return isStoring;
}

// le joueur a entré -?

void Computer::ShowHelp()
{
    cout << "\t-s Afficher l'historique \n\-t Enregistrer dans un Fichier\n";
    cout << "\t-? Aide\n\t-q Quiter\n" << endl;

}

void Computer::Writer(Writer & wrtr) const
{
    wrtr << false; //non, je suis pas un humain
    Decrypter::Write(wrtr);
    mySmartstring->write(wrtr);
    wrtr << total;
}
