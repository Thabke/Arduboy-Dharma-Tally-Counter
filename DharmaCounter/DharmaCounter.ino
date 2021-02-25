//
//Lobsang Thabke
//November 25/02/2021
//Dharma Counter for ArduBoy
//Ver. 1.6
//
//--- Controls:
//[A] - increase counter
//[B] - decrease counter
//[B] (long press) - reset counter to 0
//[UP] - switch audio ON/OFF
//[DOWN] - increase counter
//[LEFT] - previous mode
//[RIGHT] - next mode
//---
//The first three modes (7, 21 and 108) always start at 0.
//The ten tally counter modes store the current counter value in the EEPROM.
//Maximum counting value for the tally counting modes is 999999.
//In the 'Titles.h' file, you can add titles for the tally counter modes.
//
#include <EEPROM.h>
#include <Arduboy2.h>
#include <ArduboyTones.h>
#include "DharmaCounter.h"
#include "Titles.h"

ArduboyTones sound(arduboy.audio.enabled);  //Add audio

//Draw the vishva vajra for mode 7
void mode7Draw ()
{
  unsigned char* vvjr;

  if (counter == 7)
  {
    vvjr = vishvaBld;
    //Draw a title to end counting in the upper right corner of the screen
    Sprites::drawOverwrite(96, 9, mode7end, 0);
  }
  else
  {
    vvjr = vishva;
    //Draw the name "MODE 7" in the upper right corner of the screen
    Sprites::drawOverwrite(96, 9, mode7, 0);
  }

  if (counter > 0) //if current counter value 1 or more
  {
    //Draw the vishva vajra sprites
    for (int x = 1; x <= counter; x++) {
      if (x <= 4)
        Sprites::drawOverwrite((x - 1) * 24, 8, vvjr, 0);
      else
        Sprites::drawOverwrite(((x - 5) * 24) + 11, 40, vvjr, 0);
    }
  }
  else //counter == 0
  {
    //Draw the name "MODE 7" in the centre of the screen
    arduboy.setTextSize (2); //Double text size
    arduboy.setCursor(11, 21); //Put mode name in the centre of the screen
    arduboy.print("MODE 7");
    arduboy.setTextSize (1); //Return to normal text size
    //Draw "PRESS [A]"
    Sprites::drawOverwrite(30, 42, press_A, 0);
  }
}

//Draw the single vajra for mode 21
void mode21Draw ()
{
  unsigned char* vjr;

  if (counter == 21)
  {
    vjr = vajraBld;
    //Draw a title to end counting in the upper right corner of the screen
    Sprites::drawOverwrite(96, 9, mode21end, 0);
  }
  else
  {
    vjr = vajra;
    //Draw the name "MODE 21" in the upper right corner of the screen
    Sprites::drawOverwrite(96, 9, mode21, 0);
  }

  if (counter > 0) //if current counter value 1 or more
  {
    //Draw vajra sprites
    for (int x = 1; x <= counter; x++) {
      if (x <= 8)
        Sprites::drawOverwrite((x - 1) * 12, 1, vjr, 0); //first row
      else
      {
        if  (x <= 15)
          Sprites::drawOverwrite((x - 9) * 12 + 6, 21, vjr, 0); //second row
        else
          Sprites::drawOverwrite((x - 16) * 12 + 12, 41, vjr, 0);  //third row
      }
    }
  }
  else //counter == 0
  {
    //Draw the name "MODE 21" in the centre of the screen
    arduboy.setTextSize (2);  //Double text size
    arduboy.setCursor(5, 21); //Put mode name in the centre of the screen
    arduboy.print("MODE 21");
    arduboy.setTextSize (1);  //Return to normal text size
    //Draw "PRESS [A]"
    Sprites::drawOverwrite(30, 42, press_A, 0);
  }
}

