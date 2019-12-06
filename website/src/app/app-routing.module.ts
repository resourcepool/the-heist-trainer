import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { HomeComponent } from './home/home.component';
import { LoginComponent } from './login/login.component';
import { HomeGuard } from './_guards/home.guard';
import { LogoutGuard } from './_guards/logout.guard';
import { FoldersComponent } from './folders/folders.component';
import { FolderComponent } from './folders/folder/folder.component';
import { FolderDetailComponent } from './folder-detail/folder-detail.component';
import { PageNotFoundComponent } from './page-not-found/page-not-found.component';


const routes: Routes = [
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
        path: 'folder/:folder',
        component: FolderDetailComponent,
      },
      {
        path: '**',
        component: PageNotFoundComponent,
      }
    ]
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
