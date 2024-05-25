#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h> 

const int ledPin = 15;

void tareaEncender(void *parameter);
void tareaApagar(void *parameter);

SemaphoreHandle_t semaforo;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  semaforo = xSemaphoreCreateBinary();
  
  xTaskCreate(tareaEncender, "Encender LED", 1000, NULL, 1, NULL);
  xTaskCreate(tareaApagar, "Apagar LED", 1000, NULL, 1, NULL);
}

void loop() {
  // No hay código en el loop
}

void tareaEncender(void *parameter) {
  for (;;) {
    xSemaphoreTake(semaforo, portMAX_DELAY);

    digitalWrite(ledPin, HIGH);
    Serial.println("LED Encendido");
    vTaskDelay(pdMS_TO_TICKS(1000)); // Paramos la tarea durante un segundo
  }
}

void tareaApagar(void *parameter) {
  for (;;) {
    xSemaphoreTake(semaforo, portMAX_DELAY);

    digitalWrite(ledPin, LOW);
    Serial.println("LED Apagado");
    vTaskDelay(pdMS_TO_TICKS(1000)); // Paramos la tarea durante un segundo
  }
}




