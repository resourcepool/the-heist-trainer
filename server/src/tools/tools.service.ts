import {BadRequestException, Injectable} from '@nestjs/common';
import {Buffer} from "buffer";

@Injectable()
export class ToolsService {

    private convert(from, to) {
        return data => Buffer.from(data, from).toString(to);
    }

    hexToString(data) {
        return this.convert('hex', 'utf8')(data);
    }

    stringToHex(data) {
        return this.convert('utf8', 'hex')(data);
    }

    hexStringToIntLittleEndian(data, byteLength) {
        try {
            const buf = Buffer.alloc(byteLength);
            buf.writeIntLE(data, 0, byteLength);
            return buf.toString('hex');
        } catch (e) {
            throw new BadRequestException('Les données sont invalides');
        }
    }

    intLittleEndianToHexString(data, byteLength) {
        try {
            return Buffer.from(data, 'hex').readIntLE(0, byteLength);
        } catch (e) {
            throw new BadRequestException('Les données sont invalides');
        }
    }

    hexStringToIntBigEndian(data, byteLength) {
        try {
            const buf = Buffer.alloc(byteLength);
            buf.writeIntBE(data, 0, byteLength);
            return buf.toString('hex');
        } catch (e) {
            throw new BadRequestException('Les données sont invalides');
        }
    }

    intBigEndianToHexString(data, byteLength) {
        try {
            return Buffer.from(data, 'hex').readIntBE(0, byteLength);
        } catch (e) {
            throw new BadRequestException('Les données sont invalides');
        }
    }
}
