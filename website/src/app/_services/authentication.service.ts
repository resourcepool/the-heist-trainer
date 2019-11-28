import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from '../../environments/environment';
import { User } from '../_models/user.model';
import { Observable } from 'rxjs';
import { map } from 'rxjs/operators';

@Injectable()
export class AuthenticationService {

  private _isLogged = false;

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
        this._isLogged = true;
        return data;
      }));
  }

  /**
   * Is user logged ?
   * @returns boolean if user is logged
   */
  isLogged(): boolean {
    return this._isLogged;
  }

  getUser(): boolean {
    const user = localStorage.getItem('user') || null;
    return user ? JSON.parse(user) : null;
  }

  logout() {
    localStorage.removeItem('user');
    this._isLogged = false;
  }
}
