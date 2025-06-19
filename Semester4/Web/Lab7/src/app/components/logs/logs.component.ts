import { Component, OnInit } from '@angular/core';
import { LogService } from '../../services/log.service';
import { AuthService } from '../../services/auth.service';
import { FormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';
import { RouterLink } from '@angular/router';

@Component({
  selector: 'app-logs',
  standalone: true,
  imports: [CommonModule, FormsModule, RouterLink],
  templateUrl: './logs.component.html',
  styleUrls: ['./logs.component.css']
})
export class LogsComponent implements OnInit {
  logs: any[] = [];
  userLogs: any[] = [];
  totalCount: number = 0;
  userLogsCount: number = 0;
  currentPage: number = 1;
  type: string = '';
  severity: string = '';
  view: string = 'my';
  successMessage: string = '';
  errorMessage: any;
  
  constructor(
    private logService: LogService,
    public authService: AuthService
  ) {}

  ngOnInit(): void {
    this.loadLogs();
  }

  loadLogs(): void {
    this.logService.getLogs(this.type, this.severity, this.view, this.currentPage)
      .subscribe({
        next: data => {
          console.log('Logs response:', data);
          console.log('Current user ID:', this.authService.currentUserId);
          console.log('Current view mode:', this.view);
          
          // Add this null check to avoid the TypeError
          this.logs = data.logs || [];
          this.totalCount = data.total_count || 0;
        },
        error: error => {
          console.error('Error loading logs', error);
          this.logs = [];  // Set empty array on error
          this.totalCount = 0;
        }
      });
  }

  loadLogsUser(): void {
    this.logService.getUserLogs(this.type, this.severity, this.view, this.currentPage)
      .subscribe({
        next: data => {
          console.log('Logs response:', data);
          console.log('Current user ID:', this.authService.currentUserId);
          console.log('Current view mode:', this.view);
          
          // Add this null check to avoid the TypeError
          this.userLogs = data.logs || [];
          this.userLogsCount = data.total_count || 0;
        },
        error: error => {
          console.error('Error loading logs', error);
          this.logs = [];  // Set empty array on error
          this.userLogsCount = 0;
        }
      });
  }

  onFilterChange(): void {
    this.currentPage = 1;
    this.loadLogs();
  }

  previousPage(): void {
    if (this.currentPage > 1) {
      this.currentPage--;
      this.loadLogs();
    }
  }

  nextPage(): void {
    this.currentPage++;
    this.loadLogs();
  }

  deleteLog(id: number): void {
    if (!id) {
      console.error('Invalid log ID:', id);
      return;
    }
    
    if (confirm('Are you sure you want to delete this log?')) {
      console.log('Confirming deletion of log ID:', id);
      
      this.logService.deleteLog(id).subscribe({
        next: response => {
          console.log('Delete response:', response);
          
          if (response.success) {
            // Remove the log from the list
            this.logs = this.logs.filter(log => log.log_id !== id);
            
            // Show success message
            this.successMessage = 'Log deleted successfully';
            setTimeout(() => this.successMessage = '', 3000);
          } else {
            this.errorMessage = response.message || 'Error deleting log';
            setTimeout(() => this.errorMessage = '', 5000);
          }
        },
        error: error => {
          console.error('Error deleting log:', error);
          this.errorMessage = 'Failed to delete log. Please try again.';
          setTimeout(() => this.errorMessage = '', 5000);
        }
      });
    }
  }

  isLastPage(): boolean {
    const perPage = 5;
    return this.currentPage * perPage >= this.totalCount;
  }

  // Returns count of logs belonging to current user
  getUserLogsCount(): number {
    if (!this.logs || !this.authService.currentUserId) return 0;
    return this.logs.filter(log => log.user_id === this.authService.currentUserId).length;
  }

  // Checks if a log belongs to current user
  isUserLog(logUserId: any): boolean {
    return Number(logUserId) === this.authService.currentUserId;
  }
}