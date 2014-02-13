@echo off

pushd "C:\Projects\ACTApro.git"
git rev-list HEAD | findstr /R /N "^" | find /C ":" >> _tempRevFile.txt
set /p REVNUMBER=<_tempRevFile.txt
del _tempRevFile.txt
popd 

bin\scansrc_bcbxe3.exe "C:\Projects\ACTApro.git" "ACTApro-2.1.0.%REVNUMBER%" "AP21_" > "interfaces_ACTApro-2.1.0.%REVNUMBER%.xml"