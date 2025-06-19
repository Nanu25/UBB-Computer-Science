using System;
using System.Linq;
using System.Threading.Tasks;
using System.Security.Claims;
using System.Collections.Generic;
using LogManagementSystem.Models;
using LogManagementSystem.ViewModels;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace LogManagementSystem.Controllers
{
    [Authorize]
    public class LogsController : Controller
    {
        private readonly ApplicationDbContext _context;
        
        public LogsController(ApplicationDbContext context)
        {
            _context = context;
        }
        
        public IActionResult Index()
        {
            return View();
        }
        
        public async Task<IActionResult> GetLogs(string type, string severity, string view, int page = 1)
        {
            int userId = int.Parse(User.FindFirst(ClaimTypes.NameIdentifier).Value);
            int limit = 4;
            int skip = (page - 1) * limit;
            
            var query = _context.LogReports.AsQueryable();
            
            if (view == "my")
            {
                query = query.Where(l => l.UserId == userId);
            }
            
            if (!string.IsNullOrEmpty(type))
            {
                query = query.Where(l => l.Type == type);
            }
            
            if (!string.IsNullOrEmpty(severity))
            {
                query = query.Where(l => l.Severity == severity);
            }
            
            int totalCount = await query.CountAsync();
            
            var logs = await query
                .OrderByDescending(l => l.Date)
                .Skip(skip)
                .Take(limit)
                .Select(l => new {
                    l.LogId,
                    l.Type,
                    l.Severity,
                    l.Date,
                    l.Message,
                    l.Priority,
                    IsOwner = l.UserId == userId
                })
                .ToListAsync();
                
            return Json(new { logs, totalCount });
        }
        
        [HttpGet]
        public IActionResult Create()
        {
            return View();
        }
        
        [HttpPost]
        public async Task<IActionResult> Create(LogReport model)
        {
            try
            {
                // Set UserId and Date BEFORE validation
                model.UserId = int.Parse(User.FindFirst(ClaimTypes.NameIdentifier).Value);
                model.Date = DateTime.Now;
                
                // Disable validation for User navigation property
                ModelState.Remove("User");
                
                if (!ModelState.IsValid)
                {
                    return View(model);
                }

                
                _context.LogReports.Add(model);
                await _context.SaveChangesAsync();
                
                return RedirectToAction(nameof(Index));
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Error creating log: {ex.Message}");
                if (ex.InnerException != null)
                {
                    Console.WriteLine($"Inner exception: {ex.InnerException.Message}");
                }
                
                ModelState.AddModelError("", "Error saving log: " + ex.Message);
                return View(model);
            }
        }
        
        [HttpGet]
        public async Task<IActionResult> Edit(int id)
        {
            int userId = int.Parse(User.FindFirst(ClaimTypes.NameIdentifier).Value);
            
            var log = await _context.LogReports
                .FirstOrDefaultAsync(l => l.LogId == id && l.UserId == userId);
                
            if (log == null)
            {
                return NotFound();
            }
            
            return View(log);
        }
        
        [HttpPost]
        public async Task<IActionResult> Edit(int id, LogReport model)
        {
            if (id != model.LogId)
            {
                return NotFound();
            }
            
            int userId = int.Parse(User.FindFirst(ClaimTypes.NameIdentifier).Value);
            
            if (ModelState.IsValid)
            {
                var log = await _context.LogReports
                    .FirstOrDefaultAsync(l => l.LogId == id && l.UserId == userId);
                    
                if (log == null)
                {
                    return NotFound();
                }
                
                log.Type = model.Type;
                log.Severity = model.Severity;
                log.Message = model.Message;
                log.Priority = model.Priority;
                
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            
            return View(model);
        }
        
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Delete(int id)
        {
            int userId = int.Parse(User.FindFirst(ClaimTypes.NameIdentifier).Value);
            
            var log = await _context.LogReports
                .FirstOrDefaultAsync(l => l.LogId == id && l.UserId == userId);
                
            if (log != null)
            {
                _context.LogReports.Remove(log);
                await _context.SaveChangesAsync();
                return Json(new { success = true });
            }
            
            return Json(new { success = false });
        }
        
        // Add this action to LogsController for testing
        [HttpGet]
        public async Task<IActionResult> TestLogInsert()
        {
            try
            {
                var log = new LogReport
                {
                    Type = "Test",
                    Severity = "debug",
                    Message = "Test log entry",
                    Priority = 1,
                    UserId = int.Parse(User.FindFirst(ClaimTypes.NameIdentifier).Value),
                    Date = DateTime.Now
                };
                
                _context.LogReports.Add(log);
                await _context.SaveChangesAsync();
                
                return Content($"Test log created successfully with ID: {log.LogId}");
            }
            catch (Exception ex)
            {
                return Content($"Error creating test log: {ex.Message}\n{(ex.InnerException != null ? ex.InnerException.Message : "")}");
            }
        }
    }
}