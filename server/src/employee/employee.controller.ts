import {Controller, Get, Header, NotFoundException, Param, Response, ParseUUIDPipe} from '@nestjs/common';
import { EmployeeService } from './employee.service';
import { Employee } from '../_interface/employee.model';
import { ApiUseTags } from '@nestjs/swagger';

@Controller('employees')
@ApiUseTags('employees')
export class EmployeeController {
    constructor(private readonly employeeService: EmployeeService) {}

    @Get()
    getEmployees(): Employee[] {
        return this.employeeService.getEmployees();
    }

    @Get('/:userId')
    getEmployee(@Param('userId', new ParseUUIDPipe({version: '4'})) userId): Employee {
        try {
            return this.employeeService.getEmployee(userId);
        } catch (e) {
            throw new NotFoundException(e);
        }
    }

    @Get('/:userId/hexdump')
    @Header(`Content-type`, 'text/plain')
    async getEmployeeCardDumpAsString(@Param('userId', new ParseUUIDPipe({version: '4'})) userId, @Response() res) {
        try {
            res.send(this.employeeService.getEmployeeCardDumpAsString(userId));
        } catch (e) {
            throw new NotFoundException(e);
        }
    }

    @Get('/:userId/hex.dmp')
    @Header(`Content-type`, 'application/octet-stream')
    async getEmployeeCardDump(@Param('userId', new ParseUUIDPipe({version: '4'})) userId, @Response() res) {
        try {
            res.send(this.employeeService.getEmployeeCardDump(userId));
        } catch (e) {
            throw new NotFoundException(e);
        }
    }

}
