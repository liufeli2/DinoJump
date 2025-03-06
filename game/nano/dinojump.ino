// // Define onboard LED pin
// #define LED_PIN 2

// void setup() {
//     pinMode(, OUTPUT);  // Set LED pin as output
// }

// void loop() {
//     digitalWrite(LED_PIN, HIGH);  // Turn LED on
//     delay(500);                   // Wait 500ms
//     digitalWrite(LED_PIN, LOW);   // Turn LED off
//     delay(500);                   // Wait 500ms
// }

#include "game.hpp"
#include "terminal_display.hpp"
#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

const int SPEED = 10000; // Delay speed in game loop

Game game;

// Constants for button GPIO pins
const int BUTTON_JUMP_PIN = 12;
const int BUTTON_DUCK_PIN = 13;
const int BUTTON_QUIT_PIN = 14;

std::atomic<bool> quit{false};      // Flag to signal quitting the game
std::atomic<bool> game_over{false}; // Flag to signal game over

// Function for handling input from the buttons
void input_thread_func() {
  while (!game_over) {
    // Read button states
    int jump_state = digitalRead(BUTTON_JUMP_PIN);
    int duck_state = digitalRead(BUTTON_DUCK_PIN);
    int quit_state = digitalRead(BUTTON_QUIT_PIN);

    // Store button states, each button corresponds to a different key press
    // action
    if (jump_state == HIGH) {
      player_input(JUMP); // Simulate the 'w' key press for jumping
    } else if (duck_state == HIGH) {
      player_input(DUCK); // Simulate the 's' key press for ducking
    } else if (quit_state == HIGH) {
      game_over = true; // Set game over flag to true to end the game
    }
  }
}

// Function to handle player input and update game actions
void player_input(Input_State input) {
  if (!game_over) {
    game.input(input);
  }
}

void print_compressed_frame(Frame frame) {
  // Each column (uint64_t) takes at most 13 characters (16 - 4 for hex, 1 for
  // comma) 1 additional character for '\0'
  char buf[MAX_X * 13 + 1] = {0};
  frame.compressed_form(buf);
  // std::cout << buf << std::endl;
  Serial.println(buf);
}

void setup() {
  // Initialize serial communication and button pins
  // Serial.begin(115200);
  Serial.begin(9600);

  pinMode(BUTTON_JUMP_PIN, INPUT); // Set button pins as input
  pinMode(BUTTON_DUCK_PIN, INPUT);
  pinMode(BUTTON_QUIT_PIN, INPUT);

  Serial.println("setup");
}

void loop() {
  // Game game = Game();  // Initialize your game object

  // Start input thread for button polling
  std::thread input_thread(input_thread_func);

  // while (!game.get_collision() && !game_over) {
  //     // Update the game logic and frame
  //     game.update_obstacles();
  //     game.update_frame();
  //     print_compressed_frame(game.get_frame());
  //     // print_frame(game.get_frame());  // Print the updated game frame to
  //     the Serial Monitor delay(SPEED / 1000);  // Add a delay (in
  //     milliseconds)
  // }

  game.update_obstacles();
  game.update_frame();
  print_compressed_frame(game.get_frame());
  // print_frame(game.get_frame());  // Print the updated game frame to the
  // Serial Monitor
  delay(SPEED / 1000); // Add a delay (in milliseconds)

  // // Game over
  // if (game_over) {
  //     // std::cout << "Game Over!" << std::endl;
  //     Serial.println("Game Over!");
  // }

  // // std::cout << "Score: " << game.get_score() << "\n";
  // // std::cout << "Press Quit button to quit!\n";
  // Serial.println("Score");
  // Serial.println("Quit");

  // Wait for the quit signal from the button press, while allowing the input
  // thread to finish
  input_thread.join();
}