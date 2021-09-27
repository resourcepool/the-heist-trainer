import {data} from "../server/src/_data/data.mjs";
import {bytesToPrettyHexString, hexStringToBytes} from "./utils.js";

export function getEmployeeCardDump(userId) {
    const result = data.find(o => o.userId === userId);
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

export function getEmployeeCardSectors(userId) {
    const result = data.find(o => o.userId === userId);
    if (!result) {
        throw new NotFoundException('user not found');
    }
    const sector0 = Buffer.alloc(32);
    sector0.writeUInt8(0xFD, 0);
    sector0.writeUInt8(0x3E, 1);
    result.firstName.substr(0, 30).toUpperCase().split('').forEach((c, i) => sector0.writeUInt8(c.charCodeAt(0), i));
    const sector1 = Buffer.alloc(48);
    result.firstName.substr(30, 62).toUpperCase().split('').forEach((c, i) => sector0.writeUInt8(c.charCodeAt(0), i));
    sector1.writeUInt8(0xFD, 32);
    sector1.writeUInt8(0x3E, 33);
    result.lastName.substr(0, 14).toUpperCase().split('').forEach((c, i) => sector1.writeUInt8(c.charCodeAt(0), i + 34));
    const sector2 = Buffer.alloc(48);
    result.lastName.substr(14, 62).toUpperCase().split('').forEach((c, i) => sector2.writeUInt8(c.charCodeAt(0), i));
    const uuidTLVHeader = Buffer.from(Uint8Array.of(0xFD, 0x10));
    const timestampTLVHeader = Buffer.from(Uint8Array.of(0xFD, 0x04));
    const uuidBuffer = Buffer.from(hexStringToBytes(result.userId));
    const endTLVHeader = Buffer.alloc(12);
    endTLVHeader.fill(0);
    endTLVHeader.writeUInt8(0xFE, 0);
    const dateOfBirthTimestamp = Math.round(
        new Date(result.dateOfBirth[0], result.dateOfBirth[1], result.dateOfBirth[2], 0, 0, 0, 0).getTime() / 1000);
    const dateOfHiringTimestamp = Math.round(
        new Date(result.dateOfHiring[0], result.dateOfHiring[1], result.dateOfHiring[2], 9, 30, 0, 0).getTime() / 1000);
    const lastLoginTimestamp = Math.round(
        new Date(result.lastLogin[0], result.lastLogin[1], result.lastLogin[2], result.lastLogin[3],
            result.lastLogin[4], result.lastLogin[5], 0).getTime() / 1000);
    const dateOfBirthBuffer = Buffer.alloc(4);
    dateOfBirthBuffer.writeInt32LE(dateOfBirthTimestamp, 0);
    const dateOfHiringBuffer = Buffer.alloc(4);
    dateOfHiringBuffer.writeInt32LE(dateOfHiringTimestamp, 0);
    const lastLoginBuffer = Buffer.alloc(4);
    lastLoginBuffer.writeInt32LE(lastLoginTimestamp, 0);
    const sector3 = Buffer.concat([uuidTLVHeader, uuidBuffer,
        timestampTLVHeader, dateOfBirthBuffer,
        timestampTLVHeader, dateOfHiringBuffer,
        timestampTLVHeader, lastLoginBuffer, endTLVHeader]);

    return [
        sector0,
        sector1,
        sector2,
        sector3,
    ];
}

export function getEmployeeCardDumpAsString(userId)
{
    return bytesToPrettyHexString(this.getEmployeeCardDump(userId));
}

export function getEmployeesCardDumps()
{
    return data.map(e => {
        return {
            firstName: e.firstName,
            lastName: e.lastName,
            hexDump: this.getEmployeeCardDumpAsString(e.userId),
        };
    });
}
