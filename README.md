# Meow Hash Node

![Master CI Pipeline](https://github.com/FenrirWillow/meow-hash-node/workflows/Master%20CI%20Pipeline/badge.svg?branch=master)

---

## Overview

NodeJS bindings for Casey Muratori's Meow Hash - https://github.com/cmuratori/meow_hash/

Meow is a 128-bit Level 3 hash taking 128 bytes of seed. It operates at very high speeds on x64 processors, and potentially other processors that provide accelerated AES instructions.

---

## Installation

With NPM: `npm install https://github.com/FenrirWillow/meow-hash-node`

With yarn: `yarn add https://github.com/FenrirWillow/meow-hash-node`

When the module is installed, it will try to rebuild itself. Make sure you have a compiler toolchain setup for your target.

> ⚠ I will eventually add this module to the NPM registry, however installing and pinning to a particular git commit works just as well.

---

## Usage

Using the module is really simple:

```js
const meowhash = require(`meow-hash-node`);

const testBufferA = Buffer.from('Hello World!');
const testBufferB = Buffer.from('Hello World!');

// Comparing buffers:
meowhash.CompareBuffers(testBufferA, testBufferB);

// Hash a file using a read stream:
const fs = require('fs');
const readStream = fs.createReadStream('path/to/my/file');
const meowHashStream = new meowhash.MeowHashNativeStream();

readStream.on('data', (chunk) => meowHashStream.absorb(chunk))
readStream.on('end', () => console.info(meowHashStream.end()))

```

The module comes with TypeScript definitions that should help you in your development.

---

## Contributing

> ⚠ This section is incomplete, sorry about that 😢

If you find an issue with this module, feel free to open an issue or PR to fix it.

---
