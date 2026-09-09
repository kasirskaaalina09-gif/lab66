## Laboratory work V

Данная лабораторная работа посвещена изучению фреймворков для тестирования на примере **GTest**

```sh
$ open https://github.com/google/googletest
```

## Tasks

- [ ] 1. Создать публичный репозиторий с названием **lab66** на сервисе **GitHub**
- [ ] 2. Выполнить инструкцию учебного материала
- [ ] 3. Ознакомиться со ссылками учебного материала
- [ ] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

```sh
$ export GITHUB_USERNAME=<имя_пользователя>
$ alias gsed=sed # for *-nix system
```

```sh
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
```

```sh
$ git clone https://github.com/${GITHUB_USERNAME}/lab04 projects/lab66
```

```sh
$ cd projects/lab66
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab66
```

```sh
$ mkdir third-party
$ git submodule add https://github.com/google/googletest third-party/gtest
```

Вывод:

```sh
Cloning into '/home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest'...
remote: Enumerating objects: 28637, done.
remote: Counting objects: 100% (74/74), done.
remote: Compressing objects: 100% (53/53), done.
remote: Total 28637 (delta 36), reused 22 (delta 20), pack-reused 28563 (from 2)
Receiving objects: 100% (28637/28637), 13.79 MiB | 2.54 MiB/s, done.
Resolving deltas: 100% (21272/21272), done.
```

```sh
$ cd third-party/gtest && git checkout release-1.8.1 && cd ../..
```

Вывод:

```sh
Note: switching to 'release-1.8.1'.

You are in 'detached HEAD' state. You can look around, make experimental
changes and commit them, and you can discard any commits you make in this
state without impacting any branches by switching back to a branch.

If you want to create a new branch to retain commits you create, you may
do so (now or later) by using -c with the switch command. Example:

  git switch -c <new-branch-name>

Or undo this operation with:

  git switch -

Turn off this advice by setting config variable advice.detachedHead to false

HEAD is now at 2fe3bd99 Merge pull request #1433 from dsacre/fix-clang-warnings
```

```sh
$ git add third-party/gtest
$ git commit -m"added gtest framework"
```

```sh
$ gsed -i '/option(BUILD_EXAMPLES "Build examples" OFF)/a\
option(BUILD_TESTS "Build tests" OFF)
' CMakeLists.txt
```

```sh
$ cat >> CMakeLists.txt <<EOF
if(BUILD_TESTS)

    enable_testing()

    add_subdirectory(third-party/gtest)

    file(GLOB ${PROJECT_NAME}_TEST_SOURCES
        tests/*.cpp
    )

    add_executable(
        check
        ${${PROJECT_NAME}_TEST_SOURCES}
    )

    target_link_libraries(
        check
        ${PROJECT_NAME}
        gtest_main
    )

    add_test(
        NAME check
        COMMAND check
    )

    add_executable(
        banking_tests
        banking/tests/test_account.cpp
        banking/tests/test_transaction.cpp
    )

    target_include_directories(
        banking_tests PUBLIC
        banking
    )

    target_link_libraries(
        banking_tests
        banking
        gtest
        gtest_main
        gmock
        pthread
    )

    add_test(
        NAME banking_tests
        COMMAND banking_tests
    )

endif()
EOF
```

```sh
$ mkdir tests
$ cat > tests/test1.cpp <<EOF
#include <print.hpp>

#include <gtest/gtest.h>

TEST(Print, InFileStream)
{
  std::string filepath = "file.txt";
  std::string text = "hello";
  std::ofstream out{filepath};

  print(text, out);
  out.close();

  std::string result;
  std::ifstream in{filepath};
  in >> result;

  EXPECT_EQ(result, text);
}
EOF
```

```sh
$ cmake -H. -B_build -DBUILD_TESTS=ON
$ cmake --build _build
```

Вывод:

