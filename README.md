# Arduboy-Dharma-Tally-Counter
Tally counter for Arduboy compatible platform with dharmic bias.

Version 1.7

Controls:<br>
[A] - increase counter<br>
[B] - decrease counter<br>
[B] (long press) - reset counter to 0<br>
[UP] - switch audio ON/OFF<br>
[DOWN] - increase counter<br>
[LEFT] - previous mode<br>
[RIGHT] - next mode

The first three modes (7, 21 and 108) always start at 0.<br>
The ten tally counter modes store the current counter value in the EEPROM. Maximum counting value for the tally counting modes is 999999.<br>
In the 'Titles.h' file, you can add titles for the tally counter modes. Changing the title and reuploading of the program do not change the stored counter value!
In 'DharmaCounter.h' by changing the value of SCREEN_MAX_TIME in milliseconds, you can add the display auto-turn off functionality for energy saving purposes.

<a href="https://felipemanga.github.io/ProjectABE/?url=https://github.com/Thabke/Arduboy-Dharma-Tally-Counter/raw/main/DharmaCounter/DharmaCounter.hex">Look in the emulator</a>

Some screenshots:<br>
<img src="https://github.com/Thabke/Arduboy-Dharma-Tally-Counter/raw/main/Screenshots/mode7.png" alt="Mode 7 counts" width="128" height="64">
<img src="https://github.com/Thabke/Arduboy-Dharma-Tally-Counter/raw/main/Screenshots/mode21.png" alt="Mode 21 counts" width="128" height="64">
<img src="https://github.com/Thabke/Arduboy-Dharma-Tally-Counter/raw/main/Screenshots/mode108.png" alt="Mode mala 108 counts (beads)" width="128" height="64">
<img src="https://github.com/Thabke/Arduboy-Dharma-Tally-Counter/raw/main/Screenshots/tally1.png" alt="Tally counter" width="128" height="64">
<img src="https://github.com/Thabke/Arduboy-Dharma-Tally-Counter/raw/main/Screenshots/tally2.png" alt="Tally counter with user custom title" width="128" height="64">
<img src="https://github.com/Thabke/Arduboy-Dharma-Tally-Counter/raw/main/Screenshots/tally3.png" alt="Tally counter with user custom title" width="128" height="64">
