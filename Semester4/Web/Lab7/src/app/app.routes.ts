import { Routes } from '@angular/router';
import { LoginComponent } from './components/login/login.component';
import { RegisterComponent } from './components/register/register.component';
import { HomeComponent } from './components/home/home.component';
import { LogsComponent } from './components/logs/logs.component';
import { AddLogComponent } from './components/add-log/add-log.component';
import { EditLogComponent } from './components/edit-log/edit-log.component';
import { inject } from '@angular/core';
import { AuthService } from './services/auth.service';
import { Router } from '@angular/router';

// Auth guard function for standalone components
function authGuard() {
  const authService = inject(AuthService);
  const router = inject(Router);
  
  if (authService.isLoggedIn) {
    return true;
  }
  
  return router.parseUrl('/login');
}

export const routes: Routes = [
  { path: 'login', component: LoginComponent },
  { path: 'register', component: RegisterComponent },
  { path: 'home', component: HomeComponent, canActivate: [() => authGuard()] },
  { path: 'logs', component: LogsComponent, canActivate: [() => authGuard()] },
  { path: 'add-log', component: AddLogComponent, canActivate: [() => authGuard()] },
  { path: 'edit-log/:id', component: EditLogComponent, canActivate: [() => authGuard()] },
  { path: '', redirectTo: '/login', pathMatch: 'full' },
  { path: '**', redirectTo: '/login' },
  { path: 'UserLogs', component: LogsComponent, canActivate: [() => authGuard()]}
];