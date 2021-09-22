import {NfcService} from "./nfc.service.js";

const nfcService = new NfcService();

// Update Scofield Level 3
nfcService.updateCardListener('4c78e64b-1dcd-40ba-999e-74e05d6459a2');