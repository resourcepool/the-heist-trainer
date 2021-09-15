import { ApiProperty } from '@nestjs/swagger';
import { IsString } from 'class-validator';

export class DumpDto {

    @ApiProperty()
    @IsString()
    firstName: string;

    @ApiProperty()
    @IsString()
    lastName: string;

    @ApiProperty()
    @IsString()
    hexDump: string;
}
