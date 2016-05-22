/// <reference path="../../../alarm-clock-web.d.ts" />

import * as React from 'react';
import * as Radium from 'radium';
var dateFormat = require('dateformat');

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
      width: '480px',
      alignItems: 'baseline'
    },

    timeContainer: {
      width: '480px',
      textAlign: 'right'
    },
    
    time: {
      fontSize: '140px',
      textAlign: 'right',
      lineHeight: '120px',
      display: 'inline'
    },
    
    ampm: {
      fontSize: '30px',
      marginRight: '10px',
      display: 'inline'
    },

    dateContainer: {
      textAlign: 'center'
    },

    date: {

    }
  };
  
  state = {
    time: new Date()
  };
  
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
    const time = this.state.time;
    return dateFormat(time, 'h:MM');
  }
  
  getAMPM() {
    const time = this.state.time;
    return dateFormat(time, 'tt');
  }

  getDate() {
    const time = this.state.time;
    return dateFormat(time, 'mmmm, dd');
  }
  
  render() {
    return (
      <div style={this.styles.container}>
        <div style={this.styles.timeContainer}>
          <div style={this.styles.time}>{this.getTimeString()}</div>
          <div style={this.styles.ampm}>{this.getAMPM()}</div>
        </div>
        <div style={this.styles.dateContainer}>
          <div style={this.styles.date}>{this.getDate()}</div>
        </div>
      </div>
    )
  }
}
