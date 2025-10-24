# Harmonic Visualizer (C++)

A modular-exponentiation powered **visualizer** that generates repeating sequences and maps them into dynamic ASCII animations.  
No external dependencies — just C++17.

---

## Features

- **Pure C++** (no GMP required)
- **Cross-platform**: Windows, macOS, Linux
- **Three visual modes**:
  - Oscilloscope (waveform trace)
  - Lissajous (dual-axis curve)
  - Plasma (ASCII shaded field)
- Interactive menu for:
  - Base & modulo adjustment
  - Sequence inspection
  - Animation start/stop
  - Settings: animation speed, canvas size, and mode
  - Toggle sequence creation report display

---

## Build and Run

### Prerequisites

- g++ 7+ (C++17 capable) or MSVC 2019+

### Compile

```bash
g++ -I ./ *.cpp -o harmonic
```

### Run

  - `./harmonic`
  - `.\harmonic.exe` (Windows)

### Usage

When started, the program initializes with:

  - `base = 2`
  - `modulo = 61`

---

## Examples

  - base = 2, mod = 11 → period 10
  - base = 2, mod = 13 → period 12
  - base = 2, mod = 19 → period 18 (2^9 ≡ −1, so full order 18)
  - base = 2, mod = 29 → period 28 (2^14 ≡ −1 → full order 28)
  - base = 2, mod = 61 → period 60 (2^30 ≡ −1 → full order 60)
  - base = 3, mod = 31 → period 30 (3^15 ≡ −1 → full order 30)
  - base = 5, mod = 23 → period 22 (5^11 ≡ −1 → full order 22)

---

## Menus

### Main

  1. Set base
  2. Set modulo
  3. Show sequence
  4. Start/Stop visual
  5. Toggle sequence report
  6. Settings (speed, size, mode)
  7. Exit

### Settings

  - Animation speed: set frame delay in ms (default 40)
  - Canvas size: width & height (min 40x16)
  - Mode: 1=Oscilloscope, 2=Lissajous, 3=Plasma

### Controls

  - Switch modes via Settings
  - Start and stop the animation from the menu with option `4`

---

## Notes

  - Performance: The visual runs at ~100 FPS by default.
  - Terminal size: Make sure your console window is large enough to fit the chosen canvas size.
  - Compatibility: On Windows, VT/ANSI sequences are auto-enabled.

---

## Example Output of Mode 3

**Using:**

  - Mode: 3
  - Size: 100x300 (W x H)
  - Base: 2
  - Modulo: 61
  - Partials: 24

**Single frame snapshot during runtime:**
<details>
  
