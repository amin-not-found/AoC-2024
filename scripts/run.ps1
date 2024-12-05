param(
    [parameter(mandatory)]
    [validatescript({Test-Path $_ -PathType Container})]
    [System.Io.DirectoryInfo]$Dir
)

$ErrorActionPreference = 'Stop'

$Src="./$Dir/main.cpp"
$Obj="./$Dir/out.obj"
$Out="./$Dir/out.exe"

cl /EHsc /std:c++17 /W4 /Fo:$Obj /Fe:$Out $Src 
& "$Out"
Remove-Item $Obj
Remove-Item $Out