```sh
[  4%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[  9%] Linking CXX static library libprint.a
[  9%] Built target print
[ 13%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
In file included from /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest-all.cc:42:
/home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest-death-test.cc: In function ‘bool testing::internal::StackGrowsDown()’:
/home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest-death-test.cc:1224:24: warning: ‘dummy’ may be used uninitialized [-Wmaybe-uninitia>
 1224 |   StackLowerThanAddress(&dummy, &result);
      |   ~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~
/home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest-death-test.cc:1214:13: note: by argument 1 of type ‘const void*’ to ‘void testing::>
 1214 | static void StackLowerThanAddress(const void* ptr, bool* result) {
      |             ^~~~~~~~~~~~~~~~~~~~~
/home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest-death-test.cc:1222:7: note: ‘dummy’ declared here
 1222 |   int dummy;
      |       ^~~~~
[ 18%] Linking CXX static library libgtest.a
[ 18%] Built target gtest
[ 22%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[ 27%] Linking CXX static library libgtest_main.a
[ 27%] Built target gtest_main
[ 31%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[ 36%] Linking CXX executable check
[ 36%] Built target check
[ 40%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 45%] Linking CXX static library libformatter.a
[ 45%] Built target formatter
[ 50%] Building CXX object formatter_ex_lib/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 54%] Linking CXX static library libformatter_ex.a
[ 54%] Built target formatter_ex
[ 59%] Building CXX object solver_lib/CMakeFiles/solver.dir/solver.cpp.o
[ 63%] Linking CXX static library libsolver.a
[ 63%] Built target solver
[ 68%] Building CXX object hello_world_application/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 72%] Linking CXX executable hello_world
[ 72%] Built target hello_world
[ 77%] Building CXX object solver_application/CMakeFiles/solver_application.dir/equation.cpp.o
[ 81%] Linking CXX executable solver_application
[ 86%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 90%] Linking CXX static library libgmock.a
[ 90%] Built target gmock
[ 95%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[100%] Linking CXX static library libgmock_main.a
[100%] Built target gmock_main
```

```sh
$ cmake --build _build --target test
```

Вывод:

```sh
Running tests...
Test project /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/_build
    Start 1: check
1/1 Test #1: check ............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```

```sh
$ _build/check
```

Вывод:

```sh
Running main() from /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest_main.cc
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from Print
[ RUN      ] Print.InFileStream
[       OK ] Print.InFileStream (0 ms)
[----------] 1 test from Print (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test.
```

```sh
$ cmake --build _build --target test -- ARGS=--verbose
```

```sh
$ gsed -i 's/lab04/lab66/g' README.md
$ gsed -i 's/\(DCMAKE_INSTALL_PREFIX=_install\)/\1 -DBUILD_TESTS=ON/' .travis.yml
$ gsed -i '/cmake --build _build --target install/a\
- cmake --build _build --target test -- ARGS=--verbose
' .travis.yml
```

```sh
$ travis lint
```

```sh
$ git add .travis.yml
$ git add tests
$ git add -p
$ git commit -m"added tests"
$ git push origin master
```

```sh
$ travis login --auto
$ travis enable
```

```sh
$ mkdir artifacts
$ sleep 20s && gnome-screenshot --file artifacts/screenshot.png
# for macOS: $ screencapture -T 20 artifacts/screenshot.png
# open https://github.com/${GITHUB_USERNAME}/lab66
```

## Report

```sh
$ popd
$ export LAB_NUMBER=05
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gist REPORT.md
```

## Homework

### Задание
1. Создайте `CMakeList.txt` для библиотеки *banking*.
2. Создайте модульные тесты на классы `Transaction` и `Account`.
    * Используйте mock-объекты.
    * Покрытие кода должно составлять 100%.
