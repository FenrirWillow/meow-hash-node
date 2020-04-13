const fs = require('fs');
const path = require('path');
const meowHash = require('../');

describe('meow-hash-node Module', () => {
  describe('MeowHash::CreateHash()', () => {
    it('Successfully creates a hash from a given buffer', () => {
      const stringToHash = 'Lorem ipsum dolor sit amet';
      const hashValue = meowHash.CreateHash(Buffer.from(stringToHash));

      expect(typeof hashValue).toBe('string');
      expect(hashValue.length).toBeGreaterThan(0);
    });

    it('Throws a JS Exception when there are 0 arguments', () => {
      const wrapper = () => { meowHash.CreateHash() }
      expect(wrapper).toThrow(/CreateHash()/);
    });

    it('Throws a JS Exception when there are more than 1 arguments', () => {
      const bufferArg = Buffer.from('Lorem ipsum dolor sit amet');

      const wrapper = () => { meowHash.CreateHash(bufferArg, bufferArg) }
      expect(wrapper).toThrow(/CreateHash()/);
    });

    it('Throws a JS Exception when the provided argument is not of type Buffer', () => {
      const argument = 123;

      const wrapper = () => { meowHash.CreateHash(argument) }
      expect(wrapper).toThrow(/CreateHash()/);
    });
  });

  describe('MeowHash::CompareBuffers()', () => {
    it('Returns true when the two buffers given hash to the same value (are equal)', () => {
      const stringToHash = 'Lorem ipsum dolor sit amet';
      const bufferArg1 = Buffer.from(stringToHash);
      const bufferArg2 = Buffer.from(stringToHash);

      const result = meowHash.CompareBuffers(bufferArg1, bufferArg2);
      expect(result).toBe(true);
    });

    it('Returns false when the two buffers given hash to different values (are not equal)', () => {
      const stringToHash = 'Lorem ipsum dolor sit amet';
      const bufferArg1 = Buffer.from(stringToHash);
      const bufferArg2 = Buffer.from('Some other string to hash...');

      const result = meowHash.CompareBuffers(bufferArg1, bufferArg2);
      expect(result).toBe(false);
    });

    it('Throws an exception when there are 0 arguments', () => {
      const wrapper = () => { meowHash.CompareBuffers() }
      expect(wrapper).toThrow(/CompareBuffers()/);
    });

    it('Throws an exception when there is only 1 argument', () => {
      const stringToHash = 'Lorem ipsum dolor sit amet';
      const bufferArg1 = Buffer.from(stringToHash);

      const wrapper = () => { meowHash.CompareBuffers(bufferArg1) }

      expect(wrapper).toThrow(/CompareBuffers()/);
    });

    it('Throws an exception when there are more than 2 arguments', () => {
      const stringToHash = 'Lorem ipsum dolor sit amet';
      const bufferArg1 = Buffer.from(stringToHash);

      const wrapper = () => { meowHash.CompareBuffers(bufferArg1, bufferArg1, bufferArg1) }

      expect(wrapper).toThrow(/CompareBuffers()/);
    });

    it('Throws an exception when either argument is not of type Buffer', () => {
      const stringToHash = 'Lorem ipsum dolor sit amet';
      const bufferArg1 = Buffer.from(stringToHash);
      const bufferArg2 = 123;

      const permutationA = () => { meowHash.CompareBuffers(bufferArg1, bufferArg2) }
      const permutationB = () => { meowHash.CompareBuffers(bufferArg2, bufferArg1) }

      expect(permutationA).toThrow(/CompareBuffers()/);
      expect(permutationB).toThrow(/CompareBuffers()/);
    });
  });

  describe('MeowHash::MeowHashNativeStream', () => {
    it('Constructs without any errors', () => {
      const wrapper = () => new meowHash.MeowHashNativeStream();
      expect(wrapper).not.toThrow();
    });

    it('Can absorb a single buffer and end, returning the hash', () => {
      const stream = new meowHash.MeowHashNativeStream();
      const stringToHash = 'Lorem ipsum dolor sit amet';

      stream.absorb(Buffer.from(stringToHash));
      const hash = stream.end();

      const straightHash = meowHash.CreateHash(Buffer.from(stringToHash));

      expect(typeof hash).toBe('string');
      expect(hash.length).toBeGreaterThan(0);
      expect(hash).toBe(straightHash);
    });
  });
});
