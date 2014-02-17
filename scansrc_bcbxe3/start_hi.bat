@echo off

pushd "C:\Projects\HiDA4.git"
git rev-list HEAD | findstr /R /N "^" | find /C ":" >> _tempRevFile.txt
set /p REVNUMBER=<_tempRevFile.txt
del _tempRevFile.txt
popd 

bin\scansrc_bcbxe3.exe "C:\Projects\HiDA4.git" "HiDA-4.6.0.%REVNUMBER%" "HI46_" "interfaces_HiDA-4.6.0.%REVNUMBER%.xml"