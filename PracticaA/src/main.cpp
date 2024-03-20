#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h> 

// Definir el pin del LED
const int ledPin = 15;

// Prototipos de funciones
void tareaEncender(void *parameter);
void tareaApagar(void *parameter);

// Crear un semáforo
SemaphoreHandle_t semaforo;

void setup() {
    Serial.begin(115200);
  // Inicializar el pin del LED como salida
  pinMode(ledPin, OUTPUT);

  // Crear un semáforo
  semaforo = xSemaphoreCreateBinary();
  
  // Crear tareas
  xTaskCreate(tareaEncender, "Encender LED", 1000, NULL, 1, NULL);
  xTaskCreate(tareaApagar, "Apagar LED", 1000, NULL, 1, NULL);
}

void loop() {
  // No hay código en el loop
}

// Tarea para encender el LED
void tareaEncender(void *parameter) {
  for (;;) {
    // Esperar a que el semáforo esté disponible
    xSemaphoreTake(semaforo, portMAX_DELAY);

    // Encender el LED
    digitalWrite(ledPin, HIGH);
    Serial.println("LED Encendido");
    delay(1000);
  }
}

// Tarea para apagar el LED
void tareaApagar(void *parameter) {
  for (;;) {
    // Esperar a que el semáforo esté disponible
    xSemaphoreTake(semaforo, portMAX_DELAY);

    // Apagar el LED
    digitalWrite(ledPin, LOW);
    Serial.println("LED Apagado");
    delay(1000);
  }
}
