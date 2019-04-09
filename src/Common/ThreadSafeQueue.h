// Copyright (c) 2018-2019, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.

#pragma once

#include <mutex>

#include <queue>

#include <utility>

namespace Common
{
  template <typename T>
  class ThreadSafeQueue
  {
      public:
          ThreadSafeQueue() {}

          void enqueue(T item)
          {
              push(item);
          }

          T dequeue()
          {
              T item;

              if (empty())
              {
                  return item;
              }

              item = front();

              pop();

              return item;
          }

          T peek()
          {
              T item;

              if (empty())
              {
                  return item;
              }

              return front();
          }

          T front()
          {
              std::lock_guard<std::mutex> lock(m_mutex);

              return m_queue.front();
          }

          T back()
          {
              std::lock_guard<std::mutex> lock(m_mutex);

              return m_queue.back();
          }

          bool empty()
          {
              std::lock_guard<std::mutex> lock(m_mutex);

              return m_queue.empty();
          }

          size_t size()
          {
              std::lock_guard<std::mutex> lock(m_mutex);

              return m_queue.size();
          }

          void push(T item)
          {
              std::lock_guard<std::mutex> lock(m_mutex);

              m_queue.push(item);
          }

          void emplace(T item)
          {
              std::lock_guard<std::mutex> lock(m_mutex);

              m_queue.emplace(item);
          }

          void pop()
          {
              std::lock_guard<std::mutex> lock(m_mutex);

              m_queue.pop();
          }

      private:
          std::queue<T> m_queue;

          std::mutex m_mutex;
  };
}