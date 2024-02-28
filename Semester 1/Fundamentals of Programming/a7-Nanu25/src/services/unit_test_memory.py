import unittest
from unittest import TestCase
from src.domain.domain_a7 import *
from src.repository.memory_repository import *

class TestExpenses_Memory(TestCase):

    def setUp(self):
        self.__repository = MemoryRepository()

    def test_add_expenses(self):
        new_expenses = Expenses(31, 50, "gas")
        self.__repository.add_new_expenses(new_expenses)
        self.assertIn(new_expenses, self.__repository.get_all())

    def test_duplicate_expenses(self):
        #if the expenses is not in the list
        new_expenses = Expenses(32, 50, "heat")
        self.assertNotIn(new_expenses, self.__repository.get_all())
        self.__repository.add_new_expenses(new_expenses)
        self.assertNotIn(new_expenses, self.__repository.get_all()) #this should be an error


if __name__ == '__main__':
    unittest.main()
