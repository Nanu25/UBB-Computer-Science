using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc.Rendering;

namespace ExamAsp.Models.ViewModels
{
    public class AppViewModel
    {
        public List<Flights> AllFlights { get; set; }
        public List<Flights> UserCourses { get; set; }
        public List<Hotels> AllHotels { get; set; }
        public string CurrentUserName { get; set; }

        // Constructor
        public AppViewModel()
        {
            AllFlights = new List<Flights>();
            // UserCourses = new List<Flights>();
            AllHotels = new List<Hotels>();
        }
    }
}
