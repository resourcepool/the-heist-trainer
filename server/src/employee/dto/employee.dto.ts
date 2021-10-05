import {AccessLevelEnum} from '../../_interface/access-level.enum';

export interface EmployeeDto {
    userId: string;
    firstName: string;
    lastName: string;
    accessLevel: AccessLevelEnum;
    dateOfBirth: string;
    dateOfHiring: string;
    lastLogin: string;
    dateOfBirthTimestamp: number;
    dateOfHiringTimestamp: number;
    lastLoginTimestamp: number;
}
