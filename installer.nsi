Name "RayLib PHP"
# define installer name
OutFile "raylib-php.exe"

# set desktop as install directory
InstallDir $PROGRAMFILES\RayLib-PHP

# default section start
Section

# define output path
SetOutPath $INSTDIR

# specify file to go in output path
ZipDLL::extractall "C:\Users\Admin\Apps\php-7.4.4-ts-Win32-vc15-x64\php-7.4.4-ts-Win32-vc15-x64.zip" "$INSTDIR"

# define uninstaller name
WriteUninstaller $INSTDIR\uninstaller.exe

createShortCut "$SMPROGRAMS\raylib-php.lnk" "$INSTDIR\php.exe"

EnVar::AddValue "Path" "$INSTDIR"

#-------
# default section end
SectionEnd

# create a section to define what the uninstaller does.
# the section will always be named "Uninstall"
Section "Uninstall"

# Always delete uninstaller first
Delete $INSTDIR\uninstaller.exe

Delete "$SMPROGRAMS\raylib-php.lnk"

# now delete installed file
Delete $INSTDIR

SectionEnd