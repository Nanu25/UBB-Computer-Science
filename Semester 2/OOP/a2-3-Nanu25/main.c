#include "Ui.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Tests/Test.h"
#include <stdio.h>
int main() {
    DynamicArray *Repository = createDynamicArray(1);
    UndoRedoDynamicArray *undo_list = createUndoRedoDynamicArray(1), *redo_list = createUndoRedoDynamicArray(1);

    test_all();
    Ui_start(Repository, undo_list, redo_list);

    destroy(Repository);
    destroyUndoRedoDynamicArray(undo_list);
    destroyUndoRedoDynamicArray(redo_list);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    printf("%d", _CrtDumpMemoryLeaks());

    return 0;
}