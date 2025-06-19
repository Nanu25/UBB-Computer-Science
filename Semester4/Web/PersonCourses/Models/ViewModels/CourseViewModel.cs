using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc.Rendering;

namespace ExamAsp.Models.ViewModels
{
    public class CoursesViewModel
    {
        public List<Courses> AllCourses { get; set; }
        public List<Courses> UserCourses { get; set; }
        public List<Persons> AllProfessors { get; set; }
        public string CurrentUserName { get; set; }
        

        public string CourseToAssign { get; set; }
        public string GradeToAssign { get; set; }

        // Constructor
        public CoursesViewModel()
        {
            AllCourses = new List<Courses>();
            UserCourses = new List<Courses>();
            AllProfessors = new List<Persons>();
        }
    }
}
