import {KEY_TYPE_A, NFC, TAG_ISO_14443_3} from 'nfc-pcsc';
import {CardListener} from './CardListener.js';
import {getEmployeeCardSectors} from "./user.utils.js";
import {data} from "./data.js";

const key = 'FFFFFFFFFFFF'; // key must be a 12-chars HEX string, an instance of Buffer, or array of bytes
const keyType = KEY_TYPE_A;

export class NfcService {
    nfc = new NFC();
    cardListener = new CardListener();

    constructor() {
        this.nfc.on('reader', (reader) => {
            reader.on('card', async (card) => {
                // MIFARE Classic is ISO/IEC 14443-3 tag
                // skip other standards
                if (card.type !== TAG_ISO_14443_3) {
                    return;
                }
                console.log('Card detected');
                try {
                    const data = this.cardListener.getSectors();
                    if (!data) {
                        console.log('No User set');
                        return;
                    }
                    for (let i = 0; i < data.length; i++) {
                        if (data[i]) {
                            if (i === 0) {
                                console.log('Writing sector 0');
                                await reader.authenticate(1, keyType, key);
                                const sector = data[i];
                                for (let s = 0; s < sector.length / 16; s++) {
                                    const block = sector.slice(s * 16, (s + 1) * 16);
                                    console.log(block);
                                    await reader.write(1 + s, block, 16);
                                }
                            } else {
                                console.log('Writing sector ' + i);
                                await reader.authenticate((4 * i), keyType, key);
                                const sector = data[i];
                                for (let s = 0; s < sector.length / 16; s++) {
                                    const block = sector.slice(s * 16, (s + 1) * 16);
                                    console.log(block);
                                    await reader.write((4 * i) + s, block, 16);
                                }
                            }
                        }
                    }
                    console.log('Done');
                } catch (err) {
                    console.error(err);
                    throw err;
                }
            });

            reader.on('card.off', (card) => {
                console.log(`${reader.reader.name}  card removed`);
            });

            reader.on('error', (err) => {
                console.log(`${reader.reader.name}  an error occurred`, err);
            });

            reader.on('end', () => {
                console.log(`${reader.reader.name}  device removed`);
            });
        });

        this.nfc.on('error', (err) => {
            console.log('an error occurred', err);
        });
    }

    updateCardListener(userId) {
        try {
            const user = data.find(o => o.userId === userId)
            console.log('Setting card listener to new employee:');
            console.log(user);
            const sectors = getEmployeeCardSectors(userId);
            this.cardListener.updateSectors(sectors);
        } catch (e) {
            throw new Error(e);
        }
    }
}