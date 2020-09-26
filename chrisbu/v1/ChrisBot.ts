import * as readline from 'readline';
import {PlanetWars, Planet, Fleet} from '../PlanetWars';

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

let mapData = '';
rl.on('line', (input) => {
  if (input.length >=2 && input.startsWith('go')) {
    const pw = new PlanetWars(mapData);
    try {
    doTurn(pw);
    } catch(e) {
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
const HELP_THRESHOLD = 10;

// When considering if we can take a planet send this much extra as a buffer.
const TAKEOVER_BUFFER = 10;

// Bot implementation goes here.
function doTurn(pw: PlanetWars) {
  const planets = pw.neutralPlanets();
  const myPlanets = pw.myPlanets();
  const enemyFleets = pw.enemyFleets();
  const myFleets = pw.myFleets();


  // Enemeny/neutral lanets i have fleets in flight to.
  const myTargetedSet = new Set(pw.myFleets().map((f: Fleet) => {
    return f.destPlanet;
  }));

  // Are any of my planets being targeted? If so, attempt to save them in order of value
  const myTargetedPlanets: number[] = enemyFleets.filter((f: Fleet) => {
      return pw.getPlanet(f.destPlanet).owner === 1
    }).map((f) => {
      return f.destPlanet;
    }).sort((a: number, b: number) => {
      return pw.getPlanet(a).growthRate - pw.getPlanet(b).growthRate;
    });

  myTargetedPlanets.forEach((tp: number) => {
    const targetedPlanet = pw.getPlanet(tp);

    const attackingFleets = enemyFleets.filter((f: Fleet)=> {
      return f.destPlanet === tp;
    }).sort((a: Fleet, b: Fleet) => {
      return a.turnsRemaining - b.turnsRemaining;
    });

    // TODO(chrisbu): better deal with case where multiple fleets are targeting one planet.
    // For each attacking fleet, get my closest planets and try and send help from
    attackingFleets.forEach((f: Fleet) => {
      const distance = f.turnsRemaining;
      const shipsAtImpactTime = targetedPlanet.numShips + targetedPlanet.growthRate * distance;
      let shipsNeeded = shipsAtImpactTime - f.numShips;
      // Start with the closest planet and look till we find one that can save us.
      // TODO(chrisbu): implement saving by multiple planets.
      const closestPlanets = myPlanets.sort((a: Planet, b: Planet) => {
        return pw.distance(a, targetedPlanet) - pw.distance(b, targetedPlanet);
      });
      closestPlanets.forEach((p: Planet) => {
        // If other ships have sent help don't worry.
        if (shipsNeeded <= 0) { return; }

        // If planet isn't closest to contribute, skip it.
        if (pw.distance(p, targetedPlanet) > distance) { return; }

        // If planet doesn't have enough ships, skip it.
        if (p.numShips < (shipsNeeded + HELP_THRESHOLD)) { return; }

        // Send the help order!
        pw.issueOrder(p, targetedPlanet, shipsNeeded);

        // This will just zero out but eventually we want multiple planets to chip in. 
        shipsNeeded = shipsNeeded - shipsNeeded;
      });
    });
  });
  
  const myTargetedPlanetSet = new Set(myTargetedPlanets);
  const myNonTargetedPlanets = pw.myPlanets().filter((p: Planet) => {
    return !myTargetedPlanetSet.has(p.planetId);
  });

  // For each of my planets not under attack, find the closest planet, not owned by me and take it if possible.
  myNonTargetedPlanets.forEach((p: Planet) => {
    const targetPlanet = pw.notMyPlanets().filter((p: Planet) => {
      // Only consider targets im not currently targeting.
      return !myTargetedSet.has(p.planetId);
    }).sort((a: Planet, b: Planet) => {
      return pw.distance(a, p) - pw.distance(b, p);
    })[0];

    if (!targetPlanet) return;
    const distance = pw.distance(p, targetPlanet);
    const growth = targetPlanet.owner ? targetPlanet.growthRate * distance : 0;
    const costToTake = targetPlanet.numShips + growth;
    
    // Do we already have a ship heading to this target? If so skip.
    if (pw.myFleets().find((f: Fleet) => {
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
function targeting(pw: PlanetWars, planet: Planet) {
  return pw.myFleets().some((f: Fleet) => {
    return f.destPlanet === planet.planetId;
  });
}

