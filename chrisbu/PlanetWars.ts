export class Fleet {
  constructor(public owner: number, public numShips: number, public srcPlanet: number,
    public destPlanet: number, public totalTripLength: number, public turnsRemaining: number) {
  }
}

export class Planet {
    constructor(public planetId: number, public owner: number, public numShips: number,
        public growthRate: number, public x: number, public y: number) {
    }

    addShips(amount: number) {
        this.numShips += amount;
    }
    
    removeShips(amount: number) {
        this.numShips -= amount;
    }
}

export class PlanetWars {
    private planets: Planet[] = [];
    private fleets: Fleet[] = [];

    constructor(gameState: string) {
        this.parseGameState(gameState);
    }

    numPlanets(): number {
        return this.planets.length;
    }

    getPlanet(planetId: number): Planet {
        return this.planets[planetId];
    }

    numFleets(): number {
        return this.fleets.length;
    }

    getFleet(fleetId: number): Fleet {
        return this.fleets[fleetId];
    }

    allPlanets(): Planet[] {
        return this.planets;
    }

    myPlanets(): Planet[] {
        const r = [];
        for  (let p of this.planets) {
            if (p.owner != 1) {
                continue;
            }
            r.push(p);
        }
        return r;
    }

    neutralPlanets(): Planet[] {
        const r = [];
        for  (let p of this.planets) {
            if (p.owner != 0) {
                continue;
            }
            r.push(p);
        }
        return r;
    }

    enemyPlanets(): Planet[] {
        const r = [];
        for (let p of this.planets) {
            if (p.owner <= 1) {
                continue;
            }
            r.push(p);
        }
        return r;
    }

    notMyPlanets(): Planet[] {
        const r = [];
        for  (let p of this.planets) {
            if (p.owner === 1) {
                continue;
            }
            r.push(p);
        }
        return r;
    }

    allFleets(): Fleet[] {
        return this.fleets;
    }

    myFleets(): Fleet[] {
        const r = [];
        for (let f of this.fleets) {
            if (f.owner !== 1) {
                continue;
            }
            r.push(f);
        }
        return r;
    }

    enemyFleets(): Fleet[] {
        const r = [];
        for (let f of this.fleets) {
            if (f.owner <= 1) {
                continue;
            }
            r.push(f);
        }
        return r;
    }

    toString(): string {
        let s = '';
        for (let p of this.planets) {
            s += `P ${p.x} ${p.y} ${p.owner} ${p.numShips} ${p.growthRate}`;
        }
        for (let f of this.fleets) {
            s += `F ${f.owner} ${f.numShips} ${f.srcPlanet} ${f.destPlanet} ${f.totalTripLength} ${f.turnsRemaining}`;
        }
        return s;
    }

    distance(srcPlanet: Planet, destPlanet: Planet): number {
        const dx = srcPlanet.x - destPlanet.x;
        const dy = srcPlanet.y - destPlanet.y;
        return Number(Math.ceil(Math.sqrt(dx * dx + dy * dy)));
    }

    issueOrder(srcPlanet: Planet, destPlanet: Planet, numShips: number) {
        // Send the command to the engine.
        console.log(`${srcPlanet.planetId} ${destPlanet.planetId} ${numShips}`);

        // Update game state so future calculations take this order into account.
        srcPlanet.removeShips(numShips);
        this.fleets.push(new Fleet(1, numShips, srcPlanet.planetId, destPlanet.planetId,
           this.distance(srcPlanet, destPlanet), this.distance(srcPlanet, destPlanet)));
    }

    isAlive(playerId: number): boolean {
        for (let p of this.planets) {
            if (p.owner === playerId) {
                return true;
            }
        }
        for (let f of this.fleets) {
            if (f.owner === playerId) {
                return true;
            }
        }
        return false;
    }

    parseGameState(s: string) {
        const lines = s.split('\n');
        let planetId = 0;
        
        for (let line of lines) {
            // Remove comments
            line = line.split('#')[0];
            const tokens = line.split(' ');
            if (tokens.length === 1) {
                continue;
            }
            if (tokens[0] === 'P') {
                if (tokens.length !== 6) {
                    return 0;
                }
                const planet = new Planet(planetId, Number(tokens[3]), Number(tokens[4]), Number(tokens[5]), 
                Number(tokens[1]), Number(tokens[2]));
                planetId++;
                this.planets.push(planet);
            }
            else if (tokens[0] === 'F') {
                if (tokens.length !== 7) {
                    return 0;
                }
                const fleet = new Fleet(Number(tokens[1]), Number(tokens[2]), Number(tokens[3]),
                    Number(tokens[4]), Number(tokens[5]), Number(tokens[6]));
                this.fleets.push(fleet);
            }
            else {
                return 0;
            }
        }
        return 1;
    }

    finishTurn() {
        console.log('go');
    }
}
