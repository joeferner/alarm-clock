/// <reference path="../../../alarm-clock-web.d.ts" />
/// <reference path="../../../src/routes/googleCalendar.d.ts" />

import * as React from 'react';
import * as Radium from 'radium';
import axios = require('axios');
var dateFormat = require('dateformat');

interface GoogleCalendarProps {
}

interface GoogleCalendarState {
  items?: GoogleCalendarEvent[];
  unauthorized?: boolean;
}

@Radium
export default class GoogleCalendar extends React.Component<GoogleCalendarProps, GoogleCalendarState> {
  updateEventsInterval;
  
  styles = {
    authorizeContainer: {
      width: '240px',
      height: '100px',
      textAlign: 'center',
      paddingTop: '35px'
    },

    authorizeLink: {
      color: 'white'
    },

    container: {
      width: '240px',
      height: '100px',
      overflowY: 'scroll',
      overflowX: 'hidden'
    },

    list: {
      listStyleType: 'none',
      paddingLeft: '0px',
      marginTop: '0px'
    },

    line: {
      whiteSpace: 'nowrap',
      textOverflow: 'ellipsis'
    },

    dateTime: {
      fontWeight: 'bold',
      marginRight: '5px',
      display: 'inline-block',
      width: '100px',
      textAlign: 'right'
    },

    summary: {

    }
  };
  
  state = {
    items: [],
    unauthorized: false
  };
  
  componentDidMount() {
    this.updateEventsInterval = setInterval(this.updateEvents.bind(this), 10 * 60 * 1000);
    this.updateEvents();
  }

  componentWillUnmount() {
    clearInterval(this.updateEventsInterval);
  }
  
  updateEvents() {
    axios.get('/googleCalendar/events')
      .then((body) => {
        var res: GoogleCalendarEventsResponse = body.data as GoogleCalendarEventsResponse;
        this.setState({
          items: res.items,
          unauthorized: false
        });
      })
      .catch((err) => {
        console.error('Could not get events', err);
        this.setState({items: []});
        if (err.status == 401) {
          this.setState({unauthorized: true});
        }
      });
  }

  static getEventDateTime(item: GoogleCalendarEvent): Date {
    var dateTimeString = item.start.dateTime || item.start.date;
    return new Date(Date.parse(dateTimeString) + 1);
  }

  static getEventDateTimeString(item: GoogleCalendarEvent): string {
    var date = GoogleCalendar.getEventDateTime(item);
    if (item.start.dateTime) {
      return dateFormat(date, "ddd h:mmtt");
    } else {
      return dateFormat(date, "ddd");
    }
  }
  
  render() {
    if (this.state.unauthorized) {
      return (
        <div style={this.styles.authorizeContainer}>
          <a style={this.styles.authorizeLink} href="/googleCalendar/auth">Authorize Calendar</a>
        </div>
      );
    } else {
      return (
        <div style={this.styles.container}>
          <ol style={this.styles.list}>
            {this.renderListItems()}
          </ol>
        </div>
      );
    }
  }

  renderListItems() {
    return this.state.items.map((item: GoogleCalendarEvent) => {
      return (
        <li style={this.styles.line} key={item.id}>
          <span style={this.styles.dateTime}>{GoogleCalendar.getEventDateTimeString(item)}</span>
          <span style={this.styles.summary}>{item.summary}</span>
        </li>
      );
    });
  }
}
