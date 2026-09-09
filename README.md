# Laboratory work VI

## Цель работы

Целью лабораторной работы является изучение системы пакетирования CPack и настройка автоматической сборки пакетов для разных операционных систем с использованием GitHub Actions

В ходе работы были настроены пакеты для Linux, Windows и macOS, а также автоматическое создание GitHub Release при публикации нового тега

## Используемые инструменты

В процессе выполнения лабораторной работы использовались следующие инструменты

- Git и GitHub
- CMake
- CPack
- GitHub Actions
- Ubuntu Linux
- nano
- GitHub Releases

## Подготовка проекта

Работа выполнялась в репозитории `lab66`

В начале была проверена конфигурация проекта и версия CMake во всех файлах `CMakeLists.txt`

Для поиска используемых версий была выполнена команда

```bash
grep -R "cmake_minimum_required" --include="CMakeLists.txt" .
```

После обновления минимальной версии CMake результат проверки выглядел следующим образом

```text
./formatter_ex_lib/CMakeLists.txt:cmake_minimum_required(VERSION 3.10)
./solver_lib/CMakeLists.txt:cmake_minimum_required(VERSION 3.10)
./formatter_lib/CMakeLists.txt:cmake_minimum_required(VERSION 3.10)
./solver_application/CMakeLists.txt:cmake_minimum_required(VERSION 3.10)
./CMakeLists.txt:cmake_minimum_required(VERSION 3.10)
./banking/CMakeLists.txt:cmake_minimum_required(VERSION 3.10)
./hello_world_application/CMakeLists.txt:cmake_minimum_required(VERSION 3.10)
```

Для обеспечения совместимости проекта с современной версией CMake минимальная версия была изменена на 3.10 во всех необходимых файлах

Изменения были сохранены следующими коммитами

```text
040d9f9 update minimum CMake version
f02c232 update CMake minimum version for all targets
```

## Настройка CPack

Для пакетирования проекта была добавлена конфигурация CPack

Были настроены версия пакета, описание проекта, контактная информация и параметры генераторов пакетов

Начальная конфигурация CPack была добавлена следующим коммитом

```text
e9f67f5 added cpack config
```

После этого конфигурация пакетирования была изменена таким образом, чтобы создаваемые пакеты содержали приложение `solver`

```text
7e516a4 configure solver packaging
```

Также имя RPM-пакета было изменено на `solver`

```text
76cf1aa rename RPM package to solver
```

## Проверка сборки проекта

После изменения конфигурационных файлов была выполнена очистка предыдущей директории сборки и повторная конфигурация проекта

```bash
rm -rf _build && cmake -B _build
```

Результат выполнения команды

```text
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/vboxuser/kasirskaaalina09-gif/workspace/projects/lab66/_build
```

После успешной конфигурации была выполнена сборка проекта

```bash
rm -rf _build && cmake -B _build && cmake --build _build
```

Результат сборки

```text
[  6%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 13%] Linking CXX static library libprint.a
[ 13%] Built target print
[ 20%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 26%] Linking CXX static library libformatter.a
[ 26%] Built target formatter
[ 33%] Building CXX object formatter_ex_lib/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 40%] Linking CXX static library libformatter_ex.a
[ 40%] Built target formatter_ex
[ 46%] Building CXX object solver_lib/CMakeFiles/solver.dir/solver.cpp.o
[ 53%] Linking CXX static library libsolver.a
[ 53%] Built target solver
[ 60%] Building CXX object hello_world_application/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 66%] Linking CXX executable hello_world
[ 66%] Built target hello_world
[ 73%] Building CXX object solver_application/CMakeFiles/solver_application
астроена система GitHub Actions, которая автоматически собирает проект на Linux, Windows и macOS

Для каждой платформы создается подходящий формат пакета, после чего результаты автоматически публикуются в GitHub Release

Настроенная система позволяет создавать новые релизы приложения `solver` без ручной сборки и загрузки пакетов.d
ir/equation.cpp.o
[ 80%] Linking CXX executable solver_application
[ 80%] Built target solver_application
[ 86%] Building CXX object banking/CMakeFiles/banking.dir/Account.cpp.o
[ 93%] Building CXX object banking/CMakeFiles/banking.dir/Transaction.cpp.o
[100%] Linking CXX static library libbanking.a
[100%] Built target banking
```

