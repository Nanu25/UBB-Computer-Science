from connect_four.domain.board import Board, COLUMNS, ROWS


# class Computer(Board):
#     def __init__(self):
#         super().__init__()
#
#     def where_to_move(self, last_move):
#         if self.board[0][last_move] == '●':
#             return last_move
#         elif last_move == 0:
#             return 1
#         else:
#             return last_move - 1
#

class Computer():

    def __init__(self, ai_symbol, opponent_symbol, difficulty):
        self.ai_symbol = ai_symbol
        self.difficulty = difficulty
        self.opponent_symbol = opponent_symbol

    @property
    def symbol(self):
        return self.ai_symbol

    def is_legal_move(self, game_board, column):
        i = 5
        while i > -1:
            if game_board.board[i][column] == ' ':
                return True
            i -= 1
        return False

    def simulate_move(self, game_board, column, symbol):
        new_board = Board()
        for i in range(ROWS):
            for j in range(COLUMNS):
                new_board.board[i][j] = game_board.board[i][j]
        new_board.move(column, symbol)
        return new_board

    def make_move(self, game_board):
        legal_moves = {}
        for i in range(COLUMNS):
            if self.is_legal_move(game_board, i):
                new_board = self.simulate_move(game_board, i, self.ai_symbol)
                legal_moves[i] = -self.evaluate_move(self.difficulty - 1, new_board, self.opponent_symbol)

        best_score = float('-inf')
        best_move = None
        moves = legal_moves.items()
        for move, score in moves:
            if score > best_score:
                best_score = score
                best_move = move

        return best_move

    def evaluate_move(self, depth, game_board, symbol):
        legal_moves = []
        for i in range(COLUMNS):
            if self.is_legal_move(game_board, i):
                new_board = self.simulate_move(game_board, i, symbol)
                legal_moves.append(new_board)

        if depth == 0 or len(legal_moves) == 0 or game_board.game_won():
            return self.calculate_score(game_board, symbol)

        opponent_circle = self.opponent_symbol if symbol == self.ai_symbol else self.ai_symbol
        score = float('-inf')
        for new_board in legal_moves:
            score = max(score, -self.evaluate_move(depth - 1, new_board, opponent_circle))

        return score

    def calculate_score(self, game_board, symbol):
        opponent_circle = self.opponent_symbol if symbol == self.ai_symbol else self.ai_symbol

        ai_fours = self.count_connections(game_board, symbol, 4)
        ai_threes = self.count_connections(game_board, symbol, 3)
        ai_twos = self.count_connections(game_board, symbol, 2)
        opponent_fours = self.count_connections(game_board, opponent_circle, 4)
        opponent_threes = self.count_connections(game_board, opponent_circle, 3)
        opponent_twos = self.count_connections(game_board, opponent_circle, 2)

        if opponent_fours > 0:
            return -100000
        else:
            return ai_fours * 100000 + ai_threes * 100 + ai_twos - opponent_threes * 100 - opponent_twos

    def count_connections(self, game_board, symbol, length):
        count = 0
        for i in range(ROWS):
            for j in range(COLUMNS):
                if game_board.board[i][j] == symbol:
                    count += self.check_vertical_connection(i, j, game_board, length, symbol)
                    count += self.check_horizontal_connection(i, j, game_board, length, symbol)
                    count += self.check_diagonal_connection(i, j, game_board, length, symbol)
        return count

    def check_vertical_connection(self, i, j, game_board, length, symbol):
        count = 0
        if i + length - 1 < ROWS:
            for x in range(length):
                if game_board.board[i + x][j] == symbol:
                    count += 1
                else:
                    break

        return 1 if count == length else 0

    def check_horizontal_connection(self, i, j, game_board, length, symbol):
        count = 0
        if j + length - 1 < 7:
            for x in range(length):
                if game_board.board[i][j + x] == symbol:
                    count += 1
                else:
                    break

        return 1 if count == length else 0

    def check_diagonal_connection(self, i, j, game_board, length, symbol):
        total = 0
        total += self.check_diagonal_up_connection(i, j, game_board, length, symbol)
        total += self.check_diagonal_down_connection(i, j, game_board, length, symbol)
        return total

    def check_diagonal_up_connection(self, i, j, game_board, length, symbol):
        count = 0
        if j + length - 1 < 7 and i + length - 1 < 6:
            for x in range(length):
                if game_board.board[i + x][j + x] == symbol:
                    count += 1
                else:
                    break

        return 1 if count == length else 0

    def check_diagonal_down_connection(self, i, j, game_board, length, symbol):
        count = 0
        if j + length - 1 < 7 and i - length + 1 > -1:
            for x in range(length):
                if game_board.board[i - x][j + x] == symbol:
                    count += 1
                else:
                    break

        return 1 if count == length else 0
