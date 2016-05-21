/// <reference path="../../alarm-clock-web.d.ts" />

import * as React from 'react';
import * as ReactDOM from 'react-dom';
import { Provider } from 'react-redux'
import { applyMiddleware, createStore } from 'redux'
import thunk from 'redux-thunk';
import * as createLogger from 'redux-logger';
import reducers from './reducers'
import Clock from './components/Clock';

const logger = createLogger();
const storeMiddleware = applyMiddleware(thunk, logger);
const store = createStore(reducers, storeMiddleware);

ReactDOM.render(
  <Provider store={store}>
    <Clock />
  </Provider>,
  document.getElementById('root')
);
