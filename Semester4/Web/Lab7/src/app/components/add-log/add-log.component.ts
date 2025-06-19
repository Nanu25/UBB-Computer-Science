import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { FormsModule } from '@angular/forms';
import { CommonModule } from '@angular/common';
import { RouterLink } from '@angular/router';
import { LogService } from '../../services/log.service';

@Component({
  selector: 'app-add-log',
  standalone: true,
  imports: [CommonModule, FormsModule, RouterLink],
  templateUrl: './add-log.component.html',
  styleUrls: ['./add-log.component.css']
})
export class AddLogComponent {
  type: string = '';
  severity: string = 'notice';
  message: string = '';
  errorMessage: string = '';
  isSubmitting: boolean = false;

  constructor(
    private logService: LogService,
    private router: Router
  ) {}

  onSubmit(): void {
    // Reset error message
    this.errorMessage = '';
    
    // Validate form
    if (!this.type || !this.message) {
      this.errorMessage = 'Please fill in all fields';
      return;
    }
    
    this.isSubmitting = true;
    
    // Submit log
    this.logService.addLog(this.type, this.severity, this.message).subscribe(
      response => {
        this.isSubmitting = false;
        if (response.success) {
          this.router.navigate(['/logs']);
        } else {
          this.errorMessage = response.message || 'Failed to add log';
        }
      },
      error => {
        this.isSubmitting = false;
        this.errorMessage = 'Failed to add log. Please try again.';
        console.error('Add log error:', error);
      }
    );
  }
}