// Подключаем библиотеку для работы с маховиком
#include <IS_Drive_Two_Ch.h>
#include <IS_Bluetooth.h>

// Задаем I2C-адрес двигателя
#define IS_Drive_1 0x33


// Задаем объект класса Drive
Drive drive;

// Задаем переменную угловой скорости
uint16_t MotSpeed = 0;

void setup() {
  //Init();
  // Инициализируем работу I2C
  Wire.begin();
  
  // Инициализируем работу UART
  Serial.begin(115200, SERIAL_8E1);
}

void loop() {
  if (Serial.available()) {
    char msg = Serial.read();
    if (msg == 'b') {
      enter_bootloader();
    }
  }
  
  // Постепенно наращиваем скорость вращения против часовой стрелки
  while (MotSpeed < 3000)
  {
    // Увеличиваем скорость на 50 об/мин на каждой итерации цикла while
    MotSpeed += 50;

    // Функция, задающая направление и скорость вращения
    drive.speed_control(IS_Drive_1, 0, MotSpeed, 0);
    // Выводим текущую скорость в UART
    Serial.println(MotSpeed);
    // Задержка между итерациями для плавного увеличения угловой скорости
    delay(200);
  }


  // Обнуляем переменную MotSpeed
  MotSpeed = 0;
  // Останавливаем маховик
  drive.speed_control(IS_Drive_1, 0, MotSpeed, 0);
  // Даем маховику немного времени на остановку
  delay(4000);

  // Постепенно наращиваем скорость вращения по часовой стрелке
  while (MotSpeed < 3000)
  {
    // Увеличиваем скорость на 50 об/мин на каждой итерации цикла while
    MotSpeed += 50;

    // Функция, задающая направление и скорость вращения
    drive.speed_control(IS_Drive_1, 1, MotSpeed, 0);
    // Выводим текущую скорость в UART
    Serial.println(MotSpeed);
    // Задержка между итерациями для плавного уменьшения угловой скорости
    delay(200);
  }

  // Обнуляем переменную MotSpeed
  MotSpeed = 0;
  // Останавливаем маховик
  drive.speed_control(IS_Drive_1, 1, MotSpeed, 0);
  // Даем маховику немного времени на остановку
  delay(4000);
}