//Draw numbers for mode 108
void mode108Draw ()
{
  String cnt;     //Counter value in text
  String digit;   //Different digits from the counter number
  int digits = 0; //length of the counter number
  int y = 9;      //Screen position

  //Draw mala
  Sprites::drawOverwrite(0, 0, mala108empty, 0);

  if (counter == 108)
  {
    //Draw a title to end counting in the upper right corner of the screen
    Sprites::drawOverwrite(96, 9, mode108end, 0);
    //Draw the big bead
    Sprites::drawOverwrite(16, 30, big_bead, 0);
  }
  else
  {
    //Draw the name "MODE 108" in the upper right corner of the screen
    Sprites::drawOverwrite(96, 9, mode108, 0);
  }

  //    if (counter < 5) counter = 105; //for testing purposes

  if (counter > 0)
  {
    cnt = String (counter); //Convert digits of the counter to text
    digits = cnt.length();  //Find the length of the counter numbers
  }
  else //counter == 0
  {
    //Draw the name "MODE 108" in the centre of the screen
    arduboy.setCursor(25, 22); //Put mode name in the centre of the screen
    arduboy.print("MODE 108");
    //Draw "PRESS [A]"
    Sprites::drawOverwrite(32, 36, press_A, 0);
  }

  switch (digits) {
    case 1: //Only one digit
      digit = cnt[0];
      Sprites::drawOverwrite(41, y + 12, numbers6dgt, digit.toInt());
      break;
    case 2: //Two digits
      //First digit in the counter
      digit = cnt[0];
      Sprites::drawOverwrite(33, y + 12, numbers6dgt, digit.toInt());
      //Second digit in the counter
      digit = cnt[1];
      Sprites::drawOverwrite(48, y + 12, numbers6dgt, digit.toInt());
      break;
    case 3: //Three digits
      //First digit in the counter
      digit = cnt[0];
      Sprites::drawOverwrite(24, y + 12, numbers6dgt, digit.toInt());
      //Second digit in the counter
      digit = cnt[1];
      Sprites::drawOverwrite(39, y + 12, numbers6dgt, digit.toInt());
      //Third digit in the counter
      digit = cnt[2];
      Sprites::drawOverwrite(54, y + 12, numbers6dgt, digit.toInt());
      break;
    default:
      // statements
      break;
  }

  //Draw beads
  if (counter < 108)
  {
    for (int i = 0; i < counter; i++)
      Sprites::drawExternalMask(beadsX[i], beadsY[i], bead, bead_mask, 0, 0);     //Draw beads, new for each count
  }
  else //counter == 108
  {
    for (int i = 0; i < counter; i++)
      Sprites::drawExternalMask(beadsX[i], beadsY[i], beadBld, bead_mask, 0, 0);  //Draw bold beads
  }
}