```
QUuf)]~!I:^`''....          .......                                   ......''''''''''''''''```^^,,:
QYut)?~!;,^`''....          .......                                   ......'''''''''''''''''```^,,:
LYut1?~!;,^`'.....           .....                                    .......''''''''''''''''```^,,:
LYnt1?<!;,^`'.....           .....                                    .......''''''''''''''''```^^,:
LXn/1?<!;,^`'....             ...                                     .......''''''''''''''''```^^,:
LXn/{-<!;,^`'....              .                                      ........'''''''''''''''```^^,:
CXx/{-<!;,^`'....                                                     ........''''''''''''''''``^^,:
CXx/{-<l;,^`'....                                                      .......''''''''''''''''``^^,:
Czx\{-<l;,``'....                                                      ........'''''''''''''''``^^,:
Czx\{-<l;,`''....                                                      ........'''''''''''''''``^^,:
Czx\{-<l;,`''....                                                      ........'''''''''''''''```^,:
Czx\{->l;,`''....                                                      .........''''''''''''''```^,:
Czx\}->l;,`''....                                                      .........''''''''''''''```^,,
Czr\}_>l;,`''....                                                      .........''''''''''''''```^,,
Czr\}_>l;,`''....                                                      .........''''''''''''''```^,,
Czr\}_>l;,`''....                                                      .........''''''''''''''```^,,
Czr\}_>l;,`''....                                                      .........''''''''''''''```^,,
Czr\}_>l;,`''....                                                      .........''''''''''''''```^,,
Czx\}->l;,`''....                                                      .........''''''''''''''```^,,
Czx\{->l;,`''....                                                      .........''''''''''''''```^,,
Czx\{->l;,`''....                                                      ........'''''''''''''''```^,:
Czx\{-<l;,`''....                                                      ........'''''''''''''''```^,:
Czx\{-<l;,`''....                                                      ........'''''''''''''''``^^,:
Czx\{-<l;,``'....                                                      .......''''''''''''''''``^^,:
CXx/{-<l;,^`'....                                                      .......''''''''''''''''``^^,:
LXn/{-<!;,^`'....                                                     ........''''''''''''''''``^^,:
LXn/1-<!;,^`'....              ..                                     ........'''''''''''''''```^^,:
LXn/1?<!;,^`'....             ...                                     .......''''''''''''''''```^^,:
LYnt1?<!;,^`'.....           .....                                    .......''''''''''''''''```^^,:
LYut1?~!;,^`'.....           .....                                    .......''''''''''''''''```^,,:
QYut)?~!;,^`''....          .......                                   ......'''''''''''''''''```^,,:
QYut)]~!I,^`''....          .......                                   ......''''''''''''''''```^^,,:
QUuf)]~iI:^`''....         ........                                   ......''''''''''''''''```^^,::
0Uvf)]+iI:^`''.....        .........                                  .....'''''''''''''''''```^^,:;
0Uvj(]+iI:^`''.....       ..........                                 ......'''''''''''''''''```^^,:;
0Jcj([+iI:^`''.....       ..........                                 ......''''''''''''''''````^^,:;
OJcj|[+iI:^`''......     ............                                ......''''''''''''''''````^,,:;
OCcr|[_>l:,`''......    .............                                .....''''''''''''''''````^^,,:;
OCzr|}_>l:,``'.......  ..............                                .....''''''''''''''''````^^,,:;
ZCzx\}_>l;,^`''......................                                .....'''''''''''''''`````^^,:;I
ZLXx\{->l;,^`''.......................                               .....''''''''''''''``````^^,:;I
ZLXn/{-<l;,^`''.......................                              .....'''''''''''''```````^^,,:;I
mQYn/{-<!;,^`''.......................                              .....'''''''`````````````^^,,:;I
mQYut1?<!;,^`''.......................                              .....''''''``````````````^^,,:;I
w0Uut1?~!I:^`''........................                             .....'''''``````````````^^^,::;l
w0Uvf)]~!I:^`''........................                             ....'''''```````````````^^,,:;Il
w0Jvf)]~iI:^`'''.......................                            .....'''''``````````````^^^,,:;Il
qOJcj(]+iI:,``''.......................                            .....''''```````````````^^^,,:;Il
qOCcj([+iI:,^`''........................                           .....''''``````````````^^^,,::;I!
pZCzr|[_>l:,^`''........................                           ....''''``````````````^^^^,,:;Il!
pZLzr|}_>l;,^`''........................                           ....''''`````````````^^^^^,,:;Il!
pmLXx\}_>l;,^`'''.......................                           ....'''````````^^^^^^^^^^,,::;Ili
dmQXx\{-<!;,^`'''........................                         .....'''`````^^^^^^^^^^^^^,,::;Ili
dwQYn/{-<!;:^``''........................                         ....''''````^^^^^^^^^^^^^,,,:;;l!i
bw0Yut1?<!I:^``'''...........'''''.......                         ....'''````^^^^^^^^^^^^^^,,::;Il!>
bq0Uut1?~!I:,``'''..........'''''''......                         ....'''````^^^^^^^^^^^^^,,,::;Il!>
bqOJvf)]~iI:,^`'''.........''''''''.......                        ....'''```^^^^^^^^^^^^^,,,,:;;Ili>
kqOJvf)]+iI:,^`''''........'''''''''......                       .....''````^^^^^^^^^^^^,,,,::;Il!i<
kpZCcj([+il;,^``'''.......''''''''''......                       ....'''```^^^^^^,,,,,,,,,,,::;Il!i<
kpZCzr|[_>l;,^``''''.....''''''''''''.....                       ....'''```^^^^,,,,,,,,,,,,::;;Il!><
hdmLzr|}_>l;,^``'''''..''''''''''''''......                      ....'''``^^^^,,,,,,,,,,,,,::;;Ili>~
hdmLXx\}_<!;:^``'''''''''''''''''''''......                      ....''```^^^,,,,,,,,,,,,,:::;Il!i>~
hdwQXx\{-<!I:,^`''''''''''''''''''''''.....                     ....'''```^^,,,,,,,,,,,,,:::;;Il!i<+
abwQYn/{-<!I:,^``'''''''''''''''''''''.....                     ....'''``^^^,,,,,,,,,,,:::::;IIl!><+
abq0Uut1?~iI:,^``''''''''''''''''''''''.....                    ....'''``^^,,,,,:::::::::::;;Il!i>~_
akqOUut1?~iI:,^``''''''''''''''``''''''.....                    ....''```^^,,,::::::::::::;;;Il!i>~_
okqOJvf)]+il;,^```'''''''''''`````'''''.....                    ....''``^^^,,:::::::::::::;;IIl!i<~_
okpZJvf(]+>l;,^^``''''''''''```````''''.....                   ....'''``^^,,,:::::::::::;;;;Ill!><+-
ohpZCcj([+>l;:,^``'''''''''````````'''''....                   ....'''``^^,,::::::::::;;;;;IIl!i>~+-
*hdmCzr|[_>l;:,^```'''''''``````````''''.....                  ....''``^^,,,:::;;;;;;;;;;;IIIl!i>~_?
*hdmLzr|}_<!I:,^```''''''```````````''''.....                  ....''``^^,,:::;;;;;;;;;;;;IIll!i<~_?
*abwQXx\}-<!I:,^^```''''`````````````'''.....                  ....''``^^,,::;;;;;;;;;;;;IIIl!i><+-]
*abwQXx\{-<!I:,^^````''``````````````''''....                 ....'''``^^,:::;;;;;;;;;;IIIIll!i>~+-]
#abw0Yn/{?~iI;,,^`````````````````````'''.....                ....'''`^^,,::;;;;IIIIIIIIIIll!!i<~_?[
#okq0Uut1?~il;:,^`````````````^^^`````'''.....                ....''``^^,,::;;IIIIIIIIIIIIll!i><~_?[
#okqOUut)]+il;:,^^```````````^^^^^````'''.....                ....''``^^,::;;;IIIIIIIIIIIll!!i><+-]}
#okpOJvf)]+>l;:,^^``````````^^^^^^^````'''....               .....''``^,,::;;IIIIIIIIIIllll!ii>~+-]}
MohpZJvf([+>!I:,^^^````````^^^^^^^^^```'''.....              ....'''``^,,:;;IIIIllllllllll!!i><~_-]{
M*hdZCcj([_>!I:,,^^```````^^^^^^^^^^```'''.....              ....'''`^^,::;;IIlllllllllll!!ii><~_?[{
M*hdZCcj|}_<!I;:,^^``````^^^^^^^^^^^```'''.....              ....''``^^,::;IIIllllllllll!!!i>>~+_?[1
M*admLzr|}-<!I;:,^^^````^^^^^^^^^^^^^```'''....              ....''``^^,:;;IIlllll!!!!!!!!ii><~+-]}1
M*abmLXx\}-<il;:,^^^^``^^^^^^^,,,^^^^```'''.....            .....''``^,,:;;Illl!!!!!!!!!!!ii><~_-]})
M#abwQXx\{-~il;:,,^^^^^^^^^^^,,,,,^^^^``'''.....            .....''``^,::;IIll!!!!!!!!!!!ii>><+_?[{)
W#abwQYn/{?~il;:,,^^^^^^^^^^,,,,,,,^^^``'''.....            ....'''`^^,::;Ill!!!!!!!!!!iiii><~+_?[{(
W#okq0Yn/1?+>lI::,^^^^^^^^^,,,,,,,,^^^```''.....            ....'''`^^,:;;Ill!!!iiiiiiiiii>><~+-]}1(
W#okq0Uut1]+>!I;:,,^^^^^^^^,,,,,,,,,^^```'''.....          .....''``^^,:;IIl!!!iiiiiiiiii>><<~_-]}1|
W#okqOUut)]+>!I;:,,^^^^^^^,,,,,,,,,,^^^``'''.....          .....''``^,,:;Ill!!iiiiiiiiii>>><~+_?]})|
WMohpOUvf)[_<!I;:,,,^^^^^,,,,,,,,,,,,^^``'''.....          .....''``^,::;Il!!iiiiiiii>>>>><<~+_?[{)\
WM*hpOJvf([_<!l;::,,^^^^,,,,,,::::,,,^^``'''.....          .....''``^,:;;Il!!iii>>>>>>>>><<~~_-?[{(\
&M*hpZJcj([_<il;::,,,^^,,,,,,:::::,,,^^```''......        .....'''`^^,:;Ill!ii>>>>>>>>>>><<~+_-]}1(/
&M*hdZCcj|}-<ilI;:,,,,,,,,,,:::::::,,^^^``'''.....        .....'''`^^,:;Il!!ii>>>>>>>>><<<~~+_?]}1(/
&M*admCcr|}-~ilI;:,,,,,,,,,::::::::,,,^^``'''.....        .....''``^,,:;Il!ii>>><<<<<<<<<<~++-?]})|t
&M*admLzr|{-~ilI;::,,,,,,,,:::::::::,,^^``'''......      ......''``^,,:;Il!ii>><<<<<<<<<<~~+_-?[{)|t
&W#abmLzr\{?~>!I;::,,,,,,,::::::::::,,^^``'''......      ......''``^,:;;Il!i>><<<<<<<<<<~~++_-][{)\t
&W#abwLXx\{?+>!I;::,,,,,,:::::;;;:::,,^^``'''......      ......''``^,:;Il!!i>><<<<<<<<~~~~+__?]}1(\f
&W#abwQXx/1?+>!l;;::,,,,,::::;;;;;:::,,^^``''.......    ......'''``^,:;Il!ii><<<~~~~~~~~~++_-?]}1(/f
&W#obwQYn/1]+>!lI;:::,,,::::;;;;;;;::,,^^``'''......    ......'''`^^,:;Il!i>><<~~~~~~~~~~++_-?[}1(/j
&W#okwQYn/1]+<ilI;::::::::::;;;;;;;::,,^^``'''.......  .......'''`^^,:;Il!i><<~~~~~~~~~~++__-][{)|/j
&W#okq0Ynt)]_<ilI;:::::::::;;;;;;;;::,,^^``'''................''``^,,:;Il!i><<~~~~++++++++_-?][{)|tj
8WMokq0Uut)[_<ilI;;::::::::;;;;;;;;;::,^^``'''................''``^,,:;l!i>><~~~+++++++++__-?]}{)\tr
8WMokq0Uuf)[_<ilI;;:::::::;;;;;I;;;;::,,^``'''................''``^,:;Il!i><<~~+++++++++___-?]}1(\tr
8&M*kpOUvf([-~i!I;;:::::::;;;;III;;;::,,^``'''................''``^,:;Il!i><~~+++++++++___-??[}1(\fr
8&M*hpOJvf([-~>!lI;;:::::;;;;IIIII;;::,,^^``''...............'''``^,:;Il!i><~~++++________-?][}1(/fx
8&M*hpOJvj(}-~>!lI;;:::::;;;;IIIII;;;:,,^^``'''..............'''``^,:;Il!i><~+++_________--?][{)|/fx
8&M*hpZJvj|}-~>!lI;;::::;;;;IIIIIII;;::,^^``'''..............'''`^^,:;Il!><<~++__________--?]}{)|/jx
8&M*hpZJcj|}-~>!lI;;;::;;;;;IIIIIII;;::,^^``'''..............'''`^^,:;Ili><~~++_________--??[}{)|/jn
8&M*hdZCcj|{?+>!lI;;;;;;;;;IIIIIIII;;::,^^``'''..............'''`^^,:;I!i><~++_________---?][}1)|tjn
8&M*hdZCcr|{?+>ilII;;;;;;;;IIIIIIIII;::,,^``'''..............''``^^,:;l!i><~++___--------??][}1(\trn
8&W*adZCzr\{?+<ilII;;;;;;;IIIIIllIII;;:,,^``'''..............''``^,,:Il!i><~+___---------??][}1(\trn
8&W#admCzr\{?+<ilII;;;;;;;IIIIlllIII;;:,,^``'''..............''``^,:;Il!i><~+__---------??]][{1(\tru
8&W#admLzr\{]+<i!lI;;;;;;;IIIlllllII;;:,,^``'''..............''``^,:;Il!i>~++__---------??][}{1(\fru
8&W#admLzx\1]_<i!lI;;;;;;IIIIlllllII;;:,,^^``''.............'''``^,:;Il!i<~++_---------???][}{)(/fxu
8&W#abmLzx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__----??-?????][}{)|/fxu
8&W#abmLXx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__---????????]][}{)|/fxv
8&W#abmLXx/1]_<i!lII;;;;IIIIlllllllII;::,^^``'''............'''``^,:;Ili><~+_---?????????]][}1)|/jxv
8&W#abwQXx/1]_~>!lII;;;;IIIIlllllllII;::,^^``'''............'''``^,:;Ili><~+_--??????????][[}1)|/jxv
8&W#abwQXn/1]_~>!lIII;;;IIIllllllllII;;:,^^``'''............'''``^,:;Ili><~+_--?????????]][}{1(|tjxv
8&W#obwQXn/)[_~>!lIII;;IIIIllllllllII;;:,^^``'''............'''``^,:;I!i><~+_--?????????]][}{1(\tjnv
88W#obwQXnt)[_~>!llIIIIIIIIllll!llllI;;:,^^``'''............'''`^^,:;I!i><+__-?????????]]][}{1(\tjnv
88W#obwQYnt)[-~>!llIIIIIIIIllll!!lllI;;:,^^``'''............'''`^^,:;I!i>~+__-????????]]]][}{1(\tjnc
%8W#obwQYnt)[-~>illIIIIIIIIlll!!!lllI;;:,,^``'''............'''`^^,:;I!i>~+_--????]]]]]]][[}{1(\tjnc
%8W#obwQYnt)[-~>illIIIIIIIllll!!!lllI;;:,,^``'''............'''`^^,:;l!i>~+_--???]]]]]]]][[}{)(\trnc
%8W#okwQYnt)[-~>i!lIIIIIIIllll!!!!llII;:,,^``'''............'''`^^,:;l!i>~+_--??]]]]]]]]][[}{)(\trnc
%8W#okwQYnt)[-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............'''`^^,:;l!i<~+_--??]]]]]]]]][[}{)(\trnc
%8W#okw0Yut)[-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............'''`^^,:;l!i<~+_-???]]]]]]]]][[}{)(\trnc
%8W#okq0Yut)[-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:;l!i<~+_-???]]]]]]]]][}}1)(\frnc
%8WMokq0Yut)[-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:Il!i<~+_-??]]]]]]]]][[}}1)|\fruc
%8WMokq0Yut([-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|\fruc
%8WMokq0Yut([-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Yut([-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Yut(}-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''...........'''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Yut(}-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''...........'''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Yut(}-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''...........'''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Yut(}-~>i!lIIIIIIllll!!!!!llII;:,,^``'''...........'''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Yut(}-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''...........'''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Yut(}-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''...........'''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Yut([-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''...........'''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Yut([-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Yut([-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Yut([-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|\fruc
%8WMokq0Yut)[-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:Il!i<~+_-??]]]]]]]]][[}}1)|\fruc
%8WMokq0Yut)[-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:;l!i<~+_-??]]]]]]]]]][}}1)|\frnc
%8W#okq0Yut)[-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:;l!i<~+_-???]]]]]]]]][}}{)(\trnc
%8W#okw0Yut)[-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............'''`^^,:;l!i<~+_-???]]]]]]]]][[}{)(\trnc
%8W#okwQYnt)[-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............'''`^^,:;l!i<~+_--??]]]]]]]]][[}{)(\trnc
%8W#okwQYnt)[-~>i!lIIIIIIIllll!!!!llII;:,,^``'''............'''`^^,:;l!i<~+_--??]]]]]]]]][[}{)(\trnc
%8W#okwQYnt)[-~>i!lIIIIIIIllll!!!!llII;:,,^``'''............'''`^^,:;l!i>~+_--??]]]]]]]]][[}{)(\trnc
%8W#obwQYnt)[-~>illIIIIIIIllll!!!lllI;;:,,^``'''............'''`^^,:;l!i>~+_--???]]]]]]]][[}{)(\trnc
%8W#obwQYnt)[-~>illIIIIIIIllll!!!lllI;;:,,^``'''............'''`^^,:;l!i>~+_--???]]]]]]]][[}{1(\tjnc
%8W#obwQYnt)[-~>!llIIIIIIIIlll!!!lllI;;:,,^``'''............'''`^^,:;I!i>~+_--???????]]]][[}{1(\tjnc
88W#obwQYnt)[-~>!llIIIIIIIIlll!!!lllI;;:,,^``'''............'''`^^,:;I!i>~+__-????????]]]][}{1(\tjnc
88W#obwQYnt)[_~>!llIIIIIIIIllll!!lllI;;:,^^``'''............'''`^^,:;I!i><+__-?????????]]][}{1(\tjnc
8&W#obwQXnt)[_~>!llIIIIIIIIllll!llllI;;:,^^``'''............'''`^^,:;I!i><+__-?????????]]][}{1(\tjnv
8&W#obwQXn/)[_~>!lIII;;IIIIlllllllllI;;:,^^``'''............'''``^,:;I!i><~+_-?????????]]][}{1(\tjnv
8&W#obwQXn/)[_~>!lIII;;IIIIllllllllII;;:,^^``'''............'''``^,:;I!i><~+_--?????????]][}{1(\tjnv
8&W#obwQXn/)[_~>!lIII;;IIIIllllllllII;;:,^^``'''............'''``^,:;I!i><~+_--?????????]][}{1(|tjnv
8&W#abwQXn/1]_~>!lIII;;;IIIllllllllII;;:,^^``'''............'''``^,:;Ili><~+_--?????????]][}{1(|tjxv
8&W#abwQXn/1]_~>!lIII;;;IIIllllllllII;::,^^``'''............'''``^,:;Ili><~+_--?????????]][[{1)|/jxv
8&W#abwQXx/1]_~>!lII;;;;IIIIlllllllII;::,^^``'''............'''``^,:;Ili><~+_--?????????]][[}1)|/jxv
8&W#abwQXx/1]_~>!lII;;;;IIIIlllllllII;::,^^``'''............'''``^,:;Ili><~+_--??????????][[}1)|/jxv
8&W#abwLXx/1]_<>!lII;;;;IIIIlllllllII;::,^^``'''............'''``^,:;Ili><~+_---?????????]][}1)|/jxv
8&W#abmLXx/1]_<i!lII;;;;IIIIlllllllII;::,^^``'''............'''``^,:;Ili><~+_---?????????]][}1)|/jxv
8&W#abmLXx/1]_<i!lII;;;;IIIIlllllllII;::,^^``'''............'''``^,:;Ili><~+__--?????????]][}1)|/fxv
8&W#abmLXx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__--?????????]][}1)|/fxv
8&W#abmLXx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__---????????]][}{)|/fxv
8&W#abmLXx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__---????????]][}{)|/fxv
8&W#abmLXx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__---????????]][}{)|/fxu
8&W#abmLXx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__----???????]][}{)|/fxu
8&W#abmLXx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__----????????][}{)|/fxu
8&W#abmLzx/1]_<i!lII;;;;;IIIIlllllIII;::,^^``'''............'''``^,:;Il!><~+__--------????][}{)|/fxu
8&W#abmLzx\1]_<i!lII;;;;;IIIIlllllIII;::,^^``'''............'''``^,:;Il!><~+__--------????][}{)|/fxu
8&W#abmLzx\1]_<i!lII;;;;;IIIIlllllIII;::,^^``''.............'''``^,:;Il!><~+__--------????][}{)|/fxu
8&W#abmLzx\1]_<i!lII;;;;;IIIIlllllIII;::,^^``''.............'''``^,:;Il!><~+__--------????][}{)|/fxu
8&W#abmLzx\1]_<i!lII;;;;;IIIIlllllIII;::,^^``''.............'''``^,:;Il!><~+__--------????][}{)|/fxu
8&W#abmLzx\1]_<i!lII;;;;;IIIIlllllIII;::,^^``''.............'''``^,:;Il!><~+__--------????][}{)|/fxu
8&W#abmLzx\1]_<i!lII;;;;;IIIIlllllIII;::,^^``''.............'''``^,:;Il!><~+__--------????][}{)|/fxu
8&W#abmLzx\1]_<i!lII;;;;;IIIIlllllIII;::,^^``'''............'''``^,:;Il!><~+__--------????][}{)|/fxu
8&W#abmLzx/1]_<i!lII;;;;;IIIIlllllIII;::,^^``'''............'''``^,:;Il!><~+__--------????][}{)|/fxu
8&W#abmLzx/1]_<i!lII;;;;;IIIllllllIII;::,^^``'''............'''``^,:;Il!><~+__----??-?????][}{)|/fxu
8&W#abmLXx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__----???????]][}{)|/fxu
8&W#abmLXx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__---????????]][}{)|/fxu
8&W#abmLXx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__---????????]][}{)|/fxv
8&W#abmLXx/1]_<i!lII;;;;;IIIlllllllII;::,^^``'''............'''``^,:;Il!><~+__--?????????]][}{)|/fxv
8&W#abmLXx/1]_<i!lII;;;;IIIIlllllllII;::,^^``'''............'''``^,:;Ili><~+__--?????????]][}1)|/fxv
8&W#abmLXx/1]_<i!lII;;;;IIIIlllllllII;::,^^``'''............'''``^,:;Ili><~+_---?????????]][}1)|/jxv
8&W#abwQXx/1]_<>!lII;;;;IIIIlllllllII;::,^^``'''............'''``^,:;Ili><~+_---?????????]][}1)|/jxv
8&W#abwQXx/1]_~>!lII;;;;IIIIlllllllII;::,^^``'''............'''``^,:;Ili><~+_--?????????]][[}1)|/jxv
8&W#abwQXn/1]_~>!lIII;;;IIIllllllllII;;:,^^``'''............'''``^,:;Ili><~+_--?????????]][}{1(|/jxv
8&W#obwQXn/)[_~>!lIII;;IIIIllllllllII;;:,^^``'''............'''``^,:;I!i><~+_--?????????]][}{1(|tjnv
8&W#obwQXn/)[_~>!lIIII;IIIIlllllllllI;;:,^^``'''............'''``^,:;I!i><++_-?????????]]][}{1(\tjnv
88W#obwQYnt)[-~>!llIIIIIIIIllll!!lllI;;:,^^``'''............'''`^^,:;I!i><+__-?????????]]][}{1(\tjnc
%8W#obwQYnt)[-~>illIIIIIIIIlll!!!lllI;;:,,^``'''............'''`^^,:;I!i>~+_--????]]]]]]][[}{1(\tjnc
%8W#okwQYnt)[-~>illIIIIIIIllll!!!!llII;:,,^``'''............'''`^^,:;l!i>~+_--???]]]]]]]][[}{)(\trnc
%8W#okw0Ynt)[-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............'''`^^,:;l!i<~+_-???]]]]]]]]][[}{)(\trnc
%8WMokq0Yut([-~>i!lIIIIIIIlll!!!!!llII;:,,^``'''............''``^^,:Il!i<~+_-??]]]]]]]]][[}{1)|\fruc
%8WMokq0Yuf(}-+>i!lIIIIIIllll!!!!!llII;:,,^``''''..........'''``^,,:Il!><~+_-??]]]]]]]]][[}{1)|/fruc
%8WMokq0Uuf(}-+<i!llIIIIIlll!!!!!!!llI;::,^``''''..........'''``^,,;Il!><~+_-?]]]]]]]]][[[}{1)|/fruz
%8&Mokq0Uuf(}?+<i!llIIIIIlll!!!!!!!llI;::,^^``'''..........'''``^,:;Il!><~_--?]]]][[][[[[}}{1(|/fxuz
%8&Mokq0Uvf(}?+<i!llIIIIlll!!!!!!!!llI;::,^^``'''..........'''``^,:;Ili><+_-??]][[[[[[[[[}}{1(|/fxuz
%8&M*kqOUvf|}?+<i!lllIIIlll!!!!i!!!llI;;:,^^``'''..........'''``^,:;Ili><+_-?]][[[[[[[[[}}{1)(\tjxvz
%8&M*hpOJvj|{?+<>!!llIIllll!!!iii!!!lII;:,^^``'''..........'''``^,:;Ili>~+_-?]][[[[[[[[[}}{1)(\tjxvX
%8&M*hpOJvj|{?_<>i!lllllll!!!iiiii!!lII;:,^^``'''..........'''``^,:;I!i>~+_-?][[[[[[[[[}}}{1)|\tjnvX
%8&M*hpOJcj|{]_~>i!lllllll!!!iiiii!!llI;:,,^``'''..........'''``^,:;I!i<~+-?]][[[}}}}}}}}{{1)|\trncX
%8&M*hpZJcr\{]_~>i!llllll!!!iiiiiii!llI;:,,^``''''........''''`^^,:;l!i<~_-?][[[}}}}}}}}}{1)(|/frncX
%8&M*hpZCcr\1]_~>i!!lllll!!!iiiiiii!!lI;:,,^``''''........'''``^^,:;l!i<~_-?][[}}}}}}}}}{{1)(|/frucY
%8&W*hdZCzr\1]_~<i!!llll!!!iiii>iii!!lI;::,^``''''........'''``^^,:Il!><+_-?][}}}}}}}}{{{11)(\/fxucY
%8&W*adZCzx/1[-~<ii!!lll!!!iii>>>iii!lI;;:,^^``'''........'''``^,,:Il!><+_?][[}}{{{{{{{{{1))|\tjxuzY
%8&W#admLzx/)[-+<>i!!!!!!!iii>>>>>ii!lII;:,^^``''''......''''``^,:;Ili>~+-?][}}{{{{{{{{{11)(|\tjxvzU
%8&W#admLXx/)[-+<>i!!!!!!!ii>>>>>>>i!llI;:,^^``''''......''''``^,:;Ili>~+-?][}{{{{{{{{{111)(|/tjnvzU
%8&W#abmLXnt)}?+<>i!!!!!!iii>>>>>>>i!!lI;:,^^``''''......''''``^,:;Ili<~_-?[[}{{{11111111)((\/frnvXU
%%8W#abwQXnt(}?+~>ii!!!!!ii>>><<<>>ii!lI;:,,^``''''......''''``^,:;I!i<~_-][}{{111111111))(|\/frncXJ
%%8W#obwQYnt(}?_~<>ii!!!iii>><<<<<>>i!lI;:,,^``'''''....''''``^^,:;I!i<+_?][}{111111111))((|\tjrucYJ
%%8W#obwQYuf({?_~<>iiiiiii>>><<<<<>>i!lI;::,^```''''....''''``^^,:;l!><+_?]}{{11)))))))))(|\/tjxucYC
%%8WMokq0Uuf|{]_~<>iiiiiii>><<<<<<<>ii!lI;:,^^``'''''..'''''``^^,:Il!>~+-?[}{11)))))))))((|\/fjxvzYC
%%8&Mokq0Uvj|{]-+<>>iiiii>><<<~~~<<>>i!lI;:,^^``''''''''''''``^,,:Ili>~_-][}{1))))(((((((||\tfrnvzUC
B%8&Mokq0Uvj\1[-+~<>iiii>>><<~~~~~<<>i!lI;:,^^``''''''''''''``^,:;Ili>~_-][{11))((((((((||\/tfrnvXUL
B%8&M*kqOJcr\1[-+~<>>>>>>><<~~~~~~~<>i!lI;:,,^``''''''''''''``^,:;Ili<~_?]}{1))((((((((||\\/tjxucXJL
B%8&M*hpOJcr\)[?_~<>>>>>><<<~~~++~~<>>!lI;:,,^```''''''''''```^,:;I!i<+_?[}{1)((|||||||||\/tfjxucYJQ
B%8&M*hpZCcr/)}?_+<<>>>>><<~~+++++~~<>i!lI;:,^^``''''''''''``^^,:;I!><+-][{1)((||||||||\\\/tfrnvzYJQ
B%8&M*hpZCzx/)}?_+~<<>>><<~~~+++++~~<>i!lI;:,^^``''''''''''``^^,:;l!>~+-]}{1)(||\\\\\\\\\/tfjrnvzUCQ
B%8&W*hdZLzxt({]-+~<<<<<<<~~+++__++~<>i!lI;:,^^``''''''''''``^,,:Il!>~_?]}{)(||\\\\\\\\\//tfjxucXUC0
B%8&W#admLXnt({]-_~~<<<<<~~++_____++~<>!lI;:,^^```''''''''```^,:;Ili>~_?[}1)(|\\\////////tfjrxucXUL0
B%%&W#admLXnf|{[?_+~~<<<~~++_______+~<>i!I;:,,^```''''''''```^,:;Ili<+-?[{1(|\\/////////ttfjrnvzYJLO
B%%8W#abwQYuf|1[?_+~~~~~~~++__---__+~<>i!l;::,^^``''''''''``^^,:;I!i<+-]}{)(|\///ttttttttfjrxnvzYJQO
B%%8W#obwQYuj\1}?-_+~~~~~++__-----__+~<i!lI;:,^^```''''''```^^,:;I!><+-]}1)|\//tttttttttffjrxucXUCQZ
BB%8W#obw0Uvj\)}]-_++~~+++__---?---_+~<>!lI;:,^^```''''''```^^,:;l!>~_?[{1(|\/tttffffffffjrxnucXUC0Z
BB%8&Mokq0Ucr/){]?_++++++__--?????-_+~<>ilI;:,,^````''''````^,,:Ili>~_?[{)(\/ttffffffffjjjrxnvzYJL0Z
BB%8&MokqOJcx/({[?-_++++__--???????-_+~>i!I;:,,^^````''````^^,:;Ili<+-]}1)|\/tffjjjjjjjjjrxnuvzYJLOm
BB%8&M*kpOJzxt(1[?-___+___--??]]]??-_+~<i!lI::,^^``````````^^,:;I!i<+-]}1(|/tffjjjjjjjjrrxxnvcXUCQOm
BB%8&M*hpZCznf|1}]?-_____--??]]]]]??-_~<>!lI;:,^^``````````^^,:;I!i<+-[{)(\/tfjjrrrrrrrrxxnuvzXUCQZw
BB%8&M*hpZLXnf\)}]?--__---??]][[[]]?-_+<>ilI;:,,^^````````^^,,:;l!>~_?[{)|\tfjrrrrrrrxxxxnnuczYJL0Zw
BB%8&W*hdmLXuj\){[]?-----??]][[[[[]]?_+~>i!I;:,,^^````````^^,,:Il!>~_?}1(|/tjjrxxxxxxxxxnnuvcXYJL0mq
BB%%&W#admQYuj/({[]??---??]][[}}}[[]?-_~<i!l;::,^^````````^^,:;Ili<+-]}1(\tfjrxxxnnnnnnnnuvczXUCQOmq
BB%%8W#abwQYvr/(1}[]?????]][[}}}}}[[]-_+<>!lI;:,^^^``````^^^,:;Ili<+-]{)|/tjrxxnnnnnnnnuuvvczYJCQOmp
BBB%8W#abw0Ucrt|1}[]????]][[}}{{{}}[]?_+<>!lI;:,,^^``````^^,,:;I!i<+?[{)|/fjrxnnuuuuuuuuvvczXYJL0Zwp
BBB%8W#obq0Jcxt|){}[]]]]][[}}{{{{{}}[?-+~>ilI;:,,^^^````^^^,,:;l!>~_?[1(\tfrxnuuuuuuuuvvvcczYUCL0Zwp
BBB%8WMokqOJznf\)1}[]]]][[}}{{1111{}[]-_~<i!I;::,^^^^``^^^^,:;Il!>~_]}1(\tjrnnuvvvvvvvvvcczXYJCQOmqd
@BB%8&MokqOCznj/(1{}[[[[[}}{111)111{}]?_+<i!lI;:,,^^^^^^^^,,:;Ili<+-]})|/frxnuvvccccccccczXYUJL0Omqd
@BB%8&M*hpZCXuj/|){}}[[[}}{11)))))1{}[?-+<>!lI;:,,^^^^^^^^,,:;Ili<+-[{)\tjrnuvvcccccccczzXXYUCL0Zwpb
@BB%8&M*hpZLYvrt|)1{}}}}}{{1))((())1{[]-_~>ilI;::,,^^^^^^,,::;I!i<+?[{(\tjxnuvcczzzzzzzzXXYUJCQOZwpb
@BB%8&M*hdmQYvxt\(1{{}}{{{1))((((()1{}]?_~<i!I;::,,^^^^^^,,:;Il!>~_?}1|/frnuvczzzXXXXXXXXYUUCL0Omqdb
@BB%8&W*admQUcxf\()1{{{{{1))((|||(()1}[?_+<i!lI;:,,,^^^^,,,:;Il!>~_]})|/jxnvczzXXXXXXXXYYYUJCQ0Zwqdk
@BB%%&W#abw0Ucnj/|(11{{11))((|||||((1{[]-+<>!lI;::,,,^^^,,::;Ili<+-]{)\tjxuvczXXYYYYYYYYYUJCLQOZwpbk
@BBB%8W#abw0Jznjt\()1111))((|\\\\\|()1}]-_~>ilI;::,,,,,,,,::;I!i<+-[{(\frnuczXYYYYYYYYUUUJJCL0Omwpbh
@BBB%8W#obqOCXurt\|()))))((|\\///\\|(1{[?_~<i!I;;:,,,,,,,,:;Il!><_?[1(/fxnvzXYYUUUUUUUUUJJCLQ0Zmqdbh
@@BB%8W#okqOCXvxf/|(()))((|\\/////\|(){[]-+<i!lI;::,,,,,,::;Il!>~_?}1|tjxuczXYUUUJJJJJJJJCLL0OZwqdkh
@@BB%8&MokpZLYvxjt\|(((((|\\//tttt/\|)1}]-+<>!lI;:::,,,,:::;Ili>~_]})\trnvcXYUUJJJJJJJJCCCLQ0Omwpbka
@@BB%8&M*hpZLUcnjt/||((||\\/tttfftt/|(1{[?_~>ilI;;::,,,,::;;I!i<+-]{(\frnvzXUUJJCCCCCCCCLLQ0OZmqpbha
@@BB%8&M*hdmQUzurf/\||||\\/ttffffft/\|){[?_~<i!lI;::::::::;Il!i<+-[1(/jxucXYUJCCCCLLLLLLLQQ0OZwqdbha
@@BB%8&M*hdm0Jzuxjt/\\\\\/ttffjjjjft/|(1}]-+<i!lI;;::::::;;Il!>~_?}1|tjnvzXUJCCLLLLLLLLLQQ0OZmwpdkho
@@BB%8&W*abw0JXvxjf//\\//ttfjjjrrjjf/\(1}]-+<>!lI;;::::::;;Ili>~_]})\trnvzYUJCLLQQQQQQQQQ00OZmqpbkao
@@BB%%&W#abwOCYcnrft////ttfjjrrrrrjft/|){[?_~>i!lI;;::::;;Il!i<+-]{)\fxucXUJCLLQQQQQQQQ000OZmwqdbhao
@@BBB%8W#abqOLYcurjftttttfjjrrxxxxrjf/|){[?_~<i!lI;;;::;;;Il!i<+-[{(/jxvzYUCLLQQ000000000OZZmwpdkha*
@@@BB%8W#okqZLUzuxrffttffjjrxxxnnxxrft\(1}]-+<>!lII;;;;;;IIl!><+?[1|/jnvzYJCLQ00000000OOOOZmwqpbkho*
@@@BB%8W#okpZQJXvnrjffffjjrxxnnnnnxrjt/|)}]-+<>i!lI;;;;;;Il!i>~_?}1|trucXUCLQ00OOOOOOOOOZZmmwqdbkao*
@@@BB%8&MohpmQJXcnxrjjjjjrxxnnuuunnxrf/|){[?_~>i!lII;;;;IIl!i<~_]})\fxuzYJCLQ0OOOZZZZZZZZmmwqpdbhao*
@@@BB%8&M*hdm0CYcuxrrjjjrxxnuuuvuuunrjt\(1[?_~<i!llII;;IIll!i<+-]{(/fxvzYJLQ0OOZZZZZZZZZmmwwqpbkha*#
@@@BB%8&M*hdwOCYzvnxrrrrxxnuuvvvvvunxjf/(1}]-+<>i!lIIIIIIl!i><+-[{(/jnvXUCL0OOZZZmmmmmmmmwwqpdbkho*#
@@@BB%8&M*abwOLUXvunxxxxxnuuvvcccvvunrf/|){]-+~>i!llIIIIll!i>~_?[1|trucXJCQ0OZZmmmmmmmmmwwqqpdbhao*#
@@@BB%8&W#abqZQJXcunnxxxnnuvvcczccvvnxjt\){[?_~<i!lllIIlll!i<~_?})\truzYJLQOZZmmmwwwwwwwwqqpdbkhao*M
@@@BB%%&W#akqZQJYzvunnnnuuvvczzzzzcvuxrf\(1[?_~<>i!llllll!i><+-]{)\fxvzUCQ0OZmmwwwwwwwwwqqppdbkha*#M
@@@BB%%8W#okpm0CYzcvunnuuvvczzXXXzzcvnrf/|1}]-+<>i!!llll!!i>~+-[{(/jnvXUCQOZmmwwwqqqqqqqqppdbkhao*#M
@@@@BB%8W#okpm0CUXcvuuuuvvczzXXXXXzcvuxjt|)}]-+~>i!!llll!!i>~_?[1(/jncYJL0OZmwwqqqqqqqqqppddbkhao*#M
@@@@BB%8WMohdwOLJYzcvvvvvczzXYYYYYXzcuxjt\){[?_~<>i!!!!!!i><~_?}1|truzYCQ0Zmwwqqqpppppppppdbbkhao*#M
@@@@BB%8&M*hdwOQJYXccvvcczzXYYYUUYYXcvnrf\(1[?_+<>ii!!!!ii><+-]})\fxvzUCQOZmwqqppppppppppddbkhao*#MW
@@@@BB%8&M*hbqZQCUXzcccczzXYYUUUUUYXzcuxf/|1}]-+~>>i!!!!i>>~+-]{)\fxvXUL0Omwqqppppppppddddbbkhao*#MW
@@@@BB%8&M*abqZ0CUYXzzzzzXYYUUJJJUUYXcuxjt|)}]-_~<>iiiiii><~_?[{(/jncYJL0Zmwqppddddddddddbbkhhao*#MW
@@@@BB%8&M*abpm0LJYXXzzzXXYUUJJJJJUYXzvnrt\){[?_~<>>iiii>><+_?[1|/rucYCQOZwqppdddddddddbbbkkhao*##MW
@@@@BB%8&W#akpmOLCUYXXXXYYUUJJCCCCJUYzcurf\(1[?_+~<>iiii><~+-]}1|truzUCQOmwqpdddbbbbbbbbbbkhhao*#MWW
@@@@BB%8&W#okpwOQCJYYXXYYUUJCCCLCCCJYXcuxf/(1}]-+~<>>>>>><~+-]})\fxvXUL0Zmqppddbbbbbbbbbkkkhaao*#MW&
@@@@BB%%&W#okdwZ0LJUYYYYUUJCCLLLLLCJUYzvnjt|)}]-_~<<>>>><<~_?[{)\fxvXJL0Zwqpddbbbbbbbbkkkkhhaoo*#MW&
@@@@@B%%8W#ohdqZ0LCJUUUUUJJCLLLQQLLCJYzvnrt\){[?_+~<<>><<~+_?[{(/jncYJQOmwqpdbbkkkkkkkkkkhhaao*##MW&
@@@@@BB%8WMohbqmOQCJUUUUJJCLLQQQQQLCJUXcurf\({[?-+~<<<<<<~+-?}1|/juzYCQOmqpdbbkkkkkkkkkkhhhaao*#MMW&
@@@@@BB%8WM*hbpmOQLCJJJJJCLLQQQ00QQLCUYzuxf/(1}]-_+~<<<<~+_-]}1|truzUL0Zwqpdbkkkkkhhhhhhhhaaoo*#MWW&
@@@@@BB%8&M*abpwZ0LCCJJJCCLQQ00000QLCJYzvxj/|1}]?_+~~<<~~+_?]{)\fxvXUL0Zwpdbbkkhhhhhhhhhhaaao**#MW&&
@@@@@BB%8&M*akpwZ0QLCCCCCLQQ000OO00QLJUXvnjt|){[?-++~~~~++-?[{)\fxvXJQOmqpdbkkhhhhhhhhhhaaaoo*##MW&&
@@@@@BB%8&M*akdqZOQLLCCCLLQ00OOOOO0QLCUXcurt\){[?-_+~~~~+_-?[1(/jncYCQOmqpdbkhhhhhhhhhaaaaoo**#MMW&8
@@@@@BB%8&W#okdqmO0QLLLLLQ00OOOZOOO0QCJYcuxf\(1}]-_++++++_-]}1(/jncYC0Zwqdbkkhhhaaaaaaaaaaoo**#MWW&8
@@@@@BB%8&W#ohdqmZ0QQLLLQQ0OOZZZZZO0QLJYzvxf/(1}]?-_++++_-?]}1|truzUL0Zwpdbkhhaaaaaaaaaaaoo**##MWW&8
@@@@@BB%8&W#ohbpwZO0QQQQQ00OZZZZZZZO0LCUXvnj/|){[?-__++__-?[{)\truzUL0mqpdbkhhaaaaaaaaaaooo**#MMW&&8
@@@@@BB%%&W#ohbpwZO0QQQQ00OOZZmmmZZO0QCUXcnrt|){[]--____--][{)\fxvXJLOmqpbkhhaaaaooooooooo**##MMW&&8
@@@@@BB%%8WM*abpqmZO00000OOZZmmmmmZZOQLJYcurt\({}]?-____-?]}1(/fxvXJQOmqdbkhaaaooooooooooo**##MWW&88
@@@@@@B%%8WM*akdqmZO0000OOZZmmwwwmmZO0LJYzuxf\(1}[?--__--?[}1(/jncYCQZwpdbkhaaooooooooooo***##MWW&88
@@@@@@BB%8WM*akdqwZOO00OOZZmmwwwwwmZO0QCYzvxf/|1}[]?----?][{)|/jncYC0Zwpdkhhaooooooooooo***##MMW&&88
@@@@@@BB%8&M*akdpwmZOOOOOZmmwwwwwwwmZOQCUXvxj/|){[]?----?][{)|truzUL0mqpbkhaaoooo**********##MMW&&88
@@@@@@BB%8&M*ohbpwmZZOOOZZmmwwqqqwwmZOQLUXcnjt|){}]??--??]}{)\truzULOmqdbkhaooo***********###MWW&&88
@@@@@@BB%8&M#ohbpqmmZZZZZmmwwqqqqqwwmO0LJYcnrt\(1}[]????][}1(\fxvXJLOmqdbhhaoo************##MMWW&&88
@@@@@@BB%8&W#ohbdqwmZZZZmmwwqqqqqqqwmZ0LJYcurf\(1{[]]??]][{1(/fxvXJQOwpdkhaaoo***********###MMWW&88%
@@@@@@BB%8&W#ohkdqwmmZZmmmwwqqpppqqwmZOQCYzuxf/(){}[]]]][}{)|/jncYJQZwpbkhaoo***********###MMMW&&88%
@@@@@@BB%8&W#oakdpwwmmmmmwwqqpppppqqwZOQCUzvxj/|){}[]]]][}{)|tjncYC0Zwpbkhaoo*****#########MMWW&&88%
@@@@@@BB%8&W#*akdpqwmmmmwwqqpppppppqwmOQCUXvnjt|)1}[[]][[}1)|trncYC0Zqpbkhao****###########MMWW&&88%
@@@@@@BB%8&WM*akbpqwwmmwwwqqpppddppqwmZ0LJXcnjt\(1{}[[[[}{1(\truzUL0mqdbhaoo***###########MMMWW&&88%
@@@@@@BB%8&WM*ahbdqqwwwwwqqpppddddpqqmZ0LJYcnrt\(1{}[[[[}{1(\fruzULOmqdkhaoo**############MMWWW&&88%
@@@@@@BB%%8WM*ahbdpqwwwwqqqppdddddppqwZ0QJYcurf\(){}}[[}}{)|/fxvXJLOmqdkhao**############MMMWW&&88%%
@@@@@@BB%%8WM*ohbdpqqwwwqqppdddddddpqwmOQCYzuxf/|)1{}}}}{1)|/fxvXJQOwpbkhao**###########MMMMWW&&88%%
@@@@@@BB%%8WM*ohkdpqqqqqqqppdddbbddpqwmOQCUzuxf/|)1{}}}}{1)|/jxvXJQZwpbkhao**##########MMMMMWW&&88%%
@@@@@@BB%%8&M#ohkbppqqqqqppdddbbbbdppwmOQCUzvxj/|(1{{}}}{1(\tjncYCQZwpbkaoo*#####MMMMMMMMMMWWW&&88%%
@@@@@@@BB%8&M#oakbdpqqqqpppddbbbbbddpqmZ0LUXvnjt\()1{}}{{)(\tjncYC0Zwpbhao**####MMMMMMMMMMMWWW&&88%%
@@@@@@@BB%8&M#oakbdppqqqppddbbbbbbbdpqwZ0LJXvnjt\()1{{{{1)(\trncYC0Zqdbhao**###MMMMMMMMMMMMWW&&&88%%
@@@@@@@BB%8&M#oakbdpppqpppddbbbbbbbdpqwZ0LJXcnrt\|)1{{{{1)|\fruzUC0mqdkhao**##MMMMMMMMMMMMWWW&&888%%
Mode: Plasma  |  size 100x300  |  partials: 24  |  Press [4] in menu to stop.
```

</details>
