
#ifndef OOP_A10_NANU25_UNDOREDO_H
#define OOP_A10_NANU25_UNDOREDO_H


#include <vector>
#include "../Service/Service.h"

class UndoRedo {
private:
    std::vector <Service> undo_list;
    std::vector <Service> redo_list;
public:
    Service make_undo();
    Service make_redo();
    void add_undo(Service service);
};


#endif //OOP_A10_NANU25_UNDOREDO_H
