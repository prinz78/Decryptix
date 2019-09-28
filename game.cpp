#include "game.h"
#include "defvals.h"
#include "SmartStr.h"
#include "Decryptr.h"
#include "Human.h"
#include "computer.h"

#include <time.h>

int Game::homManyLetters = 0;
int Game::howManyPositions = 0;


Game::Game(Reader & rdr)
{
    bool isHuman;

    rdr >> isHuman;

    if( isHuman )
        pDecrypter = new Human(rdr);
    else
        pDecrypter = new Computer(rdr);

    rdr >> duplicates;
    rdr >> howManyLetters;
    rdr >> howManyPositions;

    cout << "jeu restauré. \n";
}

Game::Game()
{
    for(;;)
    {
        while(howManyLetters < minLetters ||
              howManyLetterz > maxLetters)
        {
            cout << "nombre de lettres ? (";
            cout << minLetters << "-" << maxLetters << "): ";
            cin >> howManyLetters;

            if( howManyLetters < minLetters ||
               howManyLetters > maxLetters)
            {
                cout << "veuillez entrer un nombre entre ";
                cout << minLetters << "et";
                cout << maxLetters << endl;
            }

        }

        while(howManyPositions < minPos ||
              howManypositions > maxPos)
        {
            cout << "Nombre de position ? (";
            cout << minPos << "-" << maxPos << "): ";
            cin << howManyPositions;
            if (howManyPositions < minPos ||
                howManyPositions > maxPos)
            {
                cout << "Veuillez entrer un nombre entre ";
                cout << minPos << " et " << maxPos << endl;
            }
        }

        char choice = ' ';
        while( choice != 'o' && choice != 'n')
        {
            cout << "Permettre les doubles (o/n) ? ";
            cin >> choice;
        }

        duplicates = choice == 'o' ? true : false;

        if ( ! duplicates && howManyPositions > howManyLetters )
        {
            cout << "\n Impossible de mettre " << howManyLetters;
            cout << " lettres dans " << howManyPositions;
            cout << "positions sans doublons ! ";
            cout << "Essayez à nouveau.\n\n";
            howManyLetters = 0;
            howManyPositions = 0;
            continue;
        }

        choice = ' ';

        while(choice != 'h' && choice != 'c')
        {
            cout << "Qui devine. (H)umain";
            cout << " ou (C)alculateur ? (h/c) ? ";
            cin >> choice;
        }

        bool ok = choice == 'h' ? true : VerifyComputerChoices();
        if( ok )
        {
            if ( choice == 'h')
                pDecrypter = new Human(duplicates);
            else
                pDecrypter = new Computer(duplicates);

            break;
        }
    }

}

void Game::DisplayTime(int totalSeconds)
{
    int totalDays = totalSeconds / secondsInDay;
    int totalHours = totalSeconds / secondsInHour;
    int totalMinutes = totalSeconds / secondsInMinute;

    if( totalDays > 1 )
        cout << totalDays << " jours !";

    else if ( totalHours > 1 )
        cout << totalHours << " heures !";

    else if (totalMinutes > 1 )
        cout << totalMinutes << " minutes. ";

    else
        cout << totalSeconds << " secondes. ";
}

void Game::Play()
{
    int start = time(NULL);

    bool storeGame = pDecrypter->Play();
    if ( storeGame )
        Store();

    int end = time(NULL);
    int totalSeconds = end - start;

    cout << "\n Temps total passé, pour ce jour : ";
    DisplayTime(totalSeconds);

    cout << "\n";

    howManyLetters = 0;
    howManyPositions = 0;
}

bool Game::VerifyComputerChoices()
{
    int totalGuesses = 1;

    if( duplicates )
    {
        for(int i = 0; i < howManyPositions; i++ )
            totalGuesses *= howManyLetters;
        else
            for (
                 int i = howManyLetters;
                  i > howManyLetters - howManyPositions;
                  i-
                 )
                 totalGuesses *= i;

        int totalSeconds = totalGuesses / GUESSES_PER_SECOND;

        if ( totalSeconds > 2 )
        {
            cout << "\n\nVous me deviner ";
            cout << "parmi ";
            cout << totalGuesses;
            cout << " combinaisons possibles. ";

            cout << "\nJe peux venir à bout d'environ ";
            cout << GUESSES_PER_SECOND;
            cout << " combinaisons par seconde. ";
            cout << "Si l'énigme est difficile,";
            cout << "\nune seule proposition peut me prendre plus de ";

            DisplayTime(totalSeconds);

            char confirm = ' ';
            while (confirm != 'o' && confirm != 'n')
            {
                cout << "\n\nEtes-vous sûr de vouloir continuer (o/n) ? ";
                cin >> confirm;
            }

            if ( confirm == 'n')
            {
                howManyLetters = 0;
                howManyPositions = 0;
                return false;
            }
        }

        else
        {
            cout << "choix parmi " << totalGuesses;
            cout << " combinaisons possibles...\n\n";
        }

        return true;

    }

void Game::Write(Writer & wrtr) const
{
    pDecrypter->Write(wrtr);
    wrtr << duplicates;
    wrtr << howManyLetters;
    wrtr << howManyPositions;

}

vois Game::Store()
{
    char fileName[80];
    cout << "Sauvegarder dans le fichier nommé : ";
    cin >> fileName;
    Writer * writer = new Writer(fileName);
    Write(*writer);
    delete writer;
}
