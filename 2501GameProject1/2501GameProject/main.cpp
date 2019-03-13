#include "Game.h"
int main() {
	cout << "INSTRUCTIONS" << endl;
	cout << "Press Enter to go from Title Screen to playing" << endl;
	cout << "Movement: Arrow Keys" << endl;
	cout << "When touching the orange spider, press space to ride. You can now go through walls and move differently" << endl;
	cout << "Pick up items with Q" << endl;
	cout << "Press I to open and close inventory." << endl;
	cout << "Press E to scroll through inventory." << endl;
	cout << "Click to shoot enemies" << endl;
	cout << "EXPLANATIONS:" << endl;
	cout << "Some tiles are designated as 'poison tiles' they look different based on the zone and will damage you over time" << endl;

	Game theGame;
	theGame.loop();
	return 0;
}