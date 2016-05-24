/// <reference path="../../../alarm-clock-web.d.ts" />
/// <reference path="../services/Wunderground.d.ts" />

import * as React from "react";
import WundergroundBase, {WundergroundBaseProps, WundergroundBaseState} from "./WundergroundBase";
import * as Radium from "radium";

const DEGREES = '\xB0';

interface WundergroundExpandedProps extends WundergroundBaseProps {
}

interface WundergroundExpandedState extends WundergroundBaseState {
}

@Radium
export default class WundergroundExpanded extends WundergroundBase<WundergroundExpandedProps, WundergroundExpandedState> {
  styles = {
    container: {
      marginLeft: 'auto'
    },

    table: {
      width: '100%'
    },

    radarContainer: {
      textAlign: 'center'
    },

    radarImage: {
      width: '300px',
      height: '200px'
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

  state:WundergroundExpandedState = {};

  render() {
    return (
      <div style={this.styles.container}>
        <table style={this.styles.table}>
          <tbody>
          <tr>
            <td style={this.styles.radarContainer} colSpan="4">
              <img style={this.styles.radarImage} src="/wunderground/radar.png"/>
            </td>
          </tr>
          <tr>
            <td style={this.styles.dayContainer}>
              <img style={this.styles.image} src={this.getIcon()} alt={this.getIconAlt()}/>
              <div style={this.styles.temperature}>{this.getTemperature()}</div>
              <div style={this.styles.weekday}>Current</div>
            </td>
            {[0, 1, 2].map((x, i) =>
              <td style={this.styles.dayContainer}>
                <img style={this.styles.image} src={this.getForecastIcon(i)} alt={this.getForecastIconAlt(i)}/>
                <div style={this.styles.temperature}>{this.getForecastTemperature(i)}</div>
                <div style={this.styles.weekday}>{this.getForecastWeekday(i)}</div>
              </td>
            )}
          </tr>
          </tbody>
        </table>
      </div>
    )
  }
}
