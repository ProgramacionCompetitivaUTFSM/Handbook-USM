#let lib = plugin("hash.wasm")

/// Hashes the given data with the given digest.
///
/// Arguments:
/// - digest: The digest to use for hashing. Must be one of
///           "blake2", "blake2s", "md5", "sha1", "sha224",
///           "sha256", "sha384", "sha512", or "sha3".
/// - data: The data to hash. Must be of type array, bytes, or string.
///
/// Returns: The hashed data as bytes.
#let hash(digest, data) = lib.hash(bytes(digest), bytes(data))

/// Converts a byte array to a hexadecimal string.
///
/// Arguments:
/// - bytes: The bytes to convert.
///
/// Returns: The hexadecimal string.
#let hex(bytes) = for byte in array(bytes) {
  if byte < 16 { "0" }
  str(int(byte), base: 16)
}

#let blake2 = hash.with("blake2")
#let blake2s = hash.with("blake2s")
#let md5 = hash.with("md5")
#let sha1 = hash.with("sha1")
#let sha224 = hash.with("sha224")
#let sha256 = hash.with("sha256")
#let sha384 = hash.with("sha384")
#let sha512 = hash.with("sha512")
#let sha3 = hash.with("sha3")