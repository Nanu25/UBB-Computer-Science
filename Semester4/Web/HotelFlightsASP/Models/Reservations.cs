using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ExamAsp.Models
{
    public class Reservations
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public string person { get; set; }


        [Required]
        public string Type { get; set; }
        
        public int idReservedResource { get; set; }

    }
}
