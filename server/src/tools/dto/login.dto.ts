import { ApiProperty } from '@nestjs/swagger';
import {IsNumber, IsOptional, IsString} from 'class-validator';

export class EntryDto {

    @ApiProperty()
    data: string;

    @ApiProperty()
    @IsNumber()
    @IsOptional()
    byteLength: number;

}
