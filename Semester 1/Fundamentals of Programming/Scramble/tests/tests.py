import unittest

from Scramble.repository.repository import Repository
from Scramble.service.service import Service


class Test(unittest.TestCase):
    def setUp(self):
        self.__repository = Repository("input.txt")
        self.__service = Service(self.__repository)
        self.__sentence =  self.__service.get_random_sentence()

    def test_score(self):
        initial_score = self.__service.score
        self.__service.count_score(self.__sentence)
        self.assertNotEqual(initial_score, self.__service.score)

    def test_swap_letters(self):
        swapped_sentence = self.__service.swap_letters(self.__sentence, 0, 0, 0, 1)
        self.assertNotEqual(swapped_sentence, self.__sentence)

