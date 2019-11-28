import { Module } from '@nestjs/common';
import { EmployeeController } from './employee.controller';
import { EmployeeService } from './employee.service';

@Module({
    imports: [EmployeeModule],
    controllers: [EmployeeController],
    providers: [EmployeeService],
})
export class EmployeeModule {}
