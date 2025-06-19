using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ExamAsp.Models
{
    public class Persons
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public string Name { get; set; }

        [Required]
        public string Role { get; set; }
        
        // Navigation property
        public virtual ICollection<Courses> ManagedCourses { get; set; } = new List<Courses>();
    }
}
