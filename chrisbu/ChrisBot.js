const readline = require('readline');

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

function doTurn(pw) {
  // Implement Me!
}

class PlanetWars {
  constructor(pw) {
    this.pw = pw;
  }

  finishTurn() {
    console.log('go');
  }
}