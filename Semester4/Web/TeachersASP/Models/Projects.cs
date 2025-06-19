using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ExamAsp.Models
{
    public class Projects
    {
        [Key]
        public int id { get; set; }

        [Required]
        public string name { get; set; }


        [Required]
        public int duration { get; set; }
        
    }
}
