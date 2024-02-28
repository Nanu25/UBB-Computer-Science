class Player():
    def __init__(self, name, symbol):
        self.__name = name
        self.__symbol = symbol
    @property
    def name(self):
        return self.__name

    @property
    def symbol(self):
        return self.__symbol

    def __str__(self):
        return "Player name is: " + self.__name + " and plays with symbol: " + self.__symbol

if __name__ == '__main__':
    player = Player('John', 'X')
    print(player)