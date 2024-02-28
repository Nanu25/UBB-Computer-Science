class Repository:
    def __init__(self, file_name):
        self.__file_name = file_name
        self.__data = []
        self.__load_file()

    def __load_file(self):
        with open(self.__file_name, "r") as file:
            for line in file.readlines():
                line.strip()
                self.__data.append(line)
        file.close()

    def get_data(self):
        return self.__data

if __name__ == '__main__':
    sentenceses = Repository("input.txt")
    for sentence in sentenceses.get_data():
        print(sentence)