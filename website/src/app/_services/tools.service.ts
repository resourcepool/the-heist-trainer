import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { environment } from '../../environments/environment';

interface ConvertData {
  data: string;
}

@Injectable()
export class ToolsService {

  constructor(
    private http: HttpClient,
  ) { }

  hexToString(data: string, reverse = false): Promise<string> {
    const url = reverse ? `${environment.apiUrl}/tools/stringtohex` : `${environment.apiUrl}/tools/hextostring`;
    return this.http.post<ConvertData>(url, {data})
      .toPromise()
      .then(result => {
        return result?.data;
      });
  }

  hexToLE(data: string, reverse = false, byteLength): Promise<string> {
    const url = reverse ? `${environment.apiUrl}/tools/hextole` : `${environment.apiUrl}/tools/letohex`;
    return this.http.post<ConvertData>(url, {data, byteLength})
      .toPromise()
      .then(result => {
        return result?.data;
      })
      .catch(e => { throw new Error(e.error?.message) });
  }

  hexToBE(data: string, reverse = false, byteLength): Promise<string> {
    const url = reverse ? `${environment.apiUrl}/tools/hextobe` : `${environment.apiUrl}/tools/betohex`;
    return this.http.post<ConvertData>(url, {data, byteLength})
      .toPromise()
      .then(result => {
        return result?.data;
      })
      .catch(e => { throw new Error(e.error?.message) });
  }

  hexToLE16(data, reverse): Promise<string> {
    return this.hexToLE(data, reverse, 2);
  }

  hexToLE32(data, reverse): Promise<string> {
    return this.hexToLE(data, reverse, 4);
  }

  hexToBE16(data, reverse): Promise<string> {
    return this.hexToBE(data, reverse, 2);
  }

  hexToBE32(data, reverse): Promise<string> {
    return this.hexToBE(data, reverse, 4);
  }

  timestampToDate(data, reverse = false) {
    if (!reverse) {
      return new Date(Math.round(Number(data) * 1000)).toISOString();
    } else {
      return new Date(data).getTime() / 1000;
    }
  }

  timestampMilliToDate(data, reverse = false) {
    if (!reverse) {
      return new Date(Number(data)).toISOString();
    } else {
      return new Date(data).getTime();
    }
  }
}
