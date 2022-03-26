MODULE Chars;


PROCEDURE IsDigit*(c: CHAR): BOOLEAN;
(** Return true, if '0' <= c <= '9' *)
BEGIN
  RETURN (c >= "0") & (c <= "9")
END IsDigit;

PROCEDURE IsAlpha*(c: CHAR): BOOLEAN;
BEGIN
  RETURN ((c >= "a") & (c <= "z")) OR ((c >= "A") & (c <= "Z"))
END IsAlpha;

PROCEDURE IsAlphaNum*(c: CHAR): BOOLEAN;
BEGIN
  RETURN     ((c >= "a") & (c <= "z"))
          OR ((c >= "0") & (c <= "9"))
          OR ((c >= "A") & (c <= "Z"))
END IsAlphaNum;

PROCEDURE IsUppercase*(c: CHAR): BOOLEAN;
BEGIN
  RETURN (c >= "A") & (c <= "Z")
END IsUppercase;

PROCEDURE IsLowercase*(c: CHAR): BOOLEAN;
BEGIN
  RETURN (c >= "a") & (c <= "z")
END IsLowercase;

PROCEDURE IsWhitespace*(c: CHAR): BOOLEAN;
BEGIN
  RETURN (c = " ") OR (c = 9X) OR (c = 0AX) OR (c = 0DX)
END IsWhitespace;

PROCEDURE IsPrintable*(c: CHAR): BOOLEAN;
BEGIN
  RETURN     ((c >= " ") & (c <= "~"))
           OR (c = 0AX)
           OR (c = 0DX)
           OR (c = 09X)
END IsPrintable;

PROCEDURE IsMember*(c: CHAR;   s: ARRAY OF CHAR): BOOLEAN;
VAR
  i, max: LONGINT;
  cc: CHAR;
BEGIN
  max := LEN(s);
  i := 0;
  LOOP
    IF i = max THEN RETURN FALSE END;
    cc := s[i];
    IF cc = c THEN RETURN TRUE END;
    IF cc = 0X THEN RETURN FALSE END;
    INC(i)
  END
END IsMember;

(*---------------------------------------------------------------------------*)
END Chars. (* (c) sts-q 2022-Mrz *)
