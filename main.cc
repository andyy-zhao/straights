#include <iostream>
#include <vector>
#include <memory>
#include "gamecontroller.h"
#include <string>
#include "observer.h"
#include "addtext.h"
#include <sstream>
#include "card.h"


int main(int argc, char **argv) {
    // use a time-based seed for the default seed value
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	
	if ( argc > 1 ) {
		try {
			seed = std::stoi( std::string{ argv[1] } );
		} catch( std::invalid_argument & e ) {
			std::cerr << e.what() << std::endl;
			return 1;
		} catch( std::out_of_range & e ) {
			std::cerr << e.what() << std::endl;
			return -1;
		} // catch
	} // if

    std::default_random_engine rng{seed};

    std::shared_ptr<GameController> controller = std::make_shared<GameController>(rng);

    controller->startGame();
    std::shared_ptr<Table> table = controller->getTable();

    std::shared_ptr<AddText> textobserver = std::make_shared<AddText>(table);

    controller->invitePlayers();
    controller->dealCards();

    // while the game is not over
    while (!controller->getGameState()->isGameOver()) {
        controller->startRound();
        controller->playRound();

        controller->printEndRoundResults(); // if game is Over, should set it to true

        if (controller->getGameState()->isGameOver()) {
            controller->printWinners();
            exit(0);
        }
    } // while

    return 0;

}