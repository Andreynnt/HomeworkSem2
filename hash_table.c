#include "hash_table.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



unsigned hash(char *s){
    unsigned hashval;
    //на вход получаем строку и переводим ее в хэш значение для library
    for (hashval = 0; *s != '\0'; s++){
        hashval = *s + 31 *hashval;
    }
    return hashval % HASHSIZE;
}

Book *lookup(char *s){
    //проверяем по номеру isbm была ли книга
    Book *book;
    for (book = library[hash(s)]; book != NULL; book = book->next){
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
        tmp = (Book*)malloc(sizeof(*tmp));
        if ((tmp == NULL) || (tmp->isbn = strdup(book->isbn)) == NULL){
            return NULL;
        }
        hashval = hash(book->isbn);
        tmp->next = library[hashval];

        tmp->author = (char*)malloc(64);
        memcpy(tmp->author, book->author, 64);

        tmp->bookName = (char*)malloc(64);
        memcpy(tmp->bookName, book->bookName, 64);

        tmp->bookCount = book->bookCount;
        tmp->bookAvailable = book->bookAvailable;
        tmp->next = NULL;

        library[hashval] = tmp;

    }else{
        printf("Книга %s уже есть в библиотеке\n", book->isbn);
        return NULL;
    }
}

void deleteBook(Book *book){
    if(lookup(book->isbn) != NULL){
        free(book->author);
        free(book->bookName);
        free(book->isbn);
        free(book);
        printf("Книга была удалена\n");
    }
}

void deleteLibrary(Book *library[]){
    for (int i = 0; i < HASHSIZE; i++){
        if (library[i]){
            free(library[i]->isbn);
            free(library[i]->author);
            free(library[i]->bookName);
        }
    }
}