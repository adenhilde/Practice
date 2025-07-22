# Ciphertext and key
ciphertext = "0a120015085b1c5f52271b42597f50551d593b09100a301f5a5d"
key = "i can do xor"

# Convert the ciphertext (hex) into bytes
cipher_bytes = bytes.fromhex(ciphertext)

# Convert the key into bytes
key_bytes = key.encode('utf-8')

# Decrypt the ciphertext using XOR with the key
decrypted_bytes = bytearray()

for i in range(len(cipher_bytes)):
    decrypted_bytes.append(cipher_bytes[i] ^ key_bytes[i % len(key_bytes)])

# Convert decrypted bytes back into a string
decrypted_text = decrypted_bytes.decode('utf-8', errors='ignore')
print(decrypted_text)
