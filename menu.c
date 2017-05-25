#include "menu.h"
#include "read.h"


int show_menu(){
    int selected = 0;
    printf("Добро пожаловать в библиотеку!\n\n");

        printf("Выберете пункт из меню: \n");
        printf("1.  Добавить новую книгу\n");
        printf("2.  Удалить книгу\n");
        printf("3.  Показать информацию по книге\n");
        printf("4.  Вывести список всех книг\n");
        printf("5.  Редактировать информацию по книге\n");
        printf("6.  Посчитать количество доступных книг в библиотеке\n");
        printf("7.  Выдать книгу студенту\n");
        printf("8.  Принять книгу от студента\n");
        printf("10. Сохранить текущее состояние и выйти\n");

    //бесконечный цикл, чтобы выйти надо нажать 10
        while (1) {
            printf("Ожидание команды:");
            scanf("%d", &selected);
            printf("%s%d\n", "Выбранная команда ", selected);
            switch (selected) {
                case 10:
                    update(library);
                    printf("До свидания!");
                    return selected;
                case 1:
                    addBook();
                    break;
                case 2:
                    delete();
                    break;
                case 3:
                    showBook();
                    break;
                case 4:
                    showLibrary(library);
                    break;
                case 5:
                    changeBook();
                    break;
                case 6:
                    countAvailable();
                    break;
                case 7:
                    giveBook();
                    break;
                case 8:
                    takeBook();
                    break;
                default:
                    printf("Нет такой команды\nВыучите сначала правила!\n");
                    return 1;
            }
        }

}