3. Настройте сборочную процедуру на **TravisCI**.
4. Настройте [Coveralls.io](https://coveralls.io/).

Команды:

```sh
$cd banking
$nano CMakelists.txt
```

В CMakelists.txt записываем следующий код:

```sh
cmake_minimum_required(VERSION 3.10)

project(banking)

add_library(banking STATIC
    Account.cpp
    Transaction.cpp
)

target_include_directories(banking PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
```

Команды:

```sh
$ mkdir tests
$cd tests
$mkdir mocks
$cd mocks
$ nano MockAccount.hpp
```

В  MockAccount.hpp записываем следующий код:

```sh
#ifndef MOCK_ACCOUNT_HPP
#define MOCK_ACCOUNT_HPP

#include "../../Account.h"
#include <gmock/gmock.h>

class MockAccount : public Account {
public:
    MockAccount(int id, int balance)
        : Account(id, balance) {}

    MOCK_CONST_METHOD0(GetBalance, int());

    MOCK_METHOD1(ChangeBalance, void(int));

    MOCK_METHOD0(Lock, void());

    MOCK_METHOD0(Unlock, void());
};

#endif
```

Создаем MockTransaction.hpp

```sh
$touch MockTransaction.hpp
$nano MockTransaction.hpp
```

MockTransaction.hpp содержит следующий код:

```sh
ifndef MOCK_TRANSACTION_HPP
#define MOCK_TRANSACTION_HPP

#include "../../Transaction.h"
#include <gmock/gmock.h>

class MockTransaction : public Transaction {
public:
    MOCK_METHOD3(
        SaveToDataBase,
        void(Account& from, Account& to, int sum)
    );
};

#endif
```

```sh
$ cd ..
$nano test_account.cpp
```

test_account.cpp содержит следующий код:

```sh
#include <gtest/gtest.h>

#include "Account.h"

TEST(AccountTest, Constructor)
{
    Account acc(1, 100);

    EXPECT_EQ(acc.id(), 1);
    EXPECT_EQ(acc.GetBalance(), 100);
}

TEST(AccountTest, LockAndChangeBalance)
{
    Account acc(1, 100);

    acc.Lock();

    acc.ChangeBalance(50);

    EXPECT_EQ(acc.GetBalance(), 150);

    acc.Unlock();
}

TEST(AccountTest, ChangeBalanceWithoutLockThrows)
{
    Account acc(1, 100);

    EXPECT_THROW(acc.ChangeBalance(50), std::runtime_error);
}

TEST(AccountTest, LockTwiceThrows)
{
    Account acc(1, 100);

    acc.Lock();

    EXPECT_THROW(acc.Lock(), std::runtime_error);
}

TEST(AccountTest, UnlockWithoutLock)
{
    Account acc(1, 100);

    EXPECT_NO_THROW(acc.Unlock());
}

```

Создаем test_transaction.cpp

```sh
$touch test_transaction.cpp
$nano test_transaction.cpp
```

test_transaction.cpp должен содержать слелующий код:

```sh
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Transaction.h"
#include "Account.h"
#include "mocks/MockAccount.hpp"
#include "mocks/MockTransaction.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;

// 1. Перевод на тот же аккаунт
TEST(TransactionTest, SameAccountThrows)
{
    MockAccount acc(1, 1000);

    Transaction tx;

    EXPECT_THROW(tx.Make(acc, acc, 200), std::logic_error);
}

// 2. Отрицательная сумма
TEST(TransactionTest, NegativeSumThrows)
{
    MockAccount from(1, 1000);
    MockAccount to(2, 500);

    Transaction tx;

    EXPECT_THROW(tx.Make(from, to, -100), std::invalid_argument);
}

// 3. Слишком маленькая сумма
TEST(TransactionTest, TooSmallSumThrows)
{
    MockAccount from(1, 1000);
    MockAccount to(2, 500);

Transaction tx;

    EXPECT_THROW(tx.Make(from, to, 50), std::logic_error);
}

// 4. Комиссия слишком большая
TEST(TransactionTest, FeeTooLargeReturnsFalse)
{
    MockAccount from(1, 1000);
    MockAccount to(2, 500);

    Transaction tx;
    tx.set_fee(100);

    EXPECT_FALSE(tx.Make(from, to, 150));
}

// 5. Успешный перевод
TEST(TransactionTest, SuccessfulTransfer)
{
    MockAccount from(1, 1000);
    MockAccount to(2, 500);

    Transaction tx;
    tx.set_fee(1);

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);

    EXPECT_CALL(to, ChangeBalance(200)).Times(1);

    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(1000));

    EXPECT_CALL(from, ChangeBalance(-201)).Times(1);

    EXPECT_CALL(from, Unlock()).Times(1);
 EXPECT_TRUE(tx.Make(from, to, 200));
}

// 6. Недостаточно денег
TEST(TransactionTest, InsufficientFunds)
{
    MockAccount from(1, 100);
    MockAccount to(2, 500);

    Transaction tx;
    tx.set_fee(1);

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);

    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(100));

    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    EXPECT_FALSE(tx.Make(from, to, 150));
}

// 7. SaveToDataBase вызывается
TEST(TransactionTest, SaveToDataBaseIsCalled)
{
    MockAccount from(1, 1000);
    MockAccount to(2, 500);
    MockTransaction tx; // mock transaction

    tx.set_fee(1);

    EXPECT_CALL(from, Lock()).Times(1);
    EXPECT_CALL(to, Lock()).Times(1);
 EXPECT_CALL(to, ChangeBalance(200)).Times(1);

    EXPECT_CALL(from, GetBalance())
        .WillOnce(Return(1000));

    EXPECT_CALL(from, ChangeBalance(-201)).Times(1);

    EXPECT_CALL(tx, SaveToDataBase(_, _, 200)).Times(1);

    EXPECT_CALL(from, Unlock()).Times(1);
    EXPECT_CALL(to, Unlock()).Times(1);

    EXPECT_TRUE(tx.Make(from, to, 200));
}

TEST(TransactionTest, RealTransactionCoverage)
{
    Account from(1, 1000);
    Account to(2, 500);

    Transaction tx;
    tx.set_fee(1);

    EXPECT_TRUE(tx.Make(from, to, 200));

    EXPECT_EQ(from.GetBalance(), 799);
    EXPECT_EQ(to.GetBalance(), 700);
}
```

```sh
$nano CMakeLists.txt
```

Обновим CMakeLists.txt в корне папки теперь там будет следующий код:

```sh
cmake_minimumFF_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=maybe-uninitialized")

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)

project(print)

if(BUILD_TESTS)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

add_library(print STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp
)

target_include_directories(print PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(BUILD_EXAMPLES)

    file(GLOB EXAMPLE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp"
    )

    foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})

        get_filename_component(
            EXAMPLE_NAME
            ${EXAMPLE_SOURCE}
            NAME_WE
        )

        add_executable(
            ${EXAMPLE_NAME}
            ${EXAMPLE_SOURCE}
        )

        target_link_libraries(
            ${EXAMPLE_NAME}
            print
        )

        install(
            TARGETS ${EXAMPLE_NAME}
            RUNTIME DESTINATION bin
        )

    endforeach()

endif()

install(
    TARGETS print
    EXPORT print-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
)

install(
    EXPORT print-config
    DESTINATION cmake
)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(hello_world_application)
add_subdirectory(solver_application)
add_subdirectory(banking)

if(BUILD_TESTS)

    enable_testing()

    add_subdirectory(third-party/gtest)

    file(GLOB ${PROJECT_NAME}_TEST_SOURCES
        tests/*.cpp
    )

    add_executable(
        check
        ${${PROJECT_NAME}_TEST_SOURCES}
    )

    target_link_libraries(
        check
        ${PROJECT_NAME}
        gtest_main
    )

    add_test(
        NAME check
        COMMAND check
    )

    add_executable(
        banking_tests
        banking/tests/test_account.cpp
        banking/tests/test_transaction.cpp
    )

    target_include_directories(
        banking_tests PUBLIC
        banking
    )

    target_link_libraries(
        banking_tests
        banking
        gtest
        gtest_main
        gmock
        pthread
    )

    add_test(
        NAME banking_tests
        COMMAND banking_tests
    )

endif()
```

Команды:

```sh
$rm -rf _build
$cmake -H. -B_build -DBUILD_TESTS=ON
```

Вывод(для rm -rf _build):

```sh
CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
CMake Deprecation Warning at formatter_lib/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at formatter_ex_lib/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at solver_lib/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at hello_world_application/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at solver_application/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at third-party/gtest/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at third-party/gtest/googlemock/CMakeLists.txt:42 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at third-party/gtest/googletest/CMakeLists.txt:49 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Warning (dev) at third-party/gtest/googletest/cmake/internal_utils.cmake:239 (find_package):
  Policy CMP0148 is not set: The FindPythonInterp and FindPythonLibs modules
  are removed.  Run "cmake --help-policy CMP0148" for policy details.  Use
  the cmake_policy command to set the policy and suppress this warning.

Call Stack (most recent call first):
  third-party/gtest/googletest/CMakeLists.txt:84 (include)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Found PythonInterp: /usr/bin/python3 (found version "3.12.3") 
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE  
-- Configuring done (0.6s)
-- Generating done (0.0s)
-- Build files have been written to: /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/_build
```

Команда:

```sh
$cmake --build _build
```

Вывод:

```sh
[  3%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[  7%] Linking CXX static library libprint.a
[  7%] Built target print
[ 10%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
In file included from /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest-all.cc:42:
/home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest-death-test.cc: In function ‘bool testing::internal::StackGrowsDown()’:
/home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest-death-test.cc:1224:24: warning: ‘dummy’ may be used uninitialized [-Wmaybe-uninitialized]
 1224 |   StackLowerThanAddress(&dummy, &result);
      |   ~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~
/home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest-death-test.cc:1214:13: note: by argument 1 of type ‘const void*’ to ‘void testing::internal::StackLowerThanAddress(const void*, bool*)’ declared here
 1214 | static void StackLowerThanAddress(const void* ptr, bool* result) {
      |             ^~~~~~~~~~~~~~~~~~~~~
/home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest-death-test.cc:1222:7: note: ‘dummy’ declared here
 1222 |   int dummy;
      |       ^~~~~
[ 14%] Linking CXX static library libgtest.a
[ 14%] Built target gtest
[ 17%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[ 21%] Linking CXX static library libgtest_main.a
[ 21%] Built target gtest_main
[ 25%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[ 28%] Linking CXX executable check
[ 28%] Built target check
[ 32%] Building CXX object banking/CMakeFiles/banking.dir/Account.cpp.o
[ 35%] Building CXX object banking/CMakeFiles/banking.dir/Transaction.cpp.o
[ 39%] Linking CXX static library libbanking.a
[ 39%] Built target banking
[ 42%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 46%] Linking CXX static library libgmock.a
[ 46%] Built target gmock
[ 50%] Building CXX object CMakeFiles/banking_tests.dir/banking/tests/test_account.cpp.o
[ 53%] Building CXX object CMakeFiles/banking_tests.dir/banking/tests/test_transaction.cpp.o
[ 57%] Linking CXX executable banking_tests
[ 57%] Built target banking_tests
[ 60%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 64%] Linking CXX static library libformatter.a
[ 64%] Built target formatter
[ 67%] Building CXX object formatter_ex_lib/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 71%] Linking CXX static library libformatter_ex.a
[ 71%] Built target formatter_ex
[ 75%] Building CXX object solver_lib/CMakeFiles/solver.dir/solver.cpp.o
[ 78%] Linking CXX static library libsolver.a
[ 78%] Built target solver
[ 82%] Building CXX object hello_world_application/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 85%] Linking CXX executable hello_world
[ 85%] Built target hello_world
[ 89%] Building CXX object solver_application/CMakeFiles/solver_application.dir/equation.cpp.o
[ 92%] Linking CXX executable solver_application
[ 92%] Built target solver_application
[ 96%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[100%] Linking CXX static library libgmock_main.a
[100%] Built target gmock_main
```

Команды:

```sh
$rm -rf _build
$ cmake --build _build --target test -- ARGS=--verbose
```

Вывод(для  cmake --build _build --target test -- ARGS=--verbose):

```sh
Running tests...
UpdateCTestConfiguration  from :/home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/_build/DartConfiguration.tcl
UpdateCTestConfiguration  from :/home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/_build/DartConfiguration.tcl
Test project /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/_build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: check

1: Test command: /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/_build/check
1: Working Directory: /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/_build
1: Test timeout computed to be: 10000000
1: Running main() from /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest_main.cc
1: [==========] Running 1 test from 1 test case.
1: [----------] Global test environment set-up.
1: [----------] 1 test from Print
1: [ RUN      ] Print.InFileStream
1: [       OK ] Print.InFileStream (0 ms)
1: [----------] 1 test from Print (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 1 test from 1 test case ran. (0 ms total)
1: [  PASSED  ] 1 test.
1/2 Test #1: check ............................   Passed    0.01 sec
test 2
    Start 2: banking_tests

2: Test command: /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/_build/banking_tests
2: Working Directory: /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/_build
2: Test timeout computed to be: 10000000
2: Running main() from /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/third-party/gtest/googletest/src/gtest_main.cc
2: [==========] Running 13 tests from 2 test cases.
2: [----------] Global test environment set-up.
2: [----------] 5 tests from AccountTest
2: [ RUN      ] AccountTest.Constructor
2: [       OK ] AccountTest.Constructor (0 ms)
2: [ RUN      ] AccountTest.LockAndChangeBalance
2: [       OK ] AccountTest.LockAndChangeBalance (0 ms)
2: [ RUN      ] AccountTest.ChangeBalanceWithoutLockThrows
2: [       OK ] AccountTest.ChangeBalanceWithoutLockThrows (0 ms)
2: [ RUN      ] AccountTest.LockTwiceThrows
2: [       OK ] AccountTest.LockTwiceThrows (0 ms)
2: [ RUN      ] AccountTest.UnlockWithoutLock
2: [       OK ] AccountTest.UnlockWithoutLock (0 ms)
2: [----------] 5 tests from AccountTest (0 ms total)
2: 
2: [----------] 8 tests from TransactionTest
2: [ RUN      ] TransactionTest.SameAccountThrows
2: [       OK ] TransactionTest.SameAccountThrows (0 ms)
2: [ RUN      ] TransactionTest.NegativeSumThrows
2: [       OK ] TransactionTest.NegativeSumThrows (0 ms)
2: [ RUN      ] TransactionTest.TooSmallSumThrows
2: [       OK ] TransactionTest.TooSmallSumThrows (0 ms)
2: [ RUN      ] TransactionTest.FeeTooLargeReturnsFalse
2: [       OK ] TransactionTest.FeeTooLargeReturnsFalse (0 ms)
2: [ RUN      ] TransactionTest.SuccessfulTransfer
2: [       OK ] TransactionTest.SuccessfulTransfer (0 ms)
2: [ RUN      ] TransactionTest.InsufficientFunds
2: [       OK ] TransactionTest.InsufficientFunds (0 ms)
2: [ RUN      ] TransactionTest.SaveToDataBaseIsCalled
2: [       OK ] TransactionTest.SaveToDataBaseIsCalled (0 ms)
2: [ RUN      ] TransactionTest.RealTransactionCoverage
2: [       OK ] TransactionTest.RealTransactionCoverage (0 ms)
2: [----------] 8 tests from TransactionTest (0 ms total)
2: 
2: [----------] Global test environment tear-down
2: [==========] 13 tests from 2 test cases ran. (0 ms total)
2: [  PASSED  ] 13 tests.
2/2 Test #2: banking_tests ....................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 2

Total Test time (real) =   0.03 sec
```

Команда:

```sh
$gcovr -r . \ --filter '.*banking/.*' \ --exclude '.*tests.*' \ --exclude '.*mocks.*' \ --exclude '.*third-party.*' \ --exclude '.*_build.*' \ --print-summary 
```

Вывод:

```sh
(INFO) Reading coverage data...
(INFO) Writing coverage report...
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: .
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
banking/Account.cpp                           20      20   100%
banking/Transaction.cpp                       26      26   100%
------------------------------------------------------------------------------
TOTAL                                         46      46   100%
------------------------------------------------------------------------------
```
## Links

Далее исправляем ci.yml:

Команды:

```sh
$cd .github/workflows
$nano ci.yml
```

Содержимое ci.yml теперь выглядит вот так:

```sh
name: CI

on:
  push:
    branches: [ master, main ]

  pull_request:
    branches: [ master, main ]

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v4
        with:
          submodules: recursive

      - name: Install dependencies
        run: sudo apt-get update && sudo apt-get install -y cmake lcov gcovr libgtest-dev libgmock-dev

      - name: Configure CMake with coverage
        run: cmake -B _build -DBUILD_TESTS=ON -DCMAKE_CXX_FLAGS="--coverage -O0 -g -w"

      - name: Build
        run: cmake --build _build

      - name: Run tests
        working-directory: _build
        run: ctest --verbose

      - name: Collect coverage
        working-directory: _build
        run: |
          gcovr -r .. \
            --filter '.*banking/.*' \
            --exclude '.*tests.*' \
            --exclude '.*mocks.*' \
            --xml coverage.xml
```

Далее добавляем файлы и делаем коммит

Команды:

```sh
$git add .
$git commit -m "update ci"
$git push origin main
```

## Links

- [C++ CI: Travis, CMake, GTest, Coveralls & Appveyor](http://david-grs.github.io/cpp-clang-travis-cmake-gtest-coveralls-appveyor/)
- [Boost.Tests](http://www.boost.org/doc/libs/1_63_0/libs/test/doc/html/)
- [Catch](https://github.com/catchorg/Catch2)

```
Copyright (c) 2015-2021 The ISC Authors
```
