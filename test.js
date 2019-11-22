const assert = require('assert');
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
