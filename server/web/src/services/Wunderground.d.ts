interface WundergroundConditions {
  current_observation:{
    weather:string,
    temp_f:number,
    icon:string,
    icon_url:string
  }
}

interface WundergroundForecastSimpleForecastForecastDay {
  date:{
    year:number,
    month:number,
    day:number,
    weekday_short:string
  },
  period:number,
  high:{
    fahrenheit:string,
    celsius:string
  },
  low:{
    fahrenheit:string,
    celsius:string
  },
  conditions:string,
  icon:string,
  icon_url:string
}

interface WundergroundForecast {
  forecast:{
    simpleforecast:{
      forecastday:WundergroundForecastSimpleForecastForecastDay[]
    }
  }
}
