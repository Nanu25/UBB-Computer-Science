using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace ExamAsp.Models
{
    public class Teachers
    {
        [Key]
        public int id { get; set; }
        
        public string name { get; set; }
        
        public string courseList { get; set; }
        
        public string projectList { get; set; }

    }
}
