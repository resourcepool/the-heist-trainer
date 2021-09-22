import { ApiProperty } from '@nestjs/swagger';
import { IsUUID } from 'class-validator';

export class AuthorizationDto {

    @ApiProperty()
    @IsUUID('4')
    userId: string;
    lastLogin: number;
}
