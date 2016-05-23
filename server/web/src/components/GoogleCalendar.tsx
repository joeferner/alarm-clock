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
      width: '240px'
    },

    line: {

    },

    day: {
      fontWeight: 'bold',
      borderBottom: '1px solid white'
    },

    time: {
      fontWeight: 'bold',
      marginRight: '5px',
      textAlign: 'right',
      whiteSpace: 'nowrap',
      width: '70px'
    },

    summary: {

    },

    summaryDiv: {
      whiteSpace: 'nowrap',
      textOverflow: 'ellipsis',
      overflow: 'hidden',
      width: '150px'
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

  private static getEventDateTime(item: GoogleCalendarEvent): Date {
    var dateTimeString = item.start.dateTime || item.start.date;
    return this.parseDateString(dateTimeString);
  }

  private static parseDateString(str: string): Date {
    var date;
    var m = str.match(/^([0-9]+)-([0-9]+)-([0-9]+)$/);
    if (m) {
      date = new Date(parseInt(m[1]), parseInt(m[2]) - 1, parseInt(m[3]));
    } else {
      date = new Date(Date.parse(str));
    }
    return date;
  }

  static getEventDateTimeString(item: GoogleCalendarEvent): string {
    var date = GoogleCalendar.getEventDateTime(item);
    if (item.start.dateTime) {
      return dateFormat(date, 'h:mmtt');
    } else {
      return 'All day';
    }
  }

  private groupItemsByDay() {
    var groups = {};
    this.state.items.forEach((item) => {
      var yearMonthDay = dateFormat(GoogleCalendar.getEventDateTime(item), 'yyyy-mm-dd');
      var group = groups[yearMonthDay];
      if (!group) {
        group = [];
        groups[yearMonthDay] = group;
      }
      group.push(item);
    });
    return groups;
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
          <table style={this.styles.list}>
            <tbody>
              {this.renderListItems()}
            </tbody>
          </table>
        </div>
      );
    }
  }

  renderListItems() {
    var groups = this.groupItemsByDay();
    return Object.keys(groups).sort().map((groupName) => {
      return this.renderGroup(groupName, groups[groupName]);
    });
  }

  renderGroup(yearMonthDay, items) {
    var date = GoogleCalendar.parseDateString(yearMonthDay);
    var yearMonthDayString = dateFormat(date, 'dddd mm/dd');

    const header = (
      <tr style={this.styles.line} key={yearMonthDay}>
        <td style={this.styles.day} colSpan="2">{yearMonthDayString}</td>
      </tr>
    );

    return [header, items.map((item: GoogleCalendarEvent) => {
      return (
        <tr style={this.styles.line} key={item.id}>
          <td style={this.styles.time}>{GoogleCalendar.getEventDateTimeString(item)}</td>
          <td style={this.styles.summary}><div style={this.styles.summaryDiv}>{item.summary}</div></td>
        </tr>
      );
    })];
  }
}
