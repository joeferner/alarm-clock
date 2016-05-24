/// <reference path="../../../alarm-clock-web.d.ts" />

import * as React from "react";
import * as Radium from "radium";
import Clock from "./Clock";
import Wunderground from "./Wunderground";
import WundergroundExpanded from "./WundergroundExpanded";
import Refresh from "./Refresh";
import Back from "./Back";
import GoogleCalendar from "./GoogleCalendar";
import WundergroundService from "../services/WundergroundService";

interface AppProps {
}

interface AppState {
  hash:string
}

@Radium
export default class App extends React.Component<AppProps, AppState> {
  private hashChangeListener;
  private wundergroundService;

  styles = {
    table: {
      borderLeft: '0px',
      borderRight: '0px',
      borderTop: '0px',
      borderBottom: '0px',
      borderCollapse: 'collapse',
      borderStyle: 'none'
    },

    tableCell: {
      border: '0px'
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

  state = {
    hash: window.location.hash
  };

  constructor(props) {
    super(props);
    this.hashChangeListener = this.onHashChange.bind(this);
    this.wundergroundService = new WundergroundService();
  }

  componentDidMount() {
    window.addEventListener('hashchange', this.hashChangeListener);
  }

  componentWillUnmount() {
    window.removeEventListener('hashchange', this.hashChangeListener)
  }

  onHashChange() {
    this.setState({hash: window.location.hash});
  }

  render() {
    return (
      <div>
        <Refresh />
        {(window.location.hash) ? <Back/> : null}
        {this.renderContents()}
      </div>
    )
  }

  private renderContents() {
    if (this.state.hash) {
      if (this.state.hash == '#wunderground') {
        return (
          <WundergroundExpanded wundergroundService={this.wundergroundService}/>
        );
      }

      return (
        <div>Unhandled Hash: {this.state.hash}</div>
      );
    }

    return (
      <table style={this.styles.table}>
        <tbody>
        <tr>
          <td colSpan="2" style={this.styles.tableCell}>
            <div style={this.styles.primaryWidgetContainer}><Clock /></div>
          </td>
        </tr>
        <tr>
          <td style={this.styles.tableCell}>
            <div style={this.styles.secondaryWidgetContainer}><Wunderground wundergroundService={this.wundergroundService}/></div>
          </td>
          <td style={this.styles.tableCell}>
            <div style={this.styles.secondaryWidgetContainer}><GoogleCalendar /></div>
          </td>
        </tr>
        </tbody>
      </table>
    );
  }
}
