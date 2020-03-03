import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs/index';
import { environment } from '../../environments/environment';
import { Injectable } from '@angular/core';
import { Employee } from '../../../../server/src/_interface/employee.model';

@Injectable()
export class TnsaEmployeesService {

  constructor(
    private http: HttpClient,
  ) { }

  getEmployees(): Observable<Employee[]> {
    return this.http.get<Employee[]>(`${environment.apiUrl}/employees`);
  }
}
