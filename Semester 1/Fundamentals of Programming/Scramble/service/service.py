import copy
import random

from Scramble.repository.repository import Repository


class Service:
    def __init__(self, sentence_repository : Repository):
        self.__sentence_repository = sentence_repository
        self.score = 0
    def get_random_sentence(self):
        sentence = random.choice(self.__sentence_repository.get_data())
        sentence.strip()
        return sentence

    def shuffle_sentence(self, sentence):
        shuffle_sentance = list(sentence)
        shuffle_sentance[1], shuffle_sentance[2] = shuffle_sentance[2], shuffle_sentance[1]

        #make the sentence back
        shuffle_sentance_list = ""
        for letter in shuffle_sentance:
            shuffle_sentance_list += letter
        return shuffle_sentance_list

    def shuffle_sentence_better(self, sentence):
        new_sentence = copy.deepcopy(sentence)

        new_sentence.strip()
        new_sentence = new_sentence.split(' ')

        better_sentence = ""
        for sen in new_sentence:
            propozitie = list(sen)

            for i in range(1, len(propozitie) - 3):
                propozitie[i], propozitie[i + 1] = propozitie[i + 1], propozitie[i]

            new_sen = ""
            for letter in propozitie:
                new_sen += letter

            better_sentence += new_sen + " "

        better_sentence = better_sentence[:-1]
        return better_sentence

    def count_score(self, sentence):
        for letter in sentence:
            if ('a' <= letter and letter <= 'z') or ('A' <= letter and letter <= 'Z'):
                self.score += 1

    def swap_letters(self, sentence_aux, first_word, first_letter, last_word, last_letter):
        self.score -= 1
        sentence = copy.deepcopy(sentence_aux)
        swapped_sentence = sentence.split(" ")
        swapped_sentence = list(swapped_sentence)

        if first_word != last_word:
            word1 = list(swapped_sentence[first_word])
            word2 = list(swapped_sentence[last_word])

            word1[first_letter], word2[last_letter] = word2[last_letter], word1[first_letter]

            swapped_sentence[first_word] = ''.join(word1)
            swapped_sentence[last_word] = ''.join(word2)
        else:
            word = list(swapped_sentence[first_word])
            word[first_letter], word[last_letter] = word[last_letter], word[first_letter]
            swapped_sentence[first_word] = ''.join(word)


        swaped_sentance_list = ""
        for letter in swapped_sentence:
            swaped_sentance_list += letter + " "

        swaped_sentance_list = swaped_sentance_list[:-1]
        return swaped_sentance_list



if __name__ == '__main__':
    repository = Repository("input.txt")
    sentence_service = Service(repository)
    sentence = sentence_service.get_random_sentence()
    sentence = sentence_service.shuffle_sentence(sentence)

    print(sentence)

    sentence = sentence_service.shuffle_sentence_better(sentence)
    print(sentence)