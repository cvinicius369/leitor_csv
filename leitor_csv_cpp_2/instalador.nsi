!include "MUI2.nsh"

Outfile "leitorcsv_setup.exe"
InstallDir "$PROGRAMFILES\leitor_csv_cpp_2"

!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES

Section

SetOutPath $INSTDIR
File /r "leitor_csv_cpp_2.cpp"

CreateDirectory $SMPROGRAMS\leitor_csv_cpp_2
CreateShortCut "$SMPROGRAMS\leitor_csv_cpp_2\SeuProjeto.lnk" "$INSTDIR\leitor_csv_cpp_2.exe"

SectionEnd
