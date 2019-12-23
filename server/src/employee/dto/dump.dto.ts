import { ApiModelProperty } from '@nestjs/swagger';
import { IsString } from 'class-validator';

export class DumpDto {

    @ApiModelProperty()
    @IsString()
    firstName: string;

    @ApiModelProperty()
    @IsString()
    lastName: string;

    @ApiModelProperty()
    @IsString()
    hexDump: string;
}
