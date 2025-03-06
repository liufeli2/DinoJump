// #include "game.hpp"
// #include "terminal_display.hpp"
// #include <atomic>
// #include <iostream>
// #include <mutex>
// #include <thread>

// const int SPEED = 10000;  // Delay speed in game loop

// // Constants for button GPIO pins
// const int BUTTON_JUMP_PIN = 12;
// const int BUTTON_DUCK_PIN = 13;
// const int BUTTON_QUIT_PIN = 14;

// std::atomic<bool> quit{false};  // Flag to signal quitting the game
// std::atomic<bool> game_over{false};  // Flag to signal game over

// // Function for handling input from the buttons
// void input_thread_func() {
//     while (!game_over) {
//         // Read button states
//         int jump_state = digitalRead(BUTTON_JUMP_PIN);
//         int duck_state = digitalRead(BUTTON_DUCK_PIN);
//         int quit_state = digitalRead(BUTTON_QUIT_PIN);

//         // Store button states, each button corresponds to a different key
//         press action if (jump_state == HIGH) {
//             player_input(JUMP);  // Simulate the 'w' key press for jumping
//         } else if (duck_state == HIGH) {
//             player_input(DUCK);  // Simulate the 's' key press for ducking
//         } else if (quit_state == HIGH) {
//             game_over = true;  // Set game over flag to true to end the game
//         }
//     }
// }

// // Function to handle player input and update game actions
// void player_input(Input_State input) {
//     if (!game_over) {
//         game.input(input);
//     }
// }

// void setup() {
//     // Initialize serial communication and button pins
//     Serial.begin(115200);

//     pinMode(BUTTON_JUMP_PIN, INPUT);  // Set button pins as input
//     pinMode(BUTTON_DUCK_PIN, INPUT);
//     pinMode(BUTTON_QUIT_PIN, INPUT);
// }

// void loop() {
//     Game game = Game();  // Initialize your game object

//     // Start input thread for button polling
//     std::thread input_thread(input_thread_func);

//     while (!game.get_collision() && !game_over) {
//         // Update the game logic and frame
//         game.update_obstacles();
//         game.update_frame();
//         print_frame(game.get_frame());  // Print the updated game frame to
//         the Serial Monitor delay(SPEED / 1000);  // Add a delay (in
//         milliseconds)
//     }

//     // Game over
//     if (game_over) {
//         std::cout << "Game Over!" << std::endl;
//     }

//     std::cout << "Score: " << game.get_score() << "\n";
//     std::cout << "Press Quit button to quit!\n";

//     // Wait for the quit signal from the button press, while allowing the
//     input thread to finish input_thread.join();

// }

// #include "game.hpp"
// #include "terminal_display.hpp"
// #include <atomic>
// #include <iostream>
// #include <mutex>
// #include <thread>

// const int SPEED = 10000;

// std::atomic<char> curr_input{'\0'};
// bool quit = false;

// void input_thread_func() {
// 	while (!quit) {
// 		char key = read_key();
// 		curr_input.store(key);
// 	}
// }

// void player_input(Game &game) {
// 	char key = curr_input.load();
// 	Input_State input = NEUTRAL;
// 	if (key == 'w') {
// 		input = JUMP;
// 	} else if (key == 's') {
// 		input = DUCK;
// 	}
// 	game.input(input);
// }

// bool player_quit() {
// 	char key = curr_input.load();
// 	if (key == 'q') {
// 		return true;
// 	}
// 	return false;
// }

// int main() {
// 	Game game = Game();
// 	init_terminal();

// 	std::thread input_thread(input_thread_func);

// 	while (!game.get_collision()) {
// 		player_input(game);
// 		game.update_obstacles();
// 		game.update_frame();
// 		print_frame(game.get_frame());
// 		usleep(SPEED);
// 	}
// 	std::cout << "Score: " << game.get_score() << "\n";
// 	std::cout << "Press Q to quit!\n";

// 	while (!quit) {
// 		quit = player_quit();
// 	}

// 	input_thread.join();
// 	reset_terminal();
// }
