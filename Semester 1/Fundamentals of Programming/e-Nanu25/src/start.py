from UI.ui import Ui
from domain.Board import Board

#comands:
#fire G4
#cheat

if __name__ == '__main__':
    board = Board()
    ui = Ui(board)

    ui.Start()
