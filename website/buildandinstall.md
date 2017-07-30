## How to build and install scope2d

Source code for scope2d can be downloaded from [the project page](/readme.md).
Build instructions are given in scope2d's project build folder, in files named `BUILD`. Qt's `QMake` is necessary to build scope2d.

scope2d needs <a href="https://www.qt.io/download/">Qt</a> 5.8.0 or above, <a href="http://qwt.sourceforge.net">Qwt</a> 6.1.3 or above and <a href="http://eigen.tuxfamily.org/index.php?title=Main_Page">Eigen</a> 3.3.4 or above to be built.

### Build scope2d on Windows

#### Build 64bit with MSVC using nmake

1. Open either `scope2d_release.pro` or `scope2d_debug.pro` depending on the build type you want

2. Set `EIGENDIR` to your installation location of Eigen library.

3. Set `QWTDIR` to your installation location of Qwt library.

4. Start Qt Console for MSVC

5. Change directory to this directory (i.e. `<YOUR_PATH>/build/make-msvc`)

6. Run 

    `qmake scope2d_release.pro`

    OR

    `qmake scope2d_debug.pro`

    depending on which build you want; release or debug

7. Change directory to the MSVC folder that has the nmake.exe for 64 bit. It is usually at `C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64` if you have MS Visual Studio

8. Run 

    `vcvars64.bat`

9. Change directory back to the make-msvc folder

10. Run

    `nmake`

11. When above line finishes executing, run below

    `nmake install`

12. When the build is completed, you will find scope2d.exe in `../x64/Release` or `..x64/Debug`, depending on the build type you chose

#### Build 32bit with MinGW

1. Open either `scope2d_release.pro` or `scope2d_debug.pro` depending on the build type you want

2. Set `EIGENDIR` to your installation location of Eigen library.

3. Set `QWTDIR` to your installation location of Qwt library.

4. Start Qt Console for MSVC

5. Change directory to this directory (i.e. `<YOUR_PATH>/build/make-mingw`)

6. Run 

    `qmake scope2d_release.pro`

    OR

    `qmake scope2d_debug.pro`

    depending on which build you want; release or debug

7. Run

    `mingw32-make`

8. When above line finishes executing, run below

    `mingw32-make install`

9. When the build is completed, you will find scope2d.exe in `../x64/Release` or `..x64/Debug`, depending on the build type you chose

### Build scope2d on Linux

1. Open either `scope2d_release.pro` or `scope2d_debug.pro` depending on the build type you want

2. Set `EIGENDIR` to your installation location of Eigen library.

3. Set `QWTDIR` to your installation location of Qwt library.

4. Start a Terminal

5. Change directory to this directory (i.e. `<YOUR_PATH>/build/make-linux`)

6. Run 

    `qmake scope2d_release.pro`

    OR

    `qmake scope2d_debug.pro`

    depending on which build you want; release or debug

7. Run

    `make`

8. When the build is completed, you will find scope2d in `../x64/Release` or `..x64/Debug`, depending on the build type you chose

### Alternative methods to build scope2d

Since scope2d has a small source code, its source code can easily be imported into Visual Studio or Qt Creator to be built. Qwt and Eigen need to be added as additional dependencies to the project in either environment. In Visual Studio, the <a href="https://download.qt.io/official_releases/vsaddin/">Qt VS Addin</a> can be used to create a Qt project within Visual Studio, after which the scope2d source code can be imported.
