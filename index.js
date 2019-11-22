const meowHash = require('./build/Release/meow_hash_node.node');

const testBufferA = Buffer.from('Lorem Ipsum');
const testBufferB = Buffer.from('Lorem Ipsum');

const hash32A = meowHash.GetMeowHash32(testBufferA);
const hash32B = meowHash.GetMeowHash32(testBufferB);
// console.info(`Compare Buffers:${meowHash.CompareBuffers(testBufferA, testBufferB)}`);
// console.info(`JS Land equal: ${(hash32A === hash32B)}`);

module.exports = meowHash;
