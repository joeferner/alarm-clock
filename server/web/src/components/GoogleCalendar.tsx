/// <reference path="../../../alarm-clock-web.d.ts" />

import * as React from 'react';
import { connect } from 'react-redux';
import State from '../models/State';
import * as Radium from 'radium';

interface GoogleCalendarProps {
}

interface GoogleCalendarState {
}

@Radium
export default class GoogleCalendar extends React.Component<GoogleCalendarProps, GoogleCalendarState> {
  updateEventsInterval;
  
  styles = {
    container: {
      
    }
  }
  
  state = {
    
  }
  
  componentDidMount() {
    this.updateEventsInterval = setInterval(this.updateEvents.bind(this), 10 * 60 * 1000);
  }

  componentWillUnmount() {
    clearInterval(this.updateEventsInterval);
  }
  
  updateEvents() {
    
  }
  
  render() {
    return (
      <div style={this.styles.container}>

      </div>
    )
  }
}
