from texttable import Texttable

ROWS = 6
COLUMNS = 7

class Board:
    #the board will be a matrix of 6 * 7
    def __init__(self):
        self.__board =[[' ' for i in range(COLUMNS)] for j in range(ROWS)]

    def __str__(self):
        draw_table = Texttable()
        for i in range(ROWS):
            auxiliary_string = ''
            for j in range(COLUMNS):
                auxiliary_string += self.__board[i][j]
            draw_table.add_row(auxiliary_string)
        return draw_table.draw()

    @property
    def board(self):
        return self.__board

    def move(self, column, symbol):
        if not isinstance(column, int):
            raise TypeError('Column must be an integer')

        if column < 0 or column >= COLUMNS:
            raise ValueError("Invalid column number")

        for i in range(ROWS - 1, -1, -1):
            if self.__board[i][column] == ' ':
                self.__board[i][column] = symbol
                return None

        raise ValueError("The column is full")

    def game_won(self):
        for i in range(ROWS - 3):
            for j in range(COLUMNS):
                if self.__board[i][j] != ' ':
                    if self.__board[i][j] == self.__board[i + 1][j] and self.board[i][j] == self.__board[i + 2][j] and self.board[i][j] == self.__board[i + 3][j]:
                        return True
        for i in range(ROWS):
            for j in range(COLUMNS - 3):
                if self.__board[i][j] != ' ':
                    if self.__board[i][j] == self.__board[i][j + 1] and self.board[i][j] == self.__board[i][j + 2] and self.board[i][j] == self.__board[i][j + 3]:
                        return True

        for i in range(ROWS - 3):
            for j in range(COLUMNS - 3):
                if self.__board[i][j] != ' ':
                    if self.__board[i][j] == self.__board[i + 1][j + 1] and self.__board[i][j] == self.__board[i + 2][j + 2] and self.__board[i][j] == self.__board[i + 3][j + 3]:
                        return True

        for i in range(ROWS - 3):
            j = 6
            while j > 2:
                if self.__board[i][j] != ' ':
                    if self.__board[i][j] == self.__board[i + 1][j - 1] and self.__board[i][j] == self.__board[i + 2][j - 2] and self.__board[i][j] == self.__board[i + 3][j - 3]:
                        return True
                j -= 1

        return False

    def still_play(self):
        for i in range(ROWS):
            for j in range(COLUMNS):
                if self.__board[i][j] == ' ':
                    return True
        return False

if __name__ == '__main__':
    board = Board()
    print(board)

    #board.move(3, C)
    #print(board)
    #print(board.game_won())
    #print(board)