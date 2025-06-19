import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { FormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';
// Remove RouterLink if not using any routerLink directives in the template
import { LogService } from '../../services/log.service';

@Component({
  selector: 'app-edit-log',
  standalone: true,
  imports: [CommonModule, FormsModule], // Remove RouterLink from imports
  templateUrl: './edit-log.component.html',
  styleUrls: ['./edit-log.component.css']
})
export class EditLogComponent implements OnInit {
  logId: number = 0;
  type: string = '';
  severity: string = '';
  message: string = '';
  errorMessage: string = '';
  isLoading: boolean = true;
  isSaving: boolean = false;

  constructor(
    private route: ActivatedRoute,
    private router: Router,
    private logService: LogService
  ) {}

  ngOnInit(): void {
    // Get log ID from route parameter
    const id = this.route.snapshot.paramMap.get('id');
    if (id) {
      this.logId = parseInt(id);
      this.loadLogDetails();
    } else {
      this.errorMessage = 'No log ID provided';
      this.isLoading = false;
    }
  }

  loadLogDetails(): void {
    this.isLoading = true;
    this.logService.getLog(this.logId).subscribe({
      next: (response) => {
        console.log('Log details:', response);
        this.isLoading = false;
        
        if (response.success) {
          // Populate form fields
          this.type = response.log.type;
          this.severity = response.log.severity;
          this.message = response.log.message;
        } else {
          this.errorMessage = response.message || 'Failed to load log details';
        }
      },
      error: (error) => {
        console.error('Error loading log:', error);
        this.isLoading = false;
        this.errorMessage = typeof error === 'string' ? error : 'Failed to load log. Please try again.';
      }
    });
  }

  // Add this public method to use in the template instead of directly accessing router
  cancelEdit(): void {
    this.router.navigate(['/logs']);
  }

  onSubmit(): void {
    // Reset error message
    this.errorMessage = '';
    
    // Validate form
    if (!this.type || !this.message) {
      this.errorMessage = 'Please fill in all fields';
      return;
    }
    
    this.isSaving = true;
    
    // Update log
    this.logService.updateLog(this.logId, this.type, this.severity, this.message).subscribe({
      next: response => {
        this.isSaving = false;
        if (response.success) {
          this.router.navigate(['/logs']);
        } else {
          this.errorMessage = response.message || 'Failed to update log';
        }
      },
      error: error => {
        this.isSaving = false;
        this.errorMessage = 'Failed to update log. Please try again.';
        console.error('Update log error:', error);
      }
    });
  }
}