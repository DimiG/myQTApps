myQTApps
========
This repository dedicated to myOWN QT C++ programs I use for tests or daily purposes.

These programs created in Qt Creator 3.2.2 which based on Qt 5.3 (MSVC 2010, 32 bit) or Qt 5.3 (MinGW 4.8.2, 32 bit).
Repository contain Qt Creator project which you're able to clone and open in your Qt Creator version.
Compile it and use it.

Codes description
-------------------

### myQTApps folder

* `QTstatic`: This folder with PowerShell [script][QtlMovie] inside downloads a Qt source code, compiles and installs a static version of Qt.<br>
   This script adds a static version of the Qt libraries in order to allow the construction of standalone and self-sufficient executable.<br>
   ***Requires :*** [Qt Creator][qt-project] preinstalled (prebuilt Qt / MinGW environment), Windows 7, Mac OS 10.6 or Linux, Windows PowerShell 3.0 or higher, 7-zip.<br>
   **Note :** [Qt 5.3][qt-project] or above must be located in C:\Qt. Root directory where the static versions of Qt are installed. By default, use C:\Qt\Static The [7-Zip Command Line Version][7-ZipCLI] located in C:\bin<br>
   This PowerShell script belongs to Thierry Lelegard. I had to modify it (see the code) cause it didn't work for me. But now it works. The files location and links are changing, so you'll have to change the script to get it working again in the future.<br>
   Here is [instruction][qt-static] how to play with it.<br>
   
* `theClock`: Shows window form with current date and clock. Just demonstrate how to do it in Qt C++<br>
   **Note :** This code is not well optimized. If any tips, write me about.<br>

* `All Applications`:<br>
   ***Requires :*** [Qt Creator][qt-project] preinstalled, Windows 7, Mac OS 10.6 or Linux<br>
   ***Important:*** To distribute your compiled programm you need to add additional libs into your relese folder.
   
* `To be continued...`

Your Questions - my Answers
---------------------------

### Why is it public?

Exist some reasons for it:

* I don't like to make one job many times and want to save it in the cloud.

* If someone have same needs he can contribute and improve this code.
  
* I want to use the `Git` for personal study and project collaboration

### When do you finish?

Just fill it one by one.

### Is it safe to use?

These code is not fully tested, and may not work correctly. Just inform me if you want.

### Who Are You?

My name is [Dmitri][dimig] and I'm a splendid chap.

### Where can I find more info?

Additional tips and tricks are on [myOWN blog][homepage].

Contributing
------------

Fork the [DimiG repository on GitHub](https://github.com/dimig) and
send a Pull Request.

[homepage]:http://dimig.blogspot.com
[dimig]:http://dimig.blogspot.com
[qt-project]:http://qt-project.org/downloads
[QtlMovie]:http://sourceforge.net/p/qtlmovie/code/ci/master/tree/build
[qt-static]:http://qt-project.org/wiki/How-to-build-a-static-Qt-for-Windows-MinGW
[7-ZipCLI]:http://www.7-zip.org/download.html
