import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders, HttpParams } from '@angular/common/http';
import { catchError, Observable, tap, throwError } from 'rxjs';
import { ApiService } from './ApiService';

@Injectable({
  providedIn: 'root'
})
export class LogService {
  constructor(private http: HttpClient, private apiService: ApiService) {}

  getLogs(type: string = '', severity: string = '', view: string = 'my', page: number = 1): Observable<any> {
    let params = new HttpParams()
      .set('type', type)
      .set('severity', severity)
      .set('view', view)
      .set('page', page.toString());

    return this.http.get(this.apiService.getLogsUrl(), { params, withCredentials: true });
  }

  getUserLogs(type: string = '', severity: string = '', view: string = 'my', page: number = 1): Observable<any> {
    let params = new HttpParams()
      .set('type', type)
      .set('severity', severity)
      .set('view', view)
      .set('page', page.toString());

    return this.http.get(this.apiService.getLogsUrl(), { params, withCredentials: true });
  }

  addLog(type: string, severity: string, message: string): Observable<any> {
    const formData = new FormData();
    formData.append('type', type);
    formData.append('severity', severity);
    formData.append('message', message);

    return this.http.post(this.apiService.getAddLogUrl(), formData, { withCredentials: true });
  }

  getLog(id: number): Observable<any> {
    const params = new HttpParams().set('id', id.toString());
    return this.http.get(`${this.apiService.getGetLogUrl()}`, { params, withCredentials: true });
  }

  updateLog(id: number, type: string, severity: string, message: string): Observable<any> {
    const formData = new FormData();
    formData.append('type', type);
    formData.append('severity', severity);
    formData.append('message', message);

    return this.http.post(`${this.apiService.getEditLogUrl()}?id=${id}`, formData, { withCredentials: true });
  }

  deleteLog(id: number): Observable<any> {
    console.log('Deleting log:', id);
    
    // Fix the URL - remove the duplicate /delete_log.php
    return this.http.post(`${this.apiService.getDeleteLogUrl()}`, { id }, {
      withCredentials: true,
      headers: new HttpHeaders({
        'Content-Type': 'application/json',
        'Accept': 'application/json'
      })
    }).pipe(
      tap(response => console.log('Delete log response:', response)),
      catchError(error => {
        console.error('Delete log error:', error);
        
        let errorMsg = 'Failed to delete log';
        if (error.error && error.error.message) {
          errorMsg = error.error.message;
        }
        
        return throwError(() => ({ success: false, message: errorMsg }));
      })
    );
  }
}