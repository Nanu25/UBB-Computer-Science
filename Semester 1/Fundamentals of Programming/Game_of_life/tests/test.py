import copy
import unittest

from Game_of_life.domain.Board import Board
from Game_of_life.repository.repo import Repository
from Game_of_life.service.service import Service


class test(unittest.TestCase):
    def setUp(self):
        self.__board = Board()
        self.__repository = Repository("input.txt", self.__board)
        self.__service = Service(self.__repository)

    def test_tick_function(self):
        self.__service.place_pattern("blinker", 2, 2)
        matrix = copy.deepcopy(self.__service.get_board().board)

        self.__service.tick_generation(10)
        self.assertNotEqual(matrix, self.__service.get_board().board)

        self.__service.tick_generation()
        self.assertNotEqual(matrix, self.__service.get_board().board)