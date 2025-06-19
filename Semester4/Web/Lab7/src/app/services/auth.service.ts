import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable, BehaviorSubject } from 'rxjs';
import { tap } from 'rxjs/operators';
import { ApiService } from './ApiService';

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  private currentUserSubject = new BehaviorSubject<any>(null);
  public currentUser = this.currentUserSubject.asObservable();

  constructor(private http: HttpClient, private apiService: ApiService) {
    // Check if user is already logged in from previous session
    this.checkAuthStatus();
  }

  checkAuthStatus() {
    // This will call a new endpoint you'll need to create to check session status
    this.http.get(`${this.apiService.getLoginUrl()}?check_status=1`, { withCredentials: true })
      .subscribe(
        (user: any) => {
          if (user && user.user_id) {
            this.currentUserSubject.next(user);
          }
        },
        error => {
          console.error('Auth check failed:', error);
        }
      );
  }

  login(username: string, password: string): Observable<any> {
    const formData = new FormData();
    formData.append('username', username);
    formData.append('password', password);

    return this.http.post(this.apiService.getLoginUrl(), formData, { withCredentials: true })
      .pipe(
        tap((response: any) => {
          if (response && response.success) {
            this.currentUserSubject.next(response.user);
          }
        })
      );
  }

  register(username: string, password: string): Observable<any> {
    const formData = new FormData();
    formData.append('username', username);
    formData.append('password', password);

    return this.http.post(this.apiService.getRegisterUrl(), formData, { withCredentials: true })
      .pipe(
        tap((response: any) => {
          if (response && response.success) {
            this.currentUserSubject.next(response.user);
          }
        })
      );
  }

  logout(): Observable<any> {
    return this.http.get(this.apiService.getLogoutUrl(), { withCredentials: true })
      .pipe(
        tap(() => {
          this.currentUserSubject.next(null);
        })
      );
  }

  get isLoggedIn(): boolean {
    return this.currentUserSubject.value !== null;
  }

  get currentUserId(): number {
    return this.currentUserSubject.value?.user_id;
  }

  get currentUsername(): string {
    return this.currentUserSubject.value?.username;
  }
}