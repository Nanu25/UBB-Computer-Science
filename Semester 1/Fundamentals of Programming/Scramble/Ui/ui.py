import copy

from Scramble.service.service import Service


class Ui():
    def __init__(self, service : Service):
        self.__service = service
        self.__sentence = None
        self.__shuffle_sentence = None
        self.__undo = []

    def __Validate_comand(self, comand):
        copy_comand = copy.deepcopy(comand)

        copy_comand = copy_comand.split("-")
        if len(copy_comand) != 2:
            raise TypeError("Invalid comand")


    def __game_won(self):
        if str(self.__sentence) == str(self.__shuffle_sentence):
            return True
        return False

    def Start(self):
        print("Welcome to the scramble game")

        self.__sentence = self.__service.get_random_sentence()
        self.__shuffle_sentence = self.__service.shuffle_sentence_better(self.__sentence)
        self.__service.count_score(self.__sentence)
        self.__undo.append((self.__shuffle_sentence, self.__service.score))
        print("The sentence is: " + self.__shuffle_sentence + "Your score is:" + str(self.__service.score))

        while(True):
            print("")
            print("1 for swap 2 letters")
            print("2 for undo last operation")
            option = int(input("Tell me your option"))

            if(option == 1):

                comand = input("Tell your letters to swap: " )

                comand.strip()
                try:
                    self.__Validate_comand(comand)
                    comand = comand.split(' ')
                    word1 = int(comand[1])
                    letter1 = int(comand[2])

                    word2 = int(comand[4])
                    letter2 = int(comand[5])

                    if letter1  == 0 or letter2 == 0:
                        print("You must not swap the first letter")
                        continue

                    self.__shuffle_sentence = self.__service.swap_letters(self.__shuffle_sentence, word1, letter1, word2, letter2)
                    print("The sentence is: " + self.__shuffle_sentence + "Your score is:" + str(self.__service.score))

                    self.__undo.append((self.__shuffle_sentence, self.__service.score))
                except TypeError as Te:
                    print(Te)

                if self.__service.score == 0:
                    print("You lose the game")
                    break
                if self.__game_won() == True:
                    print("You win! Your score is " + str(self.__service.score))
                    break
            else:
                self.__undo.pop()
                self.__shuffle_sentence, self.__service.score = self.__undo[len(self.__undo) - 1]
                print("The sentence is: " + self.__shuffle_sentence + "Your score is:" + str(self.__service.score))