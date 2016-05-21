/// <reference path="../../../alarm-clock-web.d.ts" />
import State from '../models/State';
import * as actions from '../actions';

function getInitialState(): State {
  return new State();
}

export default function reducer(state: State, action: actions.Action): State {
  if (typeof state === 'undefined') {
    return getInitialState();
  }
  
  return state;
}
