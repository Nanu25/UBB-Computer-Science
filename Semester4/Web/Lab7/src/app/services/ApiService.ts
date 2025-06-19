import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class ApiService {
  // Update this to point to your PHP backend
  private baseUrl = 'http://localhost/Lab7';

  getLoginUrl(): string {
    return `${this.baseUrl}/login.php`;
  }

  getRegisterUrl(): string {
    return `${this.baseUrl}/register.php`;
  }

  getLogoutUrl(): string {
    return `${this.baseUrl}/logout.php`;
  }

  getLogsUrl(): string {
    return `${this.baseUrl}/get_logs.php`;
  }

  getAddLogUrl(): string {
    return `${this.baseUrl}/add_log.php`;
  }

  getEditLogUrl(): string {
    return `${this.baseUrl}/edit_log.php`;
  }

  getDeleteLogUrl(): string {
    return `${this.baseUrl}/delete_log.php`;
  }

  getGetLogUrl(): string {
    return `${this.baseUrl}/get_log.php`;
  }

  getUserLogs(): string {
    return `${this.baseUrl}/get_user_logs.php`;
  }

}