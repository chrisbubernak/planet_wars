"use strict";
exports.__esModule = true;
exports.PlanetWars = exports.Planet = exports.Fleet = void 0;
var Fleet = /** @class */ (function () {
    function Fleet(owner, numShips, srcPlanet, destPlanet, totalTripLength, turnsRemaining) {
        this.owner = owner;
        this.numShips = numShips;
        this.srcPlanet = srcPlanet;
        this.destPlanet = destPlanet;
        this.totalTripLength = totalTripLength;
        this.turnsRemaining = turnsRemaining;
    }
    return Fleet;
}());
exports.Fleet = Fleet;
var Planet = /** @class */ (function () {
    function Planet(planetId, owner, numShips, growthRate, x, y) {
        this.planetId = planetId;
        this.owner = owner;
        this.numShips = numShips;
        this.growthRate = growthRate;
        this.x = x;
        this.y = y;
    }
    Planet.prototype.addShips = function (amount) {
        this.numShips += amount;
    };
    Planet.prototype.removeShips = function (amount) {
        this.numShips -= amount;
    };
    return Planet;
}());
exports.Planet = Planet;
var PlanetWars = /** @class */ (function () {
    function PlanetWars(gameState) {
        this.planets = [];
        this.fleets = [];
        this.parseGameState(gameState);
    }
    PlanetWars.prototype.numPlanets = function () {
        return this.planets.length;
    };
    PlanetWars.prototype.getPlanet = function (planetId) {
        return this.planets[planetId];
    };
    PlanetWars.prototype.numFleets = function () {
        return this.fleets.length;
    };
    PlanetWars.prototype.getFleet = function (fleetId) {
        return this.fleets[fleetId];
    };
    PlanetWars.prototype.allPlanets = function () {
        return this.planets;
    };
    PlanetWars.prototype.myPlanets = function () {
        var r = [];
        for (var _i = 0, _a = this.planets; _i < _a.length; _i++) {
            var p = _a[_i];
            if (p.owner != 1) {
                continue;
            }
            r.push(p);
        }
        return r;
    };
    PlanetWars.prototype.neutralPlanets = function () {
        var r = [];
        for (var _i = 0, _a = this.planets; _i < _a.length; _i++) {
            var p = _a[_i];
            if (p.owner != 0) {
                continue;
            }
            r.push(p);
        }
        return r;
    };
    PlanetWars.prototype.enemyPlanets = function () {
        var r = [];
        for (var _i = 0, _a = this.planets; _i < _a.length; _i++) {
            var p = _a[_i];
            if (p.owner <= 1) {
                continue;
            }
            r.push(p);
        }
        return r;
    };
    PlanetWars.prototype.notMyPlanets = function () {
        var r = [];
        for (var _i = 0, _a = this.planets; _i < _a.length; _i++) {
            var p = _a[_i];
            if (p.owner === 1) {
                continue;
            }
            r.push(p);
        }
        return r;
    };
    PlanetWars.prototype.allFleets = function () {
        return this.fleets;
    };
    PlanetWars.prototype.myFleets = function () {
        var r = [];
        for (var _i = 0, _a = this.fleets; _i < _a.length; _i++) {
            var f = _a[_i];
            if (f.owner !== 1) {
                continue;
            }
            r.push(f);
        }
        return r;
    };
    PlanetWars.prototype.enemyFleets = function () {
        var r = [];
        for (var _i = 0, _a = this.fleets; _i < _a.length; _i++) {
            var f = _a[_i];
            if (f.owner <= 1) {
                continue;
            }
            r.push(f);
        }
        return r;
    };
    PlanetWars.prototype.toString = function () {
        var s = '';
        for (var _i = 0, _a = this.planets; _i < _a.length; _i++) {
            var p = _a[_i];
            s += "P " + p.x + " " + p.y + " " + p.owner + " " + p.numShips + " " + p.growthRate;
        }
        for (var _b = 0, _c = this.fleets; _b < _c.length; _b++) {
            var f = _c[_b];
            s += "F " + f.owner + " " + f.numShips + " " + f.srcPlanet + " " + f.destPlanet + " " + f.totalTripLength + " " + f.turnsRemaining;
        }
        return s;
    };
    PlanetWars.prototype.distance = function (srcPlanet, destPlanet) {
        var dx = srcPlanet.x - destPlanet.x;
        var dy = srcPlanet.y - destPlanet.y;
        return Number(Math.ceil(Math.sqrt(dx * dx + dy * dy)));
    };
    PlanetWars.prototype.issueOrder = function (srcPlanet, destPlanet, numShips) {
        // Send the command to the engine.
        console.log(srcPlanet.planetId + " " + destPlanet.planetId + " " + numShips);
        // Update game state so future calculations take this order into account.
        srcPlanet.removeShips(numShips);
        this.fleets.push(new Fleet(1, numShips, srcPlanet.planetId, destPlanet.planetId, this.distance(srcPlanet, destPlanet), this.distance(srcPlanet, destPlanet)));
    };
    PlanetWars.prototype.isAlive = function (playerId) {
        for (var _i = 0, _a = this.planets; _i < _a.length; _i++) {
            var p = _a[_i];
            if (p.owner === playerId) {
                return true;
            }
        }
        for (var _b = 0, _c = this.fleets; _b < _c.length; _b++) {
            var f = _c[_b];
            if (f.owner === playerId) {
                return true;
            }
        }
        return false;
    };
    PlanetWars.prototype.parseGameState = function (s) {
        var lines = s.split('\n');
        var planetId = 0;
        for (var _i = 0, lines_1 = lines; _i < lines_1.length; _i++) {
            var line = lines_1[_i];
            // Remove comments
            line = line.split('#')[0];
            var tokens = line.split(' ');
            if (tokens.length === 1) {
                continue;
            }
            if (tokens[0] === 'P') {
                if (tokens.length !== 6) {
                    return 0;
                }
                var planet = new Planet(planetId, Number(tokens[3]), Number(tokens[4]), Number(tokens[5]), Number(tokens[1]), Number(tokens[2]));
                planetId++;
                this.planets.push(planet);
            }
            else if (tokens[0] === 'F') {
                if (tokens.length !== 7) {
                    return 0;
                }
                var fleet = new Fleet(Number(tokens[1]), Number(tokens[2]), Number(tokens[3]), Number(tokens[4]), Number(tokens[5]), Number(tokens[6]));
                this.fleets.push(fleet);
            }
            else {
                return 0;
            }
        }
        return 1;
    };
    PlanetWars.prototype.finishTurn = function () {
        console.log('go');
    };
    return PlanetWars;
}());
exports.PlanetWars = PlanetWars;
