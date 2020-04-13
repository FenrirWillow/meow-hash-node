declare class MeowHashNativeStream {
  /**
   * Appends the given buffer to the hash stream, extending the hash
   * using the value of the bytes in the buffer.
   * @param b {Buffer} The buffer to extend the hash with.
   * @returns void
   */
  public absorb(b: Buffer): void;

  /**
   * Closes the underlying hash stream, returning the hash as a string.
   * @returns string
   */
  public end(): string;
}

export function CreateHash(b: Buffer): string

export function CompareBuffers(a: Buffer, b: Buffer): boolean
