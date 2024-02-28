from texttable import Texttable

from domain.Board import Board


class Ui:
    def __init__(self, board : Board):
        self.__board = board

    def print_board_cheat(self):
        table = Texttable()

        Header = [" ", "A", "B", "C", "D", "E", "F", "G"]
        table.header(Header)

        for i in range(7):
            row = ""
            row += str(i + 1)
            for j in range(7):
                row += self.__board.board[i][j]
            table.add_row(row)

        return table.draw()

    def Start(self):
        self.__board.place_earth()
        self.__board.place_asteroids()
        self.__board.place_aliens()
        self.__board.copy_initial_board()
        cheat = 0
        move = 0
        while True:
            if cheat == 0:
                print(self.__board)
            else:
                print(self.print_board_cheat())

            comand = input("> ")

            comand.strip()
            comand = comand.split(" ")

            if comand[0] == "fire":
                fire = 0
                line = int(comand[1][1]) - 1
                column = ord(comand[1][0]) - ord('A')
                try:
                    self.__board.fire(line, column)
                    fire += 1
                except TypeError as te:
                    print(te)
                    continue
            elif comand[0] == "cheat":
                cheat = 1
                continue

            self.__board.move_alien(move % 2)
            move += 1

            if self.__board.game_won == 1:
                print("You won the game!")
                break

            if self.__board.game_lost == 1:
                print("You lose the game!")
                break