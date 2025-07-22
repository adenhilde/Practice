use std::fs::File;
use std::io::{self, Read};
use sha2::{Digest, Sha256};

fn main() -> io::Result<()> {
    let file_path = "hash.txt";
    let mut file = File::open(file_path)?;
    let mut hasher = Sha256::new();
    let mut buf = Vec::new();

    file.read_to_end(&mut buf)?;
    hasher.update(&buf);

    let hash = hasher.finalize();
    println!("SHA-256 hash of {}: {:x}", file_path, hash);

    Ok(())
}
