using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ExamAsp.Models
{
    public class Courses
    {
        [Key]
        public int Id { get; set; }
        
        public int? ProfessorId { get; set; }
        
        [Required]
        public string CourseName { get; set; }
        
        public string Participants { get; set; }
        
        public string Grades { get; set; }
        
        // Navigation property
        public virtual Persons Professor { get; set; }
    }
}
