from Stelar_journey.UI.ui import Ui
from Stelar_journey.domain.Board import Board

#cheat
#fire G4
#wrap G4(row, column, diag)

if __name__ == '__main__':

    board = Board()
    ui = Ui(board)
    ui.Start()