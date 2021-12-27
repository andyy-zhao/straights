#include "addtext.h"
#include "card.h"
#include <iostream>
#include <string>
#include "table.h"
#include <vector>
#include <memory>

AddText::AddText( std::shared_ptr<Table> table) : table{table} {
    table->attach( this ); 
}

AddText::~AddText() {
    table->detach( this );
}

void AddText::notify() {
    
    std::cout << "Cards on the table:" << std::endl;

    // if there are no cards on the table
    if (table->isTableEmpty()) {
        std::cout << "Clubs:" << std::endl;
        std::cout << "Diamonds:" << std::endl;
        std::cout << "Hearts:" << std::endl;
        std::cout << "Spades:" << std::endl;
    }
    else {
        std::cout << "Clubs:";

        std::vector<std::shared_ptr<Card>> tempclubs = table->getPile(C);
        for (size_t i = 0; i < tempclubs.size(); ++i) {
            std::cout << " " << tempclubs[i]->getRank();
        }
        std::cout << std::endl;

        std::cout << "Diamonds:";

        std::vector<std::shared_ptr<Card>> tempdiamonds = table->getPile(D);
        for (size_t i = 0; i < tempdiamonds.size(); ++i) {
            std::cout << " " << tempdiamonds[i]->getRank();
        }
        std::cout << std::endl;
        
        std::cout << "Hearts:";

        std::vector<std::shared_ptr<Card>> temphearts = table->getPile(H);
        for (size_t i = 0; i < temphearts.size(); ++i) {
            std::cout << " " << temphearts[i]->getRank();
        }
        std::cout << std::endl;

        std::cout << "Spades:";

        std::vector<std::shared_ptr<Card>> tempspades = table->getPile(S);
        for (size_t i = 0; i < tempspades.size(); ++i) {
            std::cout << " " << tempspades[i]->getRank();
        }
        std::cout << std::endl;

    }
}