using Microsoft.EntityFrameworkCore;

namespace LogManagementSystem.Models
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        public DbSet<User> Users { get; set; }
        public DbSet<LogReport> LogReports { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<User>()
                .HasIndex(u => u.Username)
                .IsUnique();
                
            // Configure the LogReport entity
            modelBuilder.Entity<LogReport>()
                .HasOne(l => l.User)
                .WithMany(u => u.LogReports)
                .HasForeignKey(l => l.UserId)
                .IsRequired();
                
            // Configure navigation property as optional for validation
            modelBuilder.Entity<LogReport>()
                .Navigation(l => l.User)
                .IsRequired(false);
        }
    }
}