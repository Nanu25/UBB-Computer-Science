using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ExamAsp.Models
{
    public class Hotels
    {
        [Key]
        public int hotelId { get; set; }

        [Required]
        public string hotelName { get; set; }

        public string date { get; set; }

        [Required]
        public string City { get; set; }
        
        public int availableRooms { get; set; }

    }
}
