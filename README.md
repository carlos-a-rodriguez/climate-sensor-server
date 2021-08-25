# climate-sensor-server
DHT22 Sensor Exposed on Arduino Server

## requirements

### hardware

- Arduino Uno (or equivalent)
- DHT22 Sensor
- Ethernet Shield

### 3rd party libraries

- [ArduinoJson](https://arduinojson.org/?utm_source=meta&utm_medium=library.properties)
- [DHT senor library](https://github.com/adafruit/DHT-sensor-library)


## example

### request

Assuming the Arduino was assigned `192.168.1.100` on the local network:

```shell
curl -X GET 192.168.1.100
```

### response

`200 OK`

```json
{"temperature":29.7,"humidity":65.9}
```