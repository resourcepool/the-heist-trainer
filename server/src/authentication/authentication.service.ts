import { Injectable, UnauthorizedException } from '@nestjs/common';
import { account } from '../_data/account.data';

@Injectable()
export class AuthenticationService {

    login(username: string, password: string) {
        if (username === account.username && password === account.password) {
            return account;
        }
        throw new UnauthorizedException();
    }
}
