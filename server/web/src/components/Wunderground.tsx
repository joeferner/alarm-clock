/// <reference path="../../../alarm-clock-web.d.ts" />

import * as React from "react";
import * as Radium from "radium";
import axios = require('axios');

const DEGREES = '\xB0';

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

interface WundergroundProps {
}

interface WundergroundState {
  conditions?:WundergroundConditions,
  forecast?:WundergroundForecast
}

@Radium
export default class Wunderground extends React.Component<WundergroundProps, WundergroundState> {
  updateConditionsInterval;
  updateForecastInterval;

  styles = {
    container: {
      marginLeft: 'auto'
    },

    table: {
      width: '100%'
    },

    dayContainer: {
      margin: '5px',
      textAlign: 'center'
    },

    image: {
      width: '50px',
      height: '50px'
    },

    temperature: {
      textAlign: 'center'
    },

    weekday: {
      textAlign: 'center'
    }
  };

  state:WundergroundState = {};

  componentDidMount() {
    this.updateConditionsInterval = setInterval(this.updateConditions.bind(this), 60 * 1000);
    this.updateConditions();

    this.updateForecastInterval = setInterval(this.updateForecast.bind(this), 60 * 1000);
    this.updateForecast();
  }

  componentWillUnmount() {
    clearInterval(this.updateConditionsInterval);
    clearInterval(this.updateForecastInterval);
  }

  updateConditions() {
    axios.get('/wunderground/conditions')
      .then((body) => {
        try {
          var conditions:WundergroundConditions = body.data as WundergroundConditions;
          this.setState({conditions: conditions});
        } catch (e) {
          console.error('Could not parse conditions: ', body, e);
          this.setState({conditions: null});
        }
      })
      .catch((err) => {
        console.error('Could not get conditions', err);
        this.setState({conditions: null});
      });
  }

  updateForecast() {
    axios.get('/wunderground/forecast')
      .then((body) => {
        try {
          var forecast:WundergroundForecast = body.data as WundergroundForecast;
          this.setState({forecast: forecast});
        } catch (e) {
          console.error('Could not parse forecast: ', body, e);
          this.setState({forecast: null});
        }
      })
      .catch((err) => {
        console.error('Could not get forecast', err);
        this.setState({forecast: null});
      });
  }

  getTemperature():string {
    if (!this.state.conditions) {
      return 'NA';
    }
    return this.state.conditions.current_observation.temp_f + DEGREES + ' F';
  }

  getIcon():string {
    if (!this.state.conditions) {
      return '/wunderground/na.gif';
    }
    return '/wunderground/' + this.state.conditions.current_observation.icon + '.gif';
  }

  getIconAlt():string {
    if (!this.state.conditions) {
      return 'NA';
    }
    return this.state.conditions.current_observation.weather;
  }

  getForecastTemperature(idx:number):string {
    if (!this.state.forecast) {
      return 'NA';
    }
    var day = this.state.forecast.forecast.simpleforecast.forecastday[idx];
    if (!day) {
      return 'NA';
    }
    return day.low.fahrenheit + DEGREES + '/' + day.high.fahrenheit + DEGREES;
  }

  private getForecastDay(idx:number) {
    if (!this.state.forecast) {
      return null;
    }
    if (new Date().getHours() > 20) {
      idx++;
    }
    return this.state.forecast.forecast.simpleforecast.forecastday[idx];
  }

  getForecastIcon(idx:number):string {
    var day = this.getForecastDay(idx);
    if (!day) {
      return '/wunderground/na.gif';
    }
    return '/wunderground/' + day.icon + '.gif';
  }

  getForecastIconAlt(idx:number):string {
    var day = this.getForecastDay(idx);
    if (!day) {
      return 'NA';
    }
    return day.conditions;
  }

  getForecastWeekday(idx:number):string {
    var day = this.getForecastDay(idx);
    if (!day) {
      return 'NA';
    }
    return day.date.weekday_short;
  }

  render() {
    return (
      <div style={this.styles.container}>
        <table style={this.styles.table}>
          <tbody>
          <tr>
            <td style={this.styles.dayContainer}>
              <img style={this.styles.image} src={this.getIcon()} alt={this.getIconAlt()}/>
              <div style={this.styles.temperature}>{this.getTemperature()}</div>
              <div style={this.styles.weekday}>Current</div>
            </td>
            <td style={this.styles.dayContainer}>
              <img style={this.styles.image} src={this.getForecastIcon(0)} alt={this.getForecastIconAlt(0)}/>
              <div style={this.styles.temperature}>{this.getForecastTemperature(0)}</div>
              <div style={this.styles.weekday}>{this.getForecastWeekday(0)}</div>
            </td>
            <td style={this.styles.dayContainer}>
              <img style={this.styles.image} src={this.getForecastIcon(1)} alt={this.getForecastIconAlt(1)}/>
              <div style={this.styles.temperature}>{this.getForecastTemperature(1)}</div>
              <div style={this.styles.weekday}>{this.getForecastWeekday(1)}</div>
            </td>
          </tr>
          </tbody>
        </table>
      </div>
    )
  }
}
