export class CardListener {
    sector0;
    sector1;
    sector2;
    sector3;

    getSectors() {
        if (!this.sector0 || !this.sector1 || !this.sector2 || !this.sector3) {
            return null;
        }
        return [this.sector0, this.sector1, this.sector2, this.sector3];
    }

    updateSectors(sectors) {
        this.sector0 = sectors[0];
        this.sector1 = sectors[1];
        this.sector2 = sectors[2];
        this.sector3 = sectors[3];
    }
}
