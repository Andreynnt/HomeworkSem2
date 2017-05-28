#include "hash_table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//функция хэширования - получаем строку(номер книги) и преобразуем в номер для хэш таблицы
unsigned hash(char *s){
    unsigned hashval;
    //на вход получаем строку и переводим ее в хэш значение для library
    for (hashval = 0; *s != '\0'; s++){
        hashval = *s + 31 *hashval;
    }
    return hashval % HASHSIZE;
}



Book *lookup(char *s){
    //проверяем по номеру isbm была ли книга, если да, то возвращаем ссылку на нее
    Book *book;
    for (book = library[hash(s)]; book != NULL; book = book->next){
        //проверяем совпадение
        if (strcmp(s, book->isbn) == 0){
            return book;
        }
    }
    return NULL;
}



Book *install(Book *book){
    //вставляет новую книгу, если ее не было
    Book *tmp;
    unsigned hashval;
    if ((tmp = lookup(book->isbn)) == NULL){
        //если не было, выделяем память под новую книгу
        tmp = (Book*)malloc(sizeof(*tmp));
        if ((tmp == NULL) || (tmp->isbn = strdup(book->isbn)) == NULL){
            return NULL;
        }
        hashval = hash(book->isbn);
        tmp->next = library[hashval];

        //выделяем память под автора книги и присваеваем его
        tmp->author = (char*)malloc(64);
        memcpy(tmp->author, book->author, 64);
        //выделяем память под название книги и присваеваем его
        tmp->bookName = (char*)malloc(64);
        memcpy(tmp->bookName, book->bookName, 64);

        //заполняем количество книг и количество доступных
        tmp->bookCount = book->bookCount;
        tmp->bookAvailable = book->bookAvailable;
        tmp->next = NULL;

        library[hashval] = tmp;

    }else{
        //если книга уже была, выводи ошибку
        printf("Книга %s уже есть в библиотеке\n", book->isbn);
        return NULL;
    }
}



void deleteBook(Book *book){
    unsigned hashval;
    //если книга былпа, то освобождаем ранее выделенную память
    if(lookup(book->isbn) != NULL){
        hashval =  hash(book->isbn);
        free(book->author);
        free(book->bookName);
        free(book->isbn);
        free(book);
        library[hashval] = NULL;
        printf("Книга была удалена\n");
    }
}



void deleteLibrary(Book *library[]){
    //проходим по всей хэш таблицы и чистим все книги
    for (int i = 0; i < HASHSIZE; i++){
        if (library[i]){
            free(library[i]->isbn);
            free(library[i]->author);
            free(library[i]->bookName);
        }
    }
}