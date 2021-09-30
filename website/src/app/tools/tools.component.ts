import {Component, OnInit} from '@angular/core';
import {ToolsService} from "../_services/tools.service";

@Component({
  selector: 'app-tools',
  templateUrl: './tools.component.html',
  styleUrls: ['./tools.component.scss']
})
export class ToolsComponent implements OnInit {

  constructor(private toolsService: ToolsService) {
  }

  converterTypes = [
    {name: 'Hexadecimal <-> String', fn: 'hexToString'},
    {name: 'Hexadecimal <-> INT16 Little-Endian', fn: 'hexToLE16'},
    {name: 'Hexadecimal <-> INT32 Little-Endian', fn: 'hexToLE32'},
    {name: 'Hexadecimal <-> INT16 Big-Endian', fn: 'hexToBE16'},
    {name: 'Hexadecimal <-> INT32 Big-Endian', fn: 'hexToBE32'},
    {name: 'Timestamp (seconds) <-> ISO Date', fn: 'timestampToDate'},
    {name: 'Timestamp (millisecs) <-> ISO Date', fn: 'timestampMilliToDate'},
  ];

  converter: any;
  zone1: string;
  zone2: string;
  error: string;

  ngOnInit() {
    this.converter = this.converterTypes[0].fn;
  }

  formatData(input: string) {
    const regex = /[^0123456789ABCDEF]/ig;
    const res = this[input].replaceAll(regex, '')?.toUpperCase();
    return this[input] = res;
  }

  async convert(reverse = false) {
    try {
      if (!reverse) {
        this.zone2 = await this.toolsService[this.converter](this.zone1);
      } else {
        this.zone1 = await this.toolsService[this.converter](this.zone2, reverse);
      }
    } catch (error) {
      this.error = error.message;
    }
  }

}