Таким образом, проект успешно конфигурируется и собирается в Linux

## Исправление параметров компилятора

При выполнении сборки в Windows возникла ошибка, связанная с параметром компилятора GNU

```text
-Wno-error=maybe-uninitialized
```

Этот параметр поддерживается GCC, но не поддерживается компилятором Microsoft Visual C++

Для исправления параметр был ограничен проверкой используемого компилятора

```cmake
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=maybe-uninitialized")
endif()
```

После этого проект смог успешно конфигурироваться и собираться как в Linux, так и в Windows

Исправление было сохранено следующим коммитом

```text
c64c711 fix compiler-specific warning flags
```

## Настройка GitHub Actions

Для автоматической сборки и создания пакетов был настроен workflow

```text
.github/workflows/ci.yml
```

Workflow запускается при публикации тега, название которого начинается с буквы `v`

```yaml
on:
  push:
    tags:
      - "v*"
```

Таким образом, каждый новый тег автоматически запускает процесс сборки и пакетирования проекта

Начальная настройка CI для работы с CPack была добавлена следующим коммитом

```text
9c46b43 update CI for CPack packages
```

## Сборка пакетов для Linux

Для Linux используется GitHub Actions runner

```text
ubuntu-latest
```

Перед сборкой устанавливаются необходимые зависимости

```bash
sudo apt-get update
sudo apt-get install -y cmake rpm
```

После этого выполняется конфигурация проекта

```bash
cmake -B _build
```

Затем выполняется сборка

```bash
cmake --build _build
```

После успешной сборки создается DEB-пакет

```bash
cd _build
cpack -G DEB
```

Также создается RPM-пакет

```bash
cd _build
cpack -G RPM
```

## Сборка пакета для Windows

Для Windows используется runner

```text
windows-latest
```

Сначала выполняется конфигурация проекта

```bash
cmake -B _build
```

Затем выполняется сборка в конфигурации Release

```bash
cmake --build _build --config Release
```

После этого создается MSI-пакет с использованием генератора WIX

```bash
cd _build
cpack -G WIX
```

Поддержка создания WIX-пакета для Windows была добавлена следующим коммитом

```text
4975626 add Windows WIX package build
```

## Сборка пакета для macOS

Для macOS используется runner

```text
macos-latest
```

Проект конфигурируется командой

```bash
cmake -B _build
```

После этого выполняется сборка

```bash
cmake --build _build --config Release
```

Для создания DMG-образа используется генератор DragNDrop

```bash
cd _build
cpack -G DragNDrop
```

Поддержка создания пакета для macOS была добавлена следующим коммитом

```text
29d9a50 add macOS DragNDrop package build
```

## Загрузка пакетов в GitHub Actions artifacts

После создания пакетов результаты сборки сохраняются как artifacts GitHub Actions

Для Linux сохраняются DEB и RPM пакеты

```yaml
- name: Upload Linux packages
  uses: actions/upload-artifact@v4
  with:
    name: linux-packages
    path: |
      _build/*.deb
      _build/*.rpm
```

Для Windows сохраняется MSI-пакет

```yaml
- name: Upload Windows package
  uses: actions/upload-artifact@v4
  with:
    name: windows-package
    path: _build/*.msi
```

Для macOS сохраняется DMG-пакет

```yaml
- name: Upload macOS package
  uses: actions/upload-artifact@v4
  with:
    name: macos-package
    path: _build/*.dmg
```

Загрузка CPack-пакетов как artifacts была добавлена следующим коммитом

```text
cd334ff upload CPack packages as artifacts
```

## Автоматическое создание GitHub Release

После успешного завершения сборки для всех трех операционных систем запускается отдельная задача создания GitHub Release

Она ожидает завершения следующих задач

```yaml
needs:
  - build-linux
  - build-windows
  - build-macos
```

