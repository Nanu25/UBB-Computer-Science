using System.ComponentModel.DataAnnotations;
using System.Collections.Generic;

namespace LogManagementSystem.Models
{
    public class User
    {
        [Key]
        public int UserId { get; set; }
        
        [Required]
        [StringLength(50)]
        public string Username { get; set; }
        
        [Required]
        public string PasswordHash { get; set; }
        
        public virtual ICollection<LogReport> LogReports { get; set; }
    }
}