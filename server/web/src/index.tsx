import * as React from "react";
import * as ReactDOM from "react-dom";
import {Provider} from "react-redux";
import {applyMiddleware, createStore} from "redux";
import thunk from "redux-thunk";
import {createLogger} from "redux-logger";
import reducers from "./reducers";
import App from "./components/App";

const logger = createLogger();
const storeMiddleware = applyMiddleware(thunk, logger);
const store = createStore(reducers, storeMiddleware);

ReactDOM.render(
    <Provider store={store}>
        <App/>
    </Provider>,
    document.getElementById('root')
);
