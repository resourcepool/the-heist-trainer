import { Component, OnInit } from '@angular/core';
import { FormControl, FormGroup, Validators } from '@angular/forms';
import { AuthenticationService } from '../_services/authentication.service';
import { Router } from '@angular/router';

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

  ngOnInit() {
    this.loginForm.addControl('username', new FormControl(null, [Validators.required]));
    this.loginForm.addControl('password', new FormControl(null, [Validators.required]));
  }

  onSubmit() {
    console.log('submit');
    const username = this.loginForm.get('username').value;
    const password = this.loginForm.get('password').value;
    const logged = this._authService.authenticate(username, password);
    console.log(logged);
    if (logged) {
      this._router.navigate(['/']);
    }
  }

}
