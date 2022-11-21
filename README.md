# lessons.cpp

Конспект лекций по С++

Краткий разбор множества тем, связанных с программированием на С++.
Содержит определения, правила, пояснения, примеры.

Материалы взяты из лекций В.С. Чуканова


Лекция 1.
1. Структура классов
2. Наследование и уровни доступа классов
3. Правило конструкирование объектов
4. Неявный вызов конструктора и ключевое слово - explicit
5. Наследование конструкторов
6. Операции классов по умолчанию
7. Деструкторы
8. Виртуальные функции
9. override & final 
10. Рекомендации к проектированию
11. Заключение


Лекция 2.
1. LValue & RValue
2. Move Semantics 
3. RValue reference
4. Форсирование Move Semantics
5. Категории значений
6. XValue
7. Move конструктор
8. Move Semantics и наследование
9. Copy Elision
10. Использование Move Semantics
11. Операторы классов по умолчанию
12. Запрет на использование
13. Static members
14. Singleton
15. Заключение


Лекция 3.
1. string
2. streams
3. i/o fstream
4. stringstream
5. Правила перегрузки функций
6. Статический полиморфизм
7. Вывод типа шаблона
8. Первичные шаблоны и специализации
9. Разрешение перегрузки шаблонных функций
10. Шаблоны классов
11. Частичная специализация классов
12. auto
13. Braced-init-list & initializer_list
14. Braced initialization
15. Template algorithm + Strategy
16. Strategy + Template Algorithm 
17. Принцип Единственной Обязанности


Лекция 4.
1. Функторы
2. Lambda функции
3. STL: Standart Template Library
4. Контейнеры STL
5. std::vector<T>
6. push_back vs emplace_back
7. std::vector<bool>
8. iterator
9. range for
10. std::list<T>
11. std::map<keyType, valueType>
12. reverse & const iterators
13. algorithms
14. Шаблон проектирования: Адаптер

  
Лекция 5.
1. Синоним типа: Using vs Typedef
2. Синонимы указателей на методы
3. Обобщенный синоним типа: Using vs Typedef
4. Исключения
5. Объекты-исключения
6. Обработка исключений
7. Исключения в конструкторах и деструкторах
8. Классы исключений в STL
9. Exception: what?
10. Exception safety
11. Работа с указателями в С++
12. Недостатки указателей
13. Умные указатели
14. Семантика исключительного владения
15. Virtual Constructor
16. Custom deleter
17. std::make_unique
18. std::shared_ptr
19. Constness: unique_ptr & shared_ptr
20. Передача указателей: raw pointer
21. Передача указателей: передача владения
22. Move + const ref
23. Передача указателей: разделение владения
24. Циклические ссылки
25. weak_ptr
26. Сильные и слабые ссылки
27. Захват shared_ptr в lambda
28. Умные указатели: заключение
  