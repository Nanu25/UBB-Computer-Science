using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc.Rendering;

namespace ExamAsp.Models.ViewModels
{
    public class AppViewModel
    {
        public List<Teachers> AllTeachers { get; set; }
        // public List<Teachers> UserCourses { get; set; }
        public List<Courses> AllCourses { get; set; }

        public List <Courses> TeacherCourses { get; set;}

        public List<object> TeacherItems { get; set;}

        public string CurrentUserName { get; set; }

        public Courses BestCourse { get; set; }

        // Constructor
        public AppViewModel()
        {
            AllTeachers = new List<Teachers>();
            // UserCourses = new List<Flights>();
            AllCourses = new List<Courses>();
            TeacherCourses = new List<Courses>();
            TeacherItems = new List<Object>();
            
        }
    }
}
