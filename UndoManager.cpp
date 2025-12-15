#include "UndoManager.h"

// 静态成员初始化
UndoManager* UndoManager::_instance = nullptr;
std::mutex UndoManager::_mutex;

// 获取单例实例
UndoManager* UndoManager::getInstance() {
    if (_instance == nullptr) {
        std::lock_guard<std::mutex> lock(_mutex); // 线程安全（单线程可移除）
        if (_instance == nullptr) {
            _instance = new UndoManager();
        }
    }
    return _instance;
}

// 销毁单例
void UndoManager::destroyInstance() {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_instance != nullptr) {
        delete _instance;
        _instance = nullptr;
    }
}

// 记录操作
void UndoManager::recordUndo(const UndoModel& undoModel) {
    _undoStack.push(undoModel);
}

// 撤销操作：弹出栈顶的操作并返回
UndoModel* UndoManager::undo() {
    if (_undoStack.empty()) {
        return nullptr;
    }
    // 注意：这里用动态分配是为了返回非局部对象（栈对象弹出后会销毁）
    UndoModel* undoModel = new UndoModel(_undoStack.top());
    _undoStack.pop();
    return undoModel;
}

// 清空操作记录
void UndoManager::clearUndos() {
    while (!_undoStack.empty()) {
        _undoStack.pop();
    }
}