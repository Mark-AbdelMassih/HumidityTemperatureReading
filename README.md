"# HumidityTemperatureReading" 

# DHT11 Temperature and Humidity Sensor Project

This project interfaces a DHT11 temperature and humidity sensor with a PIC18F45K22 microcontroller. The sensor readings are processed and displayed on an LCD.

## Components Used

- **Microcontroller**: PIC18F45K22
- **Sensor**: DHT11 Temperature and Humidity Sensor
- **Display**: LCD (4-bit mode)
- **Development Environment**: MPLAB X IDE

## Features

- Reads temperature and humidity data from the DHT11 sensor.
- Displays temperature and humidity values on an LCD.
- Error handling for checksum and invalid responses.

## How It Works

1. **Setup**: Initializes the microcontroller and the LCD.
2. **Data Acquisition**:
   - Sends a request to the DHT11 sensor.
   - Reads the response, which includes humidity and temperature values.
   - Checks the validity of the response using a checksum.
3. **Display**: Outputs the temperature and humidity data on the LCD.

## Code Explanation

### Key Functions

- `Setup()`: Initializes the pins and the LCD.
- `StartDHT11()`: Sends a start signal to the DHT11 sensor.
- `CheckDHT11Response()`: Validates the sensor's response.
- `ReadDHT11()`: Reads data from the sensor.

### Example Code Snippet

```
void StartDHT11(void) {
    dataDirection = 0; // Set pin as output to send bit '0'
    outputData = 0;    // Send bit 0 
    Delay1KTCYx(18);   // Delay for 18 ms
    outputData = 1;    // Pull back data bus to high 
    Delay10TCYx(4);    // Delay for 40 µs
    dataDirection = 1; // Set pin as input to read response from sensor
}
```

## Usage

1. **Wiring**: Connect the DHT11 sensor to the appropriate pins on the PIC18F45K22.
2. **Compile**: Use MPLAB X IDE to compile the project.
3. **Upload**: Program the PIC microcontroller with the compiled code.
4. **Run**: Power the circuit and observe the temperature and humidity readings on the LCD.

## Troubleshooting

- **Check Wiring**: Ensure the DHT11 and LCD are correctly wired to the microcontroller.
- **Power Supply**: Confirm that the power supply to the microcontroller is stable.
- **LCD Initialization**: Ensure the LCD is properly initialized before displaying data.

## Conclusion

This project effectively demonstrates how to interface a DHT11 sensor with a PIC microcontroller and display readings on an LCD, providing a hands-on experience with embedded systems and sensor integration.


