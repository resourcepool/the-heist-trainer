import {Body, Controller, HttpCode, Post} from "@nestjs/common";
import {ApiTags} from "@nestjs/swagger";
import {ToolsService} from "./tools.service";
import {EntryDto} from "./dto/login.dto";
import {Buffer} from "buffer";

@Controller('tools')
@ApiTags('tools')
export class ToolsController {

    constructor(
        private readonly toolsService: ToolsService,
    ) {}

    @Post('hextostring')
    @HttpCode(200)
    convertHexToString(@Body() entryDto: EntryDto) {
        return {data: this.toolsService.hexToString(entryDto?.data?.replace(/[ ]/g, ''))};
    }

    @Post('stringtohex')
    @HttpCode(200)
    convertStringToHex(@Body() entryDto: EntryDto) {
        return {data: this.toolsService.stringToHex(entryDto.data)};
    }

    @Post('hextole')
    @HttpCode(200)
    convertStringToLittleEndian(@Body() entryDto: EntryDto) {
        return {data: this.toolsService.hexStringToIntLittleEndian(entryDto.data, entryDto.byteLength)};
    }

    @Post('letohex')
    @HttpCode(200)
    convertLittleEndianToString(@Body() entryDto: EntryDto) {
        return {data: this.toolsService.intLittleEndianToHexString(entryDto.data, entryDto.byteLength)};
    }

    @Post('hextobe')
    @HttpCode(200)
    convertStringToBigEndian(@Body() entryDto: EntryDto) {
        return {data: this.toolsService.hexStringToIntBigEndian(entryDto.data, entryDto.byteLength)};
    }

    @Post('betohex')
    @HttpCode(200)
    convertBigEndianToString(@Body() entryDto: EntryDto) {
        return {data: this.toolsService.intBigEndianToHexString(entryDto.data, entryDto.byteLength)};
    }
}
