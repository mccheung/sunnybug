Func TestSendUnicode()
	Run("notepad.exe")
	WinWaitActive("�ޱ��� - ")
	$Text = "���� ��������" & @CR
	$Text &= "���w ��Ո���P�� " & @LF
	$Text &= "���� �������������ޤ� " & @CR
	$Text &= "������ţ� ���Ѣ٢񦨩�" & @LF
	$Text &= "@CRLF �ỻ��2��" & @CRLF
	$Text &= "End"

	SendC($Text)
EndFunc   ;==>TestSendUnicode

Func SendC($Str)
	For $i = 1 To StringLen($Str)
		Send('{ASC ' & StringToBinary(StringMid($Str, $i, 1) & ' ') & '}')
	Next
EndFunc   ;==>SendC


HotKeySet("#n", "StartNotepad")
While 1
        Sleep(1100)
	WEnd

Func StartNotepad()
	Run("notepad")
EndFunc   ;==>StartNotepad