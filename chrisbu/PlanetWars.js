class Fleet {
  constructor(owner, numShips, srcPlanet, destPlanet, totalTripLength, turnsRemaining) {
      this.owner = owner;
      this.numShips = numShips;
      this.srcPlanet = srcPlanet;
      this.destPlanet = destPlanet;
      this.totalTripLength = totalTripLength;
      this.turnsRemaining = turnsRemaining;
  }
}

class Planet {
    constructor(planetId, owner, numShips, growthRate, x, y) {
        this.planetId = planetId;
        this.owner = owner;
        this.numShips = numShips;
        this.growthRate = growthRate;
        this.x = x;
        this.y = y;
    }

    addShips(amount) {
        this.numShips += amount;
    }
    
    removeShips(amount) {
        this.numShips -= amount;
    }
}

class PlanetWars {
    constructor(gameState) {
        this.planets = [];
        this.fleets = [];
        this.parseGameState(gameState);
    }

    numPlanets() {
        return this.planets.length;
    }

    getPlanet(planetId) {
        return this.planets[planetId];
    }

    numFleets() {
        return this.fleets.length;
    }

    getFleet(fleetId) {
        return this.fleets[fleetId];
    }

    planets() {
        return this.planets;
    }

    myPlanets() {
        const r = [];
        for  (let p of this.planets) {
            if (p.owner != 1) {
                continue;
            }
            r.push(p);
        }
        return r;
    }

    neutralPlanets() {
        const r = [];
        for  (let p of this.planets) {
            if (p.owner != 0) {
                continue;
            }
            r.push(p);
        }
        return r;
    }

    enemyPlanets() {
        const r = [];
        for (let p of this.planets) {
            if (p.owner <= 1) {
                continue;
            }
            r.push(p);
        }
        return r;
    }

    notMyPlanets() {
        const r = [];
        for  (let p of this.planets) {
            if (p.owner === 1) {
                continue;
            }
            r.push(p);
        }
        return r;
    }

    fleets() {
        return this.fleets;
    }

    myFleets() {
        const r = [];
        for (let f of this.fleets) {
            if (f.owner !== 1) {
                continue;
            }
            r.push(f);
        }
        return r;
    }

    enemyFleets() {
        const r = [];
        for (let f of this.fleets) {
            if (f.owner <= 1) {
                continue;
            }
            r.push(f);
        }
        return r;
    }

    toString() {
        let s = '';
        for (let p of this.planets) {
            s += `P ${p.x} ${p.y} ${p.owner} ${p.numShips} ${p.growthRate}`;
        }
        for (let f of this.fleets) {
            s += `F ${f.owner} ${f.numShips} ${f.srcPlanet} ${f.destPlanet} ${f.totalTripLength} ${f.turnsRemaining}`;
        }
        return s;
    }

    distance(srcPlanet, destPlanet) {
        const dx = srcPlanet.x - destPlanet.x;
        const dy = srcPlanet.y - destPlanet.y;
        return Number(Math.ceil(Math.sqrt(dx * dx + dy * dy)));
    }

    issueOrder(srcPlanet, destPlanet, numShips) {
        console.log(`${srcPlanet.planetId} ${destPlanet.planetId} ${numShips}`);
    }

    isAlive(playerId) {
        for (let p of this.planets) {
            if (p.Owner === playerId) {
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

    parseGameState(s) {
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
                Number(tokens[1], Number(tokens[2])));
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

module.exports = {PlanetWars, Planet, Fleet};