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
        const dateOfBirthTimestamp = Math.round(
            new Date(result.dateOfBirth[0], result.dateOfBirth[1], result.dateOfBirth[2], 0, 0, 0, 0).getTime() / 1000);
        const dateOfHiringTimestamp = Math.round(
            new Date(result.dateOfHiring[0], result.dateOfHiring[1], result.dateOfHiring[2], 9, 30, 0, 0).getTime() / 1000);
        const lastLoginTimestamp = Math.round(
            new Date(result.lastLogin[0], result.lastLogin[1], result.lastLogin[2], result.lastLogin[3],
                result.lastLogin[4], result.lastLogin[5], 0).getTime() / 1000);
        datesBuf.writeInt32LE(dateOfBirthTimestamp, 0);
        datesBuf.writeInt32LE(dateOfHiringTimestamp, 4);
        datesBuf.writeInt32LE(lastLoginTimestamp, 8);
        return Buffer.concat([firstNameBuf, lastNameBuf, employeeIdBuf, datesBuf]);
    }

    getEmployeeCardDumpAsString(userId: string): string {
        return bytesToPrettyHexString(this.getEmployeeCardDump(userId));
    }
}
