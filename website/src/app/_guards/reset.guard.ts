import { Injectable } from '@angular/core';
import { CanActivate, ActivatedRouteSnapshot, RouterStateSnapshot, Router } from '@angular/router';
import { environment } from '../../environments/environment';

@Injectable({
  providedIn: 'root'
})
export class ResetGuard implements CanActivate {

  constructor(private router: Router) {
  }

  canActivate(route: ActivatedRouteSnapshot, state: RouterStateSnapshot) {
    let password;
    do {
      password = prompt('Password');
    } while (password != null && password !== environment.adminPassword);

    if (!password) {
      this.router.navigate(['']);
    }

    return password === environment.adminPassword;
  }

}