//Draw numbers for the tally counter modes
void modeTallyDraw (String title)
{
  String cnt;     //Counter value in text
  String digit;   //Different digits from the counter number
  int digits = 0; //length of the counter number
  int y = 9;      //Counting numbers screen position

  //if (counter < 10000) counter = 98990; //for testing purposes

  if (counter > 0)
  {
    //Printing title (optional)
    if (title != "")
    {
      printingTitle (title, 0); //Put title in the top of the screen
      y = 14; //Move the numbers on the screen under the title
    }
    cnt = String (counter); //Convert digits of the counter to text
    digits = cnt.length();  //Found length of the counter number
  }
  else //counter == 0
  {
    //Print the mode name in the centre of the screen
    if (title != "")  //Printing the title instead of the mode name
    {
      printingTitle(title, 22); //Put title in the middle of the screen
      Sprites::drawOverwrite(30, 36, press_A, 0); //Draw "PRESS [A]"
    }
    else
    {
      //Print mode name
      arduboy.setCursor(7, 16); //Put the mode name in the centre of screen
      arduboy.print("TALLY COUNTER");
      arduboy.setCursor(42, 28); //Put the mode name in the centre of screen
      arduboy.print(String (mode - 2));
      //Draw "PRESS [A]"
      Sprites::drawOverwrite(30, 42, press_A, 0);
    }
  }

  //Drawing digits
  switch (digits)
  {
    case 1: //Only one digit
      digit = cnt[0];
      Sprites::drawOverwrite(31, y, numbers3dgt, digit.toInt());
      break;
    case 2: //Two digits
      //First digit in the counter
      digit = cnt[0];
      Sprites::drawOverwrite(15, y, numbers3dgt, digit.toInt());
      //Second digit in the counter
      digit = cnt[1];
      Sprites::drawOverwrite(45, y, numbers3dgt, digit.toInt());
      break;
    case 3: //Three digits
      //First digit in the counter
      digit = cnt[0];
      Sprites::drawOverwrite(1, y, numbers3dgt, digit.toInt());
      //Second digit in the counter
      digit = cnt[1];
      Sprites::drawOverwrite(31, y, numbers3dgt, digit.toInt());
      //Third digit in the counter
      digit = cnt[2];
      Sprites::drawOverwrite(61, y, numbers3dgt, digit.toInt());
      break;
    case 4: //Four digits
      //First digit in the counter
      digit = cnt[0];
      Sprites::drawOverwrite(2, y + 6, numbers4dgt, digit.toInt());
      //Second digit in the counter
      digit = cnt[1];
      Sprites::drawOverwrite(24, y + 6, numbers4dgt, digit.toInt());
      //Third digit in the counter
      digit = cnt[2];
      Sprites::drawOverwrite(46, y + 6, numbers4dgt, digit.toInt());
      //Fourth digit in the counter
      digit = cnt[3];
      Sprites::drawOverwrite(68, y + 6, numbers4dgt, digit.toInt());
      break;
    case 5: //Five digits
      //First digit in the counter
      digit = cnt[0];
      Sprites::drawOverwrite(1, y + 10, numbers5dgt, digit.toInt());      //Second digit in the counter
      digit = cnt[1];
      Sprites::drawOverwrite(19, y + 10, numbers5dgt, digit.toInt());
      //Third digit in the counter
      digit = cnt[2];
      Sprites::drawOverwrite(37, y + 10, numbers5dgt, digit.toInt());
      //Fourth digit in the counter
      digit = cnt[3];
      Sprites::drawOverwrite(55, y + 10, numbers5dgt, digit.toInt());
      //Fifth digit in the counter
      digit = cnt[4];
      Sprites::drawOverwrite(73, y + 10, numbers5dgt, digit.toInt());
      break;
    case 6: //Six digits
      //First digit in the counter
      digit = cnt[0];
      Sprites::drawOverwrite(1, y + 12, numbers6dgt, digit.toInt());
      //Second digit in the counter
      digit = cnt[1];
      Sprites::drawOverwrite(16, y + 12, numbers6dgt, digit.toInt());
      //Third digit in the counter
      digit = cnt[2];
      Sprites::drawOverwrite(31, y + 12, numbers6dgt, digit.toInt());
      //Fourth digit in the counter
      digit = cnt[3];
      Sprites::drawOverwrite(46, y + 12, numbers6dgt, digit.toInt());
      //Fifth digit in the counter
      digit = cnt[4];
      Sprites::drawOverwrite(61, y + 12, numbers6dgt, digit.toInt());
      //Sixth digit in the counter
      digit = cnt[5];
      Sprites::drawOverwrite(76, y + 12, numbers6dgt, digit.toInt());
      break;
    default:
      // statements
      break;
  }
}

//Printing title
void printingTitle (String title, byte y)
{
  title_y = y;  //Horizontal coordinate of the title

  if (title.length() > 16)
  {
    if (first_call) //this part will be executed only once
    {
      current_title = title + " ";  //add space in the edn of the title
      creeping_on = true;           //creeping text-line effect is ON
      first_call = false;           //do not execute this part again before changing the current mode to the new
    }
  }
  else //If title just 16 letter or less, just print it in the centre
  {
    arduboy.setCursor((96 - title.length() * 6) / 2, title_y);
    arduboy.print(title);
  }
}

