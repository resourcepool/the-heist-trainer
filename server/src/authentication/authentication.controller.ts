import { Body, Controller, NotImplementedException, Post, UnauthorizedException } from '@nestjs/common';
import { LoginDto } from './dto/login.dto';
import { AuthenticationService } from './authentication.service';
import { ApiUseTags } from '@nestjs/swagger';

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

}
