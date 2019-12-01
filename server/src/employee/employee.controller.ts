import { Controller, Get, NotFoundException, Param, ParseUUIDPipe } from '@nestjs/common';
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

}
