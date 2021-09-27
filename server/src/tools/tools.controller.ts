import {Body, Controller, Post } from "@nestjs/common";
import {ApiTags} from "@nestjs/swagger";
import {ToolsService} from "./tools.service";
import {EntryDto} from "./dto/login.dto";

@Controller('tools')
@ApiTags('tools')
export class ToolsController {

    constructor(
        private readonly toolsService: ToolsService,
    ) {}

    @Post('convert/hextostring')
    convertHexToString(@Body() entryDto: EntryDto) {

    }
}
