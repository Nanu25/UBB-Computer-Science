from texttable import Texttable


class Board:
    def __init__(self):
        self.__matrix = [[" " for i in range(9)] for j in range(9)]

    def __str__(self):
        table = Texttable()

        for i in range(8):
            row = ""
            for j in range(8):
                row += self.__matrix[i][j]

            table.add_row(row)

        return table.draw()

    @property
    def board(self):
        return self.__matrix

if __name__ == '__main__':
    board = Board()
    print(board)