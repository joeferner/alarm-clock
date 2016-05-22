/// <reference path="../../../alarm-clock-web.d.ts" />

import * as React from 'react';
import { connect } from 'react-redux';
import State from '../models/State';
import * as Radium from 'radium';

interface ClockProps {
}

interface ClockState {
  time: Date
}

@Radium
export default class Clock extends React.Component<ClockProps, ClockState> {
  updateTimeInterval;
  
  styles = {
    container: {
      display: 'flex',
      flexDirection: 'row'
    },
    
    time: {
      fontSize: '175px',
      flex: '1 1 auto',
      textAlign: 'right',
      lineHeight: '136px'
    },
    
    ampm: {
      fontSize: '30px',
      flex: 'none',
      marginRight: '10px',
      alignSelf: 'flex-end'
    }
  }
  
  state = {
    time: new Date()
  }
  
  componentDidMount() {
    this.updateTimeInterval = setInterval(this.updateTime.bind(this), 1000);
  }

  componentWillUnmount() {
    clearInterval(this.updateTimeInterval);
  }
  
  updateTime() {
    this.setState({ time: new Date() })
  }
  
  getTimeString() {
    let time = this.state.time;
    var hours = time.getHours();
    hours = hours % 12;
    hours = hours ? hours : 12;
    var hoursString = hours.toString();
    
    var minutes = time.getMinutes();
    var minutesString = '00' + minutes;
    minutesString = minutesString.substr(minutesString.length - 2);
    
    return hoursString + ':' + minutesString; 
  }
  
  getAMPM() {
    let time = this.state.time;
    return time.getHours() >= 12 ? 'PM' : 'AM';
  }
  
  render() {
    return (
      <div style={this.styles.container}>
        <div style={this.styles.time}>{this.getTimeString()}</div>
        <div style={this.styles.ampm}>{this.getAMPM()}</div>
      </div>
    )
  }
}
