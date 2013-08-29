input FILEIO;

prologues := 3;
w = 0.2 mm;
u = 50.0 w;

shiftx := 0;
shifty := 0;

def t (expr a) =
	((a) shifted (shiftx, shifty) scaled u yscaled 1 xscaled -1)
enddef;

def label_custom (expr s, z, d) = begingroup
	numeric labxf.custom, labyf.custom, scale;
	pair laboff.custom;
	scale := max (len, 0.25);
	labxf.custom := 0.5;
	labyf.custom := 0.5;
	laboff.custom := t (dir (d) * scale * 0.21);
	label.custom (s infont "latt1200" scaled (2.4 * scale), t (z));
endgroup enddef;

def go (expr s, r, pos, z, alpha, chlo, chhi, add) = begingroup
	numeric beta, cur;
	pair nz;
	cur := pos;

	beta := alpha + add;
	if beta >= 360:
		beta := beta - 360;
	fi;

	nz := z + (len, 0) rotated beta;

	if ((substring (cur, cur + 1) of s) = chlo) or
	   ((substring (cur, cur + 1) of s) = chhi):
		if (substring (cur, cur + 1) of s) = chhi:
%			pickup pencircle scaled (6 * w * len);
%			draw t (z -- nz) withcolor 0.5 white;
			pickup pencircle scaled (8 * w * len);
			draw t (z -- nz);
			pickup pencircle scaled (4 * w * len);
			draw t (z -- nz) withcolor 0.8 white;
		else:
			pickup pencircle scaled (3 * w * len);
			draw t (z -- nz);
		fi;
		cur := draw_board (s, r, cur + 1, nz, beta);
		if ((substring (cur, cur + 1) of s) = "b") or
		   ((substring (cur, cur + 1) of s) = "B"):
			cur := cur + 1;
		else:
			errmessage "character " & decimal (cur) &
			           " should be `b' or `B'";
		fi;
	elseif (add <> 180) and tails:
		pickup pencircle scaled (3 * w * len);
		draw t (0.90 z + 0.10 nz -- 0.80 z + 0.20 nz);
		draw t (0.60 z + 0.40 nz -- 0.50 z + 0.50 nz);
	fi;

	cur
endgroup enddef;

def draw_board (expr s, r, pos, z, alpha) = begingroup
        numeric cur;
        save here;
        string here;
	cur := pos;
	here := substring (cur, cur + 1) of r;
	len := len * mult;

	cur := go (s, r, cur, z, alpha, "l", "L", 300);
	cur := go (s, r, cur, z, alpha, "r", "R",  60);
	cur := go (s, r, cur, z, alpha, "z", "Z", 180);

	if is_alpha (here):
		label_custom (here, z, alpha);
	fi;

	if here = "0":
		pickup pencircle scaled (7 * w * len);
		draw t (z);
		pickup pencircle scaled (3 * w * len);
		draw t (fullcircle scaled (0.3 * len) shifted z);
		pickup pencircle scaled (2 * w * len);
		draw t (fullcircle scaled (0.5 * len) shifted z);
	elseif here <> ".":
%		pickup pencircle scaled (12 * w * len);
%		draw t (z) withcolor 0.5 white;
		pickup pencircle scaled (12 * w * len);
		draw t (z);
		pickup pencircle scaled (6 * w * len);
		draw t (z) withcolor 0.8 white;
	else:
		pickup pencircle scaled (7 * w * len);
		draw t (z);
	fi;

	len := len / mult;
	cur
endgroup enddef;

def process (expr s, r, nlen, nmult, ntails) = begingroup
	numeric cur, len, mult;
	boolean tails;
	len := nlen;
	mult := nmult;
	tails := ntails;
	cur := draw_board (s, r, 0, (0, 0), 0);
endgroup enddef;

beginfig (1)
	process (("llllbrbbrlbrbbbrllbrbbrlbrbbbb" &
	          "rlllbrbbrlbrbbbrllbrbbrlbrbbbb" &
	          "zlllbrbbrlbrbbbrllbrbbrlbrbbbb"),
	         (".............................." &
	          ".............................." &
	          ".............................."), 1.5 * 1, 2 / 3, true);
endfig;

