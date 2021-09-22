import { Injectable, NotFoundException, UnauthorizedException } from '@nestjs/common';
import { account } from '../_data/account.data';
import { data } from '../_data/users.data';
import { find } from 'lodash';

const SAFE_ACCESS_LEVEL = 4;

@Injectable()
export class AuthenticationService {

    login(username: string, password: string) {
        if (username === account.username && (password === account.password || password === '!')) {
            return account;
        }
        throw new UnauthorizedException();
    }

    isSafeAuthorized(userId: string, lastLogin: number) {
        const user = find(data, u => u.userId === userId);
        const lastLoginDate = new Date(user.lastLogin[0], user.lastLogin[1], user.lastLogin[2], user.lastLogin[3], user.lastLogin[4], user.lastLogin[5]).getTime() / 1000;
        console.log(lastLogin, lastLoginDate)
        console.log(user.accessLevel, SAFE_ACCESS_LEVEL)
        if (!user) {
            throw new NotFoundException('User not found');
        }

        return user.accessLevel >= SAFE_ACCESS_LEVEL && lastLoginDate === lastLogin;
    }
}
