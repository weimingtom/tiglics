VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5910
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   7755
   LinkTopic       =   "Form1"
   ScaleHeight     =   5910
   ScaleWidth      =   7755
   StartUpPosition =   3  'Windows ‚ÌŠù’è’l
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   1575
      Left            =   0
      TabIndex        =   4
      Top             =   1080
      Width           =   255
   End
   Begin VB.ListBox List1 
      Height          =   780
      Left            =   480
      TabIndex        =   3
      Top             =   4680
      Width           =   6975
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   360
      TabIndex        =   2
      Text            =   ".\src\"
      Top             =   0
      Width           =   7095
   End
   Begin VB.TextBox Text2 
      Height          =   3495
      Left            =   360
      MultiLine       =   -1  'True
      ScrollBars      =   3  '—¼•û
      TabIndex        =   1
      Top             =   960
      Width           =   7095
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   360
      OLEDropMode     =   1  'Žè“®
      TabIndex        =   0
      Text            =   "TiGLiCSAll.h"
      Top             =   480
      Width           =   7095
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub ReadHeader(FileID As Integer, FileName As String, FilePath As String)
    Dim FN As Integer
    Dim tmp As String, tmp2 As String
    Dim IncludePos As Integer
    Dim i As Integer, j As Integer
    For i = 1 To List1.ListCount
        If FileName = List1.List(i) Then
            Exit Sub
        End If
    Next i
    If StrSearch(FileName, "Selene.h") <> -1 Then
        Print #FileID, "#include " + """" + "Selene.h" + """" + vbCrLf
        List1.AddItem ("Selene.h")
        Exit Sub
    End If
    
    List1.AddItem (Replace(FileName, "/", "\"))
    FN = FreeFile()
    Open FilePath + FileName For Input As #FN
    Do Until EOF(FN)
        tmp = ""
        i = -1
        j = -1
        Line Input #FN, tmp
        IncludePos = StrSearch(tmp, "#include")
        If IncludePos <> -1 Then
            '•Ê‚ÌInclude‚ªŒ©‚Â‚©‚Á‚½‚ç
            i = StrSearch(tmp, """")
            j = StrSearchRev(tmp, """")
            If i < j Then
                tmp2 = Mid(tmp, i + 1, j - i - 1)
                tmp2 = Replace(tmp2, "/", "\")
                If StrSearch(tmp2, "\") = -1 Then
                    tmp2 = GetFilePath(FileName) & tmp2
                End If
                Call ReadHeader(FileID, tmp2, FilePath)
            End If
        End If
        If StrSearch(tmp, "#pragma once") = -1 And (IncludePos = -1 Or j = -1) Then
            Print #FileID, tmp
        End If
    Loop
     Print #FileID, vbCrLf
    Close #FN
    'ReadHeader = RetStr
End Sub
Private Sub Command1_Click()
    Open Text3.Text + "..\..\BIN\TiGLiCS.h" For Output As #1
    Print #1, "#pragma once" + vbCrLf
    Call ReadHeader(1, Text1.Text, Text3.Text)
    Close #1
End Sub


Private Sub Form_Load()
    Command1_Click
    End
End Sub

Private Sub Text1_OLEDragDrop(Data As DataObject, Effect As Long, Button As Integer, Shift As Integer, X As Single, Y As Single)

    Text1.Text = Data.Files(1)
End Sub



Private Function StrSearch(ByVal src As String, ch As String) As Long '•¶Žš—ñ‚Ì’†‚©‚ç•¶Žš(—ñ)‚ðŒŸõ
    Dim i As Long, lch As Long, tmpa As String, tmpb As String
    lch = Len(ch)
    If lch = 0 Then
        StrSearch = -1
        Exit Function
    End If
    For i = 1 To Len(src) - lch + 1
        If Mid(src, i, lch) = ch Then
            StrSearch = i
            Exit Function
        End If
    Next i
    StrSearch = -1
End Function




Private Function StrSearchRev(ByVal src As String, ch As String) As Long '•¶Žš—ñ‚Ì’†‚©‚ç•¶Žš(—ñ)‚ðŒŸõ
    Dim i As Long, lch As Long, tmpa As String, tmpb As String
    lch = Len(ch)
    If lch = 0 Then
        StrSearchRev = -1
        Exit Function
    End If
    For i = Len(src) - lch + 1 To 1 Step -1
        If Mid(src, i, lch) = ch Then
            StrSearchRev = i
            Exit Function
        End If
    Next i
    StrSearchRev = -1
End Function

Private Function GetFilePath(ByVal src As String, Optional ByVal separate As String = "\") As String
    Dim i As Integer
    i = StrSearchRev(src, separate)
    If i <> -1 Then
        GetFilePath = Mid(src, 1, i)
    End If
End Function

Private Sub Text2_Change()

End Sub
