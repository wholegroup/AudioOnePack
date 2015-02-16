;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; ИНСТАЛЯЦИОННЫЙ СКРИПТ ДЛЯ ПРОГРАММЫ "AUDIO ONE PACK"
;;
;; последние изменения 27.09.2007
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


!include "MUI.nsh"
!include "LogicLib.nsh"

; описание продукта
!define PRODUCT   "Audio One Pack"
!define VERSION   "1.4.2"
!define URL       "www.AudioOnePack.com"
!define COPYRIGHT "Copyright (c) Whole Group (www.wholegroup.com)"

; описание файла установки
VIProductVersion "${VERSION}.0"
VIAddVersionKey "ProductVersion" "${VERSION}.0"
VIAddVersionKey "ProductName" "${PRODUCT}"
VIAddVersionKey "Comments" "Please visit ${URL}"
VIAddVersionKey "CompanyName" "${URL}"
VIAddVersionKey "LegalTrademarks" "${COPYRIGHT}"
VIAddVersionKey "LegalCopyright" "${COPYRIGHT}"
VIAddVersionKey "FileDescription" "${PRODUCT}"
VIAddVersionKey "FileVersion" "${VERSION}.0"

; включение проверки CRC
CRCCheck on

; установка компрессии
SetCompress   force
SetCompressor /SOLID lzma

; включение стиля XP
XPStyle on

; определение параметров установки
Name         "${PRODUCT}"
OutFile      "AudioOnePack_v${VERSION}_install.exe"
InstallDir   "$PROGRAMFILES\${PRODUCT}"
BrandingText "${PRODUCT} v${VERSION} (${URL})"

VAR MUI_TEMP
VAR STARTMENU_FOLDER

; настройки страниц
!define MUI_ABORTWARNING
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP         "Documents\header.bmp"
!define MUI_ICON                       "${NSISDIR}\Contrib\Graphics\Icons\win-install.ico"
!define MUI_UNICON                     "${NSISDIR}\Contrib\Graphics\Icons\win-uninstall.ico"
!define MUI_FINISHPAGE_NOREBOOTSUPPORT
!define MUI_FINISHPAGE_RUN             "$INSTDIR\Audio One Pack.exe"
!define MUI_FINISHPAGE_LINK            "${PRODUCT} ${VERSION} (${URL})" 
!define MUI_FINISHPAGE_LINK_LOCATION   "http://${URL}"
!define MUI_COMPONENTSPAGE_NODESC

