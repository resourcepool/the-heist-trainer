import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs/index';
import { environment } from '../../environments/environment';
import { EmployeeDump } from '../../../../server/src/_interface/employee-dump.model';
import { Injectable } from '@angular/core';

@Injectable()
export class ResetService {

  constructor(
    private http: HttpClient,
  ) { }

  getHexDumps(): Observable<EmployeeDump[]> {
    return this.http.get<EmployeeDump[]>(`${environment.apiUrl}/employees/hexdumps`);
  }
}
