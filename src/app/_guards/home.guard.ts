import { Injectable } from '@angular/core';
import { CanActivate, ActivatedRouteSnapshot, RouterStateSnapshot, Router } from '@angular/router';
import { AuthenticationService } from '../_services/authentication.service';

const LOGIN_ROUTE = '/login';

@Injectable({
  providedIn: 'root'
})
export class HomeGuard implements CanActivate {

  constructor(
    private authentication: AuthenticationService,
    private router: Router
  ) {}

  canActivate(route: ActivatedRouteSnapshot, state: RouterStateSnapshot) {
    if (this.authentication.isLogged()) {
      return true;
    }
    this.router.navigate([LOGIN_ROUTE]);
    return false;
  }

}
