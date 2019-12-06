import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';
import { AuthenticationService } from '../_services/authentication.service';
import { Router } from '@angular/router';
import { first } from 'rxjs/operators';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})
export class LoginComponent implements OnInit {

  constructor(
    private _authService: AuthenticationService,
    private _router: Router,
  ) { }

  loginForm: FormGroup = new FormGroup({});
  error: string;
  loading: boolean;

  ngOnInit() {
    if (this._authService.isLogged()) {
      this._router.navigate(['/']);
    }
    this.loginForm.addControl('username', new FormControl(null, [Validators.required]));
    this.loginForm.addControl('password', new FormControl(null, [Validators.required]));
  }

  onSubmit() {
    this.loading = true;
    const username = this.loginForm.get('username').value;
    const password = this.loginForm.get('password').value;
    this._authService.authenticate(username, password)
      .pipe(first())
      .subscribe(
        () => {
          this._router.navigate(['/']);
        },
        response  => {
          this.error = response.status === 401 ? 'The username/password is invalid' : 'An error occured';
          this.loading = false;
        },
        () => { this.loading = false; }
      );
  }

}
