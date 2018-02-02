alan
=====================

### What alan is
**alan** is an open-source tool that helps to decrypt texts, encoded using a wide variety of encryption methods. <br>
Currently supported ciphers: <br>
* Basic substitution ciphers (Caesar, Affine, Atbash)
* Base to base conversions (Base64)

### What is special about alan
It turns out that in most cases when you need to decrypt something you can't know the encryption method for sure. Some are easily distinguishable from the others, however in general case you're supposed to guess and experiment until you get any result. <br>
Even when you know the cipher, you should probably still spend your time on finding a suitable online decryptor tool and copy-pasting back and forth. <br>
<b>alan</b>, as you could guess, is there to help. Now decoding a ciphertext is as easy as running 
```shell
alan <ciphertext>
```
It will do the rest for you, though you can also specify multiple arguments to configure the process. <br>

### How alan works
In short, <b>alan</b> tries all supported encryption methods to decrypt the ciphertext and that yields a set of possible solutions. Throughout the whole process <b>alan</b> makes use of a function, evaluating how "good" a solution is. The function is based on a dictionary and is pretty simple to understand. <br>
In the end, you will be provided with solutions, ordered from best to worst. This means that if <b>alan</b> succeeded to decrypt the ciphertext, you'll likely find the corresponding plaintext at the top of response. 

### How to use alan

The simplest usage example is already provided before. In order to tune <b>alan</b> for your needs, you can call it with arguments.
<br> <br>
<b>Options</b> <br>
* Specify a custom dictionary file for <b>alan</b>. Default is dict.txt which comes together with the files.
```shell
--D (--dictionary) <file>
```
* Specify a file for candidates output. Default is standard output.  
```shell
--O (--outfile) <file>
```
* Specify a file for log writing. Default is standard output.
```shell
--L (--logfile) <file>
```
* If you know the encryption method, you can specify it. Method should be one of {caesar, affine, atbash, base64}. Default is unknown which yields trying all possible options.
```shell
--T (--type) <method>
```
* Specify how many of the best candidates you want <b>alan</b> to display. Default is 100.
```shell
--N (--top) <top>
```
* If you know the key used to encrypt, you can specify it. Default is uknown which yields trying all possible options.
```shell
--K (--key) <key>
```
