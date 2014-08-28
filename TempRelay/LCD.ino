void continue_processing_display_comm() {
  unsigned char current_letter;
  if (!pausing && !pulseActive) {
    
    switch (display_state) {
      case DO_NOTHING:
            break;      
      case ENTER_MENU: // kick off setting a new message on the display. We assume we're in the default msg display screen.
        cur_letter_pos = 0; // We always start off at letter 'A', or pos 0.
        read_buf_index = 0;
        PAUSE_DUR = 90;
        pulse_pin(UP_PIN); // this goes into mode-switching state
        display_state = SELECT_INPUT;
                break;
      case SELECT_INPUT: 
        pulse_pin(UP_PIN); // keep going to the INPUT mode-selection 
        display_state = ENTER_MSG_CHANGE;
        break;
      case ENTER_MSG_CHANGE:
  
        pulse_pin(ON_OFF_PIN); // select INPUT mode.
        display_state = START_SCROLLING_TO_LETTER;
        break;
      case START_SCROLLING_TO_LETTER: // continue writing letters until we've written out the entire buffer
        PAUSE_DUR = 90;
        if (read_buf_index < write_buf_index) {
          current_letter = buffer[read_buf_index++];
          if (DEBUG_PRINT) {
            Serial.print("cur letter: ");Serial.print((char)current_letter);Serial.print(" cur pos: ");Serial.println((int)cur_letter_pos);
          }
          if (current_letter == ' ') { // special case, we need to move off the letter, and back on.
            pulse_pin(ON_OFF_PIN);   
           display_state = START_SCROLLING_TO_LETTER; // this immediately moves us to the next letter.         
          }
          else {
            PAUSE_DUR = 15;
            target_letter_pos = get_num_presses(current_letter);
            if (target_letter_pos == 150) { // bail, don't recognize
               display_state = START_SCROLLING_TO_LETTER;
               return;
            }
            
            if (DEBUG_PRINT) {
              Serial.print("target pos: ");Serial.println((int)target_letter_pos);
            }
            if (target_letter_pos >= cur_letter_pos) { // even if we're starting at the right pos, we need to move
                                                       // off and back on to the letter to avoid entering a space.
              pulse_pin(UP_PIN);
              cur_letter_pos++;
            }
            else {
              pulse_pin(DOWN_PIN);
              cur_letter_pos--;
            }
            display_state = SCROLLING;
          }          
          
        }
        else { // we're done writing out the letters, issue the finished command by holding DOWN for 3s
          write_buf_index = 0;
          Serial.println("Finished writing, exiting INPUT mode");
          pinMode(DOWN_PIN,OUTPUT);
          delay(3100);
          pinMode(DOWN_PIN,INPUT);
          display_state = DO_NOTHING;
          WordIndex=3950;
        }
        break;
      case SCROLLING:
        if (DEBUG_PRINT) {
          Serial.print("cur_pos: ");Serial.println((int)cur_letter_pos);
        }
        if (cur_letter_pos == target_letter_pos) { // we've scrolled to the correct letter, now enter it in.
          PAUSE_DUR = 90;
          pulse_pin(ON_OFF_PIN); // enter in this selection
          //delay(500); // long delay to store number
          display_state = START_SCROLLING_TO_LETTER;
        }
        else if (cur_letter_pos < target_letter_pos) {
           pulse_pin(UP_PIN);
           cur_letter_pos++;
           display_state = SCROLLING;
        }
        else {
          pulse_pin(DOWN_PIN);
          cur_letter_pos--;
          display_state = SCROLLING; 
        }
        break;
      
    }
    
   
    
  }  
}

void ground_pin(unsigned char pin, unsigned char grounded) {
  if (grounded == 1) {    
    pinMode(pin,OUTPUT);
  }
  else
    pinMode(pin,INPUT);
}

void pulse_pin(unsigned char pin) {
  pinMode(pin,OUTPUT);
  //digitalWrite(13,1);
  pulseActive = 1;
 
  pulseStartTime = millis();
  if (DEBUG_PRINT) {
    Serial.print("pulse: ");Serial.println((int)pin);
  }

}

// this is called every loop to release the last pulse.  Setting the pinMode to input effectively 
// releases a button.
void reset_pulse() {
  if (pulseActive && (millis() - pulseStartTime > PULSE_DUR)) {
    pinMode( ON_OFF_PIN,INPUT);
    pinMode(UP_PIN,INPUT);
    pinMode(DOWN_PIN,INPUT);
   // digitalWrite(13,0);
    pulseActive = 0;
    // after each pulse, we pause for a bit
    pausing = 1;
    pauseStartTime = millis();
  }
}

// this takes a target character in, and looks up how many presses from A it will take to get to that letter.
// Or, in other words, the address of that letter.

//  ascii table starting at 'A' (65 decimal), going to 'z' (122), 
//  then starting at '!' (33), going to '@' (64),
//  then 4 weird characters and back to 'A'
unsigned char get_num_presses(unsigned char letter) {
  
//  'A' to 'z'
  if (letter >= 'A' && letter <= 'z') {
     return letter - 'A';
  }
  else if (letter >= '!' && letter <= '@') { // '!' to '@'
    return ('z' - 'A') + 1 + letter - '!';
  }
  else 
    return 150; // some heart thing?
  
}

void check_pause() {
  if (pausing && millis() - pauseStartTime > PAUSE_DUR) {
     pausing = 0; 
  }
}

