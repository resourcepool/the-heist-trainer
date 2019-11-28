import { Injectable, NotFoundException } from '@nestjs/common';
import { Employee } from '../_interface/employee.model';
import { data } from '../_data/users.data';
import { find } from 'lodash';

@Injectable()
export class EmployeeService {

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
