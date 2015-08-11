var tessel = require('tessel')

var gpio = tessel.port['GPIO']
var sensor = gpio.analog[0]

var numberOfReadings = 250
var readings = []
var atReading = 0
var totalReading = 0

var analogReading
var readingInGrams

var autoZeroReading = 0
var numberOfReadingsAtZero = 0
var autoZeroAt = 10
var zeroed = 0

var analogToGrams = 0.945

for (var i = 0; i < readings.length; i++) {
  readings[i] = 0
}

function between(x, min, max) {
  return x >= min && x <= max
}

setInterval(function() {

  totalReading -= readings[atReading]
  readings[atReading] = sensor.read()
  totalReading += readings[atReading]
  atReading++

  if (atReading >= numberOfReadings) {
    atReading = 0
  }

  analogReading = Math.round((totalReading / numberOfReadings) * 1000)

}, 2000 / numberOfReadings)

setInterval(function() {

  if (between(analogReading, autoZeroReading-1, autoZeroReading+1)) {
    numberOfReadingsAtZero++
  } else {
    autoZeroReading = analogReading
    numberOfReadingsAtZero = 0
  }
  if (numberOfReadingsAtZero == autoZeroAt) {
    zeroed = autoZeroReading
  }

  readingInGrams = ((analogReading - zeroed) * analogToGrams)
  console.log(readingInGrams +"g")

}, 500)

0.23
0.236
0.242