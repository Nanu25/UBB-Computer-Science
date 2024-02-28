import random
from src.domain.Id_object import *
from src.utilities.const import *

class Book(id_object):
    def __init__(self, _id, title: str, author: str):
        super().__init__(_id)
        self.__title = title
        self.__author = author


    def __str__(self):
        return f'ID: {self.id}, Title: {self.title}, Author: {self.author}'

    @property
    def title(self):
        return self.__title

    @property
    def author(self):
        return self.__author

def generate_random_book(number_to_generate = NUMBER_TO_GENERATE):
    authors_name = ["Titu Maiorescu", "Mihai Eminescu", "Ion Creanga", "Ioan Slavici", "Gheorghe Panu", "George Cosbuc",
                    "Liviu Rebreanu", "Nichita Stanescu"]
    books_title = [
        "To Kill a Mockingbird",
        "1984",
        "The Great Gatsby",
        "Pride and Prejudice",
        "The Catcher in the Rye",
        "The Lord of the Rings",
        "Harry Potter and the Sorcerer's Stone",
        "The Hobbit",
        "The Chronicles of Narnia",
        "One Hundred Years of Solitude",
        "The Chicken Invaders",
        "The Quran",
        "The Art of War",
        "The Odyssey",
        "The Iliad",
        "Don Quixote",
        "Moby-Dick",
        "War and Peace",
        "Crime and Punishment",
        "The Brothers Karamazov",
        "Brave New World",
        "The Road",
        "The Hunger Games",
        "The Alchemist",
        "The Da Vinci Code",
        "The Girl with the Dragon Tattoo",
        "Gone with the Wind",
        "The Shining",
        "The Hitchhiker's Guide to the Galaxy"]

    _id = 1
    books_list = []
    for index in range(0, number_to_generate):
        author = random.choice(authors_name)
        book_title = random.choice(books_title)
        books_list.append(Book(_id + index, book_title, author))

    return books_list


if __name__ == '__main__':
    books = generate_random_book()
    for book in books:
        print(str(book))

# book = Book(1, 'Amintiri din copilarie', 'Ion Creanga')
# print(str(book))
