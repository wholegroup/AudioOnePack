Attribute VB_Name = "bass_ac3"
Option Explicit

' BASS_Set/GetConfig options
Global Const BASS_CONFIG_AC3_DYNRNG = &H10001

' Additional BASS_AC3_StreamCreateFile/User/URL flags
Global Const BASS_AC3_DYNAMIC_RANGE = &H800     ' enable dynamic range compression

' BASS_CHANNELINFO type
Global Const BASS_CTYPE_STREAM_AC3 = &H11000

Declare Function BASS_AC3_StreamCreateFile64 Lib "bass_ac3.dll" Alias "BASS_AC3_StreamCreateFile" (ByVal mem As Long, ByVal file As Any, ByVal offset As Long, ByVal offsethigh As Long, ByVal length As Long, ByVal lengthhigh As Long, ByVal flags As Long) As Long
Declare Function BASS_AC3_StreamCreateURL Lib "bass_ac3.dll" (ByVal url As String, ByVal offset As Long, ByVal flags As Long, ByVal proc As Long, ByVal user As Long) As Long
Declare Function BASS_AC3_StreamCreateFileUser Lib "bass_ac3.dll" (ByVal system As Long, ByVal flags As Long, ByVal procs As Long, ByVal user As Long) As Long

' 32-bit wrappers for 64-bit BASS functions
Function BASS_AC3_StreamCreateFile(ByVal mem As Long, ByVal file As Long, ByVal offset As Long, ByVal length As Long, ByVal flags As Long) As Long
BASS_AC3_StreamCreateFile = BASS_AC3_StreamCreateFile64(mem, file, offset, 0, length, 0, flags Or BASS_UNICODE)
End Function
