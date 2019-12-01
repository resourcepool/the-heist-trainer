import { Body, Controller, HttpStatus, NotImplementedException, Post, Res, UnauthorizedException, } from '@nestjs/common';
import { LoginDto } from './dto/login.dto';
import { AuthenticationService } from './authentication.service';
import { ApiUseTags } from '@nestjs/swagger';
import { AuthorizationDto } from './dto/authorization.dto';
import { Response } from 'express';

@Controller('authentication')
@ApiUseTags('authentication')
export class AuthenticationController {

    constructor(
       private readonly authenticationService: AuthenticationService,
    ) {}

    @Post('login')
    login(@Body() loginDto: LoginDto) {
        try {
            this.authenticationService.login(loginDto.username, loginDto.password);
        } catch (e) {
            throw new UnauthorizedException(e);
        }
    }

    @Post('register')
    register() {
        throw new NotImplementedException();
    }

    @Post('safe')
    isSafeAuthorized(@Res() res: Response, @Body() authorizationDto: AuthorizationDto) {
        try {
            const id = authorizationDto.userId;
            const result = {
                isAuthorized: this.authenticationService.isSafeAuthorized(id),
            };
            return res
                .status(result.isAuthorized ? HttpStatus.OK : HttpStatus.UNAUTHORIZED)
                .json(result);
        } catch (e) {
            throw new UnauthorizedException(e);
        }
    }

}
