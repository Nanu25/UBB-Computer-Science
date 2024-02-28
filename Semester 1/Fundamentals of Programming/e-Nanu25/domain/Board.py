import random

from texttable import Texttable


class Board:
    def __init__(self):
        self.__board = [[" " for i in range(8)] for j in range(8)]
        self.__player_board = [[" " for i in range(8)] for j in range(8)]
        self.game_won = 0
        self.game_lost = 0
        self.alien_count = 0

    @property
    def board(self):
        return self.__board

    @property
    def player_board(self):
        return  self.__player_board

    def __str__(self):
        table = Texttable()

        Header = [" ", "A", "B", "C", "D", "E", "F", "G"]
        table.header(Header)

        for i in range(7):
            row = ""
            row += str(i + 1)
            for j in range(7):
                row += self.__player_board[i][j]
            table.add_row(row)

        return table.draw()

    def place_earth(self):
        self.__board[3][3] = 'E'

    def inside(self, x, y):
        if 0 <= x and x <= 6 and 0 <= y and y <= 6:
            return 1
        return 0

    def check_position(self, x, y):
        if self.__board[x][y] == 'E' or self.__board[x][y] == '*':
            return 0

        ok = 1
        dx = [1, -1, 0, 0, -1, -1, 1, 1]
        dy = [0, 0, -1, 1, -1, 1, 1, -1]
        for i in range(8):
            lin = x + dx[i]
            col = y + dy[i]
            if self.inside(lin, col)  ==  1 and self.__board[lin][col] == '*':
                ok -= 1
        return ok
    def place_asteroids(self):
        number_of_asteroids = 8
        while number_of_asteroids != 0:
            x = random.randint(0, 6)
            y = random.randint(0, 6)
            if self.check_position(x, y) == 1:
                self.__board[x][y] = '*'
                number_of_asteroids -= 1

    def place_aliens(self, number_of_aliens = 2):
        while number_of_aliens != 0:
            option = random.randint(0, 3)
            position = random.randint(0, 1)

            x = random.randint(0, 6)
            y = random.randint(0, 6)
            if self.distance(x, y) == 3 and self.__board[x][y] == " " and (x == 0 or x == 6 or y == 0 or y == 6):
                self.__board[x][y] = 'X'
                number_of_aliens -= 1


            # if option == 0: #first row
            #     if position == 0:
            #         if self.__board[0][2] == ' ':
            #             self.__board[0][2] = 'X'
            #             number_of_aliens -= 1
            #     else:
            #         if self.__board[0][4] == " ":
            #             self.__board[0][4] = 'X'
            #             number_of_aliens -= 1
            # elif option == 1:   #last row
            #     if position == 0:
            #         if self.__board[6][2] == " ":
            #             self.__board[6][2] = 'X'
            #             number_of_aliens -= 1
            #     else:
            #         if self.__board[6][4] == " ":
            #             self.__board[6][4] = 'X'
            #             number_of_aliens -= 1
            # elif option == 2:   #first column
            #     if position == 0:
            #         if self.__board[2][0] == " ":
            #             self.__board[2][0] = 'X'
            #             number_of_aliens -= 1
            #     else:
            #         if self.__board[4][0] == ' ':
            #             self.__board[4][0] = 'X'
            #             number_of_aliens -= 1
            # else:
            #     if position == 0:
            #         if self.__board[2][6] == " ":
            #             self.__board[2][6] = 'X'
            #             number_of_aliens -= 1
            #     else:
            #         if self.__board[4][6] == " ":
            #             self.__board[4][6] = "X"
            #             number_of_aliens -= 1

    def copy_initial_board(self):
        for i in range(7):
            for j in range(7):
                if self.__board[i][j] != 'X':
                    self.__player_board[i][j] = self.__board[i][j]


    def  fire(self, x, y):
        """
        This function fire at the point (x, y) if there is a valid position
        raise TypeError if the position is invalid
        :param x: line of the board
        :param y: column of the board
        :return: nothing
        """
        if self.__board[x][y] == "*" or self.__board[x][y] == "-" or self.inside(x, y) == 0 or self.__board[x][y] == 'E':
            raise TypeError("Invalid fire. Fire again!")

        if self.__board[x][y] == 'X':
            print("You hit an alien!")
            self.alien_count += 1

            if self.alien_count == 2:
                self.game_won = 1

        self.__board[x][y] = '-'
        self.player_board[x][y] = '-'

    def distance(self, x, y):
        return abs(x - 3) + abs(y - 3) - 1

    def place_aliens_random(self, lin, col):
        while True:
            x = random.randint(0, 6)
            y = random.randint(0, 6)
            if self.__board[x][y] == " " and self.distance(lin, col) == self.distance(x, y) and (lin, col) != (x, y):
                self.__board[x][y] = 'X'
                break

    def move_alien(self, how_to_move):
        alien_pos = []
        for i in range(8):
            for j in range(8):
                if self.__board[i][j] == 'X':
                    alien_pos.append((i, j))

        dx = [1, -1, 0, 0, -1, -1, 1, 1]
        dy = [0, 0, -1, 1, -1, 1, 1, -1]

        if how_to_move == 0:        #random move
            for alien in alien_pos:
                self.__board[alien[0]][alien[1]] = ' '
                self.place_aliens_random(alien[0], alien[1])
        else:                       #move one step further
            for alien in alien_pos:
                x = alien[0]
                y = alien[1]

                self.__board[x][y] = " "

                for i in range(8):
                    lin = x + dx[i]
                    col = y + dy[i]
                    if self.inside(lin, col) == 1 and self.distance(lin, col) <= self.distance(x, y) and self.__board[lin][col] == " ":
                        self.__board[lin][col] = 'X'
                        break

        for i in range(8):
            lin = 3 + dx[i]
            col = 3 + dy[i]
            if self.inside(lin, col)  ==  1 and self.__board[lin][col] == 'X':
                self.game_lost = 1


if __name__ == '__main__':
    board = Board()
    board.place_earth()
    board.place_asteroids()
    board.place_aliens()
    board.copy_initial_board()
    print(board)

