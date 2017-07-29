Qt (5.8.0 or newer) needs to be installed on your system as qmake is necessary to build scope2d.

Other dependencies are;

Eigen (3.3.4 or newer),
Qwt (6.1.3 or newer)

1. Open either scope2d_release.pro or scope2d_debug.pro depending on the build type you want

2. Set EIGENDIR to your installation location of Eigen library.

3. Set QWTDIR to your installation location of Qwt library.

4. Start Qt Console for MSVC

5. Change directory to this directory (i.e. <YOUR_PATH>/build/make-msvc)

6. Run 

qmake scope2d_release.pro

OR

qmake scope2d_debug.pro

depending on which build you want; release or debug

7. Change directory to the MSVC folder that has the nmake.exe for 64 bit.
It is usually at C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64 if you have MS Visual Studio

8. Run 

vcvars64.bat

9. Change directory back to the make-msvc folder

10. Run

nmake

11. When above line finishes executing, run below

nmake install

12. When the build is completed, you will find scope2d.exe in ../x64/Release or ..x64/Debug, depending on the build type you chose