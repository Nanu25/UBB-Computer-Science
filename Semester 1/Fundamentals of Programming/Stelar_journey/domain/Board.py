import random

from texttable import Texttable


class Board:
    def __init__(self):
        self.__board = [[' ' for i in range(9)] for j in range(9)]
        self.__player_board = [[' ' for i in range(9)] for j in range(9)]
        self.__posx = 0
        self.__posy = 0
        self.__game_over = 0
        self.__game_won = 0
        self.__enemy = 3

    @property
    def game_over(self):
        return self.__game_over

    @property
    def game_won(self):
        return self.__game_won

    @property
    def enemy(self):
        return self.__enemy

    @property
    def board(self):
        return self.__board

    @property
    def player_board(self):
        return self.__player_board

    def __str__(self,):
        table = Texttable()

        Header = ["0", "1", "2", "3", "4", "5", "6", "7", "8"]
        table.header(Header)

        for i in range(0, 8):
            row = chr(ord('A') + i)
            for j in range(0, 8):
                row += self.__player_board[i][j]

            table.add_row(row)

        return table.draw()

    def inside(self, x, y):
        return 0 <= x and x <= 7 and 0 <= y and y <= 7

    def good_position(self, x, y):
        if self.__board[x][y] != " ":
            return 0

        dx = [1, -1, 0, 0, -1, -1, 1, 1]
        dy = [0, 0, -1, 1, -1, 1, 1, -1]
        for i in range(0, 8):
            newx = x + dx[i]
            newy = y + dy[i]
            if self.inside(newx, newy) and self.__board[newx][newy] == '*':
                return 0

        return 1

    def place_stars(self, number_of_starts = 10):
        """
        This function place starts on the empty board
        :param number_of_starts: how many starts i want to place(usually is 10)
        :return: none
        """

        while number_of_starts != 0:
            x = random.randint(0, 7)
            y = random.randint(0, 7)
            if self.good_position(x, y) == 1:
                self.__board[x][y] = '*'
                number_of_starts -= 1


    def place_Endeavour(self):
        while True:
            x = random.randint(0, 7)
            y = random.randint(0, 7)
            if self.__board[x][y] != '*':
                self.__board[x][y] = 'E'
                self.__posx = x
                self.__posy = y
                break

    def place_Blingon(self, number = 3):
        while number != 0:
            x = random.randint(0, 7)
            y = random.randint(0, 7)
            if self.__board[x][y] == " ":
                self.__board[x][y] ='B'
                number -= 1

    def clear_Blingon(self):
        for i in range(0, 8):
            for j in range(0, 8):
                if self.board[i][j] == 'B':
                    self.board[i][j] = " "

    def hidden_board(self):
        b_list = []
        for i in range(0, 8):
            for j in range(0, 8):
                self.__player_board[i][j] = self.__board[i][j]
                if self.__board[i][j] == "B":
                    b_list.append((i, j))

        for point in b_list:
            posx = point[0]
            posy = point[1]
            dx = [1, -1, 0, 0]
            dy = [0, 0, -1, 1]
            ok = 0
            for i in range(0, 4):
                newx = posx + dx[i]
                newy = posy + dy[i]
                if self.inside(newx, newy) and self.__player_board[newx][newy] == 'E':
                    ok += 1

            if ok != 0:
                self.__player_board[posx][posy] = 'B'
            else:
                self.__player_board[posx][posy] = " "

    def move(self, x, y):
        if self.inside(x, y) == 0:
            raise TypeError("Invalid position")

        if x == self.__posx or y == self.__posy or  x + y == self.__posx + self.__posy or x - y == self.__posx - self.__posy:
            if self.__board[x][y] == 'B':
                self.__game_over = 1

            #move the ship
            self.__board[self.__posx][self.__posy] = " "
            self.__player_board[self.__posx][self.__posy] = " "

            self.__board[x][y] = 'E'
            self.__player_board[x][y] = 'E'
            self.__posx = x
            self.__posy = y

        else:
            raise TypeError("The ship must move on the same linie/column/diagonal")

    def fire(self, x, y):
        if self.inside(x, y) == 0:
            raise TypeError("Invalid position")

        if abs(x - self.__posx) + abs(y - self.__posy) != 1:
            raise TypeError("Invalid position")

        self.__board[x][y] = " "
        self.__player_board[x][y] = " "

        self.__enemy -= 1

        if self.__enemy == 0:
            self.__game_won = 1



if __name__ == '__main__':
    brd = Board()

    brd.place_stars()
    brd.place_Endeavour()
    brd.place_Blingon()
    brd.hidden_board()
    print(brd)

