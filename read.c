#include <string.h>
#include <stdio.h>
#include "read.h"

FILE* open_file(char* fileName){
    //открываем файл
    FILE *file = fopen(fileName, "r");
    if (file){
        //проверка есть ли такой файл
        return file;
    }else{
        printf("%s\n", "Can't open this file!");
        return NULL;
    }
}


//считывание книги
void readBook(char *s, Book *book){
    //на вход получили строчку, запоминаем каждый параметр в нужную графу структуры book
    //этот кусок кода не оч важен, забить.
    char tmpNum[30];
    int j = 0;
    for (int i = 0; s[i] != ';' && s[i] != '\0' && s[i] != '\n'; i++){
        tmpNum[j] = s[i];
        j++;
    }
    tmpNum[j] = '\0';
    book->isbn = tmpNum;

    char tmpAuthor[128];
    int k = 0;
    for (int i = j + 1; s[i] != ';' && s[i] != '\0' && s[i] != '\n'; i++){
        tmpAuthor[k] = s[i];
        k++;
    }
    tmpAuthor[k] = '\0';
    book->author = tmpAuthor;

    char tmpName[128];
    int t = 0;
    for (int i = j + k + 2; s[i] != ';' && s[i] != '\0' && s[i] != '\n'; i++){
        tmpName[t] = s[i];
        t++;
    }
    tmpName[t] = '\0';
    book->bookName = tmpName;

    int g = 0;
    char tmpCount[128];
    for (int i =j + k + t + 3; s[i] != ';' && s[i] != '\0' && s[i] != '\n'; i++){
        tmpCount[g] = s[i];
        g++;
    }
    tmpCount[g] = '\0';
    book->bookCount = atoi(tmpCount);

    char leftCount[128];
    int n = 0;
    for (int i = j + k + t + g + 4; s[i] != ';' && s[i] != '\0' && s[i] != '\n'; i++){
        leftCount[n] = s[i];
        n++;
    }
    leftCount[n] = '\0';
    book->bookAvailable = atoi(leftCount);
    //получили заполненную книгу
};




void saveBooks(char* fileName, Book *library[HASHSIZE]){
    //на вход поступает файл, мы сохраняем его и соответсвующее книги вставляем в хэштаблицу
    printf("Scanning books...\n");
    char bookStr[254];
    FILE *file = open_file(fileName);
    if (file) {
        int i = 0;
        Book tmp;
        //считываем построчно из файла, запоминаем все парметры книги в структуру book, вставляем в хэштабл
        while (fgets(bookStr, 100, file) && i < HASHSIZE) {
            readBook(bookStr, &tmp);
            install(&tmp);
            i++;
        }
        printf("Scanned!...\n\n");
    }
}



void update(Book *library[]){
    // сохранение всего что мы сделали в новый файл
    printf("Updating...\n");
    FILE *file = fopen("booksResult.csv", "w");
    if (file) {
        for (int i = 0; i < HASHSIZE; i++) {
            if (library[i]) {
                fprintf(file, "%s;%s;%s;%d;%d\n", library[i]->isbn, library[i]->author,
                       library[i]->bookName, library[i]->bookCount, library[i]->bookAvailable);
            }

        }
    }else{
        printf("Не удалось открыть файл для записи\n");
    }
}



void addBook(){
    //функция добавления новой книги
    char isbn[64];
    char author[64];
    char name[64];
    int Count;
    int Available;
    printf("Cейчас будем добавлять новую книгу\n");
    printf("Введите номер ISBN: ");
    scanf("%s", isbn);
    printf("%s\n", isbn);
    printf("Введите имя автора: ");
    fflush(stdin);
    //fgets(name, 64, stdin);
    scanf("%s", author);
    printf("Введите название книги: ");
    scanf("%s", name);
    printf("Введите количество книг всего: ");
    scanf("%d", &Count);
    printf("Введите количество достпуаных книг: ");
    scanf("%d", &Available);

    Book book;
    book.isbn = isbn;
    book.author = author;
    book.bookName = name;
    book.bookCount = Count;
    book.bookAvailable = Available;
    install(&book);
}




int delete(){
    //функция удаления книги
    char isbn[64];
    unsigned hashval;
    printf("Cейчас будем удалять книгу\n");
    printf("Введите номер ISBN: \n");
    scanf("%s", isbn);
    //проверяем была ли такая книги и удаляем
    if (lookup(isbn) != NULL) {
        hashval = hash(isbn);
        deleteBook(library[hashval]);
        return 0;
    }
    //иначе выводим ошибку
    printf("Такой книги не было \n");
    return 1;
}




