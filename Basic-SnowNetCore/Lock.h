#pragma once


struct Lock {};

struct LockGuard {
    Lock& stOwnerLock;
    explicit LockGuard(Lock& lock) :
        stOwnerLock(lock)
    {}
};