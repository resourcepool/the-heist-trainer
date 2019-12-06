import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { folders } from '../_data/folders.data';

@Component({
  selector: 'app-folder-detail',
  templateUrl: './folder-detail.component.html',
  styleUrls: ['./folder-detail.component.scss']
})
export class FolderDetailComponent implements OnInit {

  constructor(
    private _route: ActivatedRoute,
    private _router: Router,
  ) { }

  folder: any;
  param: string = null;

  ngOnInit() {
    this.param = this._route.snapshot.paramMap.get('folder');
    if (!this.param) {
      this._router.navigate(['/']);
    }
    this.folder = folders[this.param];
  }

}
