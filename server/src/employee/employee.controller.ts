import { Controller, Get, Header, NotFoundException, Param, Response, ParseUUIDPipe } from '@nestjs/common';
import { EmployeeService } from './employee.service';
import { Employee } from '../_interface/employee.model';
import { ApiTags } from '@nestjs/swagger';
import { DumpDto } from './dto/dump.dto';
import {EmployeeDto} from './dto/employee.dto';

@Controller('employees')
@ApiTags('employees')
export class EmployeeController {
    constructor(private readonly employeeService: EmployeeService) {
    }

    @Get()
    getEmployees(): EmployeeDto[] {
        return this.employeeService.getEmployees().map(e => {
            return {
                userId: e.userId,
                firstName: e.firstName,
                lastName: e.lastName,
                accessLevel: e.accessLevel,
                dateOfBirth: e.dateOfBirth,
                dateOfHiring: e.dateOfHiring,
                lastLogin: e.lastLogin,
                dateOfBirthTimestamp: Math.floor(new Date(e.dateOfBirth).getTime() / 1000),
                dateOfHiringTimestamp: Math.floor(new Date(e.dateOfHiring).getTime() / 1000),
                lastLoginTimestamp: Math.floor(new Date(e.lastLogin).getTime() / 1000),
            };
        });
    }

    @Get('hexdumps')
    getEmployeesCardDumps(): DumpDto[] {
        try {
            return this.employeeService.getEmployeesCardDumps();
        } catch (e) {
            throw new NotFoundException(e);
        }
    }

    @Get(':userId')
    getEmployee(@Param('userId', new ParseUUIDPipe({version: '4'})) userId): Employee {
        try {
            return this.employeeService.getEmployee(userId);
        } catch (e) {
            throw new NotFoundException(e);
        }
    }

    @Get(':userId/hexdump')
    @Header(`Content-type`, 'text/plain')
    async getEmployeeCardDumpAsString(@Param('userId', new ParseUUIDPipe({version: '4'})) userId, @Response() res) {
        try {
            res.send(this.employeeService.getEmployeeCardDumpAsString(userId));
        } catch (e) {
            throw new NotFoundException(e);
        }
    }

}
