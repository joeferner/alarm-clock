/// <reference path="../../alarm-clock-web.d.ts" />

import * as React from "react";
import * as ReactDOM from "react-dom";
import {Provider} from "react-redux";
import {applyMiddleware, createStore} from "redux";
import thunk from "redux-thunk";
import * as createLogger from "redux-logger";
import reducers from "./reducers";
import Clock from "./components/Clock";
import Wunderground from "./components/Wunderground";
import Refresh from "./components/Refresh";
import GoogleCalendar from "./components/GoogleCalendar";

const logger = createLogger();
const storeMiddleware = applyMiddleware(thunk, logger);
const store = createStore(reducers, storeMiddleware);

const styles = {
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

ReactDOM.render(
  <Provider store={store}>
    <div>
      <Refresh />
      <table style={styles.table}>
        <tbody>
        <tr>
          <td colSpan="2" style={styles.tableCell}>
            <div style={styles.primaryWidgetContainer}><Clock /></div>
          </td>
        </tr>
        <tr>
          <td style={styles.tableCell}>
            <div style={styles.secondaryWidgetContainer}><Wunderground /></div>
          </td>
          <td style={styles.tableCell}>
            <div style={styles.secondaryWidgetContainer}><GoogleCalendar /></div>
          </td>
        </tr>
        </tbody>
      </table>
    </div>
  </Provider>,
  document.getElementById('root')
);
