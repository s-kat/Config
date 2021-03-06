# Config
Имеется файл конфигурации для программы в формате JSON.
Реализацию класса Config - это хранилищи конфигурации с удобным интерфейсом доступа к любому параметру.
Параметры могут иметь тип string, int, float, bool.

Структура файла конфигурации следующая:
{"param1":"str","param2":111,"param2":true, ... }
## Сборка и запуск
```
git clone https://github.com/s-kat/Config.git
cd Config
git submodule init
git submodule update
cmake CMakeLists.txt
make
./Config
```
## Структура класса
1. Конструктор ```Config(std::string & path_to_parse)``` принимает на вход путь к JSON файлу, который содержит конфигурацию, и сохраняет JSON во внутреннем представлении
2. Метод ```void ViewJSON()``` выводит JSON на стандартный поток вывода.
3. Метод ```bool ExistCheck(std::string key)``` возвращает ```true```, если параметр содержится в JSON файле, иначе ```false```. 
4. Метод ```std::string ValueType(std::string key)``` возвращает тип значения (```string, int, float, bool```, ), содержащегося по ключу или ```NULL```, если ключ отсутствует.
5. Метод ```std::optional<int> GetInt (std::string key)``` пытается получить значение типа ```int``` содержащееся по ключу ```key```. Результат представлен типом ```std::optional<int>```. Методы ```GetString, GetDouble, GetBool``` работают аналогичным способом.
5. Методы ```int AddStr(const std::string parameter, std::string element )``` и ```int AddValue(const std::string parameter, T element )```. Добавляют новые параметры в JSON. В случае успеха возвращают значение 1. В случае неудачи(параметр уже сущетсвует) возвращают значение -1.
6. Метод ```void SaveJson(std::string path_to_save_file = "")``` сохраняет конфигурацию по указанному пути в формате JSON. Если же путь не указан, перезаписывается исходный JSON файл.
7. Метод ```int RemoveValue(std::string key)``` удаляет параметр с именем ```key```. В случае успеха возвращает 1, если же параметра с таким именем не существует возвращает 0.
8. Методы ```int UpdateString(std::string key, std::string value)``` и ```int Update(std::string key, T value)``` обновляют значения по заданным параметрам. В случае успеха возвращают 1, в случае если параметра не существует возвращают 0.
## Логирование
Все взаимодействия с конфигурацией отображаются в лог-файле ```logs/logs/txt```.
