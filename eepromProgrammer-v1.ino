

void setup() {
    // comment out to clear the shift register at start of execution
    // #define CLEAR
    #define SHIFT_CLK  2
    #define SHIFT_DATA 3
    #define SHIFT_OE   4
    #define A_0        5
    #define A_1        6
    #define A_2        7
    #define A_3        8
    #define A_4        9
    #define A_5        10
    #define A_6        11
    #define A_7        12
    #define EEPROM_WE  13
    #define EEPROM_OE  14
    pinMode(SHIFT_CLK, OUTPUT);
    pinMode(SHIFT_DATA, OUTPUT);
    pinMode(SHIFT_OE, OUTPUT);
    pinMode(A_0, OUTPUT);
    pinMode(A_1, OUTPUT);
    pinMode(A_2, OUTPUT);
    pinMode(A_3, OUTPUT);
    pinMode(A_4, OUTPUT);
    pinMode(A_5, OUTPUT);
    pinMode(A_6, OUTPUT);
    pinMode(A_7, OUTPUT);
    pinMode(EEPROM_WE, OUTPUT);
    pinMode(EEPROM_OE, OUTPUT);

}

void clear_control_bits(void) {
    digitalWrite(SHIFT_OE, 1);
    digitalWrite(EEPROM_WE, 1);
    digitalWrite(EEPROM_OE, 1);
}
void clear_register(void) {
    digitalWrite(SHIFT_OE, 1);
    digitalWrite(SHIFT_DATA, 0);
    for (int i=0; i<8; i++) {
      
      delayMicroseconds(5);
      digitalWrite(SHIFT_CLK, 1);
      delayMicroseconds(5);
      digitalWrite(SHIFT_CLK, 0);
    }
}

void set_adress(char addr){
    char addr_pins[8] = {A_0, A_1, A_2, A_3, A_4, A_5, A_6, A_7};
    for ( int i=7; i>=0; i-- ){
        digitalWrite(addr_pins[i], addr & (0b1 << i));
    }
}

void write_to_register(char data){
    char bit;
    digitalWrite(EEPROM_WE, HIGH);
    digitalWrite(SHIFT_OE, LOW);
    delayMicroseconds(5);
    for(int i=0;i<8;i++){
        bit = 0x80 & data << i;
        digitalWrite(SHIFT_DATA, bit);
        delayMicroseconds(5);
        digitalWrite(SHIFT_CLK, HIGH);
        digitalWrite(SHIFT_CLK, LOW);
        delayMicroseconds(5);
    }
    digitalWrite(SHIFT_DATA, LOW);
    digitalWrite(SHIFT_OE, HIGH);
    delayMicroseconds(5);
}

void pulse_eeprom_we(void) {
    digitalWrite(EEPROM_WE, LOW);
    delayMicroseconds(1);
    digitalWrite(EEPROM_WE, HIGH);
}

void write_to_eeprom_helper(char addr, char data) {
    write_to_register(data);
    set_adress(addr);
    digitalWrite(SHIFT_OE, LOW);
    digitalWrite(EEPROM_OE, HIGH);
    delayMicroseconds(1);
    pulse_eeprom_we();
    delay(10);

}
void write_to_eeprom(char addr, char data) {
    write_to_eeprom_helper(addr, 0xff);
    write_to_eeprom_helper(addr, 0xff);
    write_to_eeprom_helper(addr, data);
}


void show_addr_static(char addr) {
    digitalWrite(SHIFT_OE, HIGH);
    digitalWrite(EEPROM_WE, HIGH);
    digitalWrite(EEPROM_OE, LOW);
    delayMicroseconds(1);
    set_adress(addr);
    while(1);
}
void show_shift_static(char data){
    digitalWrite(EEPROM_WE, HIGH);
    write_to_register(data);
    digitalWrite(SHIFT_OE, LOW);
    while(1);
}

void write_data_array(char start_addr, char* data) {
  
}

void loop() {
    #ifndef CRTL
    #define CRTL
    clear_control_bits();
    #endif

    char adrr = 0x00;
    char data = 0x36;
    write_to_eeprom(adrr, data);
    show_addr_static(adrr);
    while(1);
}