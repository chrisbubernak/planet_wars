const readline = require('readline');
const {PlanetWars, Planet, Fleet} = require('./PlanetWars');

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout
});

let mapData = '';
rl.on('line', (input) => {
  if (input.length >=2 && input.startsWith('go')) {
    const pw = new PlanetWars(mapData);
    doTurn(pw);
    pw.finishTurn();
    mapData = '';
  }
  else {
    mapData += input + '\n';
  }
});

// Bot implementation goes here.
function doTurn(pw) {
  const planets = pw.neutralPlanets();
  const myPlanets = pw.myPlanets();

  // For each planet I own, find the closest neutral
  // planet I can take over and send enough ships to do it.
  for (let p of myPlanets) {
    const closest = pw.neutralPlanets().sort((a, b) => {
      return (pw.distance(p, a) - pw.distance(p, b));
    });
    // If no neutral planets remain just chill.
    if (closest.length === 0) {
      continue; 
    }
    // If not targeting and able to take it, do it.
    if (p.numShips > closest[0].numShips + 1 && !targeting(pw, closest[0])) {
      pw.issueOrder(p, closest[0], closest[0].numShips + 1);
    }
  }
}

// Helper to see if I have a fleet in flight to a given planet.
function targeting(pw, planet) {
  return pw.myFleets().some((f) => {
    return f.destPlanet === planet.planetId;
  });
}