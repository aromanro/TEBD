# TEBD
A simple Time Evolving Block Decimation program

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/fcb271b74c664a9fa4b019223fadb5b7)](https://app.codacy.com/gh/aromanro/TEBD?utm_source=github.com&utm_medium=referral&utm_content=aromanro/TEBD&utm_campaign=Badge_Grade_Settings)
[![CodeFactor](https://www.codefactor.io/repository/github/aromanro/tebd/badge/master)](https://www.codefactor.io/repository/github/aromanro/tebd/overview/master)

Description is on https://compphys.go.ro/time-evolving-block-decimation/

For now only iTEBD is implemented.

### TOOLS

The project compiles on Windows with Visual Studio 2026 (the code can be compiled with older versions starting with VS 2015, but it's currently maintained with VS 2026 and C++ 17 or higher).

### LIBRARIES

Besides mfc and other typical VC++ runtime libraries, the program uses GDI+ for drawing. 
Eigen 5 is also used, on older version will not work correctly because there were some issues with the `BDCSVD` solver. If you want to use an older version, change the implementation to use `JacobiSVD`.

### PROGRAM IN ACTION

[![Program video](https://img.youtube.com/vi/KHv_Tu7UIs8/0.jpg)](https://youtu.be/KHv_Tu7UIs8)
