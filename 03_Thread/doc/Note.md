### 1 理解pthread_create的第三个参数和函数指针

`pthread_create`是POSIX线程库中用于创建线程的函数，其原型如下：

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);
```

#### 第三个参数 - 函数指针

第三个参数 `void *(*start_routine) (void *)` 是一个函数指针，它指向新线程将要执行的函数。

#### 分解理解这个函数指针

1. `void *(*start_routine) (void *)` 可以分解为：
   - `start_routine` 是一个指针
   - 它指向一个函数
   - 这个函数接受一个 `void*` 参数
   - 这个函数返回一个 `void*` 值

2. 更简单的写法（使用typedef）：
   ```c
   typedef void *(*thread_func_t)(void *);
   int pthread_create(..., thread_func_t start_routine, ...);
   ```

#### 函数指针的基本概念

函数指针是指向函数的指针变量，它存储的是函数的入口地址。通过函数指针，我们可以间接调用函数。

基本语法：
```c
返回类型 (*指针变量名)(参数列表);
```

示例：
```c
int (*func_ptr)(int, int);  // 指向接受两个int参数并返回int的函数
```

#### 如何使用

1. 定义一个符合要求的线程函数：
   ```c
   void *my_thread_func(void *arg) {
       // 线程执行的代码
       return NULL;
   }
   ```

2. 创建线程时传递这个函数：
   ```c
   pthread_t thread_id;
   pthread_create(&thread_id, NULL, my_thread_func, NULL);
   ```

   这里 `my_thread_func` 会自动转换为函数指针。

#### 为什么使用函数指针

1. **灵活性**：可以在运行时决定线程执行哪个函数
2. **回调机制**：允许库函数调用用户提供的函数
3. **多态性**：通过统一的接口调用不同的函数

## 实际示例

```c
#include <pthread.h>
#include <stdio.h>

// 线程函数
void *print_message(void *msg) {
    char *message = (char *)msg;
    printf("%s\n", message);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    char *msg1 = "Thread 1";
    char *msg2 = "Thread 2";
    
    // 创建两个线程，分别执行print_message函数
    pthread_create(&thread1, NULL, print_message, (void *)msg1);
    pthread_create(&thread2, NULL, print_message, (void *)msg2);
    
    // 等待线程结束
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    return 0;
}
```

在这个例子中，`print_message` 函数的地址被作为函数指针传递给 `pthread_create`，新创建的线程将从这个函数开始执行。