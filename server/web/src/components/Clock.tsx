import * as React from "react";
import * as Radium from "radium";
import {CSSProperties} from "react";
var dateFormat = require('dateformat');

interface ClockProps {
}

interface ClockState {
  time:Date
}

@Radium
export default class Clock extends React.Component<ClockProps, ClockState> {
  updateTimeInterval;

  styles = {
    container: {
      paddingTop: '30px',
      paddingBottom: '30px'
    } as CSSProperties,

    timeContainer: {
      width: '480px',
      textAlign: 'center'
    } as CSSProperties,

    time: {
      fontSize: '120px',
      textAlign: 'right',
      lineHeight: '120px',
      display: 'inline'
    } as CSSProperties,

    ampm: {
      fontSize: '30px',
      marginRight: '10px',
      display: 'inline',
      position: 'absolute',
      top: '107px'
    } as CSSProperties,

    dateContainer: {
      textAlign: 'center'
    } as CSSProperties,

    date: {}
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
    this.setState({time: new Date()})
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
    return dateFormat(time, 'mmmm dd');
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
