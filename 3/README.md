Номер 21.
Базовый класс Shape. Shape(double x, double y): Конструктор принимает начальные координаты x и y. virtual bool isValidCoordinates(double x, double y) const: Функция, которая предназначена для проверки значений. virtual ~Shape() {}: Виртуальный деструктор. getX() и getY() верните соответствующую координату.
Производный класс Circle. Circle(double x, double y, double radius): Конструктор: принимает координаты x, y и радиус. getRadius() возвращает радиус.
Производный класс Rectangle. Rectangle(double x, double y, double width, double height): Конструктор: принимает координаты x, y, а также ширину и высоту. bool isValidCoordinates(double x, double y) const override: Это переопределяет базовый класс и ограничивает допустимые значения, которые не могут быть отрицательными (для значений x и y). getWidth() и getHeight() возвращает соответствующее значение.

Номер 22.
Базовый класс Database. Database(const std::string& connectionString): Конструктор принимает строку подключения. virtual void connect() const: Функция connect Он выводит сообщение на консоль со строкой подключения. virtual ~Database() {}: Виртуальный деструктор. getConnectionString(): Возвращает строку подключения. 
Производный класс MySQLDatabase. MySQLDatabase(const std::string& connectionString, const std::string& username, const std::string& password): Конструктор: принимает строку подключения, имя пользователя и пароль.
Производный класс SQLiteDatabase. SQLiteDatabase(const std::string& connectionString): Конструктор принимает строку подключения.

Номер 23.
Базовый класс Task. Task(): Конструктор инициализируется initialized в false. initialize(): Установщик для initialized. virtual ~Task() {}: Виртуальный деструктор.
Производный класс PrintTask. PrintTask(const std::string& message): Конструктор выводит сообщение на печать. void execute() const override: Функция, которая будет выполнять сообщение. Она также проверит, что сообщение было initialize(), а затем выведет его на консоль.
Производный класс EmailTask. EmailTask(const std::string& recipient, const std::string& subject, const std::string& body): Конструктор принимает информацию по электронной почте. void execute() const override: Функция выведет значения EmailTask в консоль.

Номер 24.
Базовый класс Shape. virtual double getPerimeter() const: Метод ничего не делает и генерирует исключение при прямом вызове объекта. virtual ~Shape() {}: Виртуальный деструктор.
Производный класс Triangle. Triangle(double sideA, double sideB, double sideC)Конструктор: принимает стороны треугольника, проверяет, являются ли значения отрицательными, и проверяет неравенство треугольника. double getPerimeter() const override: Переопределяет метод и возвращает периметр треугольника.
Производный класс Square. Square(double side): Конструктор: принимает сторону и проверяет ее. double getPerimeter() const override: Переопределяет метод и возвращает периметр квадрата.

Номер 25.
Базовый класс WeatherService. virtual std::string getForecast(const std::string& city) const: Метод выдает исключение. virtual ~WeatherService() {}: Виртуальный деструктор.
Производный класс LocalWeatherService. LocalWeatherService(const std::string& localData): Конструктор принимает локальные данные и проверяет их. std::string getForecast(const std::string& city) const override: Проверьте, есть ли в локальных данных city, а затем верните соответствующий результат.
Производный класс RemoteWeatherService. RemoteWeatherService(const std::string& apiEndpoint): Конструктор принимает конечную точку api и проверяет ее. std::string getForecast(const std::string& city) const overrideЗатем мы получаем данные о погоде с помощью удалённой конечной точки. Мы используем ErrorCity для имитации ошибок.

Номер 26.
Базовый класс Transaction. Transaction(double amount): Конструктор: объект должен быть положительным. virtual void commit(): Реализация метода commit . Если его можно зафиксировать, отображается сообщение. virtual ~Transaction() {}: Виртуальный деструктор. getAmount(): Возвращает сумму транзакции. isCommitted(): Это сделано для того, чтобы можно было узнать, была ли транзакция уже совершена.
Производный класс BankTransaction. BankTransaction(double amount, const std::string& accountNumber): Конструктор должен подтвердить, что номер счета имеет значение. void commit() override: Вызовите реализацию базового класса и убедитесь, что она не превышает 10000, и если это так, то можно продолжить выполнение.
Производный класс CryptoTransaction. CryptoTransaction(double amount, const std::string& walletAddress)Конструктор принимает адрес кошелька и проверяет, что адрес не пустой. void commit() override: Вызовите базовую реализацию, и если это допустимый кошелек.

Номер 27.
Базовый класс Notification. Notification(const std::string& message): Конструктор принимает сообщение и проверяет, что оно не пустое. virtual void send() const: Метод, реализующий отправку, который будет производным. virtual ~Notification() {}: Виртуальный деструктор. getMessage(): Возвращает сообщение.
Производный класс EmailNotification. EmailNotification(const std::string& message, const std::string& recipient, const std::string& subject): Подтвердите, что получатель и субъект существуют. void send() const override: Метод выведет в консоль информацию и подтвердит, что это не значение invalid_email.
Производный класс SMSNotification. SMSNotification(const std::string& message, const std::string& phoneNumber): Берет номер телефона и проверяет, что он не пустой. void send() const override: После отправки будет проверено, что это не invalid_number значение.

Номер 28.
Базовый класс Shape. virtual BoundingBox getBoundingBox() const: Метод возвращает значение BoundingBox, и он выдаст исключение. virtual ~Shape() {}: Виртуальный деструктор.
Производный класс Circle. Circle(double x, double y, double radius): Конструктор: требуются координаты x, y и радиус. BoundingBox getBoundingBox() const override: Вычислит BoundingBox для круга и вернет значение.
Производный класс Polygon. Polygon(const std::vector<std::pair<double, double>>& vertices): Принимает вектор вершин. Проверяется, является ли многоугольник допустимым. BoundingBox getBoundingBox() const override: Использование вершин для вычисления BoundingBox значения.

Номер 29.
Базовый класс UserProfile. UserProfile(const std::string& username)Конструктор принимает имя пользователя и проверяет, что значение не пустое. virtual void updateProfile(const std::string& newUsername): Может изменить пользовательские значения на новое имя пользователя. virtual ~UserProfile() {}: Виртуальный деструктор. getUsername(): Возвращает имя пользователя объекта.
Производный класс AdminProfile. AdminProfile(const std::string& username, const std::string& role): Выбирает пользователя и роль. void updateProfile(const std::string& newUsername) override: У метода должен быть авторизованный пользователь для совершения действия.
Производный класс GuestProfile. GuestProfile(const std::string& username): Требуется только пользователь. void updateProfile(const std::string& newUsername) override: Выдает ошибку, в которой говорится, что пользователь не может быть обновлен.

Номер 30.
Базовый класс PaymentProcessor. PaymentProcessor(double balance): Конструктор: Баланс не может быть отрицательным, в противном случае он должен выдавать исключение. virtual ~PaymentProcessor() {}: Виртуальный деструктор. getBalance(): Возвращает баланс счета.
Производный класс CreditCardProcessor. CreditCardProcessor(double balance, const std::string& cardNumber, double creditLimit): Все входные данные были проверены, чтобы убедиться в достоверности этого значения. void processPayment(double amount) overrideЗатем с помощью базового метода проверяется, действительна ли кредитная карта.
Производный класс DebitCardProcessor. DebitCardProcessor(double balance, const std::string& accountNumber): Только подтвердите, что номер счета существует. void processPayment(double amount) override: Просто реализуйте базовый процесс.