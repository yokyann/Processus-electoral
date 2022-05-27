#include "exercice9.h"
#include <unistd.h>

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void affichage()
{
    printf("\nChoisissez le main de l'exercice que vous voulez : \n");
    printf("1- exercice1\n");
    printf("2- exercice2\n");
    printf("3- exercice3\n");
    printf("4- exercice4\n");
    printf("5- exercice5\n");
    printf("6- exercice6\n");
    printf("7- exercice7\n");
    printf("8- exercice8\n");
    printf("9- exercice9\n");
    printf("-1 pour quitter\n\n");
}

int main()
{
    int status;
    int choix;
    do
    {
        affichage();
        scanf(" %d", &choix);

        clearScreen();
        switch (choix)
        {
        case 1:
            status = system("./exec/exercice1");
            break;
        case 2:
            status = system("./exec/exercice2");
            break;
        case 3:
            status = system("./exec/exercice3");
            break;
        case 4:
            status = system("./exec/exercice4");
            break;
        case 5:
            status = system("./exec/exercice5");
            break;
        case 6:
            status = system("./exec/exercice6");
            break;
        case 7:
            status = system("./exec/exercice7");
            break;
        case 8:
            status = system("./exec/exercice8");
            break;
        case 9:
            status = system("./exec/exercice9");
            break;
        default:
            break;
        }

    } while (choix != -1);

    return 0;
}