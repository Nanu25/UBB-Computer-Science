from Game_of_life.repository.repo import Repository


class Service:
    def __init__(self, repository : Repository):
        self.__repository = repository

    def place_pattern(self, pattern, x, y):
        found = 0
        for patt in self.__repository.get_data():
            if patt == pattern:
                found = 1

        if found == 0:
            raise TypeError("This pattern doesn' t exist")

        if y + 3 >= 8:
            raise TypeError("This position will be out of matrix")

        if pattern == "blinker":
            for i in range(3):
                if self.get_board().board[x][y + i] == 'X':
                    raise TypeError("This pattern overlaps another pattern")
            for i in range(3):
                self.__repository.get_board().board[x][y + i] = "X"

    def get_board(self):
        return self.__repository.get_board()

    def save_file(self, file_name):
        self.__repository.save_file(file_name)

    def inside(self, x, y):
        return 0 <= x and x <= 7 and 0 <= y and y <= 7

    def count_alive_neighbours(self, lin, col):
        dx = [1, -1, 0, 0, -1, -1, 1, 1]
        dy = [0, 0, -1, 1, -1, 1, 1, -1]

        nr = 0
        for k in range(8):
            l = lin + dx[k]
            c = col + dy[k]
            if self.inside(lin, col) == True and self.__repository.get_board().board[l][c] == 'X':
                nr += 1
        return nr

    def tick_generation(self, years = 1):
        matrix = self.__repository.get_board().board

        for i in range(years):
            for lin in range(8):
                for col in range(8):
                    number = self.count_alive_neighbours(lin, col)
                    if self.__repository.get_board().board[lin][col] == 'X':
                        if number < 2:
                            matrix[lin][col] = " "
                        elif number > 3:
                            matrix[lin][col] = " "
                    else:
                        if number == 3:
                            matrix[lin][col] = "X"

            for lin in range(8):
                for col in range(8):
                    self.get_board().board[lin][col] = matrix[lin][col]