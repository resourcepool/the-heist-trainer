import { Controller, Get, NotFoundException, Param, ParseUUIDPipe } from '@nestjs/common';
import { AppService } from './app.service';
import { Employee } from './_interface/employee.model';

@Controller('employees')
export class AppController {
  constructor(private readonly appService: AppService) {}

  @Get()
  getEmployees(): Employee[] {
    return this.appService.getEmployees();
  }

  @Get('/:userId')
  getEmployee(@Param('userId', new ParseUUIDPipe({version: '5'})) userId): Employee {
    try {
      return this.appService.getEmployee(userId);
    } catch (e) {
      throw new NotFoundException(e);
    }
  }

}
