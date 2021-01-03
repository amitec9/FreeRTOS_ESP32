
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
const int led = 2;
void Task1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize digital pin 2 as an output.
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  for (;;) // A Task shall never return or exit.
  {
    Serial.println("Hi form task 1- Im blinking LED on pin 2");
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void Task2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  for (;;)
  {
    Serial.println("Hi from Task 2");
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}

TaskHandle_t task1handle;
TaskHandle_t task2handle;

// the setup function runs once when you press reset or power the board
void setup() {

  // Now set up two tasks to run independently.
  xTaskCreate(
    Task1
    ,  "Blink"   // A name just for humans
    ,  1000  // Stack size
    ,  NULL //the parameters to be passed's pointer
    ,  2  // priority
    ,  &task1handle );//this is task Handler

  xTaskCreate(
    Task2
    ,   "AnalogRead"
    ,  1000 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL //the parameters to be passed's pointer
    ,  1  // priority
    ,  &task2handle );//this is task Handler

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks., This portion is just to stay in phase with Arduinos Programming structure 
}
