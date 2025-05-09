

Номер 41.

Абстрактный класс Shape: Содержит чисто виртуальную функцию area(), что делает класс абстрактным.
Виртуальный деструктор добавлен для корректного удаления объектов производных классов.
Класс Circle: Проверяет, что радиус положительный.
Реализует формулу площади круга.
Класс Rectangle: Проверяет, что ширина и высота положительные.
Реализует формулу площади прямоугольника.
Класс Triangle: Проверяет, что все стороны положительные и выполняются условия неравенства треугольника.
Использует формулу Герона для вычисления площади.
Обработка исключений: Если параметры фигуры некорректны, выбрасывается std::invalid_argument.
В main() демонстрируется обработка исключений.

Номер 42.

Базовый класс Employee: Имеет чисто виртуальную функцию calculateSalary().
Проверяет, что hoursWorked не отрицательное (иначе бросает invalid_argument).
Содержит виртуальный деструктор для корректного удаления объектов.
FullTimeEmployee (полная занятость):Получает фиксированную зарплату (monthlySalary), независимо от часов. Проверяет, что зарплата не отрицательная.
PartTimeEmployee (частичная занятость): Зарплата вычисляется как hoursWorked * hourlyRate.
Проверяет, что почасовая ставка не отрицательная.
Обработка исключений: Если передать отрицательные часы или зарплату, программа выбросит исключение.

Номер 43.

Базовый класс DataReader, содержит виртуальную функцию readData(), служит интерфейсом для чтения файлов разных форматов.
Функция checkFileExists(), проверяет доступность файла, бросает исключение при отсутствии файла.
Класс CSVReader, наследуется от DataReader, реализует чтение CSV-файлов.
Алгоритм чтения CSV, построчно обрабатывает файл, разделяет строки по запятым, проверяет согласованность столбцов.
Класс XMLReader, наследуется от DataReader, реализует чтение XML-файлов упрощенного формата.
Алгоритм чтения XML, анализирует теги <row> и <cell>, проверяет правильность вложенности тегов.

Номер 44.

Базовый класс Shape, абстрактный, определяет интерфейс для всех фигур, содержит чисто виртуальные функции.
Функция scale(), виртуальная, предназначена для масштабирования фигуры, в базовом классе объявлена как чисто виртуальная.
Функция checkScaleFactor(), защищенная, проверяет положительность коэффициента масштабирования, бросает исключение при ошибке.
Класс Circle, реализует круг, хранит радиус, масштабирование изменяет радиус пропорционально коэффициенту.
Класс Square, реализует квадрат, хранит длину стороны, масштабирование изменяет длину стороны.
Класс Polygon, реализует правильный многоугольник, хранит количество сторон и их длину, масштабирование изменяет длину сторон.

Номер 45.

Базовый класс BankAccount, содержит основные функции для работы со счетом, проверяет корректность операций.
Поля класса, включают номер счета (accountNumber) и баланс (balance), защищены от прямого доступа.
Виртуальная функция transfer(), выполняет перевод средств, проверяет положительность суммы и достаточность баланса.
Функции withdraw() и deposit(), реализуют снятие и пополнение средств с проверкой входных данных.
Исключения, выбрасываются при: отрицательном балансе, недостатке средств, неверной сумме перевода.
Класс SavingsAccount, наследует BankAccount, добавляет процентную ставку (interestRate).
Лимит перевода, установлен на уровне 1000$ (WITHDRAWAL_LIMIT), превышение вызывает исключение.
Метод applyInterest(), начисляет проценты на остаток, доступен только для сберегательного счета.
Класс CheckingAccount, наследует BankAccount, вводит комиссию за перевод (TRANSACTION_FEE).

Номер 46.

Базовый класс NetworkRequest, содержит общую логику для сетевых запросов, проверяет базовые параметры.
Виртуальная функция send(), основная точка расширения, выбрасывает исключения при ошибках сети.
Имитация ошибок, метод simulateNetworkError() случайным образом генерирует ошибки (для демонстрации).
Класс HttpRequest, реализует HTTP-запросы, поддерживает методы GET/POST/PUT/DELETE.
Класс FtpRequest, реализует FTP-операции, поддерживает команды GET/PUT/LIST/DELETE.

Номер 47.

Структура BoundingBox, хранит координаты ограничивающего прямоугольника (xMin, yMin, xMax, yMax).
Базовый класс Shape, абстрактный, содержит чисто виртуальные функции getBoundingBox(), validate() и printInfo().
Класс Circle, реализует окружность с центром (centerX, centerY) и радиусом radius.
Проверки Circle, радиус должен быть положительным, координаты центра - валидными числами.
Класс Rectangle, реализует прямоугольник по двум противоположным вершинам (x1,y1) и (x2,y2).
Проверки Rectangle, ширина и высота не должны быть нулевыми, координаты - валидными.
Класс Polygon, реализует многоугольник по набору вершин (минимум 3 вершины).
Проверки Polygon, количество вершин ≥ 3, все координаты вершин - валидные числа.
Вычисление BoundingBox, для Circle - по радиусу, для Rectangle - по вершинам, для Polygon - поиск min/max координат.

Номер 48.

Базовый класс Exception, наследуется от std::exception, содержит основную логику работы с сообщениями об ошибках.
Виртуальная функция what(), переопределяет метод из std::exception, возвращает сообщение об ошибке.
Модификатор noexcept, гарантирует, что функция what() не будет выбрасывать исключения.
Класс FileNotFoundException, специализированное исключение для случаев отсутствия файлов.
Класс InvalidInputException, предназначен для ошибок валидации входных данных.
Класс NetworkException, обрабатывает ошибки сетевых операций с дополнительными деталями.
Наследование от std::exception, позволяет обрабатывать исключения стандартными средствами C++.

Номер 49.

Базовый класс Task, содержит общую логику для всех задач, проверяет инициализацию.
Флаг initialized, отслеживает состояние инициализации задачи.
Виртуальная функция execute(), основная точка расширения, требует переопределения в производных классах.
Функция checkInitialization(), проверяет готовность задачи к выполнению.
Класс PrintTask, реализует задачу печати, проверяет наличие содержимого.
Класс EmailTask, реализует отправку email, проверяет наличие получателя и темы.
Класс DatabaseTask, реализует работу с БД, проверяет SQL-запрос и строку подключения.

Номер 50.

Базовый класс Shape, содержит базовую проверку угла вращения в виртуальной функции rotate().
Проверки угла, включают проверку на NaN (не число) и бесконечность.
Класс Circle, вращение не изменяет вид окружности, но проверяет корректность угла.
Класс Square, хранит текущий угол поворота, позволяет вращение на любой угол.
Класс Triangle, реализует равносторонний треугольник, разрешает только повороты на 120°.
