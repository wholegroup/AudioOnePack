Attribute VB_Name = "bass_spx"
Option Explicit

' BASS_CHANNELINFO type
Global Const BASS_CTYPE_STREAM_SPX = &H10C00

Declare Function BASS_SPX_StreamCreateFile64 Lib "bass_spx.dll" Alias "BASS_SPX_StreamCreateFile" (ByVal mem As Long, ByVal file As Any, ByVal offset As Long, ByVal offsethigh As Long, ByVal length As Long, ByVal lengthhigh As Long, ByVal flags As Long) As Long
Declare Function BASS_SPX_StreamCreateURL Lib "bass_spx.dll" (ByVal url As String, ByVal offset As Long, ByVal flags As Long, ByVal proc As Long, ByVal user As Long) As Long
Declare Function BASS_SPX_StreamCreateFileUser Lib "bass_spx.dll" (ByVal system As Long, ByVal flags As Long, ByVal procs As Long, ByVal user As Long) As Long

' 32-bit wrappers for 64-bit BASS functions
Function BASS_SPX_StreamCreateFile(ByVal mem As Long, ByVal file As Long, ByVal offset As Long, ByVal length As Long, ByVal flags As Long) As Long
BASS_SPX_StreamCreateFile = BASS_SPX_StreamCreateFile64(mem, file, offset, 0, length, 0, flags Or BASS_UNICODE)
End Function
