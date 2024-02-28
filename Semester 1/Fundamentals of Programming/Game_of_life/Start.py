from Game_of_life.UI.Ui import Ui
from Game_of_life.domain.Board import Board
from Game_of_life.repository.repo import Repository
from Game_of_life.service.service import Service

#place blinker x y
#tick [years]
#save filename

if __name__ == '__main__':
    board = Board()
    repository = Repository("input.txt", board)
    service = Service(repository)
    ui = Ui(service)
    ui.Start()
