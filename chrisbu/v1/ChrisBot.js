"use strict";
exports.__esModule = true;
var readline = require("readline");
var PlanetWars_1 = require("../PlanetWars");
var rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});
var mapData = '';
rl.on('line', function (input) {
    if (input.length >= 2 && input.startsWith('go')) {
        var pw = new PlanetWars_1.PlanetWars(mapData);
        try {
            doTurn(pw);
        }
        catch (e) {
            console.log(e);
        }
        pw.finishTurn();
        mapData = '';
    }
    else {
        mapData += input + '\n';
    }
});
// When considering if we can help a friendly planet make sure we leave this many ships behind.
var HELP_THRESHOLD = 10;
// When considering if we can take a planet send this much extra as a buffer.
var TAKEOVER_BUFFER = 10;
// Bot implementation goes here.
function doTurn(pw) {
    var planets = pw.neutralPlanets();
    var myPlanets = pw.myPlanets();
    var enemyFleets = pw.enemyFleets();
    var myFleets = pw.myFleets();
    // Enemeny/neutral lanets i have fleets in flight to.
    var myTargetedSet = new Set(pw.myFleets().map(function (f) {
        return f.destPlanet;
    }));
    // Are any of my planets being targeted? If so, attempt to save them in order of value
    var myTargetedPlanets = enemyFleets.filter(function (f) {
        return pw.getPlanet(f.destPlanet).owner === 1;
    }).map(function (f) {
        return f.destPlanet;
    }).sort(function (a, b) {
        return pw.getPlanet(a).growthRate - pw.getPlanet(b).growthRate;
    });
    myTargetedPlanets.forEach(function (tp) {
        var targetedPlanet = pw.getPlanet(tp);
        var attackingFleets = enemyFleets.filter(function (f) {
            return f.destPlanet === tp;
        }).sort(function (a, b) {
            return a.turnsRemaining - b.turnsRemaining;
        });
        // TODO(chrisbu): better deal with case where multiple fleets are targeting one planet.
        // For each attacking fleet, get my closest planets and try and send help from
        attackingFleets.forEach(function (f) {
            var distance = f.turnsRemaining;
            var shipsAtImpactTime = targetedPlanet.numShips + targetedPlanet.growthRate * distance;
            var shipsNeeded = shipsAtImpactTime - f.numShips;
            // Start with the closest planet and look till we find one that can save us.
            // TODO(chrisbu): implement saving by multiple planets.
            var closestPlanets = myPlanets.sort(function (a, b) {
                return pw.distance(a, targetedPlanet) - pw.distance(b, targetedPlanet);
            });
            closestPlanets.forEach(function (p) {
                // If other ships have sent help don't worry.
                if (shipsNeeded <= 0) {
                    return;
                }
                // If planet isn't closest to contribute, skip it.
                if (pw.distance(p, targetedPlanet) > distance) {
                    return;
                }
                // If planet doesn't have enough ships, skip it.
                if (p.numShips < (shipsNeeded + HELP_THRESHOLD)) {
                    return;
                }
                // Send the help order!
                pw.issueOrder(p, targetedPlanet, shipsNeeded);
                // This will just zero out but eventually we want multiple planets to chip in. 
                shipsNeeded = shipsNeeded - shipsNeeded;
            });
        });
    });
    var myTargetedPlanetSet = new Set(myTargetedPlanets);
    var myNonTargetedPlanets = pw.myPlanets().filter(function (p) {
        return !myTargetedPlanetSet.has(p.planetId);
    });
    // For each of my planets not under attack, find the closest planet, not owned by me and take it if possible.
    myNonTargetedPlanets.forEach(function (p) {
        var targetPlanet = pw.notMyPlanets().filter(function (p) {
            // Only consider targets im not currently targeting.
            return !myTargetedSet.has(p.planetId);
        }).sort(function (a, b) {
            return pw.distance(a, p) - pw.distance(b, p);
        })[0];
        if (!targetPlanet)
            return;
        var distance = pw.distance(p, targetPlanet);
        var growth = targetPlanet.owner ? targetPlanet.growthRate * distance : 0;
        var costToTake = targetPlanet.numShips + growth;
        // Do we already have a ship heading to this target? If so skip.
        if (pw.myFleets().find(function (f) {
            return (f.destPlanet === targetPlanet.planetId);
        })) {
            return;
        }
        // If we can take it, send the order!
        if (p.numShips > (costToTake + TAKEOVER_BUFFER)) {
            pw.issueOrder(p, targetPlanet, costToTake + TAKEOVER_BUFFER);
        }
    });
}
// Helper to see if I have a fleet in flight to a given planet.
function targeting(pw, planet) {
    return pw.myFleets().some(function (f) {
        return f.destPlanet === planet.planetId;
    });
}
