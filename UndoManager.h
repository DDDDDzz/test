#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H

#include "UndoModel.h"
#include <stack>
#include <mutex>

class UndoManager {
public:
    // 单例模式：获取全局唯一实例
    static UndoManager* getInstance();

    // 销毁单例（程序结束时调用，可选）
    static void destroyInstance();

    // 记录一步操作到栈中
    void recordUndo(const UndoModel& undoModel);

    // 撤销上一步操作（返回需要恢复的UndoModel，空则返回nullptr）
    UndoModel* undo();

    // 清空所有操作记录（比如游戏重置时）
    void clearUndos();

    // 判断是否有可撤销的操作
    bool hasUndo() const { return !_undoStack.empty(); }

private:
    // 私有构造/析构函数，禁止外部实例化
    UndoManager() = default;
    ~UndoManager() = default;
    // 禁止拷贝和赋值
    UndoManager(const UndoManager&) = delete;
    UndoManager& operator=(const UndoManager&) = delete;

    static UndoManager* _instance;    // 单例实例
    static std::mutex _mutex;         // 线程安全锁（可选，单线程可移除）
    std::stack<UndoModel> _undoStack; // 操作记录栈（后进先出）
};

#endif // UNDO_MANAGER_H