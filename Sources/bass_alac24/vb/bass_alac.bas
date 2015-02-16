Attribute VB_Name = "bass_alac"
Option Explicit

Global Const BASS_TAG_MP4 = 7	' iTunes/MP4 metadata

' BASS_CHANNELINFO type
Global Const BASS_CTYPE_STREAM_ALAC = &H10E00

Declare Function BASS_ALAC_StreamCreateFile64 Lib "bass_alac.dll" Alias "BASS_ALAC_StreamCreateFile" (ByVal mem As Long, ByVal file As Any, ByVal offset As Long, ByVal offsethigh As Long, ByVal length As Long, ByVal lengthhigh As Long, ByVal flags As Long) As Long
Declare Function BASS_ALAC_StreamCreateURL Lib "bass_alac.dll" (ByVal url As String, ByVal offset As Long, ByVal flags As Long, ByVal proc As Long, ByVal user As Long) As Long
Declare Function BASS_ALAC_StreamCreateFileUser Lib "bass_alac.dll" (ByVal system As Long, ByVal flags As Long, ByVal procs As Long, ByVal user As Long) As Long

' 32-bit wrappers for 64-bit BASS functions
Function BASS_ALAC_StreamCreateFile(ByVal mem As Long, ByVal file As Long, ByVal offset As Long, ByVal length As Long, ByVal flags As Long) As Long
BASS_ALAC_StreamCreateFile = BASS_ALAC_StreamCreateFile64(mem, file, offset, 0, length, 0, flags Or BASS_UNICODE)
End Function
