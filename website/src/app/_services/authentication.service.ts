import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { environment } from '../../environments/environment';
import { User } from '../_models/user.model';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

@Injectable()
export class AuthenticationService {

  constructor(
    private http: HttpClient,
  ) { }

  /**
   * Authentication method
   * @param login username
   * @param password password
   * @returns Boolean is authenticated
   */
  authenticate(login: string, password: string): Observable<User> {
    return this.http.post<User>(`${environment.apiUrl}/authentication/login`, {username: login.toLowerCase(), password})
      .pipe(map((data: User) => {
        if (data) {
          localStorage.setItem('user', JSON.stringify(data));
        }
        return data;
      }));
  }

  /**
   * Is user logged ?
   * @returns boolean if user is logged
   */
  isLogged(): boolean {
    console.log(localStorage.getItem('user'));
    return Boolean(localStorage.getItem('user'));
  }

  getUser(): boolean {
    const user = localStorage.getItem('user') || null;
    return user ? JSON.parse(user) : null;
  }

  logout() {
    console.log('remove logged user');
    return localStorage.removeItem('user');
  }
}