; install страницы 
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "Documents\License.rtf"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!define MUI_STARTMENUPAGE_REGISTRY_ROOT      "HKCU"
!define MUI_STARTMENUPAGE_REGISTRY_KEY       "Software\Whole Group (www.wholegroup.com)\${PRODUCT}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "LabelNSIS (${PRODUCT}" 
!insertmacro MUI_PAGE_STARTMENU Application $STARTMENU_FOLDER
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

; uninstall страницы  
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

; настройки языка
!insertmacro MUI_LANGUAGE "English"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; функция вызывается перед запуском install
;;
Function .onInit
	;; проверка версии Windows
   Call TestWindowsVersion
   Pop $R0

	strcmp $R0 "NO" 0 +3
	MessageBox MB_OK|MB_ICONSTOP "Windows 2000 or later version is required for installation"
	Quit

	;; проверка наличия .Net 2.0
	Call GetDotNETVersion
	Pop $0
	${If} $0 == "not found"
		MessageBox MB_YESNO|MB_ICONINFORMATION "Audio One Pack software requires Microsoft .NET 2.0 Framework. Please install .NET 2.0 Framework and run this setup again. Microsoft .NET 2.0 Framework can be installed from the internet. Would you like to do this now?" IDNO +2
		ExecShell "open" "http://www.microsoft.com/downloads/details.aspx?familyid=0856EACB-4362-4B0D-8EDD-AAB15C5E04F5&displaylang=en"
		Abort
	${EndIf}
 
	StrCpy $0 $0 1 1

	${if} $0 < 2
		MessageBox MB_YESNO|MB_ICONINFORMATION "Audio One Pack software requires Microsoft .NET 2.0 Framework. Please install .NET 2.0 Framework and run this setup again. Microsoft .NET 2.0 Framework can be installed from the internet. Would you like to do this now?" IDNO +2
		ExecShell "open" "http://www.microsoft.com/downloads/details.aspx?familyid=0856EACB-4362-4B0D-8EDD-AAB15C5E04F5&displaylang=en"
		Abort
	${endif}

	;; проверка запущенного экземпляра Audio One Pack
	System::Call 'kernel32::OpenMutexA(i 0, i 0, t "CE5666CD-DD45-43d6-B7D5-8EE337ED399C") i .r1 ?e'
	Pop $R0
 
	StrCmp $R0 2 +2
	   MessageBox MB_OK|MB_ICONEXCLAMATION "The software Audio One Pack is running. Prior starting Audio One Pack installation you have to close Audio One Pack that is running."

	System::Call 'kernel32::OpenMutexA(i 0, i 0, t "CE5666CD-DD45-43d6-B7D5-8EE337ED399C") i .r1 ?e'
	Pop $R0

	StrCmp $R0 2 +2
	Quit
FunctionEnd


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; функция вызывается перед запуском uninstall
;;
Function un.onInit
	System::Call 'kernel32::OpenMutexA(i 0, i 0, t "CE5666CD-DD45-43d6-B7D5-8EE337ED399C") i .r1 ?e'
	Pop $R0
 
	StrCmp $R0 2 +2
		MessageBox MB_OK "The software Audio One Pack is running. Prior starting Audio One Pack installation you have to close Audio One Pack that is running."

	System::Call 'kernel32::OpenMutexA(i 0, i 0, t "CE5666CD-DD45-43d6-B7D5-8EE337ED399C") i .r1 ?e'
	Pop $R0

	StrCmp $R0 2 +2
		Quit
FunctionEnd


; секция установки программы
Section "${PRODUCT} ${VERSION}" SecGUI
	SectionIn RO ; не изменяет по умолчанию

	SetOutPath "$INSTDIR"                                                    ; пусть установки

	File       "Sources\vs2010\release\Audio One Pack.exe"     ; 

	File       "Documents\License.rtf"

	File       "Sources\vs2010\Release\AOPAPI.dll"
	File       "Sources\bass24\bass.dll"           
	File       "Sources\bass_aac24\bass_aac.dll"
	File       "Sources\bass_ac324\bass_ac3.dll"
	File       "Sources\bass_alac24\bass_alac.dll"
	File       "Sources\bass_ape24\bass_ape.dll"
	File       "Sources\bass_mpc24\bass_mpc.dll"
	File       "Sources\bass_ofr24\bass_ofr.dll"
	File       "Sources\bass_ofr24\OptimFROG.dll"
	File       "Sources\bass_spx24\bass_spx.dll"
	File       "Sources\bass_tta24\bass_tta.dll"
	File       "Sources\basswv24\basswv.dll"
	File       "Sources\basscd24\basscd.dll"
	File       "Sources\bassflac24\bassflac.dll"
	File       "Sources\basswm24\basswma.dll"
	File       "Sources\vs2010\Release\lameEnc.dll"
	File       "Sources\vs2010\Release\libvorbis.dll"
	File       "Sources\vs2010\Release\libogg.dll"
	File       "Sources\vs2010\Release\libFLAC.dll"
	File       "Sources\tags17\tags.dll"
	File       "Sources\StarBurn\StarBurn.dll"
	File       "Sources\StarBurn\WnASPI32.dll"
	File       "Sources\MAC_SDK_413\Shared\MACDll.dll"
	File       "Sources\wavpackdll\wavpackdll.dll"
  
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "DisplayName" "${PRODUCT}"
	WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
    
	!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
		CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
		CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\${PRODUCT}.lnk" "$INSTDIR\Audio One Pack.exe"
		CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\${PRODUCT} Uninstall.lnk" "$INSTDIR\Uninstall.exe"
		CreateShortCut  "$SMPROGRAMS\$STARTMENU_FOLDER\${PRODUCT} License.lnk" "$INSTDIR\License.rtf"
	!insertmacro MUI_STARTMENU_WRITE_END

	WriteUninstaller "$INSTDIR\Uninstall.exe"
SectionEnd

; секция создания иконок на рабочем столе
Section "Create Shortcut on Desktop" SecICON
    CreateShortCut  "$DESKTOP\${PRODUCT}.lnk" "$INSTDIR\Audio One Pack.exe"
SectionEnd

Section "Uninstall"
	; удаление ярлыков из пуска  
	!insertmacro MUI_STARTMENU_GETFOLDER Application $MUI_TEMP
	Delete "$SMPROGRAMS\$STARTMENU_FOLDER$MUI_TEMP\${PRODUCT}.lnk"
	Delete "$SMPROGRAMS\$STARTMENU_FOLDER$MUI_TEMP\${PRODUCT} Uninstall.lnk"
	Delete "$SMPROGRAMS\$STARTMENU_FOLDER$MUI_TEMP\${PRODUCT} License.lnk"
	RMDir "$SMPROGRAMS\$STARTMENU_FOLDER$MUI_TEMP"

	; удаление ярлыков с рабочего стола
	Delete "$DESKTOP\${PRODUCT}.lnk"

	; удаление файлов
	Delete "$INSTDIR\Audio One Pack.exe"
	Delete "$INSTDIR\AOPAPI.dll"
	Delete "$INSTDIR\License.rtf"
	Delete "$INSTDIR\bass.dll"
	Delete "$INSTDIR\bass_aac.dll"
	Delete "$INSTDIR\bass_ac3.dll"
	Delete "$INSTDIR\bass_alac.dll"
	Delete "$INSTDIR\bass_ape.dll"
	Delete "$INSTDIR\bass_mpc.dll"
	Delete "$INSTDIR\bass_ofr.dll"
	Delete "$INSTDIR\OptimFROG.dll"
	Delete "$INSTDIR\bass_spx.dll"
	Delete "$INSTDIR\bass_tta.dll"
	Delete "$INSTDIR\basswv.dll"
	Delete "$INSTDIR\basscd.dll"
	Delete "$INSTDIR\bassflac.dll"
	Delete "$INSTDIR\basswma.dll"
	Delete "$INSTDIR\lameEnc.dll"
	Delete "$INSTDIR\libvorbis.dll"
	Delete "$INSTDIR\libogg.dll"
	Delete "$INSTDIR\libFLAC.dll"
	Delete "$INSTDIR\tags.dll"
	Delete "$INSTDIR\StarBurn.dll"
	Delete "$INSTDIR\WnASPI32.dll"
	Delete "$INSTDIR\MACDll.dll"
	Delete "$INSTDIR\Uninstall.exe"
	Delete "$INSTDIR\wavpackdll.dll"

	; удаление каталога инсталляции
	RMDir "$INSTDIR"

	; удаление ключа в реестре для деинсталляции
	DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT}"
