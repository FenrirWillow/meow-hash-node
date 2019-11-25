const assert = require('assert');
const fs = require('fs');
const path = require('path');
const meowHash = require('./');

const testBufferA = Buffer.from('Lorem Ipsum');
const testBufferB = Buffer.from('Lorem Ipsum');

const hashA = meowHash.CreateHash(testBufferA);
const hashB = meowHash.CreateHash(testBufferB);

console.debug(`HashA: ${hashA}`);
console.debug(`HashB: ${hashB}`);
assert((hashA === hashB), 'Hashes are expected to be equal for equal inputs.');

const areEqual = meowHash.CompareBuffers(testBufferA, testBufferB);
assert(areEqual, 'Compare buffers should return true for same value buffers.');

console.info(meowHash);

const rs = fs.createReadStream(path.join(__dirname, 'yarn.lock'), { highWaterMark: 128 });
const meowHashStream = new meowHash.MeowHashNativeStream();

rs.on('data', (chunk) => meowHashStream.absorb(chunk))
rs.on('end', () => console.info(meowHashStream.end()))
