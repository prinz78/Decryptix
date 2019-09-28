#include <iostream>
#include <iterator>
#include <vector>

#include "defvals.h"
#include "game.h"
#include "guess.h"

using namespace std;

int main()
{
    cout << "Decryptix. (c)Copyright 2000";
    cout << " Liberty Associates, Inc.";
    cout << "Version 5\n\n" << endl;
    cout << "Il y a deux fa�ons de jouer � Decryptix :";
    cout << "soit en devinant un mod�le cr�e par l'ordinateur, \n";
    cout << "soit en laissant l'ordianteur deviner le v�tres.\n\n";
    cout << "si vous devinez, l'ordinateur va penser � une \n";
    cout << "suite de lettre (par exemple, abcde). \n"
    cout << "A chaque tour, vous faite une proposition et \n";
    cout << "l'ordinateur vous dit combien de lettres sont \n";
    cout << "correcte, et combien parmi celles-ci occupent \n";
    cout << "la position exacte dans le mod�le. \n\n";
    cout << "le but est de decoder l'enigme aussi rapidement ";
    cout << "que possible, vous indiquez combien de lettres\n";
    cout << "peuvent �tre utilis�es et le nombre de positions ";
    cout << " (e.g., 5 lettres possibles dans 4 positions) \n";
    cout << "ainsi que si le mod�le peut ou non contenir \n";
    cout << "des lettres ";
    cout << "en double (e.g, aabcd). \n\n";
    cout << "Si l'ordinateur devine vous pensez � une suite ";
    cout << "de lettres et donnez le score de chaque reponse. \n\n";

    bool playAgain = true;

    while(playAgain)
    {
        Game * g;

        char resume = ' ';
        while (
               resume != 'r' && resume != 'n' &&
               resume != 'R' && resume != 'N')
        {
            cout << "R)eprendre un jeu existant ou en commencer un N)ouveau ? ";
            cin >> resume
        }

        if ( resume == 'r' || resume == 'R'){

            char fileName[80]:
            cout << "Reprendre � partir du fichier nomm� : ";
            cin >> fileName;
            cin.ignore(1, '\n');
            Reader * reader = new Reader(fileName);
            g = new Game(*reader);
            delete reader;
        }
        else
            g = new Game;

        g->Play();
        delete g;

            char choice = ' ';
            while (choice != 'o' && choice != 'n' )
            {
                cout << "\nRejouer (o/n) : ";
                cin >> choice;
            }

            playAgain = choice == 'o' ? true : false;
    }

    return 0;
}
