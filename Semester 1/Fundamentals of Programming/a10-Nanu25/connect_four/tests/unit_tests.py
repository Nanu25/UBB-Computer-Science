import unittest

from connect_four.domain.board import Board
from connect_four.domain.computer import Computer
from connect_four.domain.player import Player


class UnitTest(unittest.TestCase):
    def setUp(self):
        self.board = Board()
        self.player = Player("Alex", "X")
        self.computer = Computer("0", "X", 4)

    def test_move(self):
        self.board.move(1, self.player.symbol)
        self.assertIn(self.player.symbol, self.board.board[5])

        #computer move
        self.board.move(self.computer.make_move(self.board), self.computer.symbol)
        self.assertIn(self.computer.symbol, self.board.board[5])


    def test_win_column(self):
        self.board.move(1, self.player.symbol)
        self.board.move(1, self.player.symbol)
        self.board.move(1, self.player.symbol)
        self.board.move(1, self.player.symbol)

        self.assertTrue(self.board.game_won())

    def test_win_row(self):
        self.board.move(1, self.computer.symbol)
        self.board.move(0, self.computer.symbol)
        self.board.move(2, self.computer.symbol)
        self.board.move(3, self.computer.symbol)

        self.assertTrue(self.board.game_won())

    def test_win_diagonal(self):
        self.board.move(0, self.player.symbol)
        self.board.move(1, self.computer.symbol)
        self.board.move(1, self.player.symbol)
        self.board.move(2, self.computer.symbol)
        self.board.move(2, self.computer.symbol)
        self.board.move(2, self.player.symbol)
        self.board.move(3, self.computer.symbol)
        self.board.move(3, self.computer.symbol)
        self.board.move(3, self.computer.symbol)
        self.board.move(3, self.player.symbol)

        self.assertTrue(self.board.game_won())


if __name__ == '__main__':
    unittest.main()