import { Component, OnInit } from '@angular/core';
import { ResetService } from './reset.service';

@Component({
  selector: 'app-reset',
  templateUrl: './reset.component.html',
  styleUrls: ['./reset.component.scss'],
  providers: [ResetService]
})
export class ResetComponent implements OnInit {

  constructor() { }

  ngOnInit() {
  }

}
