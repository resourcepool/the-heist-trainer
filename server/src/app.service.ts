import { Injectable, NotFoundException } from '@nestjs/common';
import { data } from './_data/users.data';
import { Employee } from './_interface/employee.model';
import { find } from 'lodash';

@Injectable()
export class AppService {

  getEmployees(): Employee[] {
    return data;
  }

  getEmployee(userId: string): Employee {
    const result = find(data, o => o.userId === userId);
    if (!result) {
      throw new NotFoundException('user not found');
    }
    return result;
  }

}
