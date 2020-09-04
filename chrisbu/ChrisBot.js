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
    finishTurn();
    mapData = '';
  }
  else {
    mapData += input + '\n';
  }
});

// Bot implementation goes here.
function doTurn(pw) {
  
  // Very dumb bot.
  const planets = pw.neutralPlanets();
  const myPlanets = pw.myPlanets();
  let p = 0;
  while (myPlanets[0].numShips >= 5 && p < planets.length) {
    pw.issueOrder(myPlanets[0], planets[p], 5);
    p++;
    myPlanets[0].removeShips(5);
  }
}

function finishTurn() {
  console.log('go');
}