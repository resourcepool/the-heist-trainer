import { Module } from '@nestjs/common';
import { EmployeeModule } from './employee/employee.module';
import { AuthenticationModule } from './authentication/authentication.module';
import { ToolsModule } from './tools/tools.module';

@Module({
  imports: [EmployeeModule, AuthenticationModule, ToolsModule],
  controllers: [],
  providers: [],
})
export class AppModule {}