//Creeping text line effect for the long titles
void creepingLineEffect ()
{
  //Creeping text line effect
  if (creeping_line_delay_counts > creeping_line_delay)
  {
    if (creeping_line_counter < 6)
      creeping_line_counter++;
    else
    {
      current_title = current_title.substring(1) + current_title.charAt(0); //Letter shifting - first letter go to back
      creeping_line_counter = 0;
    }

    creeping_line_delay_counts = 0;
  }
  else
    creeping_line_delay_counts++;
  arduboy.setCursor(-creeping_line_counter, title_y); //Creeping text to left pixel by pixel
  //arduboy.setCursor(0, 0); //Creeping text to left letter by letter
  arduboy.print(current_title.substring(0, 17)); //Print first 18 letters
}

//Play the mode sounds
void playModeSound ()
{
  switch (mode) {
    case 0:
      sound.tones(mode0_sound); //play sound
      break;
    case 1:
      sound.tones(mode1_sound); //play sound
      break;
    case 2:
      sound.tones(mode2_sound); //play sound
      break;
    case 3:
      sound.tones(mode3_sound); //play sound
      break;
    case 4:
      sound.tones(mode4_sound); //play sound
      break;
    case 5:
      sound.tones(mode5_sound); //play sound
      break;
    case 6:
      sound.tones(mode6_sound); //play sound
      break;
    case 7:
      sound.tones(mode7_sound); //play sound
      break;
    case 8:
      sound.tones(mode8_sound); //play sound
      break;
    case 9:
      sound.tones(mode9_sound); //play sound
      break;
    case 10:
      sound.tones(mode10_sound); //play sound
      break;
    case 11:
      sound.tones(mode11_sound); //play sound
      break;
    case 12:
      sound.tones(mode12_sound); //play sound
      break;
    default:
      // statements
      break;
  }
}

//Sound control
//ON/OFF sound
void soundSwitch ()
{
  if (arduboy.audio.enabled())
  {
    arduboy.audio.off(); //Audio OFF
    arduboy.audio.saveOnOff(); //Save audio state (ON or OFF)
  }
  else
  {
    arduboy.audio.on(); //Audio ON
    arduboy.audio.saveOnOff(); //Save audio state (ON or OFF)
    sound.tones(button_sound); //play sound
  }
}

//Increasing the counter value
void increaseCounter ()
{
  if (counter < max_value[mode])
  {
    counter++;

    if (counter == max_value[mode])
      sound.tones(end_sound); //play end sound
    else
      sound.tones(button_sound); //play sound
  }
  else
    sound.tones(end_sound); //play end sound

  saveCounter(); //Save current counter value
}

//Decrease the conter value
void decreaseCounter ()
{
  if (counter > 0)
    sound.tones(decr_sound); //play decrease sound
  else
    sound.tones(button_sound); //play sound

  if (counter > 0)
    counter--;

  saveCounter(); //Save current counter value
}

//Reset the counter value to 0
void resetCounter ()
{
  if (counter > 0)
    sound.tones(reset_sound); //play reset sound
  else
    sound.tones(button_sound); //play sound

  counter = 0;

  saveCounter(); //Save current counter value
}

