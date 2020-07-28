# Eng-Viet Dictionary
**Description:** An Eng-Viet dictionary was written in C. It take an text file as the word-meaning source. It have many built-in functions. It can run on any environment which already have GCC. You can customize your own dictionary by add,delete or modify word-meaning. 

**Function:** 
* auto suggest(using both prefix tree and soundex) .
* backup, restore dictionary.
* add, delete, modify word.
* etc ... (will be added in future)

**How to compile:**

`First, you need to install GTK 3 on your computer. If you are using Linux, it may have been installed on your device. If you are using Window, try install MSYS2.`

Open this app folder, then open terminal. On terminal, we will type this command to compile this application:
```php
gcc main_cmt.c $(pkg-config --cflags --libs gtk+-3.0) -o test_app libbt.a libfdr.a
```
with test_app is the name of application that you want.

```php
Note: during compile, you may have some warnings due to conflit of definitions of TRUE/FALSE in libraries we used. it does not affect the program so don't worry. 
```
**Demo pictures**

<a data-flickr-embed="true" href="https://www.flickr.com/photos/120264837@N06/50161208563/in/dateposted-public/" title="E-V Dict 1 photo"><img src="https://live.staticflickr.com/65535/50161208563_a3f22ac703_z.jpg" width="601" height="364" alt="E-V Dict 1 photo"></a>

<a data-flickr-embed="true" href="https://www.flickr.com/photos/120264837@N06/50161220653/in/dateposted-public/" title="E-V Dict 2"><img src="https://live.staticflickr.com/65535/50161220653_eb48803566_o.png" width="754" height="424" alt="E-V Dict 2"></a>

<a data-flickr-embed="true" href="https://www.flickr.com/photos/120264837@N06/50161763246/in/dateposted-public/" title="E-V Dict 3"><img src="https://live.staticflickr.com/65535/50161763246_e2511982f2_z.jpg" width="600" height="363" alt="E-V Dict 3">