SectionEnd


;;
;; функция возвращает YES, если версия Windows не младше 2000
;; иначе функция возвращает NO
;;
Function TestWindowsVersion
	Push $R0
	Push $R1

	ClearErrors

	ReadRegStr $R0 HKLM \
	"SOFTWARE\Microsoft\Windows NT\CurrentVersion" CurrentVersion

	IfErrors 0 lbl_winnt
  
	StrCpy $R0 'NO'
	Goto lbl_done

lbl_winnt:

	StrCpy $R1 $R0 1

	StrCmp $R1 '3' lbl_winnt_x
	StrCmp $R1 '4' lbl_winnt_x

	StrCpy $R1 $R0 3

	StrCpy $R0 'YES'
	Goto lbl_done

lbl_winnt_x:
	StrCpy $R0 'NO'
	Goto lbl_done

lbl_done:
	Pop $R1
	Exch $R0

FunctionEnd


;;
;; Функция возвращает версию .Net
;;
Function GetDotNETVersion
  Push $0
  Push $1
 
  System::Call "mscoree::GetCORVersion(w .r0, i ${NSIS_MAX_STRLEN}, *i) i .r1 ?u"
  StrCmp $1 0 +2
    StrCpy $0 "not found"
 
  Pop $1
  Exch $0
FunctionEnd