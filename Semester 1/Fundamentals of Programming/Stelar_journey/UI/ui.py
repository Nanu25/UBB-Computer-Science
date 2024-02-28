from texttable import Texttable

from Stelar_journey.domain.Board import Board


class Ui:
    def __init__(self, board):
        self.__board = board

    def print_board(self):
        table = Texttable()

        Header = ["0", "1", "2", "3", "4", "5", "6", "7", "8"]
        table.header(Header)

        for i in range(0, 8):
            row = chr(ord("A") + i)
            for j in range(0, 8):
                row += self.__board.board[i][j]
            table.add_row(row)

        return table.draw()
    def Start(self):
        self.__board.place_stars()
        self.__board.place_Endeavour()
        self.__board.place_Blingon()
        self.__board.hidden_board()
        cheat = 0
        while True:
            if cheat == 0:
                print(self.__board)
            else:
                print(self.print_board())
            comand = input("Tell me your comand ")
            comand.strip()

            comand = comand.split(" ")
            # line = int(ord(comand[1][0]) - ord('A'))
            # column = int(comand[1][1]) - 1


            if comand[0] == "wrap":
                line = int(ord(comand[1][0]) - ord('A'))
                column = int(comand[1][1]) - 1

                try:
                    self.__board.move(line, column)
                    self.__board.hidden_board()
                except TypeError as te:
                    print(te)
            elif comand[0] == "fire":
                line = int(ord(comand[1][0]) - ord('A'))
                column = int(comand[1][1]) - 1

                try:
                    self.__board.fire(line, column)
                    self.__board.clear_Blingon()
                    if self.__board.enemy != 0:
                        self.__board.place_Blingon(self.__board.enemy)
                        self.__board.hidden_board()
                except TypeError as te:
                    print(te)
            else:
                cheat += 1
            if self.__board.game_over == 1:
                print("You lose")
                break

            if self.__board.game_won == 1:
                print("You win")
                break