using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace LogManagementSystem.Migrations
{
    /// <inheritdoc />
    public partial class FixLogReportNavigation : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_LogReports_Users_UserId",
                table: "LogReports");

            migrationBuilder.AddForeignKey(
                name: "FK_LogReports_Users_UserId",
                table: "LogReports",
                column: "UserId",
                principalTable: "Users",
                principalColumn: "UserId");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_LogReports_Users_UserId",
                table: "LogReports");

            migrationBuilder.AddForeignKey(
                name: "FK_LogReports_Users_UserId",
                table: "LogReports",
                column: "UserId",
                principalTable: "Users",
                principalColumn: "UserId",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
