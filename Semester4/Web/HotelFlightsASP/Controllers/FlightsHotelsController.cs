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
            string currentDate = HttpContext.Session.GetString("Date");
            string currentCity = HttpContext.Session.GetString("City");

            // If the user is not logged in, redirect to login page
            if (string.IsNullOrEmpty(currentUserName))
            {
                return RedirectToAction(nameof(Login));
            }

            // Retrieve all projects from the database
            var allFlights = await _context.Flights.ToListAsync();
            var flights = allFlights.Where(f => f.date == currentDate && f.destinationCity == currentCity && f.availableSeats > 0).ToList();

            // Retrieve all developers from the database
            var allHotels = await _context.Hotels.ToListAsync();
            var hotels = allHotels.Where(h => h.date == currentDate && h.City == currentCity && h.availableRooms > 0).ToList();
            // Create the view model
            var viewModel = new AppViewModel
            {
                AllFlights = flights,
                AllHotels = hotels,
                // CurrentUserName = currentUserName
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
        public async Task<IActionResult> Login(string username, string date, string city)
        {
            if (string.IsNullOrEmpty(username))
            {
                ModelState.AddModelError("", "Username cannot be empty");
                return View();
            }

            // Store the username in the session
            HttpContext.Session.SetString("CurrentUser", username);
            HttpContext.Session.SetString("Date", date);
            HttpContext.Session.SetString("City", city);
            // // Check if the user exists in the database
            // var professor = await _context.Hotels
            //     .FirstOrDefaultAsync(d => d.Name == username);

            // // If the user doesn't exist, create a new SoftwareDeveloper
            // if (professor == null)
            // {
            //     //error, the developer does not exist;
            //     ModelState.AddModelError("", "Developer does not exist.");
            //     return View();
            // }

            return RedirectToAction(nameof(Index));
        }

        public async Task<IActionResult> HotelList()
        {
            // Get the current user info from the session
            string currentUserName = HttpContext.Session.GetString("CurrentUser");
            string currentDate = HttpContext.Session.GetString("Date");
            string currentCity = HttpContext.Session.GetString("City");

            // If the user is not logged in, redirect to login page
            if (string.IsNullOrEmpty(currentUserName))
            {
                return RedirectToAction(nameof(Login));
            }

            // Retrieve all hotels from the database
            var allHotels = await _context.Hotels.ToListAsync();
            var hotels = allHotels.Where(h => h.date == currentDate && h.City == currentCity && h.availableRooms > 0).ToList();

            // Create the view model
            var viewModel = new AppViewModel
            {
                AllHotels = hotels,
                CurrentUserName = currentUserName
            };

            return View(viewModel);
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> MakeReservation(int flightId, string reservationType)
        {
            string currentUserName = HttpContext.Session.GetString("CurrentUser");

            // Create new reservation
            var reservation = new Reservations
            {
                person = currentUserName,
                Type = reservationType,
                idReservedResource = flightId
            };

            // Add reservation and decrease available seats
            _context.Reservations.Add(reservation);
            var flight = await _context.Flights.FirstOrDefaultAsync(f => f.flightID == flightId);
            flight.availableSeats--;

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> MakeReservationHotel(int hotelId, string reservationType)
        {
            string currentUserName = HttpContext.Session.GetString("CurrentUser");

            // Create new reservation
            var reservation = new Reservations
            {
                person = currentUserName,
                Type = reservationType,
                idReservedResource = hotelId
            };

            // Add reservation and decrease available seats
            _context.Reservations.Add(reservation);
            var hotel = await _context.Hotels.FirstOrDefaultAsync(h => h.hotelId == hotelId);
            hotel.availableRooms--;

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(HotelList));
        }


        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> CancelAllReservations()
        {
            string currentUserName = HttpContext.Session.GetString("CurrentUser");
            string currentDate = HttpContext.Session.GetString("Date");
            string currentCity = HttpContext.Session.GetString("City");

            // Get all reservations for the current user
            var userReservations = await _context.Reservations
                .Where(r => r.person == currentUserName)
                .ToListAsync();

            int cancelledCount = 0;

            foreach (var reservation in userReservations)
            {
                bool shouldCancel = false;

                if (reservation.Type == "Flight")
                {
                    var flight = await _context.Flights.FirstOrDefaultAsync(f => f.flightID == reservation.idReservedResource);
                    if (flight != null && flight.date == currentDate && flight.destinationCity == currentCity)
                    {
                        flight.availableSeats++;
                        shouldCancel = true;
                    }
                }
                else if (reservation.Type == "Hotel")
                {
                    var hotel = await _context.Hotels.FirstOrDefaultAsync(h => h.hotelId == reservation.idReservedResource);
                    if (hotel != null && hotel.date == currentDate && hotel.City == currentCity)
                    {
                        hotel.availableRooms++;
                        shouldCancel = true;
                    }
                }

                if (shouldCancel)
                {
                    _context.Reservations.Remove(reservation);
                    cancelledCount++;
                }
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }
    }
}
