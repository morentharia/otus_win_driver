

target host
```sh
ssh mor@192.168.1.150
1
```



```powershell
bcdedit /set debug on
bcdedit /set debugtype serial
bcdedit /set debugport 1
bcdedit /set baudrate 115200
bcdedit /set nointegritychecks on


cd "\\vmware-host\Shared Folders\shared"
ls
cd driver
cd mydriver
ls



cd "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin"
./MSBuild --version
$env:Path
$env:Path = 'C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin;' + $env:Path 
cd  "\\vmware-host\\Shared Folders\\shared"
dir mydriver\\
###WIN!!!!!!!!!
MSBuild mydriver\\mydriver.vcxproj -p:Configuration=Debug -p:Platform=x64


use sc.exe!!!!

sc.exe create anotherone3 binPath="\\vmware-host\Shared Folders\shared\mydriver\Debug\mydriver.sys" type=kernel
sc.exe query anotherone3
sc.exe start anotherone3
sc.exe stop anotherone3

sc.exe create AAAAA binPath="\\vmware-host\Shared Folders\shared\mydriver\x64\Debug\mydriver.sys" type=kernel
sc.exe query AAAAA
sc.exe start AAAAA
sc.exe stop AAAAA
sc.exe delete AAAAA


sc.exe


cd c:\srvman-1.0\x64
dir
c:\srvman-1.0\x64\srvman.exe
```
