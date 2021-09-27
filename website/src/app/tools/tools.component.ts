import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-tools',
  templateUrl: './tools.component.html',
  styleUrls: ['./tools.component.scss']
})
export class ToolsComponent implements OnInit {

  constructor() {}

  converterTypes = [
    {name: 'Hexadecimal <-> String', fn: 'hexToString'},
    {name: 'Hexadecimal <-> Number Little-Endian', fn: 'hexToLE'},
    {name: 'Hexadecimal <-> Number Big-Endian', fn: 'hexToBE'},
  ];

  converter: any;
  zone1: string;
  zone2: string;

  ngOnInit() {
    this.converter = this.converterTypes[0].fn;
  }

  formatData(input: string) {
    const regex = /[^0123456789ABCDEF]/ig;
    const res = this[input].replaceAll(' ', '')?.replaceAll(regex, '')?.toUpperCase();
    return this[input] = res.match(/.{1,2}/g)?.join(' ');
  }

  convert(reverse = false) {
    console.log(this.converter);
  }

}
