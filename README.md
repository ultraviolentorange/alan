alan
=====================

### What alan is
**alan** is an open-source tool that helps to decrypt texts, encoded using a wide variety of encryption methods. <br>
Currently supported ciphers: <br>
* Caesar
* Affine
* Atbash
* Base64

### What is special about alan
It turns out that in most cases when you need to decrypt something you can't know the encryption method for sure. Some are easily distinguishable from the others, however in general case you're supposed to guess and experiment until you get any result. <br>
Even when you know the cipher, you should probably still spend your time on finding a suitable online decryptor tool and copy-pasting back and forth. <br>
<b>alan</b>, as you could guess, is there to help. Now decoding a ciphertext is as easy as running 
```shell
alan <ciphertext>
```

