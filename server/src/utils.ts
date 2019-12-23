const SEPARATORS = new RegExp('[-:]', 'g');

/**
 * Converts a Hex String or a Pretty Hex String to an array of bytes (Uint8Array)
 * @param hexStr
 * @returns {Uint8Array}
 */
export const hexStringToBytes = (hexStr) => {
    const str = hexStr.replace(SEPARATORS, '');
    const size = str.length / 2;
    const bytes = new Uint8Array(size);
    for (let i = 0; i < size; ++i) {
        bytes[i] = hexStringToByte(str.substr(2 *  i, 2));
    }
    return bytes;
};

/**
 * Converts a hex string to a byte value.
 * Example: '42' => 0x42 <=> 66
 * @param byteAsHexString
 * @returns {number}
 */
export const hexStringToByte = (byteAsHexString) => {
    return parseInt(byteAsHexString, 16);
};

/**
 * Converts a byte to a hex string.
 * Example: 66 <=> 0x42 => '42'
 * @param byte
 * @returns {string}
 */
const byteToHexString = (byte) => {
    // tslint:disable-next-line:no-bitwise
    return (((byte & 0xF0) >> 4).toString(16) + (byte & 0x0F).toString(16)).toLowerCase();
};

/**
 * Converts an array of bytes (Uint8Array) to a pretty Hex String like 'XX:XX:XX:XX'
 * @param bytes
 * @returns {string}
 */
export const bytesToPrettyHexString = (bytes) => {
    let hex = '';
    for (const byte of bytes.values()) {
        if (hex.length > 0) {
            hex += ':';
        }
        hex += byteToHexString(byte);
    }
    return hex.toLowerCase();
};
