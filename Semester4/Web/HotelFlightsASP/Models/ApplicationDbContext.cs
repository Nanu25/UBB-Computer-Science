using Microsoft.EntityFrameworkCore;

namespace ExamAsp.Models
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        public DbSet<Hotels> Hotels { get; set; }
        public DbSet<Flights> Flights { get; set; }
        public DbSet<Reservations> Reservations { get; set; }
        
        // protected override void OnModelCreating(ModelBuilder modelBuilder)
        // {
        //     base.OnModelCreating(modelBuilder);

        //     // Configure the relationship between Courses and Persons
        //     modelBuilder.Entity<Flights>()
        //         .HasOne(c => c.Professor)
        //         .WithMany(p => p.ManagedCourses)
        //         .HasForeignKey(c => c.ProfessorId)
        //         .OnDelete(DeleteBehavior.Restrict);

        //     // Configure table names to match the existing MySQL tables
        //     modelBuilder.Entity<Hotels>().ToTable("Persons");
        //     modelBuilder.Entity<Flights>().ToTable("Courses");
        // }
    }
}
