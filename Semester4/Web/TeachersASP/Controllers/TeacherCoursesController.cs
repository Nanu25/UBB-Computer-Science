using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using ExamAsp.Models;
using ExamAsp.Models.ViewModels;
using Microsoft.AspNetCore.Http;
using Microsoft.EntityFrameworkCore.Metadata.Internal;

namespace ExamAsp.Controllers
{
    public class ProjectController : Controller
    {
        private readonly ApplicationDbContext _context;

        public ProjectController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: Project
        public async Task<IActionResult> Index()
        {
            // Get the current user name from the session
            string currentUserName = HttpContext.Session.GetString("CurrentUser");
            // If the user is not logged in, redirect to login page
            if (string.IsNullOrEmpty(currentUserName))
            {
                return RedirectToAction(nameof(Login));
            }

            // Retrieve all projects from the database
            
            var actualTeacher = await _context.Teachers.FirstOrDefaultAsync(d => d.name == currentUserName);
            var courseList = actualTeacher.courseList.Split(" ");
            var projectList = actualTeacher.projectList.Split(" ");

            // var flights = allTeachers.Where(f => f.date == currentDate && f.destinationCity == currentCity && f.availableSeats > 0).ToList();
            // Retrieve all developers from the database
            var allCourses = await _context.Courses.ToListAsync();
            var allProjects = await _context.Projects.ToListAsync();

            List<Courses> teacherCourses = new List<Courses>();
            foreach (Courses courses in allCourses)
            {
                foreach (var c in courseList)
                {
                    if (c == courses.title)
                    {
                        teacherCourses.Add(courses);
                        break;
                    } 
                }
            }

            List<Projects> teacherProjects = new List<Projects>();
            foreach (Projects project in allProjects)
            {
                foreach (var p in projectList)
                {
                    if (p == project.name)
                    {
                        teacherProjects.Add(project);
                        break;
                    } 
                }
            }

            List<object> interleaved = new List<object>();
            int i = 0, j = 0, step = 0;
            while (i < teacherCourses.Count && j < teacherProjects.Count)
            {
                if (step % 2 == 0)
                {
                    interleaved.Add(teacherCourses[i]);
                    i += 1;
                }
                else
                {
                    interleaved.Add(teacherProjects[j]);
                    j += 1;
                }
                step += 1;
            }
            while (i < teacherCourses.Count)
            {
                interleaved.Add(teacherCourses[i]);
                i += 1;    
            }

            while (j < teacherProjects.Count)
            {
                interleaved.Add(teacherProjects[j]);
                j += 1;        
            }
            
            // var courses = allHotels.Where(c => h.date == currentDate && h.City == currentCity && h.availableRooms > 0).ToList();
            // Create the view model
            var viewModel = new AppViewModel
            {
                //AllTeachers = allTeachers,
                AllCourses = allCourses,
                TeacherCourses = teacherCourses,
                // CurrentUserName = currentUserName
                TeacherItems = interleaved
            };

            return View(viewModel);
        }

        // GET: Project/Login
        public IActionResult Login()
        {
            return View();
        }

        public IActionResult Logout()
        {
            // Clear all session data
            HttpContext.Session.Clear();
            
            // Optionally, you can also remove specific session keys
            // HttpContext.Session.Remove("CurrentUser");
            // HttpContext.Session.Remove("answer");
            
            // Redirect to login page
            return RedirectToAction(nameof(Login));
        }


        // POST: Project/Login
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Login(string username, string answer)
        {
            if (string.IsNullOrEmpty(username))
            {
                ModelState.AddModelError("", "Username cannot be empty");
                return View();
            }

            // Store the username in the session

            // // Check if the user exists in the database
            var professor = await _context.Teachers
                .FirstOrDefaultAsync(d => d.name == username);

            if (professor == null)
            {
                ModelState.AddModelError("", "Invalid Teacher Name");
                return View();
            }

            var courseList = professor.courseList;
            var projectList = professor.projectList;

            var courses = courseList.Split(" ");
            var projects = projectList.Split(" ");

            bool find = false;

            foreach (String course in courses)
            {
                if (course == answer)
                {
                    find = true;
                    break;
                }
            }

            foreach (String project in projects)
            {
                if (project == answer)
                {
                    find = true;
                    break;
                }
            }

            if (find == false)
            {
                ModelState.AddModelError("", "Invalid Teacher Name or Password");
                return View();
            }
            HttpContext.Session.SetString("CurrentUser", username);
            HttpContext.Session.SetString("answer", answer);
            return RedirectToAction(nameof(Index));
        }

        public async Task<IActionResult> FindBestCourse()
        {
            // Get the current user info from the session
            var allCourses = await _context.Courses.ToListAsync();
            var allTeachers = await _context.Teachers.ToListAsync();

            int ap = 0;
            int maxim = 0;
            Courses c = new Courses();
            foreach (var course in allCourses)
            {
                ap = 0;
                foreach (var teacher in allTeachers)
                {
                    var courseList = teacher.courseList.Split(" ");
                    foreach (var x in courseList)
                    {
                        if (x == course.title)
                        {
                            ap++;
                            break;
                        }
                    }
                }
                if (ap > maxim)
                {
                    maxim = ap;
                    c = course;
                }
            }

            // Create the view model
            var viewModel = new AppViewModel
            {
                BestCourse = c
            };

            return View(viewModel);
        }

        //     [HttpPost]
        //     [ValidateAntiForgeryToken]
        //     public async Task<IActionResult> MakeReservation(int flightId, string reservationType)
        //     {
        //         string currentUserName = HttpContext.Session.GetString("CurrentUser");

        //         // Create new reservation
        //         var reservation = new Projects
        //         {
        //             person = currentUserName,
        //             Type = reservationType,
        //             idReservedResource = flightId
        //         };

        //         // Add reservation and decrease available seats
        //         _context.Projects.Add(reservation);
        //         var flight = await _context.Teachers.FirstOrDefaultAsync(f => f.flightID == flightId);
        //         flight.availableSeats--;

        //         await _context.SaveChangesAsync();
        //         return RedirectToAction(nameof(Index));
        //     }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> AddCourse(string courseName, string courseDescription)
        {
            string currentUserName = HttpContext.Session.GetString("CurrentUser");

            // Create new reservation
            var course = new Courses
            {
                title = courseName,
                description = courseDescription
            };

            // Add reservation and decrease available seats
            _context.Courses.Add(course);
            var teacher = await _context.Teachers.FirstOrDefaultAsync(t => t.name == currentUserName);
            teacher.courseList += " " + courseName;

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> deleteProject(string projectName)
        {

            var project = await _context.Projects.FirstOrDefaultAsync(p => p.name == projectName);
            string currentUserName = HttpContext.Session.GetString("CurrentUser");
            var teacher = await _context.Teachers.FirstOrDefaultAsync(t => t.name == currentUserName);

            var projectList = teacher.projectList.Split(" ");
            String newProj = "";
            foreach (String proj in projectList)
            {
                if (proj != projectName)
                {
                    newProj += " " + proj;
                }
            }
            teacher.projectList = newProj;
            _context.Projects.Remove(project);
            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }
    }
}
