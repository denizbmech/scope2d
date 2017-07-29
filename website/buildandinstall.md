## How to build and install scope2d

Build instructions are given in scope2d's project build folder, in files named `BUILD`. Qt's `QMake` is necessary to build scope2d.

scope2d needs <a href="https://www.qt.io/download/">Qt</a> 5.8.0 or above, <a href="http://qwt.sourceforge.net">Qwt</a> 6.1.3 or above and <a href="http://eigen.tuxfamily.org/index.php?title=Main_Page">Eigen</a> 3.3.4 or above to be built.

### Build scope2d on Windows

#### Build 64bit with MSVC using nmake

<ol>
<li>Open either scope2d_release.pro or scope2d_debug.pro depending on the build type you want</li>
<li>Set EIGENDIR to your installation location of Eigen library. (+)</li>
<li>Set QWTDIR to your installation location of Qwt library.</li>
<li>Start Qt Console for MSVC</li>
<li>Change directory to this directory (i.e. <YOUR_PATH>/build/make-msvc)</li>
<li>Run 

`qmake scope2d_release.pro`

OR

`qmake scope2d_debug.pro`

depending on which build you want; release or debug</li>
<li>Change directory to the MSVC folder that has the nmake.exe for 64 bit. It is usually at `C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64` if you have MS Visual Studio</li>
<li>Run 

`vcvars64.bat`</li>
<li>Change directory back to the make-msvc folder</li>
<li>Run

`nmake`</li>
<li>When above line finishes executing, run below

`nmake install`</li>
<li>When the build is completed, you will find scope2d.exe in `../x64/Release` or `..x64/Debug`, depending on the build type you chose</li>
</ol>

(+) $$EIGENDIR/Eigen/src must be a valid location. Arrange Eigen installation to fit this.

#### Build 32bit with MinGW

<ol>
  <li>Open either scope2d_release.pro or scope2d_debug.pro depending on the build type you want</li>
  <li>Set EIGENDIR to your installation location of Eigen library.</li>
  <li>Set QWTDIR to your installation location of Qwt library.</li>
  <li>Start Qt Console for MSVC</li>
  <li>Change directory to this directory (i.e. <YOUR_PATH>/build/make-mingw)</li>
  <li>Run 

`qmake scope2d_release.pro`

OR

`qmake scope2d_debug.pro`

depending on which build you want; release or debug</li>
  <li>Run

`mingw32-make`</li>
  <li>When above line finishes executing, run below

`mingw32-make install`</li>
  <li>When the build is completed, you will find scope2d.exe in ../x64/Release or ..x64/Debug, depending on the build type you chose</li>
</ol>

### Build scope2d on Linux

Soon

### Alternative methods to build scope2d

Since scope2d has a small source code base, its source code can easily be imported into Visual Studio or Qt Creator to be built. Qwt and Eigen need to be added as additional dependencies to the project in either environment. In Visual Studio, the <a href="https://download.qt.io/official_releases/vsaddin/">Qt VS Addin</a> can be used to create a Qt project within Visual Studio, after which the scope2d source code can be imported.
