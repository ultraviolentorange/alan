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
* Specify a custom dictionary file. Default is dict.txt which comes together with the files.
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
<b>Example</b> 
```shell
alan albngIA= --outfile plaintext.txt --logfile log.txt --type base64 --top 1 
```

### Benchmarks
Coming soon.

### Inspiration
<b>alan</b> was inspired by and named after <b>Alan Turing</b>, who was an English computer scientist, mathematician, logician, cryptanalyst, philosopher, and theoretical biologist. 
Turing was highly influential in the development of theoretical computer science, providing a formalisation of the concepts of algorithm and computation with the Turing machine, which can be considered a model of a general purpose computer. Turing is widely considered to be the father of theoretical computer science and artificial intelligence. <br>
Turing played a pivotal role in cracking intercepted coded messages that enabled the Allies to defeat the Nazis in many crucial engagements, including the Battle of the Atlantic, and in so doing helped win the war. 

### Credits
<b>Author<b>: @ultraviolentorange <br>
<b>GitHub repository</b>: https://github.com/ultraviolentorange/alan <br>
<b>Contact</b>: ultraviorange@gmail.com 

