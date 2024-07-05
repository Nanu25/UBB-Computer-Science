//
// Created by alex_ on 5/31/2024.
//

#include "UndoRedo.h"

void UndoRedo::add_undo(Service service) {
    Service aux = service;
    undo_list.push_back(aux);
    redo_list.clear(); // Clear redo list on new action
}

Service UndoRedo::make_undo() {
    if (undo_list.size() == 1) {
        throw std::out_of_range("No more undos available");
    }

    Service last_undo = undo_list[undo_list.size() - 1];
    undo_list.pop_back();
    redo_list.push_back(last_undo);

    return undo_list.back();
}

Service UndoRedo::make_redo() {
    if (redo_list.empty()) {
        throw std::out_of_range("No more redos available");
    }

    Service last_redo = redo_list[redo_list.size() - 1];
    redo_list.pop_back();
    undo_list.push_back(last_redo);

    return last_redo;

}