int showBook(){
    //функция вывода информации по книге
    char isbn[64];
    unsigned hashval;
    printf("Введите ISBN книги, о которой хотите узнать:");
    scanf("%s", isbn);
    if (lookup(isbn) != NULL){
        //если книга была, то выводим инфу по ней
        hashval = hash(isbn);
        printf("\n%s%s\n", "ISB книги: ", library[hashval]->isbn);
        printf("%s%s\n", "Автор книги: ", library[hashval]->author);
        printf("%s%s\n", "Имя книги: ", library[hashval]->bookName);
        printf("%s%d\n", "Всего книг было: ", library[hashval]->bookCount);
        printf("%s%d\n", "Доступно книг: ",library[hashval]->bookAvailable);
        return 0;
    }
    printf("Такой книги не было \n");
    return 1;
}



//для qsort нужно
int compare(const void * x1, const void * x2) {
    return ( *(int*)x1 - *(int*)x2 );
}



void showLibrary(Book *library[]){
    //функция вывод нашей библиотеки
    //создали массив для сортирокви
    int arrIsbn[HASHSIZE];
    int countBooks = 0;
    unsigned hashval;
    char buffer[16];
    for (int i = 0 ; i < HASHSIZE; i++){
        if (library[i]) {
            arrIsbn[countBooks] = atoi(library[i]->isbn);
            countBooks++;
        }
    }
    //быстрая сортировка
    qsort(arrIsbn, (size_t)countBooks, sizeof(int), compare);
    printf("Отсортированный список книг:\n");
    //вывод отсторитрованной библиотеки
    for (int i = 1; i < countBooks; i++){
        snprintf(buffer, 16, "%d", arrIsbn[i]);
        hashval = hash(buffer);
        printf("ISBN: %s\t Аавтор: %s \tНазвание: %s \tКол-во: %d \tОсталось: %d\n", library[hashval]->isbn,
               library[hashval]->author, library[hashval]->bookName, library[hashval]->bookCount, library[hashval]->bookAvailable);
    }
}



int changeBook(){
    //функция изменения информации книги
    char isbn[64];
    char newAuthor[64];
    char newName[64];
    unsigned hashval;
    printf("Введите номер книги, которую будем редактировать. Если поле не требует изменения введите -\n");
    scanf("%s", isbn);
    hashval = hash(isbn);
    if (lookup(isbn)){
        //если книга была, то редактируем ее
        printf("%s %s\n", "Редактируем книгу", library[hashval]->isbn);
        printf("Введите нового автора:");
        scanf("%s", newAuthor);
        if(strcmp(newAuthor, "-")) {
            memcpy(library[hashval]->author, newAuthor, 64);
        }
        printf("%s %s\n", "Автор:", library[hashval]->author);

        printf("Введите новое название книги:");
        scanf("%s", newName);
        if(strcmp(newName, "-")) {
            memcpy(library[hashval]->bookName, newName, 64);
        }
        printf("%s %s\n", "Название:", library[hashval]->bookName);

        char newCount[16];
        printf("Введите новое значение для количества кинг:");
        scanf("%s", newCount);
        if (strcmp(newCount, "-")){
            library[hashval]->bookCount = atoi(newCount);
        }

        char newAvailable[16];
        printf("Введите новое значение для количества доступных кинг:");
        scanf("%s", newAvailable);
        if (strcmp(newAvailable, "-")){
            if(atoi(newAvailable) > library[hashval]->bookCount) {
                library[hashval]->bookAvailable = library[hashval]->bookCount;
            }else{
                library[hashval]->bookAvailable = atoi(newAvailable);
            }
        }
        return 0;
    }
    printf("Такой книги нет в библиотеке!\n");
    return 1;
}




void countAvailable(){
    //функция подсчета доступных книг
    int allBooks = 0;
    for (int i = 0; i < HASHSIZE; i++){
        if (library[i]){
            printf("%s - %d\n", library[i]->isbn, library[i]->bookAvailable);
            allBooks+=library[i]->bookAvailable;
        }
    }
    printf("%s%d%s\n", "В библиотеке ", allBooks, " книг\n");
}



void giveBook(){
    //выдать книгу студенту
    unsigned hashval;
    char buff[16];
    printf("Выдать книгу студенту. Введите номер: ");
    scanf("%s", buff);
    if (lookup(buff)){
        hashval = hash(buff);
        //проверяем есть ли доступные книги и уменьшаем их количестов на 1
        if (library[hashval]->bookAvailable > 0){
            library[hashval]->bookAvailable -= 1;
            printf("Книга выдана студенту\n");
        }else{
            printf("Доступных книг сейчас нету\n");
        }
    } else{
        printf("Нет такой кнги\n");
    }
}



void takeBook(){
    //функция взятие книги у студента
    unsigned hashval;
    char buff[16];
    printf("Забрать книгу у студента. Введите номер: ");
    scanf("%s", buff);
    if (lookup(buff)){
        //если книга была, то увеличваем количестов книг на 1
        hashval = hash(buff);
        if (library[hashval]->bookAvailable < library[hashval]->bookCount ){
            library[hashval]->bookAvailable += 1;
            printf("Книга взята у студента\n");
        }else{
            printf("Данных книг слишком много\n");
        }
    } else{
        printf("Нет такой кнги\n");
    }
}