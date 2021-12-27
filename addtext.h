#ifndef _ADDTEXT_H_
#define _ADDTEXT_H_

#include "observer.h"
#include "table.h"
#include <memory>
#include "player.h"

class AddText: public Observer {
    std::shared_ptr<Table> table;

    public:
        AddText(std::shared_ptr<Table> table);
        void notify() override;
        ~AddText();
};

#endif