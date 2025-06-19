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
            var allCourses = await _context.Courses.Include(p => p.Professor).ToListAsync();

            // Find the projects where the current user is a member
            var userCourses = allCourses
                .Where(p => p.Participants.Contains(currentUserName))
                .ToList();

            // Retrieve all developers from the database
            var allProfessors = await _context.Persons.ToListAsync();

            // Create the view model
            var viewModel = new CoursesViewModel
            {
                AllCourses = allCourses,
                UserCourses = userCourses,
                AllProfessors = allProfessors,
                CurrentUserName = currentUserName
            };

            return View(viewModel);
        }

        // GET: Project/Login
        public IActionResult Login()
        {
            return View();
        }

        // POST: Project/Login
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Login(string username)
        {
            if (string.IsNullOrEmpty(username))
            {
                ModelState.AddModelError("", "Username cannot be empty");
                return View();
            }

            // Store the username in the session
            HttpContext.Session.SetString("CurrentUser", username);

            // Check if the user exists in the database
            var professor = await _context.Persons
                .FirstOrDefaultAsync(d => d.Name == username);

            // If the user doesn't exist, create a new SoftwareDeveloper
            if (professor == null)
            {
                //error, the developer does not exist;
                ModelState.AddModelError("", "Developer does not exist.");
                return View();
            }

            return RedirectToAction(nameof(Index));
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> AddGrade(CoursesViewModel model)
        {
            var course = await _context.Courses.FirstOrDefaultAsync(c => c.CourseName == model.CourseToAssign);
            if (course == null)
            {
                ModelState.AddModelError("", "Course does not exist.");
                return View();
            }
            course.Grades += " " + model.GradeToAssign;
            await _context.SaveChangesAsync();
            TempData["SuccessMessage"] = "Grad`e Added";
            return RedirectToAction(nameof(Index));
        }

    }
}
