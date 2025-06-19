using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ExamAsp.Models
{
    public class Flights
    {
        [Key]
        public int flightID { get; set; }
        
        public string date { get; set; }
        
        public string destinationCity { get; set; }
        
        public int availableSeats { get; set; }

    }
}
