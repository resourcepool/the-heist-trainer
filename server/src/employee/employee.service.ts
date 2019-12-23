import { Injectable, NotFoundException } from '@nestjs/common';
import { Employee } from '../_interface/employee.model';
import { data } from '../_data/users.data';
import { find } from 'lodash';
import { hexStringToBytes, bytesToPrettyHexString } from '../utils';

@Injectable()
export class EmployeeService {

    getEmployees(): Employee[] {
        return data;
    }

    getEmployee(userId: string): Employee {
        const result = find(data, o => o.userId === userId);
        if (!result) {
            throw new NotFoundException('user not found');
        }
        return result;
    }

    getEmployeeCardDump(userId: string): Buffer {
        const result: Employee = find(data, o => o.userId === userId);
        if (!result) {
            throw new NotFoundException('user not found');
        }

        const firstNameBuf = Buffer.alloc(32);
        result.firstName.substr(0, 32).toUpperCase().split('').forEach((c, i) => firstNameBuf.writeUInt8(c.charCodeAt(0), i));
        const lastNameBuf = Buffer.alloc(32);
        result.lastName.substr(0, 32).toUpperCase().split('').forEach((c, i) => lastNameBuf.writeUInt8(c.charCodeAt(0), i));
        const employeeIdBuf = Buffer.from(hexStringToBytes(result.userId));
        const datesBuf = Buffer.alloc(16);
        const dateOfBirthTimestamp = Math.round(new Date(1989, 9, 28, 0, 0, 0, 0).getTime() / 1000);
        const dateOfHiringTimestamp = Math.round(new Date(2013, 2, 8, 9, 30, 0, 0).getTime() / 1000);
        const lastLoginTimestamp = Math.round(Date.now() / 1000);
        datesBuf.writeInt32BE(dateOfBirthTimestamp, 0);
        datesBuf.writeInt32BE(dateOfHiringTimestamp, 4);
        datesBuf.writeInt32BE(lastLoginTimestamp, 8);
        return Buffer.concat([firstNameBuf, lastNameBuf, employeeIdBuf, datesBuf]);
    }

    getEmployeeCardDumpAsString(userId: string): string {
        const result: Employee = find(data, o => o.userId === userId);
        if (!result) {
            throw new NotFoundException('user not found');
        }

        const firstNameBuf = Buffer.alloc(32);
        result.firstName.substr(0, 32).toUpperCase().split('').forEach((c, i) => firstNameBuf.writeUInt8(c.charCodeAt(0), i));
        const lastNameBuf = Buffer.alloc(32);
        result.lastName.substr(0, 32).toUpperCase().split('').forEach((c, i) => lastNameBuf.writeUInt8(c.charCodeAt(0), i));
        const employeeIdBuf = Buffer.from(hexStringToBytes(result.userId));
        const datesBuf = Buffer.alloc(16);
        const dateOfBirthTimestamp = Math.round(new Date(1989, 9, 28, 0, 0, 0, 0).getTime() / 1000);
        const dateOfHiringTimestamp = Math.round(new Date(2013, 2, 8, 9, 30, 0, 0).getTime() / 1000);
        const lastLoginTimestamp = Math.round(Date.now() / 1000);
        datesBuf.writeInt32BE(dateOfBirthTimestamp, 0);
        datesBuf.writeInt32BE(dateOfHiringTimestamp, 4);
        datesBuf.writeInt32BE(lastLoginTimestamp, 8);
        return `${bytesToPrettyHexString(firstNameBuf)}\r\n${bytesToPrettyHexString(lastNameBuf)}\r\n${bytesToPrettyHexString(employeeIdBuf)}\r\n${bytesToPrettyHexString(datesBuf)}`;
    }
}