Для создания релиза workflow получает все ранее созданные artifacts

```yaml
- name: Download all packages
  uses: actions/download-artifact@v4
  with:
    path: release-files
    merge-multiple: true
```

Для проверки содержимого директории используется команда

```bash
ls -la release-files
```

После этого создается GitHub Release и в него добавляются все созданные пакеты

```bash
gh release create "${{ github.ref_name }}" \
  release-files/* \
  --generate-notes
```

Автоматическое создание GitHub Release было добавлено следующим коммитом

```text
1e55dcc add automatic GitHub release
```

При первом запуске задачи создания релиза возникла ошибка

```text
failed to run git: fatal: not a git repository (or any of the parent directories): .git
```

Причиной было отсутствие checkout репозитория в задаче `create-release`

Для исправления был добавлен следующий шаг

```yaml
- uses: actions/checkout@v4
```

Исправление было сохранено коммитом

```text
00888d0 fix release job checkout
```

После внесения исправления workflow успешно завершился

Все задачи для Linux, Windows и macOS были выполнены успешно, после чего GitHub автоматически создал Release и загрузил в него готовые пакеты

## Используемые теги

В процессе выполнения лабораторной работы использовались следующие теги

```text
v0.1.0.0
v0.1.1.0
v0.1.1.1
v0.1.1.2
v0.1.1.3
v0.1.1.4
v0.1.1.5
```

Создание нового тега выполняется командой

```bash
git tag v0.1.1.5
```

После этого тег отправляется на GitHub

```bash
git push origin v0.1.1.5
```

Публикация тега запускает GitHub Actions workflow

После успешного выполнения workflow в разделе Releases появляются созданные пакеты

## История коммитов

Для проверки истории разработки проекта была выполнена команда

```bash
git log --oneline --all
```

Результат

```text
00888d0 (HEAD -> master, tag: v0.1.1.5, origin/master) fix release job checkout
1e55dcc (tag: v0.1.1.4) add automatic GitHub release
cd334ff (tag: v0.1.1.3) upload CPack packages as artifacts
c64c711 (tag: v0.1.1.2) fix compiler-specific warning flags
f02c232 (tag: v0.1.1.1) update CMake minimum version for all targets
040d9f9 update minimum CMake version
29d9a50 (tag: v0.1.1.0) add macOS DragNDrop package build
4975626 add Windows WIX package build
76cf1aa rename RPM package to solver
7e516a4 configure solver packaging
9c46b43 update CI for CPack packages
e9f67f5 (tag: v0.1.0.0) added cpack config
```

## Итоговая конфигурация CI

В результате выполнения лабораторной работы был настроен workflow, состоящий из четырех основных задач

- `build-linux` выполняет сборку проекта и создает DEB и RPM пакеты
- `build-windows` выполняет сборку проекта и создает MSI пакет
- `build-macos` выполняет сборку проекта и создает DMG пакет
- `create-release` получает все созданные пакеты и автоматически публикует их в GitHub Release

Workflow запускается только при публикации тега

## Результат работы

В ходе выполнения лабораторной работы была изучена система пакетирования CPack

Была настроена конфигурация проекта для создания пакетов с приложением `solver`

Была обеспечена совместимость проекта с современными версиями CMake на Linux, Windows и macOS

Был исправлен параметр компилятора, который поддерживался только GCC и вызывал ошибку при сборке в Windows

Была настроена автоматическая сборка проекта для трех операционных систем

Для Linux автоматически создаются пакеты

```text
.deb
.rpm
```

Для Windows автоматически создается пакет

```text
.msi
```

Для macOS автоматически создается пакет

```text
.dmg
```

Все созданные пакеты сначала сохраняются как GitHub Actions artifacts

После успешного завершения сборки для всех платформ они автоматически добавляются в GitHub Release

Таким образом, при создании нового тега выполняется полный процесс автоматической сборки, пакетирования и публикации новой версии приложения `solver`

## Вывод

В процессе выполнения лабораторной работы были изучены возможности CPack для создания пакетов программного обеспечения

