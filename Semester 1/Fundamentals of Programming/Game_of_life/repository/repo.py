from Game_of_life.domain.Board import Board


class Repository:
    def __init__(self, file_name, board : Board):
        self.__board = board
        self.__data = []
        self.__file_name = file_name
        self.__load_file()


    def __load_file(self):
        with open(self.__file_name, "r") as file:
            for line in file.readlines():
                line.strip()
                self.__data.append(line)
        file.close()

    def get_data(self):
        return self.__data

    def get_board(self):
        return self.__board

    def save_file(self, file_name):
        with open(file_name, "w") as file:
            file.write(str(self.__board))
        file.close()



if __name__ == '__main__':
    pass