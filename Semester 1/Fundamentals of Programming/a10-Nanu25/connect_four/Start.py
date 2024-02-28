from connect_four.UI.ui import Ui
from connect_four.domain.board import Board
from connect_four.domain.computer import Computer
from connect_four.domain.player import Player
EASY = 1
MEDIUM = 2
HARD = 3
EXTREME_HARD = 4

if __name__ == '__main__':
    board = Board()
    player_name = input("Enter the player name: ")
    player = Player(player_name, 'X')
    computer = Computer("O", "X", EXTREME_HARD)

    ui = Ui(player, computer, board)
    ui.option_menu()