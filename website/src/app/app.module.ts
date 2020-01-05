import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { LoginComponent } from './login/login.component';
import { HomeComponent } from './home/home.component';
import { AuthenticationService } from './_services/authentication.service';
import { ReactiveFormsModule } from '@angular/forms';
import { LoaderComponent } from './shared';
import { HttpClientModule } from '@angular/common/http';
import { FolderComponent } from './folders/folder/folder.component';
import { FolderDetailComponent } from './folder-detail/folder-detail.component';
import { FoldersComponent } from './folders/folders.component';
import { PageNotFoundComponent } from './page-not-found/page-not-found.component';
import { TnsaEmployeesComponent } from './tnsa-employees/tnsa-employees.component';
import { ResetComponent } from './reset/reset.component';

@NgModule({
  declarations: [
    AppComponent,
    LoginComponent,
    HomeComponent,
    LoaderComponent,
    FolderComponent,
    FolderDetailComponent,
    FoldersComponent,
    PageNotFoundComponent,
    TnsaEmployeesComponent,
    ResetComponent,
  ],
  imports: [
    BrowserModule,
    ReactiveFormsModule,
    AppRoutingModule,
    HttpClientModule,
  ],
  providers: [AuthenticationService],
  bootstrap: [AppComponent]
})
export class AppModule { }
