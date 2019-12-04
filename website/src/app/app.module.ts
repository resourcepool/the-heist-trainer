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

@NgModule({
  declarations: [
    AppComponent,
    LoginComponent,
    HomeComponent,
    LoaderComponent,
    FolderComponent,
    FolderDetailComponent,
    FoldersComponent,
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
