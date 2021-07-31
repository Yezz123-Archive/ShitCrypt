# ShitCrypt

![header](Header.svg)

WinGPG is a tray-based classical Windows application, Windows NT Explorer shell extension, and a classic GPGv2 distribution. Secure your data with our simple encryption tool.

## Features

### Encrypting

A public and private key each have a specific role when encrypting and decrypting documents. A public key may be thought of as an open safe. When a correspondent encrypts a document using a public key, that document is put in the safe, the safe shut, and the combination lock spun several times. The corresponding private key is the combination that can reopen the safe and retrieve the document. In other words, only the person who holds the private key can recover a document encrypted using the associated public key.

The procedure for encrypting and decrypting documents is straightforward with this mental model. If you want to encrypt a message to Alice, you encrypt it using Alice's public key, and she decrypts it with her private key. If Alice wants to send you a message, she encrypts it using your public key, and you decrypt it with your key.

To encrypt a document the option `--encrypt` is used. You must have the public keys of the intended recipients. The software expects the name of the document to encrypt as input or, if omitted, on standard input. The encrypted result is placed on standard output or as specified using the option `--output`. The document is compressed for additional security in addition to encrypting it.

```shell
alice% gpg --output doc.gpg --encrypt --recipient blake@cyb.org doc
```

The `--recipient` option is used once for each recipient and takes an extra argument specifying the public key to which the document should be encrypted. The encrypted document can only be decrypted by someone with a private key that complements one of the recipients' public keys. In particular, you cannot decrypt a document encrypted by you unless you included your own public key in the recipient list.

## decrypting

To decrypt a message the option `--decrypt` is used. You need the private key to which the message was encrypted. Similar to the encryption process, the document to decrypt is input, and the decrypted result is output.

```bash
blake% gpg --output doc --decrypt doc.gpg
```

Documents may also be encrypted without using public-key cryptography. Instead, only a symmetric cipher is used to encrypt the document. The key used to drive the symmetric cipher is derived from a passphrase supplied when the document is encrypted, and for good security, it should not be the same passphrase that you use to protect your private key. Symmetric encryption is useful for securing documents when the passphrase does not need to be communicated to others. A document can be encrypted with a symmetric cipher by using the `--symmetric` option.

```bash
alice% gpg --output doc.gpg --symmetric doc
Enter passphrase: 
```

## How to use ShitCrypt

- install Python 3.x.x
- install a C libraries and C Compiler (Gcc, Clang, MSVC)
- Check the includes folder and header files for key files
- [encrypt.c](key/encrypt.c)

```c
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <include/gpg-error.h>
#include <include/gcrypt.h>
#include <include/gcrypt-module.h>
```

- Now you can run the Python file and see the result.

__Note:__ You could see errors like this if you use windows :

```shell
Exception has occurred: FileNotFoundError
[WinError 2] The system cannot find the file specified
  File "path\ShitCrypt\main.py", line 30, in <module>
    call(["gcc", "-o", "keygen", "key/keygen.c", "-lgcrypt"])
```

- This errors are because you don't have the C libraries installed and the keygen or encrypt file run under errors.

```py
call(["gcc", "-o", "keygen", "key/keygen.c", "-lgcrypt"])
call(["gcc", "-o", "encrypt", "key/encrypt.c", "-lgcrypt"])
call("key/keygen")
```

- Understand more By reading some threads or [this](https://stackoverflow.com/questions/371878/how-to-compile-and-link-a-c-program-in-windows-using-mingw) or also [this](https://stackoverflow.com/questions/65789957/include-errors-detected-linux)

## License

This program is free software under MIT license. Please see the [LICENSE](LICENSE.rst) file in our repository for the full text.
