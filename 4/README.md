Номер 31.
Базовый класс Shape. Shape(double x, double y): Требуются координаты x и y для создания объекта. virtual void reflect(char axis): Метод reflect теперь выдает исключение, если было передано недопустимое значение. virtual ~Shape() {}: Виртуальный деструктор. getX() и getY() возвращает координаты объекта.
Производный класс Circle. Circle(double x, double y, double radius): Чтобы создать объект, методу требуется радиус для создания объекта. void reflect(char axis) override: Выводит информацию после вызова метода super reflect. 
Производный класс Rectangle. Rectangle(double x, double y, double width, double height): Конструктору требуются ширина и высота. void reflect(char axis) override: Выводит информацию после вызова метода super reflect. 

Номер 32.
Базовый класс FileReader. FileReader(const std::string& filePath): Принимает path и проверяет. virtual std::string read() const: Метод read по умолчанию генерирует исключения. virtual ~FileReader() {}: Виртуальный деструктор. getFilePath(): Возвращает путь к файлу объекта.
Производный класс TextFileReader. TextFileReader(const std::string& filePath): Получает путь к файлу. std::string read() const override: Переопределяет метод для реализации стратегии чтения текста.
Производный класс BinaryFileReader. BinaryFileReader(const std::string& filePath): Получает путь к файлу. std::string read() const override: Переопределяет метод для реализации стратегии бинарного чтения.

Номер 33.
Базовый класс Shape. virtual double getArea() const: getArea способ. virtual ~Shape() {}: Виртуальный деструктор.
Производный класс Ellipse. Ellipse(double semiMajorAxis, double semiMinorAxis): Конструктор проверяет, что оба значения являются допустимыми. double getArea() const override: Переопределяет метод и возвращает область эллипса.
Производный класс Square. Square(double side): Конструктор, который проверяет сторону. double getArea() const override: Вычислить площадь.

Номер 34.
Базовый класс EmailService. virtual void sendEmail(const std::string& recipient, const std::string& subject, const std::string& body) const: По умолчанию будет сгенерировано исключение, и оно будет const-ным, так как не изменяет состояние. virtual ~EmailService() {}: Виртуальный деструктор.
Производный класс SMTPService. SMTPService(const std::string& smtpServer, int port, const std::string& senderEmail, const std::string& password): Все данные требуют проверки, как, например, номер порта. void sendEmail(const std::string& recipient, const std::string& subject, const std::string& body) const override: Проверит данные перед отправкой сообщения.
Производный класс APIService. APIService(const std::string& apiEndpoint, const std::string& apiKey): Необходимо получить действительные учетные данные. void sendEmail(const std::string& recipient, const std::string& subject, const std::string& body) const override: Проверит наличие неверных данных.

Номер 35.
Базовый класс Game. Game(const std::string& name): Конструктор: Берет название игры. virtual void endGame(): Может завершить игру, только когда активен. virtual ~Game() {}: Виртуальный деструктор. isActive(): Возвращает значение true / false, активна игра или нет. getGameName(): Возвращает название игры.
Производный класс ChessGame. ChessGame(const std::string& name): Выбирает пользователя и роль. void endGame() override: Подтверждает, что игра активна перед окончанием.
Производный класс FootballGame. FootballGame(const std::string& name): Принимает имя. void endGame() override: Подтверждает, что игра активна перед окончанием.

Номер 36.
PointStruct: Использование struct для значения координаты. Базовый класс Shape. virtual std::vector<Point> getVertices() const: Метод по умолчанию выдаст ошибку. virtual ~Shape() {}: Виртуальный деструктор.
Производный класс Triangle. Triangle(Point a, Point b, Point c): Должны иметь вершины. Треугольник не может находиться на одной линии. std::vector<Point> getVertices() const override: Возвращает вектор точек.
Производный класс Pentagon. Pentagon(const std::vector<Point>& vertices): Имеет 5 вершин. std::vector<Point> getVertices() const override: Возвращает вершины.

Номер 37.
Базовый класс Session. Session(const std::string& sessionId): Конструктор принимает идентификатор сеанса и проверяет его. virtual void startSession(): Реализация сеанса запускается и будет генерировать исключения. virtual ~Session() {}: Виртуальный деструктор. isActive(): Возвращает состояние текущего сеанса. getSessionId(): Возвращает идентификатор сеанса.
Производный класс UserSession. UserSession(const std::string& sessionId, const std::string& userId): Требуется действительный идентификатор пользователя. void startSession() override: Метод имеет реализацию для проверки, есть ли у него разрешения на запуск.
Производный класс AdminSession. AdminSession(const std::string& sessionId, const std::string& adminId, const std::string& role): У администратора есть adminId, который должен быть подтвержден. void startSession() override: Метод имеет реализацию для проверки, есть ли у него разрешения на запуск.

Номер 38.
Базовый класс Shape. Shape(const std::string& color): Конструктор для проверки данных. virtual std::string getColor() const: Метод вернет color и выдаст исключение, если значение color пустое. virtual ~Shape() {}: Виртуальный деструктор.
Производный класс Circle. Circle(const std::string& color): Получить цвет для создания объекта. std::string getColor() const override: вернуть форматированный цвет.
Производный класс Square. Square(const std::string& color): Получить цвет для создания объекта. std::string getColor() const override: вернуть форматированный цвет.

Номер 39.
Базовый класс Logger. virtual void log(const std::string& message) const: Базовый метод. virtual ~Logger() {}: Виртуальный деструктор.
Производный класс ConsoleLogger. ConsoleLogger(): Конструктор по умолчанию. void log(const std::string& message) const override: Выводит сообщение на консоль.

Номер 40.
Базовый класс DataProcessor. virtual std::string processData(const std::string& data) const: Универсальный метод для обработки данных, и по умолчанию он выдает исключение. virtual ~DataProcessor() {}: Виртуальный деструктор.
Производный класс CSVProcessor. CSVProcessor(char delimiter = ','): Создает объект. std::string processData(const std::string& data) const override: Имеет реализацию CSV, за исключением.
Производный класс JSONProcessor. JSONProcessor(): Объект-конструктор. std::string processData(const std::string& data) const override: реализует Json проверку первого и последнего символов строки.