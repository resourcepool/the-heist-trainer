import { Controller, Get, Header, NotFoundException, Param, Response, ParseUUIDPipe } from '@nestjs/common';
import { ApiTags } from '@nestjs/swagger';
import {NfcService} from './nfc.service';

@Controller('nfc')
@ApiTags('nfc')
export class NfcController {
    constructor(private readonly nfcService: NfcService) {
    }

    @Get('format/:userId')
    setCardParameters(@Param('userId', new ParseUUIDPipe({version: '4'})) userId) {
        try {
            this.nfcService.updateCardListener(userId);
        } catch (e) {
            throw new NotFoundException(e);
        }
    }

}
