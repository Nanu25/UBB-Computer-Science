class Expenses:
    def __init__(self, new_day : int, new_amount : int, new_type : str):
        self.__day = new_day
        self.__amount = new_amount
        self.__type = new_type

    def __str__(self) -> str:
        return "Day " + str(self.__day) + " amount " + str(self.__amount) + " type " + str(self.__type)

    def file_format(self) -> str:
        return str(self.__day) + ' ' + str(self.__amount) + ' ' + str(self.__type)

    @property
    def day(self):
        return self.__day

    @property
    def amount(self):
        return self.__amount

    @property
    def type(self):
        return self.__type

    def __eq__(self, other):
        if isinstance(other, Expenses):
            return (self.day == other.day and self.amount == other.amount and self.type == other.type)
        return False