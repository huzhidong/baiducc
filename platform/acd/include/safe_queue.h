/*
 * Copyright 2002-2014 the original author or authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      CC/LICENSE
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#pragma once

#include <queue>
#include "const_define.h"

using namespace std;

const uint32_t MAX_QUEUE_COUNT = 1000000;

template<typename T>
class SafeQueue {
private:
    queue<T> mQueue;
    bgcc::Mutex mLocker;

    bgcc::Semaphore mFullSemaphore;
    bgcc::Semaphore mEmptySemaphore;

    pthread_mutex_t     _mutex;
    pthread_cond_t      _cond;
    uint32_t            _waitings;
public:
    SafeQueue();
    ~SafeQueue();
    bool Empty();
    typename queue<T>::size_type Size();
    void BlockFront(T& value);
    bool Pop(T& value);
    void BlockPop();
    void BlockPop(T& value);
    void HarfBlockPop(T& value);
    bool UnBlockPop(T& value, int32_t timeout);
    void Push(const T& value);
    void BlockPush(const T& value);
    void HarfBlockPush(const T& value);
};

template<class T>
SafeQueue<T>::SafeQueue() 
    : mFullSemaphore(0)
    , mEmptySemaphore(MAX_QUEUE_COUNT)
    , _waitings(0)
{
    pthread_mutex_init(&this->_mutex, NULL);
    pthread_cond_init(&this->_cond, NULL);
}

template<class T>
SafeQueue<T>::~SafeQueue() 
{
    pthread_mutex_destroy(&_mutex);
    pthread_cond_destroy(&_cond);
}

template<class T>
bool SafeQueue<T>::Empty() {
    SingleLocker s(&mLocker);
    return mQueue.empty();
}

template<class T>
typename queue<T>::size_type SafeQueue<T>::Size() {
    SingleLocker s(&mLocker);
    return mQueue.size();
}

template<class T>
void SafeQueue<T>::BlockFront(T& value) {
    mFullSemaphore.wait();
    mLocker.lock();
    value = mQueue.front();
    mLocker.unlock();
    mFullSemaphore.signal();
}

template<class T>
bool SafeQueue<T>::Pop(T& value) {
    SingleLocker s(&mLocker);

    if (mQueue.empty()) {
        return false;
    }

    value = mQueue.front();
    mQueue.pop();
    return true;
}

template<class T>
void SafeQueue<T>::BlockPop() {
    mFullSemaphore.wait();
    mLocker.lock();
    mQueue.pop();
    mLocker.unlock();
    mEmptySemaphore.signal();
}

template<class T>
void SafeQueue<T>::BlockPop(T& value) {
    mFullSemaphore.wait();
    mLocker.lock();
    value = mQueue.front();
    mQueue.pop();
    mLocker.unlock();
    mEmptySemaphore.signal();
}

template<class T>
void SafeQueue<T>::HarfBlockPop(T& value) {
    mFullSemaphore.wait();
    mLocker.lock();
    value = mQueue.front();
    mQueue.pop();
    mLocker.unlock();
}

template<class T>
bool SafeQueue<T>::UnBlockPop(T& value, int32_t timeout) {
    pthread_mutex_lock(&_mutex);
    mLocker.lock();
    ++_waitings;

        if (mQueue.empty()) {
            if (timeout > 0) {
                struct timespec abstime;
                clock_gettime(CLOCK_REALTIME, &abstime);
                abstime.tv_sec += timeout / 1000;
                abstime.tv_nsec += (timeout % 1000) * 1000000;
                mLocker.unlock();
                pthread_cond_timedwait(&_cond, &_mutex, &abstime);
                mLocker.lock();
            }
        }

        if (mQueue.empty()) {
            --_waitings;
            pthread_mutex_unlock(&_mutex);
            mLocker.unlock();
            return false;
        }

    value = mQueue.front();
    mQueue.pop();
    --_waitings;
    mLocker.unlock();
    pthread_mutex_unlock(&_mutex);
    return true;
}

template<class T>
void SafeQueue<T>::Push(const T& value) {
    SingleLocker s(&mLocker);

    if (mQueue.size() >= MAX_QUEUE_COUNT) { //maybe overflow, need log out
        mQueue.pop();
    }

    mQueue.push(value);

    if (_waitings > 0) {
        pthread_cond_signal(&_cond);
    }
}

template<class T>
void SafeQueue<T>::BlockPush(const T& value) {
    mEmptySemaphore.wait();
    mLocker.lock();
    mQueue.push(value);
    mLocker.unlock();
    mFullSemaphore.signal();
    if (_waitings > 0) {
        pthread_cond_signal(&_cond);
    }
}

template<class T>
void SafeQueue<T>::HarfBlockPush(const T& value) {
    bool isFull = false;
    mLocker.lock();

    if (mQueue.size() >= MAX_QUEUE_COUNT) { //maybe overflow, need log out
        isFull = true;
        mQueue.pop();
    }

    mQueue.push(value);
    mLocker.unlock();

    if (!isFull) {
        mFullSemaphore.signal();
    }

    if (_waitings > 0) {
        pthread_cond_signal(&_cond);
    }
}
