import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { HomeComponent } from './home/home.component';
import { LoginComponent } from './login/login.component';
import { HomeGuard } from './_guards/home.guard';
import { LogoutGuard } from './_guards/logout.guard';
import { FoldersComponent } from './folders/folders.component';
import { FolderDetailComponent } from './folder-detail/folder-detail.component';
import { PageNotFoundComponent } from './page-not-found/page-not-found.component';
import { TnsaEmployeesComponent } from './tnsa-employees/tnsa-employees.component';
import { ResetGuard } from './_guards/reset.guard';
import { ResetComponent } from './reset/reset.component';


const routes: Routes = [
  {
    path: 'login',
    component: LoginComponent,
  },
  {
    path: 'logout',
    canActivate: [LogoutGuard],
    children: [],
  },
  {
    path: 'reset',
    canActivate: [ResetGuard],
    component: ResetComponent,
  },
  {
    path: '',
    component: HomeComponent,
    canActivate: [HomeGuard],
    children: [
      {
        path: '',
        component: FoldersComponent,
      },
      {
        path: 'folder/tnsa-employees',
        component: TnsaEmployeesComponent,
      },
      {
        path: 'folder/:folder',
        component: FolderDetailComponent,
      },
    ]
  },
  {
    path: '**',
    component: PageNotFoundComponent,
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