//Buttons checking
//[A] - increase counter
//[B] - decrease counter
//[B] (long press) - reset counter to 0
//[UP] - switch audio ON/OFF
//[DOWN] - increase counter
//[LEFT] - previous mode
//[RIGHT] - next mode
void btnCheck ()
{
  //Just pressed
  if (arduboy.justPressed(LEFT_BUTTON))
  {
    mode--; //previous mode
    if (mode > MODE_MAX) //'mode' type is byte, that is why after 0-- it's value will be 254
      mode = MODE_MAX;

    playModeSound (); //play sound

    creeping_on = false; //Reset creeping text line effect
    first_call = true;  //Is function called first time or not

    EEPROM.put (MODE_ADDR, mode); //Save current mode number

    loadCounter(); //Load current counter value
  }
  if (arduboy.justPressed(RIGHT_BUTTON))
  {
    mode++; //next mode

    if (mode > MODE_MAX) //Go to first mode
      mode = 0;

    playModeSound (); //play sound

    creeping_on = false; //Reset creeping text line effect
    first_call = true;  //Is function called first time or not

    EEPROM.put (MODE_ADDR, mode); //Save current mode number

    loadCounter(); //Load current counter value
  }
  if (arduboy.justPressed(UP_BUTTON))
  {
    soundSwitch(); //Sound control
  }
  if (arduboy.justPressed(DOWN_BUTTON))
  {
    increaseCounter();  //Increase counter value
  }
  if (arduboy.justPressed(A_BUTTON))
  {
    increaseCounter();  //Increase counter value
  }
  if (arduboy.justPressed(B_BUTTON))
  {
    pressedTime = millis(); //read current timer value for long press detection

    decreaseCounter ();     //Decrease counter value

    //During tests, it was noted that sometimes the justPressed()
    //does not executed before pressed(), so this flag was added
    execChk = true;         //Set execution flag
  }

  //Released
  if (arduboy.justReleased(B_BUTTON)) {
    execChk = false;  //Reset justPressed() execution flag
  }

  //Pressed
  if (arduboy.pressed(LEFT_BUTTON)) {
    //Draw the pressed left button sprite
    Sprites::drawOverwrite(96, 21, btnL, 0);
  }
  if (arduboy.pressed(RIGHT_BUTTON)) {
    //Draw the pressed right button sprite
    Sprites::drawOverwrite(96, 21, btnR, 0);
  }
  if (arduboy.pressed(UP_BUTTON)) {
    if (arduboy.audio.enabled())
      Sprites::drawOverwrite(96, 31, btnUp, 0); //Draw the pressed up button sprite
    else
      Sprites::drawOverwrite(96, 31, btnUpNoSndPress, 0); //Draw pressed button UP with AUDIO OFF symbol
  }
  if (arduboy.pressed(DOWN_BUTTON)) {
    //Draw the pressed down button sprite
    Sprites::drawOverwrite(96, 39, btnDwn, 0);
  }
  if (arduboy.pressed(A_BUTTON)) {
    //Draw the pressed A button sprite
    Sprites::drawOverwrite(96, 56, btnA, 0);
  }
  if (arduboy.pressed(B_BUTTON))
  {
    if (execChk)  //If justPressed() was executed before pressed()
    {
      //Draw the pressed B button sprite
      Sprites::drawOverwrite(96, 48, btnB, 0);

      if (counter > 0)
      {
        retainTime = millis(); //read current timer value for long press detection

        //Redraw button B with a zero character to warn about zeroing the counter value 
        if ((retainTime - pressedTime) > LONG_PRESS_TIME/4)
          Sprites::drawOverwrite(96, 48, btnBzero, 0); //First draw the pressed B with zero button sprite
        if ((retainTime - pressedTime) > LONG_PRESS_TIME/2)
          Sprites::drawOverwrite(96, 48, btnBzero_inverse, 0); //Second draw the pressed B with zero inversed button sprite
          
        //If button B was pressed long enough
        if ((mode > 2) && (mode <= MODE_MAX)) //Tally counter modes begin from 3
        {
          if ((retainTime - pressedTime) > LONG_PRESS_TIME * 2) //For tally counters modes the long press time is double
            resetCounter (); //Reset the tally counter to 0
        }
        else //reset counter for first three modes
        {
          if ((retainTime - pressedTime) > LONG_PRESS_TIME)
            resetCounter (); //Reset the counter to 0
        }
      }
    }
  }
}

