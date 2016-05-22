/// <reference path="../../alarm-clock-web.d.ts" />

import * as React from 'react';
import * as ReactDOM from 'react-dom';
import { Provider } from 'react-redux'
import { applyMiddleware, createStore } from 'redux'
import thunk from 'redux-thunk';
import * as createLogger from 'redux-logger';
import reducers from './reducers'
import Clock from './components/Clock';
import Wunderground from './components/Wunderground';
import Refresh from './components/Refresh';
import GoogleCalendar from './components/GoogleCalendar';

const logger = createLogger();
const storeMiddleware = applyMiddleware(thunk, logger);
const store = createStore(reducers, storeMiddleware);

ReactDOM.render(
  <Provider store={store}>
    <div>
      <Refresh />
      <Clock />
      <div>
        <Wunderground />
        <GoogleCalendar />
      </div>
    </div>
  </Provider>,
  document.getElementById('root')
);
