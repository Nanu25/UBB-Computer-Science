using Microsoft.EntityFrameworkCore;

namespace ExamAsp.Models
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        public DbSet<Persons> Persons { get; set; }
        public DbSet<Courses> Courses { get; set; }
        
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
            
            // Configure the relationship between Courses and Persons
            modelBuilder.Entity<Courses>()
                .HasOne(c => c.Professor)
                .WithMany(p => p.ManagedCourses)
                .HasForeignKey(c => c.ProfessorId)
                .OnDelete(DeleteBehavior.Restrict);
        
            // Configure table names to match the existing MySQL tables
            modelBuilder.Entity<Persons>().ToTable("Persons");
            modelBuilder.Entity<Courses>().ToTable("Courses");
        }
    }
}
