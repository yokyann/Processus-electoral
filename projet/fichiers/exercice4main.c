#include "exercice4.h"
#include <unistd.h>

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void affichage()
{
    printf("Pour voir le contenu des fichiers :\n");
    printf("1-keys.txt\n");
    printf("2-candidates.txt\n");
    printf("3-declarations.txt\n");
    printf("-1 pour quitter\n");
}

int main(int argc, char **argv)
{

    srand(time(NULL));

    printf("TEST : Generation de 100 citoyens et de 10 candidats parmi les citoyens\n\n");
    generate_random_data(10, 2);

    int status;
    int choix;

    while (1)
    {
        affichage();
        scanf(" %d", &choix);
        clearScreen();

        if (choix == -1)
        {
            break;
        }

        switch (choix)
        {
        case 1:
            status = system("cat ./data/keys.txt");
            break;
        case 2:
            status = system("cat ./data/candidates.txt");
            break;
        case 3:
            status = system("cat ./data/declarations.txt");
            break;

        default:
            break;
        }
    }

    return 0;
}