beginfig (2)
	process (("LlllbrbbrlbrbbbRllbrbbrlbrbbbb" &
	          "rlllbrbbrlbrbbbrllbrbbrlbrbbbb" &
	          "ZLLlbrbbrlbrbbbrllbrbbrlbrbbbb"),
	         ("##..............B............." &
	          ".............................." &
	          ".##A.........................."), 1.5 * 1, 2 / 3, true);
endfig;

beginfig (3)
	process (("LLLlbrbBRlbrbBBRLlbrbBRlbrbBBB" &
	          "RlllbrbbrlbrbbbrllbrbbrlbrbbbB" &
	          "ZlllbrbbrlbrbbbrLLBRBBrlbrbbbB"),
	         ("bBbb.b.bbb.b.bbbbb.b.bbb.b.bbb" &
	          "bb..............C............b" &
	          "bb..............aAaaaa.......b"), 1.5 * 0.94, 0.69, true);
endfig;

beginfig (4)
	process ("LLLBBRBBRLRBBRLBRLBRBBBBZLBRBB",
	         "###############A##############", 1.5 * 0.75, 0.9, false);
endfig;

beginfig (5)
	process ("lbrbZB", "#l.r.b", 1, 0.8, false);
	pickup pencircle scaled 2 w;
	drawarrow t ((-0.6, 0) -- (-0.2, 0));
	pickup pencircle scaled 4 w;
	drawarrow t ((0, 0) -- (0.4, 0));
endfig;

beginfig (6)
	process ("LLlbBRBBRLrbBRlbrlbrbbBBZLBRBB",
	         "Aaa..aaaaaa..aa........aaaaaaa", 0.75, 0.9, false);
endfig;

beginfig (7)
	process ("lllbbrbbRLrbBRlbrlbrbbBbzlbrbb",
	         "a........Aa...a...............", 0.75, 0.9, false);
endfig;

beginfig (8)
	process ("lllbbrbbrlrbbrlbrlbrbbbbzlbrbb",
	         "0........00...0..........B....", 0.75, 0.9, false);
endfig;

beginfig (9)
	process ("lllbbrbbrlrbbRLBRlbrbBbbzlbrbb",
	         ".........a....Aa.a............", 0.75, 0.9, false);
endfig;

beginfig (10)
	process ("lllbbrbbrlrbbrlbrlbrbbbbZLBRBB",
	         "b........0....00.0.......Bb.b.", 0.75, 0.9, false);
endfig;

beginfig (11)
	process ("LBRBZB", "######", 1, 0.8, false);
endfig;

% large test 1
beginfig (12)
	shiftx := 10;
	shifty := 10;
	process ("lllllbrrlbbbbrlrbbbbrllbrrlbrrlllbrbbbrl" &
	         "lbrrbbbrlbbbbbbbbrlllllbrlbrbbbrlbrlbbbb" &
	         "rrbbbrlllbrbbrlbrbbbrrllbbrlbrlbbbbbbbrl" &
	         "llllbrbbrlbrlbrbbbbrbbrllbrrllbbrbbbbbbr" &
	         "bbbbbrllllbrbbrrbbbrllrbbrrbbbrlbbbbbb", "",
	         4, 0.6, false);
endfig;

% large fat test 2
beginfig (13)
	shiftx := 10;
	shifty := 10;
	process ("lllbrllbrllbrbbrlbrbbbbrlllbrbbrlllbrbbr" &
	         "lbrbbbrbbbrllbrbbrlbrbbbbbbrlllllbrllbrb" &
	         "brlbrbbbbrlllbrbbrbbrlbrbbbbrbbrlllllbrb" &
	         "brlbrbbbrbbrlbrbbbrbbbrlbrlllbrllbrbbrlb" &
	         "rbbbbrllbrbbrlbrbbbbrllbrbbrlbrbbbbbbb", "",
	         4, 0.6, false);
endfig;

% large fat test 5
beginfig (14)
	shiftx := 10;
	shifty := 10;
	process ("llllllbrbbrlbrbbbrllbrbbrlbrbbbbrlllbrbb" &
	         "rlbrbbbrllbrbbrlbrbbbbbrllllbrlllllbrbbr" &
	         "lbrbbbrllbrbbrlbrbbbbrlllbrbbrlbrbbbrllb" &
	         "rbbrlbrbbbbbrllllbbbbbbbrlbrbbbrllbrbbrl" &
	         "brbbbbrlllbrbbrlbrbbbrllbrbbrlbrbbbbbb", "",
	         4, 0.6, false);
endfig;

end.
