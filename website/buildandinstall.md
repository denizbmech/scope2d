## How to build and install scope2d

There are a number of ways to build and install scope2d on Windows and Linux. scope2d needs <a href="https://www.qt.io/download/">Qt</a> 5.8.0 or above, <a href="http://qwt.sourceforge.net">Qwt</a> 6.1.3 or above and <a href="http://eigen.tuxfamily.org/index.php?title=Main_Page">Eigen</a> 3.3.4 or above to be built.

### Build scope2d on Windows

#### Build 64bit with MSVC using nmake

<ol>
<li>Find Makefile under scope2d/build and in Makefile, change QTDIR to your Qt's installation location.</li>
<li>Find Makefile.release and Makefile.debug and in these files, change QTDIR, QWTDIR and EIGENDIR to your Qt's, Qwt's and Eigen(+)'s installation locations.</li>
<li>Start a Windows Command Window.</li>
<li>Change directory to your MSVC installation to find nmake in the folder amd64. It is usually at C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64<br>Run: <b>cd C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64</b></li>
<li>Run below line: <br><b>vcvars64.bat</b></li>
<li>Change directory to the scope2d/build folder</li>
<li>Run below line: <br><b>nmake</b></li>
</ol>

(+) $(EIGENDIR)/Eigen/src must be valid. Arrange Eigen installation to fit this. In other words, in your $(EIGENDIR) there must be a folder named Eigen and that folder must contain Eigen's src folder and other source.

At this point, nmake should start building scope2d. Once the build is complete, scope2d.exe will be created in `scope2d/build/Release/` or `scope2d/build/Debug/`

#### Build 32bit with MinGW

Soon

### Build scope2d on Linux

Soon

### Alternative methods to build scope2d

Since scope2d has a small source code base, its source code can easily be imported into Visual Studio or Qt Creator to be built. Qwt and Eigen need to be added as additional dependencies to the project in either environment. In Visual Studio, the <a href="https://download.qt.io/official_releases/vsaddin/">Qt VS Addin</a> can be used to create a Qt project within Visual Studio, after which the scope2d source code can be imported.
