/// <reference path="../../../alarm-clock-web.d.ts" />

import * as React from "react";
import * as Radium from "radium";
import Clock from "./Clock";
import Wunderground from "./Wunderground";
import Refresh from "./Refresh";
import GoogleCalendar from "./GoogleCalendar";

interface AppProps {
}

interface AppState {
}

@Radium
export default class App extends React.Component<AppProps, AppState> {
  styles = {
    table: {
      border: 0,
      borderCollapse: 'collapse',
      borderStyle: 'none'
    },

    tableCell: {
      border: 0
    },

    primaryWidgetContainer: {
      width: '480px',
      height: '200px'
    },

    secondaryWidgetContainer: {
      width: '240px',
      height: '120px'
    }
  };

  state = {};

  render() {
    return (
      <div>
        <Refresh />
        <table style={this.styles.table}>
          <tbody>
          <tr>
            <td colSpan="2" style={this.styles.tableCell}>
              <div style={this.styles.primaryWidgetContainer}><Clock /></div>
            </td>
          </tr>
          <tr>
            <td style={this.styles.tableCell}>
              <div style={this.styles.secondaryWidgetContainer}><Wunderground /></div>
            </td>
            <td style={this.styles.tableCell}>
              <div style={this.styles.secondaryWidgetContainer}><GoogleCalendar /></div>
            </td>
          </tr>
          </tbody>
        </table>
      </div>
    )
  }
}
