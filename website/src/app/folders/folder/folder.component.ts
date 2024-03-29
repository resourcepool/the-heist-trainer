import { Component, Input, OnInit } from '@angular/core';
import { Router } from '@angular/router';

@Component({
  selector: 'app-folder',
  templateUrl: './folder.component.html',
  styleUrls: ['./folder.component.scss']
})
export class FolderComponent implements OnInit {

  @Input() title: string;
  @Input() url: string;
  @Input() forbidden = false;

  constructor(
    private _router: Router,
  ) { }

  ngOnInit() {
  }

  onDblClick() {
    return this._router.navigate(['folder', this.url]);
  }

}
