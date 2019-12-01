import { Injectable, NotFoundException, UnauthorizedException } from '@nestjs/common';
import { account } from '../_data/account.data';
import { data } from '../_data/users.data';
import { find } from 'lodash';

const SAFE_ACCESS_LEVEL = 7;

@Injectable()
export class AuthenticationService {

    login(username: string, password: string) {
        if (username === account.username && password === account.password) {
            return account;
        }
        throw new UnauthorizedException();
    }

    isSafeAuthorized(userId: string) {
        const user = find(data, u => u.userId === userId);
        if (!user) {
            throw new NotFoundException('User not found');
        }

        return user.accessLevel === SAFE_ACCESS_LEVEL;
    }
}
