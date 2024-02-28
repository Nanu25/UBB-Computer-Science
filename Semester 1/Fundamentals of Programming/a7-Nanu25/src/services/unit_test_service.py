import unittest
from src.services.services_a7 import *
from src.repository.memory_repository import *

class TestExpenses_Service(unittest.TestCase):

    def setUp(self):
        self.__repository = MemoryRepository()
        self.__expenses_service = ServiceClass(self.__repository)

    def test_add_expenses(self):
        day = 31
        amount = 100
        type = "gas"
        self.assertNotIn(Expenses(day, amount, type), self.__repository.get_all())
        self.__expenses_service.add_new_expenses(day, amount, type)
        self.assertIn(Expenses(day, amount, type), self.__repository.get_all())


    def test_duplicate_expenses(self):
        day = 32
        amount = 100
        type = "heat"
        self.assertNotIn(Expenses(day, amount, type), self.__repository.get_all())
        self.__expenses_service.add_new_expenses(day, amount, type)
        self.assertIn(Expenses(day, amount, type), self.__repository.get_all())

    def test_filter_expenses(self):
        day = 32
        amount = 100
        type = "heat"
        self.__expenses_service.add_new_expenses(day, amount, type)
        self.__expenses_service.filter_only_expenses_with_amount_above_a_value(101)
        self.assertNotIn(Expenses(day, amount, type), self.__repository.get_all())  #this should be ok

    def test_undo_expenses(self):
        day = 32
        amount = 100
        type = "heat"
        self.__expenses_service.add_new_expenses(day, amount, type)
        self.__expenses_service.undo_last_operation()
        self.assertNotIn(Expenses(day, amount, type), self.__repository.get_all())


if __name__ == '__main__':
    unittest.main()