//Reading the counter value from EEPROM
void loadCounter ()
{
  if ((mode > 2) && (mode <= MODE_MAX)) //Tally counter modes begin from 3
    EEPROM.get (address_table [mode - 3], counter); //Load tally counter current value
  else
    counter = 0;   //First three modes always begin from 0
}

//Saving the counter value to EEPROM.
//Made a little over complicated due to the need to limit
//the number of rewrites to same EEPROM memory cell.
//So, every TALLY_REW times, the counter value will be overwritten to a new location.
//Every TABLE_REW times, the table with counter addresses will be overwritten to a new location.
void saveCounter ()
{
  int addr;

  if ((mode > 2) && (mode <= MODE_MAX)) //Tally counter modes begin from 3
  {
    if (counter % TALLY_REW == 0) //Try not to rewrite in the same EEPROM cell too many times
    {
      //Save to new place
      do
      {
        addr = random (EEPROM_STORAGE_SPACE_START + TABLE_ADDR + 2, eeprom_size - 3); //Random address between reserved addresses at the beginning and EEPROM maximum length
      }
      while (!checkFreePlace (addr, 4)); //Generate new address for counter (4 bytes) with checking for free place

      address_table [mode - 3] = addr;
      EEPROM.put ((table_start_addr + 1) + (mode - 3) * 2, addr); //Save tally counter new address (2 bytes)

      table_cell_use++; //One of the addresses table's cells was rewrited
      if (table_cell_use > TABLE_REW) //Try not to rewrite in the same EEPROM cell too many times
      {
        //Save to new place
        do
        {
          addr = random (EEPROM_STORAGE_SPACE_START + TABLE_ADDR + 2, eeprom_size - 20); //Random address between reserved addresses at the beginning and EEPROM maximum length
        }
        while (!checkFreePlace (addr, 21)); //Generate new address for table of the counter adresses (21 bytes) with checking for free place

        table_start_addr = addr;                    //New table address in EEPROM
        EEPROM.put (TABLE_ADDR, table_start_addr);  //Save new table address in EEPROM
        table_cell_use = 0;                         //New table, 0 rewritings
        //EEPROM.put (addr, table_cell_use); //Save table_cell_use to new place
        for (int i = 0; i < 10; i++)
        {
          EEPROM.put (addr + 1 + i * 2, address_table[i]); //Save table values to new place (2 bytes each)
        }
      }
      EEPROM.write (table_start_addr, table_cell_use); //Save table cell rewrite quantity
    }

    EEPROM.put (address_table [mode - 3], counter); //Save tally counter current value
  }
}

//Initialization of EEPROM on start
void initEEPROM ()
{
  byte init;  //Check for first time (value INIT_FLAG means that memory was already initialized)
  int addr;   //Temporary address value
  unsigned long zero = 0; //Start value for counters

  init = EEPROM.read (INIT_ADDR); //First byte in memory
  if (init != INIT_FLAG) //Begin initialization if it was not done before
  {
    //Initialization of EEPROM
    EEPROM.write (MODE_ADDR, 0);                     //Start mode
    table_start_addr = TABLE_ADDR + 2;               //Address of first element of the table (2 bytes)
    EEPROM.put (TABLE_ADDR, table_start_addr);       //Save address of first element of the table
    EEPROM.write (table_start_addr, 0);              //Cell rewrites counter init value

    //Ten counters in tally modes
    for (int i = 0; i < 10; i++)
    {
      address_table [i] = table_start_addr + 21 + i * 4;            //Counters values store after table (which is 21 bytes long), and use 4 bytes for each counter (unsigned long)
      EEPROM.put (table_start_addr + 1 + i * 2, address_table [i]); //Adresses table element size is 2 bytes each (int) and begin from second byte (that why is +1)
      EEPROM.put (address_table [i], zero);                         //Tally counters (4 bytes each) start value is 0
    }

    EEPROM.write (INIT_ADDR, INIT_FLAG); //First cell of EEPROM value is INIT_FLAG indicates that is initialization already was done
  }
  else  //If EEPROM ready just load all stored values
  {
    mode = EEPROM.read (MODE_ADDR);  //Load current mode
    EEPROM.get (TABLE_ADDR, table_start_addr); //Load address of first element of the table
    EEPROM.get (table_start_addr, table_cell_use); //Load how many times table cells was rewrited
    for (int i = 0; i < 10; i++)  //Ten counters in tally modes
    {
      addr = table_start_addr + 1 + i * 2;  //Addresses begin from second byte (that why is +1) and occupy 2 bytes each (int)
      EEPROM.get (addr, address_table [i]); //Load address of the counter value
    }

    loadCounter(); //Load current counter value
  }
}

