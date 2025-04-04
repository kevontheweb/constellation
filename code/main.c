// Code for ATtiny85 (or similar) with flickering and PWM

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

// Define LED pins (adjust if needed)
#define D1 PB0
#define D2 PB1
#define D3 PB2
#define D4 PB3
#define D5 PB4
#define D6 PA7
#define D7 PA6
#define D8 PA5
#define D9 PA4
#define D10 PA3
#define D11 PA2

// PWM settings
#define PWM_MAX 255 // Maximum PWM value (brightness)

void setup() {
  // Set LED pins as outputs
  DDRB = (1 << D1) | (1 << D2) | (1 << D3) | (1 << D4) | (1 << D5);
  DDRA = (1 << D6) | (1 << D7) | (1 << D8) | (1 << D9) | (1 << D10) | (1 << D11);

  // Initialize PWM (example using Timer0 for PB0, PB1, and Timer1 for the rest. Adjust as needed)
  TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01); // Fast PWM mode
  TCCR0B = (1 << CS01); // Prescaler 8 (adjust as needed)

  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10); // Fast PWM mode
  TCCR1B = (1 << CS11); // Prescaler 8 (adjust as needed)
}

void flickerLED(uint8_t ledPin, uint8_t port, uint8_t timerRegister) {
  uint8_t pwmValue = rand() % PWM_MAX; // Random PWM value
  if (port == 0) {
    if (ledPin == D1) {
      OCR0A = pwmValue;
    } else if (ledPin == D2) {
      OCR0B = pwmValue;
    } else {
      PORTB = (1 << ledPin);
      OCR0A = pwmValue;
    }
  } else {
    if (ledPin == D6) {
      OCR1A = pwmValue;
    } else {
      OCR1B = pwmValue;
    }
    PORTA = (1 << ledPin);
  }
  _delay_ms(rand() % 500); // Random delay
}

void loop() {
  // Flicker LEDs semi-randomly
  flickerLED(D1, 0, 0);
  flickerLED(D2, 0, 0);
  flickerLED(D3, 0, 0);
  flickerLED(D4, 0, 0);
  flickerLED(D5, 0, 0);
  flickerLED(D6, 1, 1);
  flickerLED(D7, 1, 1);
  flickerLED(D8, 1, 1);
  flickerLED(D9, 1, 1);
  flickerLED(D10, 1, 1);
  flickerLED(D11, 1, 1);
}

int main() {
  setup();
  while (1) {
    loop();
  }
  return 0;
}
