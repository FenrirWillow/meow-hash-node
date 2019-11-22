declare module meowHash {

  export function CreateHash(b: Buffer): string

  export function CompareBuffers(a: Buffer, b: Buffer): boolean
}
