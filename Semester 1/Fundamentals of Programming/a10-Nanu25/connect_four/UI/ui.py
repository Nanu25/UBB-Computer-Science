from connect_four.domain.board import Board, COLUMNS
from connect_four.domain.computer import Computer
from connect_four.domain.player import Player
HUMAN = 0
PLAYER1 = 0
HUMAN_VS_COMPUTER = 1

class Ui():
    def __init__(self, human_player : Player, computer_player  : Computer, board : Board):
        self.__human_player = human_player
        self.__computer_player = computer_player
        self.__board = board
        self.__second_player = None

    def print_menu(self):
        print("Welcome to Connect Four!")
        print("1 for human vs computer")
        print("2 for human vs human")
        print("0 for exit")

    def display_board(self):
        print(self.__board)

    def check_column(self, column):
        if not isinstance(column, int):
            raise TypeError('Column must be an integer')

        if column < 0 or column > COLUMNS:
            raise ValueError("Invalid column number")

        return True

    def option_menu(self):
        self.print_menu()
        option = int(input("Enter your choice: "))
        if option == HUMAN_VS_COMPUTER:
            self.start_game_human_computer()
        else:
            self.start_game_human_human()

    def start_game_human_computer(self):
        move = 0
        last_move = None
        self.display_board()
        won = False
        while self.__board.still_play():
            if move % 2 == HUMAN:
                while True:
                    try:
                        print(self.__human_player.name + " chose a column to move")
                        column = int(input("Enter the column number(between 1 and 7): "))
                        column -= 1
                        self.__board.move(column, self.__human_player.symbol)
                        last_move = column
                        break
                    except ValueError as ve:
                        print(ve)

                if self.__board.game_won() == True:
                    print(str(self.__human_player.name) + " won")
                    self.display_board()
                    won = True
                    break
            else:
                print("Computer move: ")
                #column = self.__computer_player.where_to_move(last_move)
                column = self.__computer_player.make_move(self.__board)
                self.__board.move(column, self.__computer_player.symbol)
                if self.__board.game_won() == True:
                    print("Computer won")
                    self.display_board()
                    won = True
                    break

            self.display_board()
            move += 1

        if won == False:
            print("The game was a draw")

    def start_game_human_human(self):
        player_name = input("Enter the second player name: ")
        self.__second_player = Player(player_name, '0')
        move = 0
        self.display_board()
        won = False
        while self.__board.still_play():
            if move % 2 == PLAYER1:
                while True:
                    try:
                        print(self.__human_player.name + " chose a column to move")
                        column = int(input("Enter the column number(between 1 and 7): "))
                        column -= 1
                        self.__board.move(column, self.__human_player.symbol)
                        break
                    except ValueError as ve:
                        print(ve)

                if self.__board.game_won() == True:
                    print(str(self.__human_player.name) + " won")
                    self.display_board()
                    won = True
                    break
            else:
                while True:
                    try:
                        print(self.__second_player.name + " chose a column to move")
                        column = int(input("Enter the column number(between 1 and 7): "))
                        column -= 1
                        self.__board.move(column, self.__second_player.symbol)

                        break
                    except ValueError as ve:
                        print(ve)

                if self.__board.game_won() == True:
                    print(str(self.__second_player.name) + " won")
                    self.display_board()
                    won = True
                    break
            self.display_board()
            move += 1

        if won == False:
            print("The game was a draw")

if __name__ == '__main__':
    board = Board()
    player_name = input("Enter the player name: ")
    player = Player(player_name, 'X')
    computer = Computer()

    ui = Ui(player, computer, board)
    ui.start_game_human_human()