boolean FILEIO_DEBUG;
FILEIO_DEBUG = false;

string buf;
numeric cur;

def is_digit (expr s) =
	((s >= "0") and (s <= "9"))
enddef;

def is_digit_or_point (expr s) =
	(is_digit (s) or (s = "."))
enddef;

def is_lowercase (expr s) =
	((ASCII (s) >= ASCII ("a")) and (ASCII (s) <= ASCII ("z")))
enddef;

def is_uppercase (expr s) =
	((ASCII (s) >= ASCII ("A")) and (ASCII (s) <= ASCII ("Z")))
enddef;

def is_alpha (expr s) =
        (is_lowercase (s) or is_uppercase (s))
enddef;

def is_alpha_or_digit (expr s) =
	(is_alpha (s) or is_digit (s))
enddef;

def is_blank (expr s) =
	((s = " ") or (s = "\n") or (s = "\r") or (s = "\t") or (s = ""))
enddef;

def is_sign (expr s) =
	((s = "+") or (s = "-"))
enddef;

def skip_blanks = begingroup
	forever:
		exitunless is_blank (substring (cur, cur + 1) of buf);
		cur := cur + 1;
	endfor;
endgroup enddef;

def get_num = begingroup
	numeric res, pow, sign;
	skip_blanks;
	res := 0;
        pow := 1;
        sign := 1;
	forever:
		exitunless is_sign (substring (cur, cur + 1) of buf);
		if substring (cur, cur + 1) of buf = "-":
			sign := -sign;
		fi;
		cur := cur + 1;
	endfor;
	forever:
		exitunless is_digit_or_point (substring (cur, cur + 1) of buf);
		if substring (cur, cur + 1) of buf = ".":
			pow := pow * 0.1;
		elseif pow = 1:
			res := res * 10 + ASCII (substring (cur, cur + 1) of buf) - 48;
		else:
			res := res + (ASCII (substring (cur, cur + 1) of buf) - 48) * pow;
			pow := pow * 0.1;
		fi;
		cur := cur + 1;
	endfor;
	res := res * sign;
	if FILEIO_DEBUG:
		show "FILEIO get_num: " & decimal (res);
	fi;
	res
endgroup enddef;

def get_word = begingroup
	string res;
	numeric temp;
	skip_blanks;
	temp = cur;
	forever:
		exitunless is_alpha_or_digit (substring (cur, cur + 1) of buf);
		cur := cur + 1;
	endfor;
	res := substring (temp, cur) of buf;
	if FILEIO_DEBUG:
		show "FILEIO get_word: " & res;
	fi;
	res
endgroup enddef;

def get_string = begingroup
	string res;
	numeric temp;
	skip_blanks;
	temp = cur;
	forever:
		exitif is_blank (substring (cur, cur + 1) of buf);
		cur := cur + 1;
	endfor;
	res := substring (temp, cur) of buf;
	if FILEIO_DEBUG:
		show "FILEIO get_word: " & res;
	fi;
	res
endgroup enddef;

def check_eof =
	buf = EOF
enddef;

def read_line (expr f) = begingroup
	buf := readfrom f;
	cur := 0;
	if FILEIO_DEBUG:
		show "FILEIO read_line: " & buf;
	fi;
endgroup enddef;
