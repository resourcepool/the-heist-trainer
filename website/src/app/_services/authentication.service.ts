import { Injectable } from '@angular/core';
import { config } from '../../config/config';

@Injectable()
export class AuthenticationService {

  private _isLogged = false;

  constructor() { }

  /**
   * Authentication method
   * @param login username
   * @param password password
   * @returns Boolean is authenticated
   */
  authenticate(login: string, password: string): boolean {
    this._isLogged = login.toLowerCase() === config.login && password === config.password;
    return this._isLogged;
  }

  /**
   * Is user logged ?
   * @returns boolean if user is logged
   */
  isLogged(): boolean {
    return this._isLogged;
  }
}
