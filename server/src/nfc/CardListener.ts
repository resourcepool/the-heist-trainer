export class CardListener {
    sector0: Buffer;
    sector1: Buffer;
    sector2: Buffer;
    sector3: Buffer;

    getSectors(): Buffer[] {
        if (!this.sector0 || !this.sector1 || !this.sector2 || !this.sector3) {
            return null;
        }
        return [this.sector0, this.sector1, this.sector2, this.sector3];
    }

    updateSectors(sectors: Buffer[]) {
        this.sector0 = sectors[0];
        this.sector1 = sectors[1];
        this.sector2 = sectors[2];
        this.sector3 = sectors[3];
    }
}
