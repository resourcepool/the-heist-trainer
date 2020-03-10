import { Module } from '@nestjs/common';
import {NfcController} from './nfc.controller';
import {NfcService} from './nfc.service';
import {EmployeeModule} from '../employee/employee.module';

@Module({
    imports: [EmployeeModule],
    controllers: [NfcController],
    providers: [NfcService],
})
export class NfcModule {}
