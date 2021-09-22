import {NfcService} from "./nfc.service.js";

const nfcService = new NfcService();

// Update Danny Ocean level 4
nfcService.updateCardListener('9d4c659a-ebbd-4ea9-be3e-5f71a25e07b3');