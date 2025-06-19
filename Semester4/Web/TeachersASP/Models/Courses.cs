using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ExamAsp.Models
{
    public class Courses
    {
        [Key]
        public int id { get; set; }

        [Required]
        public string title { get; set; }

        public string description { get; set; }

    }
}