//Checking free place for need_length bytes in EEPROM, return TRUE if place is free
boolean checkFreePlace (int addr_start, int need_length)
{
  int addr_end = addr_start + need_length - 1; //First byte of new place in addr_start, last byte in addr_end

  if ((addr_end >= table_start_addr) && (addr_start < table_start_addr + 21)) //Check for matching with current table of addresses (21 bytes long)
    return false;
  for (int i = 0; i < 10; i++)  //Counters
  {
    if ((addr_end >= address_table [i]) && (addr_start < address_table [i] + 4)) //Check for matching with counters (4 bytes each)
      return false;
  }

  return true;
}

/*
  //Print EEPROM values to serial port for testing purposes
  void testSer ()
  {
  int adr1, adr2;
  byte tst2;
  unsigned long val1;

  Serial.print ("RAM mode value : ");
  Serial.println (mode);
  Serial.print ("RAM counter value : ");
  Serial.println (counter);

  Serial.println ("---- EEPROM values ----");
  tst2 = EEPROM.read (INIT_ADDR);
  Serial.print ("Init : ");
  Serial.println (tst2);
  tst2 = EEPROM.read (MODE_ADDR);
  Serial.print ("Mode : ");
  Serial.println (tst2);
  tst2 = EEPROM.read (SOUND_ADDR);
  Serial.print ("Audio : ");
  Serial.println (tst2);
  EEPROM.get (TABLE_ADDR, adr1);
  Serial.print ("Table address : ");
  Serial.println (adr1);
  Serial.println ("- Table values -");
  tst2 = EEPROM.read (adr1);
  Serial.print ("Table use : ");
  Serial.println (tst2);
  for (int i = 0; i < 10; i++)
  {
    EEPROM.get (adr1 + 1 + i * 2, adr2);
    Serial.print ("Counter address : ");
    Serial.print (adr2);
    EEPROM.get (adr2, val1);
    Serial.print (" Counter value : ");
    Serial.println (val1);
  }
  Serial.println ("-----------------------");
  }
*/

//Draw title screen
void drawTitle ()
{
  arduboy.clear();

  Sprites::drawOverwrite(20, 16, boot_title, 0);  //Draw boot logo title

  arduboy.display();  //Update display

  arduboy.delayShort(1000);
}

//Initializations
void setup()
{
  // open the serial port at 9600 bps:
  //Serial.begin(115200);

  eeprom_size = EEPROM.length (); //Max length of EEPROM
  initEEPROM (); //Initialization of EEPROM and loading all stored values from EEPROM

  arduboy.begin();

  //Initializing randomizer
  arduboy.initRandomSeed();

  drawTitle(); //Draw boot logo title
  arduboy.clear();

  pressedTime = millis(); //Initial read current timer value for long press detection
}

