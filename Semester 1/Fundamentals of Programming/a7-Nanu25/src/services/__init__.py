# import unittest
# from src.domain import Student
# from src.services import StudentService
# from src.repository import MemoryRepository
#
# class TestStudentService(unittest.TestCase):
#   def setUp(self):
#     # Setup test case with an in-memory repository
#     self.repository = MemoryRepository()
#     self.student_service = StudentService(self.repository)
#
#   def test_add_student(self):
#     # Test adding a student
#     student_id = 1
#     student_name = "Test Student"
#     student_group = 100
#     self.student_service.add_student(student_id, student_name, student_group)
#
#     # Retrieve the student and verify details
#     added_student = self.repository.get_by_id(student_id)
#     self.assertIsNotNone(added_student)
#     self.assertEqual(added_student.id, student_id)
#     self.assertEqual(added_student.name, student_name)
#     self.assertEqual(added_student.group, student_group)
#
#   def test_add_duplicate_student(self):
#     # Test adding a student with a duplicate ID
#     student_id = 1
#     student_name = "Test Student"
#     student_group = 100
#     self.student_service.add_student(student_id, student_name, student_group)
#
#     with self.assertRaises(ValueError):
#       self.student_service.add_student(student_id, "Another Student", student_group)
#
#
# if _name_ == '_main_':
#   unittest.main()