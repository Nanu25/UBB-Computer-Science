import unittest

from domain.Board import Board


class Test(unittest.TestCase):
    def setUp(self):
        self.__board = Board()
        self.__board.place_earth()
        self.__board.place_asteroids()
        self.__board.place_aliens()

    def test_fire(self):
        self.__board.fire(1, 1)
        self.assertTrue(self.__board.game_won == False)

    def test_game_won(self):
        for i in range(8):
            for j in range(8):
                if self.__board.board[i][j] == 'X':
                    self.__board.fire(i, j)

        self.assertTrue(self.__board.game_won == 1)

    def test_hit_asteroid(self):
        points = []
        for i in range(8):
            for j in range(8):
                if self.__board.board[i][j] == '*':
                    points.append((i, j))

        try:
            self.__board.fire(points[0][0], points[0][1])
        except TypeError as te:
            print(te)

    def test_fire_multiple(self):
        self.__board.fire(1, 1)
        try:
            self.__board.fire(1, 1)
        except TypeError as te:
            print(te)