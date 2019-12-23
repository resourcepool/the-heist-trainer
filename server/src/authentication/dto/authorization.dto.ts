import { ApiModelProperty } from '@nestjs/swagger';
import { IsUUID } from 'class-validator';

export class AuthorizationDto {

    @ApiModelProperty()
    @IsUUID('4')
    userId: string;
    lastLogin: bigint;
}