//Main loop
void loop()
{
  arduboy.clear();
  arduboy.pollButtons();

  //Creeping text line effect for the long titles
  if (creeping_on)
    creepingLineEffect ();

  //Draw menu sprite
  Sprites::drawOverwrite(96, 0, menu, 0);

  //Buttons checking
  btnCheck ();

  //Draw according to current mode
  switch (mode) {
    case 0:
      mode7Draw (); //Draw a vishva vajra sprites for 7 counts mode
      break;
    case 1:
      mode21Draw (); //Draw a vajra sprites for 21 counts mode
      break;
    case 2:
      mode108Draw (); //Draw a counter for 108 counts mode
      break;
    case 3:
      //Draw the tally counter one mode text
      Sprites::drawOverwrite(96, 9, mode_tally1, 0);
      modeTallyDraw (TALLY1_TITLE); //Draw a tally counter with optional "Title" (put "" for no title on screen or edit Titles.h)
      break;
    case 4:
      //Draw the tally counter two mode text
      Sprites::drawOverwrite(96, 9, mode_tally2, 0);
      modeTallyDraw (TALLY2_TITLE); //Draw a tally counter with optional "Title" (put "" for no title on screen or edit Titles.h)
      break;
    case 5:
      //Draw the tally counter three mode text
      Sprites::drawOverwrite(96, 9, mode_tally3, 0);
      modeTallyDraw (TALLY3_TITLE); //Draw a tally counter with optional "Title" (put "" for no title on screen or edit Titles.h)
      break;
    case 6:
      //Draw the tally counter four mode text
      Sprites::drawOverwrite(96, 9, mode_tally4, 0);
      modeTallyDraw (TALLY4_TITLE); //Draw a tally counter with optional "Title" (put "" for no title on screen or edit Titles.h)
      break;
    case 7:
      //Draw the tally counter five mode text
      Sprites::drawOverwrite(96, 9, mode_tally5, 0);
      modeTallyDraw (TALLY5_TITLE); //Draw a tally counter with optional "Title" (put "" for no title on screen or edit Titles.h)
      break;
    case 8:
      //Draw the tally counter six mode text
      Sprites::drawOverwrite(96, 9, mode_tally6, 0);
      modeTallyDraw (TALLY6_TITLE); //Draw a tally counter with optional "Title" (put "" for no title on screen or edit Titles.h)
      break;
    case 9:
      //Draw the tally counter seven mode text
      Sprites::drawOverwrite(96, 9, mode_tally7, 0);
      modeTallyDraw (TALLY7_TITLE); //Draw a tally counter with optional "Title" (put "" for no title on screen or edit Titles.h)
      break;
    case 10:
      //Draw the tally counter eight mode text
      Sprites::drawOverwrite(96, 9, mode_tally8, 0);
      modeTallyDraw (TALLY8_TITLE); //Draw a tally counter with optional "Title" (put "" for no title on screen or edit Titles.h)
      break;
    case 11:
      //Draw the tally counter nine mode text
      Sprites::drawOverwrite(96, 9, mode_tally9, 0);
      modeTallyDraw (TALLY9_TITLE); //Draw a tally counter with optional "Title" (put "" for no title on screen or edit Titles.h)
      break;
    case 12:
      //Draw the tally counter ten mode text
      Sprites::drawOverwrite(96, 9, mode_tally10, 0);
      modeTallyDraw (TALLY10_TITLE); //Draw a tally counter with optional "Title" (put "" for no title on screen or edit Titles.h)
      break;
    default:
      // statements
      break;
  }

  //Draw button UP with AUDIO OFF symbol
  //Checking for pressed button B is performed so as not to interfere with the drawing of the pressed button B symbol
  if (!arduboy.audio.enabled() && !arduboy.pressed(UP_BUTTON))
    Sprites::drawOverwrite(96, 31, btnUpNoSnd, 0);

  //Send screen buffer to serial for screen mirroring functionality
  //Serial.write(arduboy.getBuffer(), 128 * 64 / 8);
  //Update display
  arduboy.display();
}
