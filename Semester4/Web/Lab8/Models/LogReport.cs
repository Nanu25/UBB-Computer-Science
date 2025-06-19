using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace LogManagementSystem.Models
{
    public class LogReport
    {
        [Key]
        public int LogId { get; set; }
        
        [Required]
        [StringLength(50)]
        public string Type { get; set; } = null!;
        
        [Required]
        [StringLength(20)]
        public string Severity { get; set; } = null!;
        
        public DateTime Date { get; set; }
        
        [Required]
        public string Message { get; set; } = null!;
        
        [Range(1, 5)]
        public int Priority { get; set; }
        
        public int UserId { get; set; }
        
        [ForeignKey("UserId")]
        public User? User { get; set; } // Make the navigation property nullable
    }
}