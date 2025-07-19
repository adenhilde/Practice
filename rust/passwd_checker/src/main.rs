use std::io;

fn main() -> io::Result<()> {
    let mut password = String::new();
    println!("Enter a password:");
    io::stdin().read_line(&mut password)?;
    let password = password.trim();
    let is_password_strong = check_password_strength(password);
    println!("Password {} is strong: {}", password, is_password_strong);
    Ok(())
}

fn check_password_strength(password: &str) -> bool {
    password.len() >= 8 &&
    password.chars().any(|c| c.is_digit(10)) &&
    password.chars().any(|c| c.is_uppercase()) &&
    password.chars().any(|c| !c.is_alphanumeric())
}
