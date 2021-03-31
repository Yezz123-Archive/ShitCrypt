```
DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
                    Version 2, December 2004 

 Copyright (C) 2004 Yasser Tahiri <yasserth19@gmail.com> 

 Everyone is permitted to copy and distribute verbatim or modified 
 copies of this license document, and changing it is allowed as long 
 as the name is changed. 

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 

  0. You just DO WHAT THE FUCK YOU WANT TO.
```

<h4> If you get an error like that :</h4>

I work on a crypt and decrypt tool and i got an error about library :
```C
#include <include/gpg-error.h>
#include <include/gcrypt.h>
#include <include/gcrypt-module.h>
```
```C
Generating the key...
keygen.c:4:10: fatal error: include/gpg-error.h: No such file or directory
    4 | #include <include/gpg-error.h>
      |          ^~~~~~~~~~~~~~~~~~~~~
compilation terminated.
encrypt.c:4:10: fatal error: include/gpg-error.h: No such file or directory
    4 | #include <include/gpg-error.h>
      |          ^~~~~~~~~~~~~~~~~~~~~
compilation terminated.
```
Also he show me a Quick fix like installing VCPKG and i do it and nothing work.

- Use Library that are in [ShitCrypt/include](https://github.com/yezz123/ShitCrypt/tree/main/include)

- Or this QST https://stackoverflow.com/questions/65789957/include-errors-detected-linux
