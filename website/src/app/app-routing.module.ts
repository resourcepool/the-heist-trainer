import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { HomeComponent } from './home/home.component';
import { LoginComponent } from './login/login.component';
import { HomeGuard } from './_guards/home.guard';
import { LogoutGuard } from './_guards/logout.guard';


const routes: Routes = [
  {
    path: '',
    pathMatch: 'full',
    component: HomeComponent,
    canActivate: [HomeGuard],
  },
  {
    path: 'login',
    component: LoginComponent,
  },
  {
    path: 'logout',
    redirectTo: 'login',
    canActivate: [LogoutGuard],
  },
  {
    path: '**',
    redirectTo: ''
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
