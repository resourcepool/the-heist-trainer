import { Component, OnInit } from '@angular/core';
import { ResetService } from './reset.service';
import { Observable } from 'rxjs/index';
import { EmployeeDump } from '../../../../server/src/_interface/employee-dump.model';

@Component({
  selector: 'app-reset',
  templateUrl: './reset.component.html',
  styleUrls: ['./reset.component.scss'],
  providers: [ResetService]
})
export class ResetComponent implements OnInit {

  constructor(
    private resetService: ResetService,
  ) { }

  employeeDumps: Observable<EmployeeDump[]>;

  ngOnInit() {
    this.employeeDumps = this.resetService.getHexDumps();
  }

  copyDump() {

  }

}
