import { Module } from '@nestjs/common';
import { EmployeeModule } from './employee/employee.module';
import { AuthenticationModule } from './authentication/authentication.module';
import {NfcModule} from './nfc/nfc.module';

@Module({
  imports: [EmployeeModule, AuthenticationModule, NfcModule],
  controllers: [],
  providers: [],
})
export class AppModule {}
