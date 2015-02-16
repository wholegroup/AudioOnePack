Attribute VB_Name = "bass_ofr"
Option Explicit

' Additional tags available from BASS_StreamGetTags
Global Const BASS_TAG_APE = 6   ' APE tags

' BASS_CHANNELINFO type
Global Const BASS_CTYPE_STREAM_OFR = &H10600


Declare Function BASS_OFR_StreamCreateFile64 Lib "bass_ofr.dll" Alias "BASS_OFR_StreamCreateFile" (ByVal mem As Long, ByVal file As Any, ByVal offset As Long, ByVal offsethigh As Long, ByVal length As Long, ByVal lengthhigh As Long, ByVal flags As Long) As Long
Declare Function BASS_OFR_StreamCreateFileUser Lib "bass_ofr.dll" (ByVal system As Long, ByVal flags As Long, ByVal procs As Long, ByVal user As Long) As Long

' 32-bit wrappers for 64-bit BASS functions
Function BASS_OFR_StreamCreateFile(ByVal mem As Long, ByVal file As Long, ByVal offset As Long, ByVal length As Long, ByVal flags As Long) As Long
BASS_OFR_StreamCreateFile = BASS_OFR_StreamCreateFile64(mem, file, offset, 0, length, 0, flags Or BASS_UNICODE)
End Function
