import { ApiProperty } from '@nestjs/swagger';
import { IsString } from 'class-validator';

export class EntryDto {

    @ApiProperty()
    @IsString()
    data: string;

}
